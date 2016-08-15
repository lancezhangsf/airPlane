/*
 * server.cpp
 *
 *  Created on: 2016年5月26日
 *      Author: root
 */

//============================================================================
// Name        : ChatServer.cpp
// Author      : Lei
// Version     :
// Copyright   :
// Description : ChatServer in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>
#include "serversocket.h"
#include "../socketexception.h"
using namespace std;

int main() {
	cout << "Running server..." << endl;

	try {
		ServerSocket server(8080);
		Socket newSocket;

		fd_set readfds;
		unsigned int max = 0;
		struct timeval tval, *ptval = &tval;
		tval.tv_sec = 60;
		tval.tv_usec = 0;
		int ret;
		bool istimeout = false;

		while (1) {
			istimeout = false;
			max = 0;
			server.Accept(newSocket);
			while (true) {

				try {
#if 0
					//               string message;
					// server.RecvFile(&newSocket);
					while (newSocket.m_sockfd) {
						++i;
						sprintf(filename, "%d.jpeg", i);
						server.RecvBinaryFile(&newSocket, filename);
						cout << "文件接受完毕！" << endl;
						bzero(filename, 10);
						//closesocket (clientSocket);
					}

					server.Receive(newSocket,message);
					cout<<"Receive message: "<<message<<endl;
					message="Here is server";
					server.Send(newSocket,message);
#else
					FD_ZERO(& readfds);
					if (max < (unsigned int) newSocket.m_sockfd) {
						max = (unsigned int) newSocket.m_sockfd;
					}
					FD_SET(newSocket.m_sockfd, &readfds);

					ret = select(max + 1, &readfds, 0, 0, ptval);
					if (0 > ret) {
						return -1;	// return -2.
					}else if(ret==0){
						printf("have timeout..........\n");
						tval.tv_sec = 60;
						tval.tv_usec = 0;
						//istimeout = true;
						//shutdown(newSocket.m_sockfd,SHUT_RDWR);
						//break;
					}else {
						if (FD_ISSET(newSocket.m_sockfd, &readfds)) {
							if (!server.RecvBinaryFile(&newSocket)) {
								cout << "文件传输完成！" << endl;
								continue;
							}else{

								cout <<"rcv failure....,maybe network have problem"<<endl;
								break;
							}
							cout << "文件接受完毕！" << endl;

						}
					}

#endif
				} catch (SocketException& ex) {
					cout << "Exception was caught:" << ex.Description()
							<< "\nExiting.\n";
				}
			}
			sleep(5);
		}
	} catch (SocketException& ex) {
		cout << "Exception was caught:" << ex.Description() << "\nExiting.\n";
	}

	return 0;
}

