/*
 * serversocket.h
 *
 *  Created on: 2016年5月26日
 *      Author: root
 */

#ifndef SOCKET_SERVERSOCKET_H_
#define SOCKET_SERVERSOCKET_H_



#include "../socket.h"
#include <iostream>
#include <fstream>

class ServerSocket:public Socket
{
    public:
        ServerSocket(const int port);
        ServerSocket();
        virtual ~ServerSocket();

        void Accept(Socket& socket);
        void RecvFile(Socket* clientSocket);
        int RecvBinaryFile(Socket* clientSocket);
};


#endif /* SOCKET_SERVERSOCKET_H_ */
