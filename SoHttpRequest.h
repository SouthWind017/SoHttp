/*
 * GitHub:https://github.com/SouthWind017/
 * Created by SouthWind017 on 2021/3/23 0023.
 * @copyright (c) EasyPhp All Rights Reserved
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>

class SoHttp{
    public:
        void start();
        SoHttp(int port);
    private:
        int sock;
        int port;
        int res;
        int clientfd;
        struct sockaddr_in sever_address;
        void handClient(int fd);//处理请求
};

SoHttp::SoHttp(int port) {
    this->port = port;
}

void SoHttp::start() {
    bzero(&sever_address, sizeof(sever_address));
    sever_address.sin_family = PF_INET;
    sever_address.sin_addr.s_addr = htons(INADDR_ANY);
    sever_address.sin_port = htons(port);
    sock = socket(AF_INET,SOCK_STREAM,0);
    assert(sock>=0);
    res = bind(sock, (struct sockaddr*)&sever_address,sizeof(sever_address));
    assert(res != -1);
    res = listen(sock,1);
    assert(res != -1);
    printf("SoHttp：成功接成功启动在端口：%i\n",port);
    while (1){

        struct sockaddr_in client;
        socklen_t client_addrlength = sizeof(client);
        clientfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
        handClient(clientfd);
    }


}
void SoHttp::handClient(int fd) {
    char buff[1024*1024] = {0}; //缓存
    int res = read(fd,buff,sizeof buff);
    if(res > 0){
        printf("SoHttp：成功接收到数据：%s \n",buff);
    }
    //解析请求
    char fileName[20]={0};
    sscanf(buff,"GET /%s",fileName);
    printf("SoHttp：请求的文件名：%s \n",fileName);

    char* mime = NULL;

    if(strstr(fileName,".html")){
        mime = "text/html";
    } else if(strstr(fileName,".jpg")){
        mime = "image/jpg";
    }

    char response[1024*1024]={0};
    sprintf(response,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n",mime);
    int responselen = strlen(response);
    int fileFd = open(fileName,O_RDONLY);
    int fileLen = read(fileFd,response+responselen, sizeof(response)-responselen);
    write(fd,response,responselen+fileLen);
    close(fd);
    close(fileFd);
    sleep(1);
}