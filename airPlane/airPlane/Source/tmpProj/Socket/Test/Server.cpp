/*
 * Server.cpp
 *
 *  Created on: 2016年5月27日
 *      Author: root
 */

#include   <sys/socket.h>
#include   <sys/types.h>
#include   <stdlib.h>
#include   <stdio.h>
#include   <string.h>
#include   <unistd.h>
#include   <error.h>
#include   <netinet/in.h>
#include   <arpa/inet.h>
#define   SER_PORT      8080
#define   MAX_LEN       256

int main(int argc,char **argv)
{
        int     listensd,connectsd;
        struct sockaddr_in   server;
        struct sockaddr_in   client;
        char    buf[MAX_LEN] = "\0";
        FILE    *fp;
        int     opt = 1;

        if( ( listensd = socket(AF_INET,SOCK_STREAM,0) ) == -1 )
        {
                perror("socket");
                exit(1);
        }
        setsockopt(listensd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
         bzero(&server,sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(SER_PORT);
        server.sin_addr.s_addr = htonl(INADDR_ANY);
         if( bind(listensd,(struct sockaddr *)&server,sizeof(server)) < 0)
        {
                perror("Bind");
                close(listensd);
                exit(1);
        }
         if( listen(listensd,5) == -1 )
        {
                perror("listen");
                close(listensd);
                exit(1);
        }
         if( ( fp = fopen("new1.jpg","ab") ) == NULL )
        {
                perror("File");
                close(listensd);
                exit(1);
        }
        while( 1 )
        {
                int   rn ;
                int   sin_len = sizeof(client);
                if( (connectsd = accept(listensd,(struct sockaddr *)&client,(unsigned int *)&sin_len)) < 0 )
                {
                        perror("accept");
                        continue;
                }
                while( 1 )
                {
                        rn = read(connectsd,buf,MAX_LEN);
                        if(rn == 0)
                                break;
                        fwrite(buf,1,rn,fp);
                }
                close(connectsd);
                fclose(fp);
        }
        close(listensd);
        return   0;
}



