/*
 * serversocket.cpp
 *
 *  Created on: 2016年5月26日
 *      Author: root
 */

#include "serversocket.h"
#include <string.h>
#include "../fileoperator.h"
#include "../socketexception.h"

ServerSocket::ServerSocket(const int port) {
	if (!Socket::Create()) {
		throw SocketException("Could not create server socket.");
	}

	if (!Socket::Bind(port)) {
		throw SocketException("Could not bind to port.");
	}

	if (!Socket::Listen()) {
		throw SocketException("Could not listen to socket.");
	}
}

ServerSocket::~ServerSocket() {
}

void ServerSocket::Accept(Socket& socket) {
	if (!Socket::Accept(socket)) {
		throw SocketException("Could not accept socket.");
	}
}

void ServerSocket::RecvFile(Socket* clientSocket) {
	std::string message;
	FileOperator fileOperator;
	//using IP address to name received file
	fileOperator.Open("1.txt", WRITE_CREATE_MODE);
	int recvBytes;
	int writeBytes;

	while ((recvBytes = Socket::Receive(*clientSocket, message)) > 0) {

		std::cout << "message length: " << message.size() << "\n";
		writeBytes = fileOperator.WriteToFile(message);
		// std::cout<<"writeBytes: "<<writeBytes<<"\n";
		std::cout << "message context: " << message << "\n";
#if 1
		if (writeBytes < recvBytes) {
			perror("write to file failed");
			Socket::Send(*clientSocket, "Error when server receiving file.");
			return;
		}

		//if all bytes has been wrote
		if (recvBytes == 0 || recvBytes != MAXRECEIVE)
			break;
#endif
	}

	if (recvBytes >= 0)
		Socket::Send(*clientSocket, "server has received your file.");
}

int ServerSocket::RecvBinaryFile(Socket* clientSocket) {
#if 0
	std::ofstream out("./1.jpg", std::fstream::out | std::fstream::binary);
	std::string message;
	int ret = 0;
	while ((ret = Socket::Receive(*clientSocket, message)) > 0) {

		out.write(message.c_str(), sizeof(char) * ret);

	}

	out.close();
	std::cout << "文件接受完毕！" << std::endl;
	//closesocket (clientSocket);
#endif
	FILE *fp;
	char buf[MAXLEN + 4] = "\0";
	char dstbuf[MAXLEN] = "\0";
	int dstlen = 0;
	static int fileindex = 0;
	char filename[10] = { 0 };
	++fileindex;
	bool issuccess = false;
	sprintf(filename, "%d.jpeg", fileindex);
	bool isover = false;

	while (1) {
		bzero(buf, MAXLEN + 4);
		isover = false;
		int rn = read(clientSocket->m_sockfd, buf, MAXLEN + 4);
		printf("rn :%d\n", rn);
		if (rn == 0) {
			remove(filename);
			--fileindex;
			printf("current fileindex... :%d",fileindex);
			isover = false;
			break;
		}else{

			if ((buf[0] == HEAD) && (buf[rn - 1] == TAIL)) {
				printf("handle.........................................!\n");
				DelHeadTail(buf, rn, dstbuf, dstlen);
				fwrite(dstbuf, 1, dstlen, fp);
				continue;
			} else if (buf[0] == ACK[0]) {
				std::cout << "=======start crt file==========" << std::endl;
				if ((fp = fopen(filename, "ab")) == NULL) {
					perror("File");
					close(clientSocket->m_sockfd);
					return 1;
					//exit(1);
				}
				continue;
			} else if (buf[0] == NCK[0]) {
				std::cout << "=============end 4K================="
						<< std::endl;
				isover = true;
				break;

			}

			while ((buf[rn - 2] != 0xffffffcc) && (buf[rn - 1] != 0xffffffff)) {
				//printf("buf[0]:%x; buf[rn - 1]:%x ;buf[rn]:%x\n", buf[0], buf[rn - 1],buf[rn]);
				int tmp_rn = read(clientSocket->m_sockfd, &buf[rn],
						MAXLEN + 4 - rn);
				printf("tmp_rn :%d\n", rn);
				if (tmp_rn > 0) {
					rn = rn + tmp_rn;
				}
			}
			//buf[rn ]= '\0';
			printf("buf[0]:%x; buf[rn - 1]:%x ;rn:%d\n", buf[0], buf[rn - 1],
					rn);
			printf("handle.........................................!\n");
			DelHeadTail(buf, rn, dstbuf, dstlen);
			fwrite(dstbuf, 1, dstlen, fp);

		}
	}

	if (isover) {
		return 0;   //success;
	} else {
		return 1;   //failure;
	}
}

