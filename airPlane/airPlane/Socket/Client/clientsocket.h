/*
 * clientsocket.h
 *
 *  Created on: 2016年5月26日
 *      Author: root
 */

#ifndef SOCKET_CLIENTSOCKET_H_
#define SOCKET_CLIENTSOCKET_H_


#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "../socket.h"
#include <string>


class ClientSocket:public Socket
{
    public:
      ClientSocket (const std::string& host,const int port );
      virtual ~ClientSocket();

      bool Send(const std::string& message) ;
      int Receive(std::string& message) ;
      void SendFile(const std::string& fileName);
      int SendBinaryFile(const std::string &fileName,int index);
      void Close();
    private:
      std::string addheadtail(std::string& buffer);
};

#endif


#endif /* SOCKET_CLIENTSOCKET_H_ */
