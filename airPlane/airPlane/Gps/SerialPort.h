/*
 * SerialPort.h
 *
 *  Created on: Jul 21, 2015
 *      Author: root
 */

#ifndef SERIALPORT_H_
#define SERIALPORT_H_



#include "../Util/common.h"
#include <iostream>


using namespace std;

typedef struct _serialconfig_
{
    long baud;/*波特率:如38400,115200等*/
    unsigned char databits;/*数据位0-8位;1-7位;2-6位;3-5位;*/
    unsigned char parity;/*奇偶校验位:0-无奇偶校验;1-设置为奇效验;2-转换为偶效验*/
    unsigned char stopbits;/*停止位:0--1位停止位;1--2位停止位*/
} serialconfig_t;


enum SerialType
{
  CONTROL_PORT,DATA_PORT

};

#define SERIALPORT_NAME_LENGTH  15

class Serialcom
{
  public:
    Serialcom();
    Serialcom(serialconfig_t serialconf,int delay,int choice);
    ~Serialcom();



    void
    setSerialName(char *serialname);

    char *
    getSerialName();

    int
    getSerialfd();

    bool isSerialOpen();
    int
    SerialcomOpen();
    int
    SerialcomOpen(char *serialName);
    int
    SerialcomClose();
    int
    CheckSerialcomData();
    int
    SerialcomRead(char* pbuffer,int dataLen);
    int
    SerialcomWrite(char* pbuffer,int dataLen);


  protected:
    int ComFd; /*串口描述符*/
    int stat;
    long baud;/*波特率:如38400,115200等*/
    unsigned char databits;/*数据位0-8位;1-7位;2-6位;3-5位;*/
    unsigned char parity;/*奇偶校验位:0-无奇偶校验;1-设置为奇效验;2-转换为偶效验*/
    unsigned char stopbits;/*停止位:0--1位停止位;1--2位停止位*/
    int usec;
    int port; /*0,1,2;only 3 choice*/
  public:
    char *serialName; //serial num
};
#endif /* SERIALPORT_H_ */
