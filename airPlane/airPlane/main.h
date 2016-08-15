/*
 * main.h
 *
 *  Created on: Aug 30, 2012
 *      Author: root
 */

#ifndef MAIN_H_
#define MAIN_H_



#include "./Gps/SerialPort.h"
#include "./Cfgini/inifile.h"

#include "./Gps/gps.h"


#include "./Camera/stdafx.h"

#include "./Camera/FlyCapture2.h"


#include <iostream>
#include <sstream>


using namespace FlyCapture2;
using namespace std;
#define FILENAMEMAXSIZE   24
#define USART3_MAX_RECV_LEN 800

u8 USART1_TX_BUF[USART3_MAX_RECV_LEN]; 					//串口1,发送缓存区
nmea_msg gpsx; 					//GPS信息
u8 dtbuf[50]; 					//打印缓存器
char g_inifile[512]={'0'};
//显示GPS定位信息
void Gps_Msg_Show(void) {
	float tp;
	static int index=0;

	bzero(g_inifile,512);
	++index;
	sprintf(g_inifile,"%d.ini",index);

	tp = gpsx.longitude;
	sprintf((char *) dtbuf, "%.5f %1c   ", tp /= 100000, gpsx.ewhemi); //得到经度字符串
	cout << dtbuf << endl;

	write_profile_string("GPS", "LONGITUDE", (const char *)dtbuf, g_inifile);

	tp = gpsx.latitude;
	sprintf((char *) dtbuf, "%.5f %1c   ", tp /= 100000, gpsx.nshemi);	//得到纬度字符串
	cout << dtbuf << endl;

	write_profile_string("GPS", "LATITUDE", (const char *)dtbuf, g_inifile);

	tp = gpsx.altitude;
	sprintf((char *) dtbuf, "%.1fm     ", tp /= 10);	//得到高度字符串

	write_profile_string("GPS", "ALTITUDE", (const char *)dtbuf, g_inifile);
	cout << dtbuf << endl;
	tp = gpsx.speed;
	sprintf((char *) dtbuf, "%.3fkm/h     ", tp /= 1000);	//得到速度字符串
	cout << dtbuf << endl;
	write_profile_string("GPS", "SPEED", (const char *)dtbuf, g_inifile);
#if 0
	if(gpsx.fixmode<=3)											//定位状态
	{
		sprintf((char *)dtbuf,"Fix Mode:%s",fixmode_tbl[gpsx.fixmode]);
		LCD_ShowString(30,210,200,16,16,dtbuf);
	}
	sprintf((char *)dtbuf,"Valid satellite:%02d",gpsx.posslnum);	//用于定位的卫星数
	LCD_ShowString(30,230,200,16,16,dtbuf);
	sprintf((char *)dtbuf,"Visible satellite:%02d",gpsx.svnum%100);//可见卫星数
	LCD_ShowString(30,250,200,16,16,dtbuf);
#endif
#if 1
	sprintf((char *)dtbuf,"%04d/%02d/%02d   ",gpsx.utc.year,gpsx.utc.month,gpsx.utc.date);//显示UTC日期
	cout << dtbuf << endl;
	write_profile_string("GPS", "DATE", (const char *)dtbuf, g_inifile);
	//printf("year2:%d\r\n",gpsx.utc.year);
	//LCD_ShowString(30,270,200,16,16,dtbuf);
	sprintf((char *)dtbuf,"%02d:%02d:%02d   ",gpsx.utc.hour,gpsx.utc.min,gpsx.utc.sec);//显示UTC时间
	cout << dtbuf << endl;
	write_profile_string("GPS", "TIME", (const char *)dtbuf, g_inifile);
	//LCD_ShowString(30,290,200,16,16,dtbuf);
#endif
}


#endif /* MAIN_H_ */
