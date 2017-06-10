/*
 * Main C++ Application
 */

/* FreeRTOS includes. */
#include "platform.h"

/* Module includes */
#include "hexapod.h"

static HEXAPOD Hexapod;

static volatile float stepTime = INITIAL_STEP_TIME;
static volatile float stepUpZ = INITIAL_STEP_UP_Z;

static int U = 1;
static const int V = 300;
static const int IU = 400;

static QueueHandle_t xPostureQueue[6];
static TaskHandle_t xInitTask;
static TaskHandle_t xWalkingTask;
static TaskHandle_t xLegGait[6];
static TaskHandle_t xIMUTask;

static TaskHandle_t xRemoteNetworkTask;

static volatile Posture xPosture[6];

// FS Function
static const TCHAR *FSPath = "0:/";
static FIL fil;		/* File object */
static FATFS fatfs;
static char fileNameLst[512];
static uint fileCount = 0;

static int sdMount();
static void sdGetFileList();
static int sdGetFilename(TCHAR *fName, uint num);
static int sdReadPosture(TCHAR *fName);

extern "C" void lwip_init();
static void init( void * );

/* Task function */
#include "taskFunctions.h"

static volatile bool MpuIntrFlag;     // indicates whether MPU interrupt pin has gone high

static void dmpDataReady(XGpioPs* cbRef, u32 bank, u32 status) {
	MpuIntrFlag = true;
	if(xIMUTask != NULL)
		vTaskNotifyGiveFromISR(xIMUTask, NULL);
}

int main (void) {
	BaseType_t status;
//-------------------------------
	for(int i = 0; i < 6; i++){
		xPostureQueue[i] = xQueueCreate( 10, sizeof( int ));
	}

	status = xTaskCreate( init, 			/* The function that implements the task. */
				( const char * ) "init", 	/* Text name for the task, provided to assist debugging only. */
				configMINIMAL_STACK_SIZE, 	/* The stack allocated to the task. */
				NULL, 						/* The task parameter is not used, so set to NULL. */
				DEFAULT_THREAD_PRIO,			/* The task runs at the idle priority. */
				&xInitTask );

	if(status != pdPASS){
		xil_printf("Can not create init task.");
		return XST_FAILURE;
	}

	vTaskStartScheduler();

	return XST_SUCCESS;
}

static void init( void *pvParameters ) {
	BaseType_t status;

	xil_printf("Initial\r\n");

	sdMount();	// Mount File System
	sdGetFileList(); // Update File List
	TCHAR fn[50];
	sdGetFilename(fn, 1);
	sdReadPosture(fn);

	Hexapod.begin( (void *) dmpDataReady, &MpuIntrFlag);

	xil_printf("Initial Network\r\n");
	/* initialize lwIP before calling sys_thread_new */
	lwip_init();

	/* any thread using lwIP should be created using sys_thread_new */
	sys_thread_new("NW_THRD", network_thread, NULL,
			THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

	TickType_t st = pdMS_TO_TICKS( 3000 );
	vTaskDelay( st );
	xil_printf("Initialed Network\r\n");

	status = xTaskCreate( hexapodIMUTask,
				 ( const char * ) "IMU",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 DEFAULT_THREAD_PRIO,
				 &xIMUTask );

	if(status != pdPASS){
		xil_printf("Can not create IMU task.\r\n");
	}
	else{
		xil_printf("Start IMU task.\r\n");
	}

	status = xTaskCreate( hexapodWalkingTask,
				 ( const char * ) "Walking",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 DEFAULT_THREAD_PRIO + 2,
				 &xWalkingTask );

	if(status != pdPASS){
		xil_printf("Can not create Walking task.\r\n");
	}
	else{
		xil_printf("Start Walking task.\r\n");
	}


	xil_printf("Initialed\r\n");
	vTaskDelete(NULL);
}

static int sdMount(){
	FRESULT Res;
	Res = f_mount(&fatfs, FSPath, 0);
	if (Res == FR_OK) {
		return XST_SUCCESS;
	}
	return XST_FAILURE;
}

static void sdGetFileList(){
	FRESULT Res;
	DIR dir;
	FILINFO fno;

	uint idx = 0;

	Res = f_opendir(&dir, FSPath);
	if (Res == FR_OK) {
		for(;;){
			Res = f_readdir(&dir, &fno);
			if (Res != FR_OK || fno.fname[0] == 0) break;
			if (!(fno.fattrib & AM_DIR)){
				fileCount++;
				idx = strlen(fileNameLst);
				sprintf(&fileNameLst[idx], "%s,", fno.fname);
//				xil_printf("%s\t%d\n", fno.fname, fno.fsize);
			}
		}
		idx = strlen(fileNameLst) - 1;
		fileNameLst[idx] = '\0';
//		xil_printf("%s\n", fileNameLst);
	}
}

static int sdGetFilename(TCHAR *fName, uint num){
	if(num > fileCount || num == 0)
		return XST_FAILURE;

	uint startIdx = 0;
	uint idx = 0;
	uint len = 0;

	uint cnt = 0;

	while(fileNameLst[idx] != '\0'){
		cnt++;
		if(cnt == num){
			startIdx = idx;
		}

		do{
			idx++;
		}
		while(!(fileNameLst[idx] == ',' || fileNameLst[idx] == '\0'));

		idx++;

		if(cnt == num){
			len = idx - startIdx;
			break;
		}
	}

	if(len > 0){
		strlcpy(fName, &fileNameLst[startIdx], len);
		fName[len + 1] = '\0';
		return XST_SUCCESS;
	}
	return XST_FAILURE;
}

static int sdReadPosture(TCHAR *fName){
		FRESULT Res;
		Res = f_open(&fil, fName, FA_READ);
		if (Res) {
			return XST_FAILURE;
		}

		Res = f_lseek(&fil, 0);
		if (Res) {
			return XST_FAILURE;
		}

		uint NumBytesRead;
		Res = f_read(&fil, (void*)xPosture, sizeof(xPosture), &NumBytesRead);
		if (Res) {
			return XST_FAILURE;
		}
		return XST_SUCCESS;
	}
