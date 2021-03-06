/*
 * client.cpp
 *
 *  Created on: 2016年5月26日
 *      Author: root
 */

//============================================================================
// Name        : ChatClient.cpp
// Author      : Lei
// Version     :
// Copyright   :
// Description : ChatClient in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>
#include <stdio.h>
#include <strings.h>
#include "clientsocket.h"
#include "../socketexception.h"
#include "../Cfgini/inifile.h"
using namespace std;

int main() {
	int i = 0;
	char filename[10] = { 0 };
	cout << "Running client...." << endl;
	//ClientSocket clientSocket("122.114.133.87", 9090);
	//ClientSocket clientSocket("127.0.0.1", 9090);
	//ClientSocket clientSocket("192.168.3.166", 9090);
	char ip_Buf[24];
	memset(ip_Buf,'\0',24);
	if(!read_profile_string("SOCKCFG","SERVERIP",ip_Buf,sizeof(ip_Buf),"211.149.203.192","./SOCKCFGINI.ini")){
		strcpy(ip_Buf,"211.149.203.192");
	};
	int port= 0;
	port = read_profile_int("SOCKCFG", "SERVERPORT", 9090, "./SOCKCFGINI.ini");

	int interval = 0;
	interval = read_profile_int("SOCKCFG", "INTERVAL", 5, "./SOCKCFGINI.ini");

	int loop = 0;
	
	ClientSocket clientSocket(ip_Buf, port);
	string ack(ACK);
	string nck(NCK);
	++i;
	bzero(filename, 10);
	sprintf(filename, "%d.ini", i);
	while (true) {
		try {
			while ((access(filename, 0) == 0)) {
				cout << "File:" << filename << endl;
				cout << "start send file:" << endl;
				clientSocket.Send(ack);  //start send file
				sleep(1);
				if (!clientSocket.SendBinaryFile(filename,i)) {

					std::cout << "------------------send over---------------------" << std::endl;
					sleep(1);
					clientSocket.Send(nck); //send over
					sleep(1);
					++i;
					bzero(filename, 10);
					sprintf(filename, "%d.ini", i);
				} else {
					cout << "reconnect " << endl;
					clientSocket.Close();
					clientSocket.Connect(ip_Buf, port);
				};

			};
		} catch (SocketException& ex) {
			cout << "Exception was caught:" << ex.Description() << "\n";
			clientSocket.Close();
			clientSocket.Connect(ip_Buf, port);
		}
		//break;
		sleep(interval);
		++loop;
		if( loop > interval){
			break;
		}
		
	}
	clientSocket.Close();
	return 0;
}

