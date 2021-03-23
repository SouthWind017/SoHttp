/*
 * GitHub:https://github.com/SouthWind017/
 * Created by SouthWind017 on 2021/3/23 0023.
 * @copyright (c) EasyPhp All Rights Reserved
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/sendfile.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<string.h>

class SoHttp{
    public:
        void connect();
        SoHttp(int port);
    private:
        int port;
        int sock;
        int connfd;
        int ret;
        struct sockaddr_in sever_address;
};

SoHttp::SoHttp( int port) {
    this->port = port;
    bzero(&sever_address,sizeof(sever_address));
    sever_address.sin_family = PF_INET;
    sever_address.sin_addr.s_addr = htons(INADDR_ANY);
    sever_address.sin_port = htons(this->port);
    sock = socket(AF_INET,SOCK_STREAM,0);
    assert(sock>=0);
    ret = bind(sock, (struct sockaddr*)&sever_address,sizeof(sever_address));
    assert(ret != -1);
    ret = listen(sock,1);
    assert(ret != -1);
}
void SoHttp::connect() {
    while (1) {
        struct sockaddr_in client;
        socklen_t client_addrlength = sizeof(client);
        connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
        if(connfd<0)
        {
            printf("errno\n");
        }
        else{
            char request[1024];
            recv(connfd,request,1024,0);
            request[strlen(request)+1]='\0';
            printf("%s\n",request);
            printf("successeful!\n");
            char buf[520]="HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";//HTTP响应
            int s = send(connfd,buf,strlen(buf),0);//发送响应
            //printf("send=%d\n",s);
            int fd = open("index.html",O_RDONLY);//消息体
            sendfile(connfd,fd,NULL,2500);//零拷贝发送消息体
            close(fd);
            close(connfd);
        }
    }
}