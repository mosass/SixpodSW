/*
 * taskFunctions.h
 *
 *  Created on: Jun 9, 2017
 *      Author: mosas
 */

#ifndef SRC_TASKFUNCTIONS_H_
#define SRC_TASKFUNCTIONS_H_

static void sendInitGait();
static void sendTripodGait();
static void sendWaveGait();
static void sendRippleGait();

static void hexapodIMUTask( void * );
static void hexapodLegGaitTask( void * );
static void hexapodWalkingTask( void * );

static void process_request(void *);
static void process_logs_request(void *);

static void remote_application_thread(void *);
static void logs_application_thread(void *);
static void network_thread(void *p);

#include "taskNetFunction.h"

static void sendInitGait(){
	IU = 401;
	for(int i = 0; i < 6; i++){
		xQueueSend(xPostureQueue[i], (void *) &IU, 0UL);

		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
	}
}

static void sendTripodGait(){
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

static void sendWaveGait(){
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

static void sendRippleGait(){
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
}

static void hexapodIMUTask( void *pvParameters ){
	for(;;){
		if(Hexapod.readIMU()){
			vTaskDelay(pdMS_TO_TICKS( 100 ));
		}
	}
}

static void hexapodLegGaitTask( void *pvParameters ){
	int poseid = (int)pvParameters;
	int state;

	for(;;){
		int id = xPosture[poseid].LegId - 1;
		FootTip Upoint(xPosture[poseid].Ux, xPosture[poseid].Uy, xPosture[poseid].Uz);
		FootTip Vpoint(xPosture[poseid].Vx, xPosture[poseid].Vy, xPosture[poseid].Vz);

		xQueueReceive(xPostureQueue[id], (void*) &state, portMAX_DELAY);

		if(state == V){
			Hexapod.footTip[id] = Hexapod.footTip[id] + Vpoint;
			Hexapod.leg[id].moveToSync(Hexapod.footTip[id], stepTime);
		}
		else if(state == IU){
			Hexapod.footTip[id].x = INITIAL_FOOTTIP_X;
			Hexapod.footTip[id].y = INITIAL_FOOTTIP_Y;
			Hexapod.footTip[id].z = INITIAL_FOOTTIP_Z;
			Hexapod.leg[id].gaitTo(Hexapod.footTip[id], stepTime * (state - 400), stepUpZ, xWalkingTask);
		}
		else {
			Hexapod.footTip[id] = Upoint;
			Hexapod.leg[id].gaitTo(Hexapod.footTip[id], stepTime * state, stepUpZ, xWalkingTask);
		}
	}
}

static void hexapodWalkingTask( void *pvParameters ){
	for(;;){
		sendInitGait();
		for(int i = 0; i < 2; i++){
			sendTripodGait();
		}
		sendInitGait();
		for(int i = 0; i < 2; i++){
			sendWaveGait();
		}
		sendInitGait();
		for(int i = 0; i < 2; i++){
			sendRippleGait();
		}
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
	}
}

#endif /* SRC_TASKFUNCTIONS_H_ */
