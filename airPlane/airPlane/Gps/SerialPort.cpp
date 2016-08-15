/*
 * SerialPort.cpp
 *
 *  Created on: Jul 21, 2015
 *      Author: root
 */

#include "SerialPort.h"

Serialcom::Serialcom()
{
  baud = 9600;
  databits = '8';
  parity = 'N';
  stopbits = '1';
  usec = 1;
  port = 2;
  stat = 0;
  ComFd = -1;
  serialName = new char[SERIALPORT_NAME_LENGTH];
  std::cout << baud << "\t" << databits << "\t" << parity << "\t" << stopbits
      << std::endl;
}

Serialcom::Serialcom(serialconfig_t serialconf,int delay,int choice)
{
  baud = serialconf.baud;
  databits = serialconf.databits;
  parity = serialconf.parity;
  stopbits = serialconf.stopbits;
  usec = delay;
  port = choice;
  stat = 0;
  ComFd = -1;
  serialName = new char[SERIALPORT_NAME_LENGTH];
}

Serialcom::~Serialcom()
{
  //  delete[] serialName;
}

int
Serialcom::SerialcomOpen(char *serialPortName)
{
  //find port
  if(serialPortName == NULL)
  {
    printf("the port is out range");
    return -1;
  }

  strcpy(serialName,serialPortName);
  /*open port*/
  ComFd = open(serialName,O_RDWR | O_NOCTTY | O_NDELAY);
  if(ComFd < 0)
  {
    ComFd = open(serialName,O_RDWR | O_NOCTTY | O_NDELAY);
    if(ComFd < 0)
    {
      perror("open serial port");

      return -1;
    }
  }

  if(fcntl(ComFd,F_SETFL,0) < 0)
  {
    perror("fcntl F_SETFL");
  }

  if(isatty(ComFd) == 0)
  {
    perror("isatty is not a terminal device");
  }
  stat = 1;

  struct termios new_cfg, old_cfg;
  int speed_arry[] =
  { B2400, B4800, B9600, B19200, B38400, B115200 };
  int speed[] =
  { 2400, 4800, 9600, 19200, 38400, 115200 };
  int i = 0;

  /*save and test the serial port*/
  if(tcgetattr(ComFd,&old_cfg) < 0)
  {
    perror("tcgetattr");
    return -1;
  }

  new_cfg = old_cfg;
  cfmakeraw(&new_cfg);
  new_cfg.c_cflag &= ~CSIZE;

  for(i = sizeof(speed_arry) / sizeof(speed_arry[0]);i > 0;i--)
  {
    if(baud == speed[i])
    {
      cfsetispeed(&new_cfg,speed_arry[i]);
      cfsetospeed(&new_cfg,speed_arry[i]);
    }
  }

  switch(databits)
  {
    case '7':
      new_cfg.c_cflag |= CS7;
      break;

    default:
    case '8':
      new_cfg.c_cflag |= CS8|CRTSCTS;
      break;
  }

  switch(parity)
  {
    default:
    case 'N':
    case 'n':
    {
      new_cfg.c_cflag &= ~PARENB;
      new_cfg.c_iflag &= ~INPCK;
    }
      break;

    case 'o':
    case 'O':
    {
      new_cfg.c_cflag |= (PARODD | PARENB);
      new_cfg.c_iflag |= INPCK;
    }
      break;

    case 'e':
    case 'E':
    {
      new_cfg.c_cflag |= PARENB;
      new_cfg.c_cflag &= ~PARODD;
      new_cfg.c_iflag |= INPCK;
    }
      break;

    case 's':
    case 'S':
    {
      new_cfg.c_cflag &= ~PARENB;
      new_cfg.c_cflag &= ~CSTOPB;
    }
      break;
  }

  switch(stopbits)
  {
    default:
    case '1':
    {
      new_cfg.c_cflag &= ~CSTOPB;
    }
      break;

    case '2':
    {
      new_cfg.c_cflag |= CSTOPB;
    }
      break;
  }

  /*set wait time*/
  new_cfg.c_cc[VTIME] = 0;
  new_cfg.c_cc[VMIN] = 1;

  tcflush(ComFd,TCIFLUSH);
  if((tcsetattr(ComFd,TCSANOW,&new_cfg)) < 0)
  {
    perror("tcsetattr");
    return -1;
  }
  printf("Open and Set serial ok,%d\n",ComFd);
  return ComFd;
}

int
Serialcom::SerialcomOpen()
{
  /*open port*/
  ComFd = open(this->serialName,O_RDWR | O_NOCTTY | O_NDELAY);
  if(ComFd < 0)
  {
    ComFd = open(this->serialName,O_RDWR | O_NOCTTY | O_NDELAY);
    if(ComFd < 0)
    {
      perror("open serial port");
      return -1;
    }
  }

  if(fcntl(ComFd,F_SETFL,0) < 0)
  {
    perror("fcntl F_SETFL");
  }

  if(isatty(ComFd) == 0)
  {
    perror("Is a tty is not a terminal device");
  }
  stat = 1;

  struct termios new_cfg, old_cfg;
  int speed_arry[] =
  { B2400, B4800, B9600, B19200, B38400, B115200 };
  int speed[] =
  { 2400, 4800, 9600, 19200, 38400, 115200 };
  int i = 0;

  /*save and test the serial port*/
  if(tcgetattr(ComFd,&old_cfg) < 0)
  {
    perror("tcgetattr");
    return -1;
  }

  new_cfg = old_cfg;
  cfmakeraw(&new_cfg);
  new_cfg.c_cflag &= ~CSIZE;

  for(i = sizeof(speed_arry) / sizeof(speed_arry[0]);i > 0;i--)
  {
    if(baud == speed[i])
    {
      cfsetispeed(&new_cfg,speed_arry[i]);
      cfsetospeed(&new_cfg,speed_arry[i]);
    }
  }

  switch(databits)
  {
    case '7':
      new_cfg.c_cflag |= CS7;
      break;

    default:
    case '8':
      new_cfg.c_cflag |= CS8;
      break;
  }

  switch(parity)
  {
    default:
    case 'N':
    case 'n':
    {
      new_cfg.c_cflag &= ~PARENB;
      new_cfg.c_iflag &= ~INPCK;
    }
      break;

    case 'o':
    case 'O':
    {
      new_cfg.c_cflag |= (PARODD | PARENB);
      new_cfg.c_iflag |= INPCK;
    }
      break;

    case 'e':
    case 'E':
    {
      new_cfg.c_cflag |= PARENB;
      new_cfg.c_cflag &= ~PARODD;
      new_cfg.c_iflag |= INPCK;
    }
      break;

    case 's':
    case 'S':
    {
      new_cfg.c_cflag &= ~PARENB;
      new_cfg.c_cflag &= ~CSTOPB;
    }
      break;
  }

  switch(stopbits)
  {
    default:
    case '1':
    {
      new_cfg.c_cflag &= ~CSTOPB;
    }
      break;

    case '2':
    {
      new_cfg.c_cflag |= CSTOPB;
    }
      break;
  }

  /*set wait time*/
  new_cfg.c_cc[VTIME] = 0;
  new_cfg.c_cc[VMIN] = 1;

  tcflush(ComFd,TCIFLUSH);
  if((tcsetattr(ComFd,TCSANOW,&new_cfg)) < 0)
  {
    perror("tcsetattr");
    return -1;
  }
  printf("Open and Set serial ok,fd:%d-->%s\n",ComFd,this->serialName);
  return ComFd;
}


void
Serialcom::setSerialName(char *serialname){

  strcpy(this->serialName,serialname);
  std::cout<<this->serialName<<std::endl;

}


char *
Serialcom::getSerialName(){

  return this->serialName;

}

int Serialcom::getSerialfd(){

  return this->ComFd;

}
bool
Serialcom::isSerialOpen(){
  if(this->stat){
    return true;
  }else{
    return false;
  };
}
int
Serialcom::SerialcomClose()
{
  close(ComFd);
  stat = 0;
  return stat;
}

/*> 0 有文件描述符可读， =0 超时 < 0 无描述符可读*/
int
Serialcom::CheckSerialcomData()
{
  fd_set rset;
  struct timeval tv;
  int ret;

  FD_ZERO(&rset);
  FD_SET(ComFd, &rset);

  tv.tv_sec = usec;
  tv.tv_usec = 0;
  ret = select(ComFd + 1,&rset,NULL,NULL,&tv);
 // if(ret > 0)
 //   printf("Check have data\n");
  return ret;
}

int
Serialcom::SerialcomRead(char* pbuffer,int dataLen)
{
  int ret;


  ret = read(ComFd,pbuffer ,dataLen);



  return ret;
}

int
Serialcom::SerialcomWrite(char* pbuffer,int dataLen)
{
  int ret;
  ret = write(ComFd,pbuffer,dataLen);
  if(ret > 0)
    printf("SerialcomWrite pbuffer = %s\n",pbuffer);
  return ret;
}

