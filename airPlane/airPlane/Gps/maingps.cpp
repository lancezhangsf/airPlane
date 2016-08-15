/*
 * maingps.cpp
 *
 *  Created on: Aug 30, 2012
 *      Author: root
 */

#include "gps.h"
#include "SerialPort.h"
#define USART3_MAX_RECV_LEN 800

using namespace std;

u8 USART1_TX_BUF[USART3_MAX_RECV_LEN]; 					//串口1,发送缓存区
nmea_msg gpsx; 					//GPS信息
u8 dtbuf[50]; 					//打印缓存器
//const u8* fixmode_tbl[4] = { "Fail", "Fail", " 2D ", " 3D " };	//fix mode字符串
#if 1
//显示GPS定位信息
void Gps_Msg_Show(void) {
	float tp;

	tp = gpsx.longitude;
	sprintf((char *) dtbuf, "Longitude:%.5f %1c   ", tp /= 100000, gpsx.ewhemi); //得到经度字符串
	cout << dtbuf << endl;
	tp = gpsx.latitude;
	sprintf((char *) dtbuf, "Latitude:%.5f %1c   ", tp /= 100000, gpsx.nshemi);	//得到纬度字符串
	cout << dtbuf << endl;
	tp = gpsx.altitude;
	sprintf((char *) dtbuf, "Altitude:%.1fm     ", tp /= 10);	//得到高度字符串
	cout << dtbuf << endl;
	tp = gpsx.speed;
	sprintf((char *) dtbuf, "Speed:%.3fkm/h     ", tp /= 1000);	//得到速度字符串
	cout << dtbuf << endl;
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
	sprintf((char *)dtbuf,"UTC Date:%04d/%02d/%02d   ",gpsx.utc.year,gpsx.utc.month,gpsx.utc.date);//显示UTC日期
	cout << dtbuf << endl;
	//printf("year2:%d\r\n",gpsx.utc.year);
	//LCD_ShowString(30,270,200,16,16,dtbuf);
	sprintf((char *)dtbuf,"UTC Time:%02d:%02d:%02d   ",gpsx.utc.hour,gpsx.utc.min,gpsx.utc.sec);//显示UTC时间
	cout << dtbuf << endl;
	//LCD_ShowString(30,290,200,16,16,dtbuf);
#endif
}
#endif
int altitude;	//high
u32 latitude;  //wei du
u32 longitude; //jing du

unsigned char buffer[1024] = { 0 };

int main(void) {


	Serialcom *gpscom = new Serialcom();

	gpscom->setSerialName("/dev/ttyUSB0");

	if (-1 == gpscom->SerialcomOpen()) {

		cout << "open serialcom error" << endl;
		return 0;
	};

	char ch;
	int k = 0;

	while (1) {
		bzero(buffer, 1024);
		k = 0;
		while (1) {

			if (gpscom->CheckSerialcomData() > 0) {
				gpscom->SerialcomRead(&ch, 1);
				buffer[k++] = ch;
				cout << ch;
				if (ch == '\n'){
					cout << endl;
					break;
				}

			}
		}
		cout << "=================================================="<<endl;
		if (memcmp(buffer, "$GPGGA", 6) == 0) {

			NMEA_GPGGA_Analysis(&gpsx, buffer);

		} else if(memcmp(buffer, "$GPRMC", 6) == 0) {

			NMEA_GPRMC_Analysis(&gpsx, buffer);

		}
		Gps_Msg_Show();
	}

//---------------------------------camera -------------------------

//---------
#if 0
	if(USART3_RX_STA&0X8000)		//接收到一次数据了
	{
		rxlen=USART3_RX_STA&0X7FFF;	//得到数据长度
		for(i=0;i<rxlen;i++)USART1_TX_BUF[i]=USART3_RX_BUF[i];
		USART3_RX_STA=0;//启动下一次接收
		USART1_TX_BUF[i]=0;//自动添加结束符
		GPS_Analysis(&gpsx,(u8*)USART1_TX_BUF);//分析字符串
		Gps_Msg_Show();//显示信息
		if(upload)printf("\r\n%s\r\n",USART1_TX_BUF);//发送接收到的数据到串口1
	}
#endif

}

