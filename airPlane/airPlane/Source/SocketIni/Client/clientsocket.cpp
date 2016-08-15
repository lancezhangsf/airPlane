/*
 * clientsocket.cpp
 *
 *  Created on: 2016年5月26日
 *      Author: root
 */

#include "clientsocket.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include "../fileoperator.h"
#include "../socketexception.h"

ClientSocket::ClientSocket(const std::string& host, const int port) {
	if (!Socket::Create())
		throw SocketException("Could not create client socket.");
	if (!Socket::Connect(host, port))
		throw SocketException("Could not connect to port.");
}

ClientSocket::~ClientSocket() {
}

bool ClientSocket::Send(const std::string& message) {
	return Socket::Send(static_cast<Socket&>(*this), message);
}

int ClientSocket::Receive(std::string& message) {
	return Socket::Receive(static_cast<Socket&>(*this), message);
}

void ClientSocket::SendFile(const std::string& fileName) {
	FileOperator fileOperator;
	fileOperator.Open(fileName.c_str(), "rb");
	std::string buffer;
	int readBytes;
	//addheadtail(filename);
	// std::ostringstream filename;
	// filename << "filename:" << fileName;

	//  Send(filename.str().c_str());

#if 1
	while ((readBytes = fileOperator.ReadFromFile(buffer)) > 0) {
		if (Send(buffer) < 0) {
			perror("failed to send file");
			break;
		}
	}
#endif
}

int ClientSocket::SendBinaryFile(const std::string& fileName, int index) {
#if 0
	std::ifstream in(fileName.c_str(), std::fstream::in | std::fstream::binary);
	char buf1[1024] = {0};
	while (!in.eof())
	{
		in.read(buf1, sizeof(buf1));
		int ret = Send(buf1);
		if (ret <0) {
			std::cout << "Send Into error: " << buf1 << std::endl;
			break;
		}
	}
	in.close();
#endif
	FILE *fq;
	char buf[MAXLEN] = "\0";
	char dstbuf[MAXLEN + 4] = "\0";
	int dstlen = 0;
	int len = 0;
	if ((fq = fopen(fileName.c_str(), "rb")) == NULL) {
		perror("File open");
		close(this->m_sockfd);
		exit(1);
	}
	bzero(buf, sizeof(buf));
	int tmp_index = index;
	system("date");
	while (!feof(fq)) {
		memset(buf, '\0', sizeof(buf));
		len = fread(buf, 1, MAXLEN, fq);
#if 0
		for (int i = 0; i < len; i++) {
			printf("%4x ", buf[i]);
		}
		std::cout << std::endl;
#endif
		bzero(dstbuf, MAXLEN + 4);
		AddHeadTail(buf, len, tmp_index, dstbuf, dstlen);
		//printf("buf[0]:%0x,buf[rn-1]:%0x,buf[rn]:%0x  dstlen:%d\n", dstbuf[0], dstbuf[dstlen - 2],dstbuf[dstlen - 1],dstlen);
#if 0
		for (int i = 0; i < dstlen; i++) {
			printf("%4x ", dstbuf[i]);
		}
		std::cout << std::endl;
#endif
		if (dstlen != write(this->m_sockfd, dstbuf, dstlen)) {
			perror("write");
			return 1;
		}
	}
	system("date");
	fclose(fq);
	return 0;
}

void ClientSocket::Close() {

	shutdown(this->m_sockfd, SHUT_WR);

}
