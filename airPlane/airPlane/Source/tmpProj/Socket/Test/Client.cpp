/*
 * server.cpp
 *
 *  Created on: 2016年5月27日
 *      Author: root
 */

#include   <stdio.h>
#include   <sys/socket.h>
#include   <stdlib.h>
#include   <sys/types.h>
#include   <string.h>
#include   <unistd.h>
#include   <netinet/in.h>
#include   <arpa/inet.h>
#include   <netdb.h>
#define   SER_PORT      8080
#define   MAX_LEN      256

int main(int argc, char **argv) {
	int sd, rn;
	struct sockaddr_in client, server;
	char buf[MAX_LEN];
	FILE *fq;
	int len, opt = 1;

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(SER_PORT);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (connect(sd, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("Connect");
		close(sd);
		exit(1);
	}
	if ((fq = fopen("1.jpg", "rb")) == NULL) {
		perror("File open");
		close(sd);
		exit(1);
	}
	bzero(buf, sizeof(buf));
	while (!feof(fq)) {
		len = fread(buf, 1, MAX_LEN, fq);
		if (len != write(sd, buf, len)) {
			perror("write");
			break;
		}
	}
	close(sd);
	fclose(fq);
	return 0;
}
