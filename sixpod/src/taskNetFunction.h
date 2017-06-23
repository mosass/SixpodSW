/*
 * taskNetFunction.h
 *
 *  Created on: Jun 10, 2017
 *      Author: mosas
 */

#ifndef SRC_TASKNETFUNCTION_H_
#define SRC_TASKNETFUNCTION_H_

#include "joint_controls.h"

#define SET_STEP_TIME	31
#define SET_STEP_UPZ	32
#define SET_SELECT_POS	33
#define GET_FILE_LIST	34

#define WALKING_STOP	40
#define WALKING_WAV		41
#define WALKING_RIPP	42
#define WALKING_TRI		43

u16_t server_port = 9000;
u16_t logs_server_port = 9001;

static struct netif server_netif;
struct netif *echo_netif;

void ftostr(char * str, float fval)
{
	float tmpVal = (fval < 0) ? -fval : fval;

	int tmpInt1 = tmpVal;                  // Get the integer.
	float tmpFrac = tmpVal - tmpInt1;      // Get fraction.
	int tmpInt2 = trunc(tmpFrac * 10000);  // Turn into integer.

	// Print as parts, note that you need 0-padding for fractional bit.
	if(fval < 0){
		sprintf (str, "-%d.%04d", tmpInt1, tmpInt2);
	}
	else{
		sprintf (str, "%d.%04d", tmpInt1, tmpInt2);
	}

}

// remote App
/* thread spawned for each connection */
static void process_request(void *p)
{
	int sd = (int)p;
	int RECV_BUF_SIZE = 2048;
	char recv_buf[RECV_BUF_SIZE];
	int n;
	int cmd;
	float fval;
	int ival;
	TCHAR filename[50];
	char ack_msg[] = "ACK";

	int walkQ;

	while (1) {
		/* read a max of RECV_BUF_SIZE bytes from socket */
		if ((n = read(sd, recv_buf, RECV_BUF_SIZE)) < 0) {
			xil_printf("%s: error reading from socket %d, closing socket\r\n", __FUNCTION__, sd);
			break;
		}
		/* break if client closed connection */
		if (n <= 0)
			break;

		sscanf(recv_buf, "%d", &cmd);

		switch(cmd){
		case SET_STEP_TIME:
			if(sscanf(recv_buf, "%d %f", &cmd, &fval) == 2){
				stepTime = fval;
				write(sd, ack_msg, strlen(ack_msg));
				xil_printf("SET_STEP_TIME\r\n");
			}
			break;
		case SET_STEP_UPZ:
			if(sscanf(recv_buf, "%d %f", &cmd, &fval) == 2){
				stepUpZ = fval;
				write(sd, ack_msg, strlen(ack_msg));
				xil_printf("SET_STEP_UPZ\r\n");
			}
			break;
		case SET_SELECT_POS:
			if(sscanf(recv_buf, "%d %d", &cmd, &ival) == 2){
				sdGetFilename(filename, ival);
				sdReadPosture(filename);
				write(sd, ack_msg, strlen(ack_msg));
				xil_printf("SET_SELECT_POS\r\n");
			}
			break;
		case GET_FILE_LIST:
			sdGetFileList();
			write(sd, fileNameLst, strlen(fileNameLst));
			xil_printf("GET_FILE_LIST\r\n");
			break;
		case WALKING_STOP:
			walkQ = WALKING_STOP;
			xQueueReset(xWalkQueue);
			xQueueSend(xWalkQueue, (void *) &walkQ, 0);
			write(sd, ack_msg, strlen(ack_msg));
			xil_printf("WALKING_STOP\r\n");
			break;
		case WALKING_WAV:
			walkQ = WALKING_WAV;
			xQueueReset(xWalkQueue);
			xQueueSend(xWalkQueue, (void *) &walkQ, 0);
			write(sd, ack_msg, strlen(ack_msg));
			xil_printf("WALKING_WAV\r\n");
			break;
		case WALKING_RIPP:
			walkQ = WALKING_RIPP;
			xQueueReset(xWalkQueue);
			xQueueSend(xWalkQueue, (void *) &walkQ, 0);
			write(sd, ack_msg, strlen(ack_msg));
			xil_printf("WALKING_RIPP\r\n");
			break;
		case WALKING_TRI:
			walkQ = WALKING_TRI;
			xQueueReset(xWalkQueue);
			xQueueSend(xWalkQueue, (void *) &walkQ, 0);
			write(sd, ack_msg, strlen(ack_msg));
			xil_printf("WALKING_TRI\r\n");
			break;
		}
	}

	/* close connection */
	close(sd);
	vTaskDelete(NULL);
}

static char header[] =
		"yaw,pitch,roll,"
		"x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,x5,y5,z5,x6,y6,z6,"
		"ta1,tb1,tc1,ta2,tb2,tc2,ta3,tb3,tc3,ta4,tb4,tc4,ta5,tb5,tc5,ta6,tb6,tc6,"
		"qa1,qb1,qc1,qa2,qb2,qc2,qa3,qb3,qc3,qa4,qb4,qc4,qa5,qb5,qc5,qa6,qb6,qc6,"
		"la1,lb1,lc1,la2,lb2,lc2,la3,lb3,lc3,la4,lb4,lc4,la5,lb5,lc5,la6,lb6,lc6,"
		"tsa1,tsb1,tsc1,tsa2,tsb2,tsc2,tsa3,tsb3,tsc3,tsa4,tsb4,tsc4,tsa5,tsb5,tsc5,tsa6,tsb6,tsc6,"
		"sa1,sb1,sc1,sa2,sb2,sc2,sa3,sb3,sc3,sa4,sb4,sc4,sa5,sb5,sc5,sa6,sb6,sc6"
	;

// logs Server
static void process_logs_request(void *p)
{
	int sd = (int)p;
	char send_buf[1024];
	int n_cnt = 0;
	int nwrote;
	TickType_t st = pdMS_TO_TICKS( 100 );

	sprintf(send_buf, "%s\r\n", header);

	n_cnt = strlen(send_buf);

	if ((nwrote = write(sd, send_buf, n_cnt)) < 0) {
		xil_printf("%s: ERROR responding to client echo request. received = %d, written = %d\r\n",
				__FUNCTION__, n_cnt, nwrote);
		xil_printf("Closing socket %d\r\n", sd);
	}

	char strfval[10];
	char *pStr;
	while (1) {
		/* handle request */
		pStr = send_buf;

		ftostr(strfval, Hexapod.bodyRot.y);
		sprintf(pStr, "%s,", strfval);
		pStr += strlen(pStr);

		ftostr(strfval, Hexapod.bodyRot.p);
		sprintf(pStr, "%s,", strfval);
		pStr += strlen(pStr);

		ftostr(strfval, Hexapod.bodyRot.r);
		sprintf(pStr, "%s,", strfval);
		pStr += strlen(pStr);

		for(int i = 0; i < 6; i++){
			ftostr(strfval, Hexapod.leg[i].footTipPos.x);
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);

			ftostr(strfval, Hexapod.leg[i].footTipPos.y);
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);

			ftostr(strfval, Hexapod.leg[i].footTipPos.z);
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);
		}

		for(int i = 0; i < 6; i++){
			ftostr(strfval, Hexapod.leg[i].linkPos.a);
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);

			ftostr(strfval, Hexapod.leg[i].linkPos.b);
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);

			ftostr(strfval, Hexapod.leg[i].linkPos.c);
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);
		}

		for(int i = 0; i < 6; i++){
			ftostr(strfval, JointGetPresentPositionDeg(Hexapod.leg[i].jointIdA));
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);

			ftostr(strfval, JointGetPresentPositionDeg(Hexapod.leg[i].jointIdB));
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);

			ftostr(strfval, JointGetPresentPositionDeg(Hexapod.leg[i].jointIdC));
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);
		}

		for(int i = 0; i < 6; i++){
			sprintf(pStr, "%d,", JointGetLoad(Hexapod.leg[i].jointIdA));
			pStr += strlen(pStr);

			sprintf(pStr, "%d,", JointGetLoad(Hexapod.leg[i].jointIdB));
			pStr += strlen(pStr);

			sprintf(pStr, "%d,", JointGetLoad(Hexapod.leg[i].jointIdC));
			pStr += strlen(pStr);
		}

		for(int i = 0; i < 6; i++){
			ftostr(strfval, Hexapod.leg[i].linkSpeed.a);
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);

			ftostr(strfval, Hexapod.leg[i].linkSpeed.b);
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);

			ftostr(strfval, Hexapod.leg[i].linkSpeed.c);
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);
		}

		for(int i = 0; i < 6; i++){
			ftostr(strfval, JointGetPresentSpeedRPM(Hexapod.leg[i].jointIdA));
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);

			ftostr(strfval, JointGetPresentSpeedRPM(Hexapod.leg[i].jointIdB));
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);

			ftostr(strfval, JointGetPresentSpeedRPM(Hexapod.leg[i].jointIdC));
			sprintf(pStr, "%s,", strfval);
			pStr += strlen(pStr);
		}

		sprintf(pStr - 1, "\r\n");
		n_cnt = strlen(send_buf);

		if ((nwrote = write(sd, send_buf, n_cnt)) < 0) {
			xil_printf("%s: ERROR responding to client echo request. received = %d, written = %d\r\n",
					__FUNCTION__, n_cnt, nwrote);
			xil_printf("Closing socket %d\r\n", sd);
			break;
		}
		vTaskDelay( st );
	}

	/* close connection */
	close(sd);
	vTaskDelete(NULL);
}

static void remote_application_thread(void *p)
{
	int sock, new_sd;
	struct sockaddr_in address, remote;
	int size;

	if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return;

	address.sin_family = AF_INET;
	address.sin_port = htons(server_port);
	address.sin_addr.s_addr = INADDR_ANY;

	if (lwip_bind(sock, (struct sockaddr *)&address, sizeof (address)) < 0)
		return;

	lwip_listen(sock, 0);

	size = sizeof(remote);

	while (1) {
		if ((new_sd = lwip_accept(sock, (struct sockaddr *)&remote, (socklen_t *)&size)) > 0) {
			xRemoteNetworkTask = sys_thread_new("ClientHandler", process_request,
					(void*)new_sd,
					THREAD_STACKSIZE,
					DEFAULT_THREAD_PRIO);
		}
	}
}

static void logs_application_thread(void *p)
{
	int sock, new_sd;
	struct sockaddr_in address, remote;
	int size;

	if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return;

	address.sin_family = AF_INET;
	address.sin_port = htons(logs_server_port);
	address.sin_addr.s_addr = INADDR_ANY;

	if (lwip_bind(sock, (struct sockaddr *)&address, sizeof (address)) < 0)
		return;

	lwip_listen(sock, 0);

	size = sizeof(remote);

	while (1) {
		if ((new_sd = lwip_accept(sock, (struct sockaddr *)&remote, (socklen_t *)&size)) > 0) {
			sys_thread_new("LogsClientHandler", process_logs_request,
				(void*)new_sd,
				THREAD_STACKSIZE,
				DEFAULT_THREAD_PRIO);
		}
	}
}

static void network_thread(void *p)
{
	struct netif *netif;
	struct ip_addr ipaddr, netmask, gw;

	/* the mac address of the board. this should be unique per board */
	unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };

	netif = &server_netif;

	/* initliaze IP addresses to be used */
	IP4_ADDR(&ipaddr,  192, 168, 3, 100);
	IP4_ADDR(&netmask, 255, 255, 255,  0);
	IP4_ADDR(&gw,      192, 168, 3, 254);

	/* print out IP settings of the board */
	xil_printf("\r\n\r\n");
	xil_printf("-----lwIP Socket Mode Echo server Demo Application ------\r\n");

	/* Add network interface to the netif_list, and set it as default */
	if (!xemac_add(netif, &ipaddr, &netmask, &gw, mac_ethernet_address, XPAR_XEMACPS_0_BASEADDR)) {
		xil_printf("Error adding N/W interface\r\n");
		return;
	}
	netif_set_default(netif);

	/* specify that the network if is up */
	netif_set_up(netif);

	/* start packet receive thread - required for lwIP operation */
	sys_thread_new("xemacif_input_thread", (void(*)(void*))xemacif_input_thread, netif,
			THREAD_STACKSIZE,
			DEFAULT_THREAD_PRIO);

	sys_thread_new("RemoteApp", remote_application_thread, 0,
		THREAD_STACKSIZE,
		DEFAULT_THREAD_PRIO);

	sys_thread_new("LogsApp", logs_application_thread, 0,
			THREAD_STACKSIZE,
			DEFAULT_THREAD_PRIO);
	vTaskDelete(NULL);
	return;
}

#endif /* SRC_TASKNETFUNCTION_H_ */
