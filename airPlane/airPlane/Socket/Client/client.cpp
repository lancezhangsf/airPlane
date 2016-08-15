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
using namespace std;

int main() {
	int i = 0;
	char filename[10] = { 0 };
	cout << "Running client...." << endl;
	ClientSocket clientSocket("122.114.133.87", 8081);
	//ClientSocket clientSocket("127.0.0.1", 8080);
	//ClientSocket clientSocket("192.168.3.166", 8080);
	string ack(ACK);
	string nck(NCK);
	++i;
	bzero(filename, 10);
	sprintf(filename, "%d.ini", i);
	while (true) {
		try {
			//clientSocket.Send("Hello,here is client");

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
					clientSocket.Connect("122.114.133.87", 8080);

				};

			};
		} catch (SocketException& ex) {
			cout << "Exception was caught:" << ex.Description() << "\n";
			clientSocket.Close();
			clientSocket.Connect("122.114.133.87", 8080);
		}
		clientSocket.Close();
		clientSocket.Connect("122.114.133.87", 8080);
		sleep(5);
	}
	clientSocket.Close();
	return 0;
}

