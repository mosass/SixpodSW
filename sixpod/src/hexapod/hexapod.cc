/*
 * hexapod.cc
 *
 *  Created on: Apr 2, 2017
 *      Author: Phanomphon Yotchon
 */

#include "hexapod.h"
#include "sleep.h"

static void print_float(float f){
	int i = (int) f;
	int s = (f - i) * 1000;

	xil_printf("%d.", i);
	s = s < 0 ? -s : s;
	if(s < 100)
		xil_printf("0");
	if(s < 10)
		xil_printf("0");
	xil_printf("%d\t", s);
}

HEXAPOD::HEXAPOD(){
	for(int i = 0; i < 6; i++){
		this->leg[i].setup(i+1, INITIAL_FOOTTIP_Z_OFF);

		this->footTip[i].x = INITIAL_FOOTTIP_X;
		this->footTip[i].y = INITIAL_FOOTTIP_Y;
		this->footTip[i].z = INITIAL_FOOTTIP_Z;
	}
}

void HEXAPOD::begin(void *imuCallBack, volatile bool* flagVar){
	Imu.setup(MPU_INTR_PIN, imuCallBack, flagVar);
	int status;
	float setup_time = SETUP_TIME;
	for(int i = 0; i < 6; i++){
		this->leg[i].moveTo(this->footTip[i], setup_time);
	}
	sleep(3);
	for(int cntloop = 0; cntloop < 2000; ){
		while (!Imu.available());
//		xil_printf(".");
		if(cntloop % 100 == 0)
			xil_printf(".");
		status = Imu.readFifoBuffer();
		if (status == XST_SUCCESS) {
			cntloop++;
		}
	}
	xil_printf("\r\n");
	bodyRotOffset.y = Imu.euler[0];
	bodyRotOffset.p = Imu.euler[1];
	bodyRotOffset.r = Imu.euler[2];
}

bool HEXAPOD::readIMU(){
	if (Imu.available()){
		int status = Imu.readFifoBuffer();
		if (status == XST_SUCCESS) {
			bodyRot.y = Imu.euler[0];
			bodyRot.p = Imu.euler[1];
			bodyRot.r = Imu.euler[2];

			bodyRot = bodyRot - bodyRotOffset;
			return true;
		}
	}

	return false;
}
