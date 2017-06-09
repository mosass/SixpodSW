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
		U = 3;
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
		U = 3;
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
	else if(last){
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
	}
	else{
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
}

static void hexapodIMUTask( void *pvParameters ){
	u32 btn;
	btn = XGpio_DiscreteRead(&GpioBtnSw, SW_CH);
	Hexapod.improvePitch = true;
	Hexapod.improveRoll = true;
	Hexapod.improveYaw = false;

	for(;;){
		if(Hexapod.readIMU()){
			btn = XGpio_DiscreteRead(&GpioBtnSw, SW_CH);
			if(btn & (u32) 1 << 3){
				if(Hexapod.improvePitch || Hexapod.improveRoll || Hexapod.improveYaw){
					// balance mode
					if(Hexapod.balance()){
						xil_printf("B");
						Hexapod.updateGoalPosition();
					}
				}
			}
			vTaskDelay(pdMS_TO_TICKS( 100 ));
		}
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
			Hexapod.targetFootTip[id] = Hexapod.targetFootTip[id] + Vpoint;
			Hexapod.footTip[id] = Hexapod.targetFootTip[id];
			Hexapod.leg[id].moveToSync(Hexapod.targetFootTip[id], stepTime);
		}
		else {
			Hexapod.targetFootTip[id] = Upoint;
			Hexapod.footTip[id] = Hexapod.targetFootTip[id];
			Hexapod.targetFootTip[id].z = 2; // (ignore balancing for this leg).
			Hexapod.leg[id].gaitTo(Hexapod.footTip[id], stepTime * state, xWalkingTask);
			Hexapod.targetFootTip[id].z = 0;
		}
	}
}

static void hexapodWalkingTask( void *pvParameters ){
	int p_arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
	char fname[20];
	uint idp = 0;
	u32 btn, sw;

	XGpio_DiscreteWrite(&GpioLed, LED_CH, idp + 1);
	for(;;){
		xil_printf("Ready\r\n");
		btn = XGpio_DiscreteRead(&GpioBtnSw, SW_CH);
		sw = XGpio_DiscreteRead(&GpioBtnSw, BTN_CH);
		while(!(btn & (u32) 0x7)){
			if(sw & (u32) 1 << 3){
				xil_printf("+");
				idp = (idp + 1) % 8;
				XGpio_DiscreteWrite(&GpioLed, LED_CH, idp + 1);
				vTaskDelay(pdMS_TO_TICKS(500));
			}
			vTaskDelay(pdMS_TO_TICKS(500));
			btn = XGpio_DiscreteRead(&GpioBtnSw, SW_CH);
			sw = XGpio_DiscreteRead(&GpioBtnSw, BTN_CH);
			xil_printf(".");
		}
		xil_printf(".\r\n");
		sdGetFilename(fname, p_arr[idp]);

		sdReadPosture(fname);
		for(int i = 0; i < 6; i++){
			xQueueReset(xPostureQueue[i]);

			xTaskCreate( hexapodLegGaitTask,
						taskName[i], configMINIMAL_STACK_SIZE,
						(void *) &xPosture[i], DEFAULT_THREAD_PRIO + 1, &xLegGait[i] );
		}

		stepTime = Hexapod.dt;

		if(btn & (u32) 1 << 0){
			xil_printf("Tripod Gait with %d\r\n", p_arr[idp]);
			sendTripodGait(true);
			for(;;){
				xil_printf(".");
				sendTripodGait();
				btn = XGpio_DiscreteRead(&GpioBtnSw, SW_CH);
				if(!(btn & (u32) 1 << 0)){
					break;
				}
			}
		}

		if(btn & (u32) 1 << 1){
			xil_printf("Wave Gait with %d\r\n", p_arr[idp]);
			sendWaveGait(true);
			for(;;){
				xil_printf(".");
				sendWaveGait();
				btn = XGpio_DiscreteRead(&GpioBtnSw, SW_CH);
				if(!(btn & (u32) 1 << 1)){
					break;
				}
			}
		}

		if(btn & (u32) 1 << 2){
			xil_printf("Ripple Gait with %d\r\n", p_arr[idp]);
			sendRippleGait(true);
			for(;;){
				xil_printf(".");
				sendRippleGait();
				btn = XGpio_DiscreteRead(&GpioBtnSw, SW_CH);
				if(!(btn & (u32) 1 << 2)){
					break;
				}
			}
			sendRippleGait(false, true);
		}

		for(int i = 0; i < 6; i++){
			vTaskDelete(xLegGait[i]);
		}
	}
	vTaskDelete(NULL);
}

#endif /* SRC_TASKFUNCTION_H_ */
