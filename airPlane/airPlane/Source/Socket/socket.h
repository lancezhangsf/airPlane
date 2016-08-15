/*
 * socket.h
 *
 *  Created on: 2016年5月26日
 *      Author: root
 */

#ifndef SOCKET_SOCKET_H_
#define SOCKET_SOCKET_H_


#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>




const int MAXCONNECTION=5;
const int MAXRECEIVE = 1024;
const int MAXLEN = 1024;
const char NCK[1]={ 0xBB };
const char ACK[1]={ 0xAA };

#define HEAD  0xfffffffe
#define TAIL  0xffffffff

class Socket
{
    public:
        Socket();
        //virtual destructior
        virtual ~Socket();

        // Server initialization
        bool Create(); //create a socket
        bool Bind(const int port);
        bool Listen() const;
        bool Accept(Socket& clientSocket) const;

        // Client initialization
        bool Connect(const std::string& host,const int port);

        // Data Transmission
        bool Send(Socket& socket,const std::string& message) const;
        int Receive(Socket& socket,std::string& message) const;

        void SetNonBlocking(const bool flag);
        bool IsValid() const;
        std::string GetAddress();
    private:
        //use m_sockfd to record the result of function socket
        struct sockaddr_in m_address;
    public:
        int m_sockfd;
};
void AddHeadTail(char *src,int srclen,char index,char *dst,int &dstlen);

void DelHeadTail(char *src,int srclen,char *dst,int &dstlen);

#endif /* SOCKET_SOCKET_H_ */
