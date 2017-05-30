/*
 * Main C++ Application
 */


/* FreeRTOS includes. */
#include "platform.h"

/* Module includes */
#include "hexapod.h"

static XGpio GpioBtnSw;
static XGpio GpioLed;

#define LED_CH 1
#define BTN_CH 1
#define SW_CH  2

static QueueHandle_t xPostureQueue[6];
static TaskHandle_t xInitTask;
static TaskHandle_t xWalkingTask;
static TaskHandle_t xLegGait[6];
static TaskHandle_t xIMUTask;

static Posture xPosture[6];

static const char * taskName[6] = {
		"Leg1Gait",
		"Leg2Gait",
		"Leg3Gait",
		"Leg4Gait",
		"Leg5Gait",
		"Leg6Gait"
};

/* Task function */
#include "networkTaskFunction.h"
#include "taskFunction.h"

extern "C" void lwip_init();
static void init( void * );

int main (void) {
	BaseType_t status;
//-------------------------------
	status = XGpio_Initialize(&GpioBtnSw, XPAR_GPIO_0_DEVICE_ID);
	if (status != XST_SUCCESS) {
		xil_printf("Gpio Initialization Failed\r\n");
		return XST_FAILURE;
	}

	status = XGpio_Initialize(&GpioLed, XPAR_GPIO_1_DEVICE_ID);
	if (status != XST_SUCCESS) {
		xil_printf("Gpio Initialization Failed\r\n");
		return XST_FAILURE;
	}

	/* Set the direction for all signals as inputs except the Btn INPUT */
	XGpio_SetDataDirection(&GpioBtnSw, SW_CH, 0xFFFFFFFF);
	XGpio_SetDataDirection(&GpioBtnSw, BTN_CH, 0xFFFFFFFF);
	XGpio_SetDataDirection(&GpioLed, LED_CH, 0xFFFFFFF0);
//	while(1){
//		u32 btn = XGpio_DiscreteRead(&Gpio, 2);
//		xil_printf("%x\r\n", btn);
//		sleep(1);
//	}
//	return XST_SUCCESS;
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

//	vTaskDelete(NULL);
//-----------------------------------------
	BaseType_t status;

	xil_printf("Initial\r\n");

	sdMount();	// Mount File System
	sdGetFileList(); // Update File List

	Hexapod.begin();

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
				 DEFAULT_THREAD_PRIO ,
				 &xIMUTask );

	if(status != pdPASS){
		xil_printf("Can not create IMU task.\r\n");
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

	xil_printf("Initialed\r\n");
	vTaskDelete(NULL);
}

