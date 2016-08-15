/*
 * socket.cpp
 *
 *  Created on: 2016年5月26日
 *      Author: root
 */

#include "socket.h"
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <fcntl.h>

Socket::Socket()
:m_sockfd(-1)
{
}

Socket::~Socket()
{
    if(IsValid())
        close(m_sockfd);
}

//server function
bool Socket::Create()
{
    m_sockfd=socket(AF_INET,SOCK_STREAM,0);

    //attribue:
    int nRecvBuf=MAXLEN+10;//设置为4K
    setsockopt(m_sockfd,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));
    //发送缓冲区
    int nSendBuf=MAXLEN+10;//设置为4K
    setsockopt(m_sockfd,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));

    int nZero=0;
    setsockopt(m_sockfd,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,sizeof(int));

    setsockopt(m_sockfd,SOL_SOCKET,SO_RCVBUF,(char *)&nZero,sizeof(int));


    bool bSet=true;
    setsockopt(m_sockfd,SOL_SOCKET,SO_KEEPALIVE,(const char*)&bSet,sizeof(bool));
    if(!IsValid())
        return false;
    return true;
}

bool Socket::Bind(const int port)
{
    if(!IsValid())
        return false;

    m_address.sin_family=AF_INET;
    m_address.sin_addr.s_addr = htonl(INADDR_ANY);
    m_address.sin_port=htons(port);

    int bindReturn=bind(m_sockfd,(struct sockaddr*)&m_address,sizeof(m_address));
    if(bindReturn==-1)
        return false;

    return true;
}

bool Socket::Listen()const
{
    if(!IsValid())
        return false;
    int listenReturn=listen(m_sockfd,MAXCONNECTION);
    if(listenReturn ==-1)
        return false;
    return true;
}

bool Socket::Accept(Socket& clientSocket) const
{
    int clientaddrLength=sizeof(clientSocket.m_address);
    clientSocket.m_sockfd=::accept(m_sockfd,(struct sockaddr*)&clientSocket.m_address,(socklen_t *)&clientaddrLength);

    if(clientSocket.m_sockfd==-1)
        return false;
    return true;
}
//end server functions

bool Socket::Connect(const std::string& host,const int port)
{
    if(!IsValid())
        return false;

    m_address.sin_family=AF_INET;
    m_address.sin_port=htons(port);
    m_address.sin_addr.s_addr=inet_addr(host.c_str());

    int connectReturn=::connect(m_sockfd,(struct sockaddr*)&m_address,sizeof(m_address));
    if(connectReturn==-1)
        return false;
    return true;

}

// Data Transmission
bool Socket::Send(Socket& socket,const std::string& message) const
{
    int result=::send(socket.m_sockfd,message.c_str(),message.length(),MSG_NOSIGNAL);
    if(result==-1)
        return false;
    return true;
}

int Socket::Receive(Socket& socket,std::string& message) const
{
    char buffer[MAXRECEIVE+1];
    message.clear();
    memset(buffer,0,MAXRECEIVE+1);

    int numberRead=::recv(socket.m_sockfd,buffer,MAXRECEIVE,0);
    if(numberRead==-1)
    {
        std::cout<<"error in Socket::Receive\n";
        return 0;
    }
    else if(numberRead==0)
        return 0;
    else
    {
        message=buffer;
        return numberRead;
    }

}

void Socket::SetNonBlocking(const bool flag)
{
    if(IsValid())
    {
          int opts;

          opts = fcntl ( m_sockfd,
                 F_GETFL );

          if ( opts < 0 )
            {
              return;
            }

          if ( flag )
            opts = ( opts | O_NONBLOCK );
          else
            opts = ( opts & ~O_NONBLOCK );

          fcntl ( m_sockfd,
              F_SETFL,opts );

    }
}

bool Socket::IsValid() const
{
    //if call function socket fail,it returns -1
    return m_sockfd!=-1;
}

std::string Socket::GetAddress(){


	return NULL;

}



void AddHeadTail(char *src,int srclen,char index,char *dst,int &dstlen){


	assert(src);assert(dst);
	dst[0] = 0xfe;
	dst[1] = index & 0xff;

	int tmp = 1;
	for(int i=0;i<srclen;i++){

		dst[++tmp] = src[i];

	}

	dst[++tmp] = 0xcc;
	dst[++tmp] = 0xff;

	dstlen = tmp+1;



}

void DelHeadTail(char *src,int srclen,char *dst,int &dstlen){

	assert(src);
	assert(dst);

	memcpy(dst, &src[2], srclen-4);

	dstlen = srclen - 4;


}
