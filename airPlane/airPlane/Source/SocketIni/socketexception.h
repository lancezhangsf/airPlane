/*
 * socketexception.h
 *
 *  Created on: 2016年5月26日
 *      Author: root
 */

#ifndef SOCKET_SOCKETEXCEPTION_H_
#define SOCKET_SOCKETEXCEPTION_H_



#include <string>

class SocketException
{
    public:
        SocketException ( std::string description ) : m_description( description ) {};
        ~SocketException (){};

        std::string Description() { return m_description; }

 private:
        std::string m_description;
};



#endif /* SOCKET_SOCKETEXCEPTION_H_ */
