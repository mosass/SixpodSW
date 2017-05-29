/*
 * task.h
 *
 *  Created on: Apr 13, 2017
 *      Author: Phanomphon Yotchon
 */

#ifndef SRC_TASKFUNCTION_H_
#define SRC_TASKFUNCTION_H_

static int U = 1;
static const int V = 300;

static volatile float stepTime;

void prinfloat(float fval){
	int whole = fval;
	int thousandths = (fval - whole) * 1000;
	thousandths = thousandths > 0 ? thousandths : -thousandths;
	xil_printf("%d.%3d", whole, thousandths);
}

static void hexapodWalkingTask( void * );
static void hexapodLegGaitTask( void * );

static void sendTripodGait(bool first = false){
	if(first){
		U = 5;
		xQueueSend(xPostureQueue[1], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &U, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
	}
	else {
		U = 5;
		xQueueSend(xPostureQueue[0], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &U, 0UL);

		for(int i = 0; i < 5; i++){
			xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
			xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
			xQueueSend(xPostureQueue[5], (void *) &V, 0UL);
		}

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		U = 5;
		xQueueSend(xPostureQueue[1], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &U, 0UL);

		for(int i = 0; i < 5; i++){
			xQueueSend(xPostureQueue[0], (void *) &V, 0UL);
			xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
			xQueueSend(xPostureQueue[4], (void *) &V, 0UL);
		}

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
	}
}

static void sendWaveGait(bool first = false){
	if(first){
		U = 1;
		xQueueSend(xPostureQueue[1], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &U, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

//		xQueueSend(xPostureQueue[0], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &U, 0UL);

//		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
//		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
	}
	else {
		U = 1;
		xQueueSend(xPostureQueue[0], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &V, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		xQueueSend(xPostureQueue[0], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &V, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		xQueueSend(xPostureQueue[0], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &V, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		xQueueSend(xPostureQueue[0], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &V, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		xQueueSend(xPostureQueue[0], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &V, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		xQueueSend(xPostureQueue[0], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &U, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
	}
}

static void sendRippleGait(bool first = false, bool last = false){
	if(first){
		U = 1;
		xQueueSend(xPostureQueue[1], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &U, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

//		xQueueSend(xPostureQueue[0], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &U, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
//		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
//		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		U = 2;
		xQueueSend(xPostureQueue[0], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &V, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
	}
	else {
		U = 2;

		xQueueSend(xPostureQueue[0], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &V, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		xQueueSend(xPostureQueue[0], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &V, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		xQueueSend(xPostureQueue[0], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &V, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		xQueueSend(xPostureQueue[0], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &V, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		xQueueSend(xPostureQueue[0], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &U, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		xQueueSend(xPostureQueue[0], (void *) &U, 0UL);
		xQueueSend(xPostureQueue[5], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[1], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[3], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[2], (void *) &V, 0UL);
		xQueueSend(xPostureQueue[4], (void *) &V, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

		if(last){
			ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		}
	}
}

static void hexapodWalkingTask( void *pvParameters ){
	Posture walkPosture[6] = {
			{1, 5, 12, 0, -2, 0, 0},
			{2, 5, 12, 0, -2, 0, 0},
			{3, 5, 12, 0, -2, 0, 0},
			{4, 5, 12, 0, -2, 0, 0},
			{5, 5, 12, 0, -2, 0, 0},
			{6, 5, 12, 0, -2, 0, 0}
	};

	for(int i = 0; i < 6; i++){
		xQueueReset(xPostureQueue[i]);

		xTaskCreate( hexapodLegGaitTask,
					taskName[i], configMINIMAL_STACK_SIZE,
					(void *) &walkPosture[i], DEFAULT_THREAD_PRIO + 1, &xLegGait[i] );
	}

	stepTime = Hexapod.dt;

	for( ;; ){
		xil_printf("Tripod Gait\r\n");
		sendTripodGait(true);
		for(int i = 0; i < 3; i++){
			sendTripodGait();
		}

		xil_printf("Wave Gaited\r\n");
		sendWaveGait(true);
		for(int i = 0; i < 3; i++){
			sendWaveGait();
		}

		xil_printf("Ripple Gaited\r\n");
		sendRippleGait(true);
		for(int i = 0; i < 2; i++){
			sendRippleGait();
		}
		sendRippleGait(false, true);
	}
}

static void hexapodLegGaitTask( void *pvParameters ){
	Posture* posture = (Posture*) pvParameters;
	int id = posture->LegId - 1;
	FootTip Upoint(posture->Ux, posture->Uy, posture->Uz);
	FootTip Vpoint(posture->Vx, posture->Vy, posture->Vz);

	int state;

	for(;;){
		xQueueReceive(xPostureQueue[id], (void*) &state, portMAX_DELAY);

		if(state == V){
			Hexapod.footTip[id] = Hexapod.footTip[id] + Vpoint;
			Hexapod.leg[id].moveToSync(Hexapod.footTip[id], stepTime);
		}
		else {
			Hexapod.footTip[id] = Upoint;
			Hexapod.leg[id].gaitTo(Upoint, stepTime * state, xWalkingTask);
		}
	}
}

#endif /* SRC_TASKFUNCTION_H_ */
