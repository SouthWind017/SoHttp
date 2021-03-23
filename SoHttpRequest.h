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

class SoHttp{
    public:
        void connect();
        SoHttp(int port);
    private:
        int fd;
        int res;
        int clientfd;
        struct sockaddr_in sever_address;
};

SoHttp::SoHttp(int port) {

    //1.创建TCP
    fd = socket(AF_INET,SOCK_STREAM,0);

    if (-1 == fd){
        printf("SoHttp：Socket创建失败 \n");
        perror("Socket创建失败");
        return;
    }

    //2.设置具体参数
    sever_address.sin_family =AF_INET;//协议族
    sever_address.sin_port = htons(port);//端口
    sever_address.sin_addr.s_addr = INADDR_ANY;//第一种
    //inet_addr("127.0.0.1") 第二种ip
    //3.绑定套接字
    res = bind(fd,(struct sockaddr*)&sever_address,sizeof(sever_address));

    if (-1 == res){
        printf("SoHttp：Socket绑定失败 \n");
        perror("Socket绑定失败");
        close(fd);
        return;
    }
    res = listen(fd,1000);

    if (-1 == res){
        printf("SoHttp：Socket监听失败 \n");
        perror("Socket监听失败");
        close(fd);
        return;
    }

    printf("SoHttp：服务器启动成功 端口在： %i \n",port);

}

void SoHttp::connect() {
    while (1){
        //等待连接
        clientfd = accept(fd,NULL,NULL);
        //处理连接
        close(clientfd);
    }
}