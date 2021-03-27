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
        void start();
        SoHttp(int port);
    private:
        int fd;
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
    //1.创建TCP
    fd = socket(AF_INET,SOCK_STREAM,0);

    if (-1 == fd){
        perror("Socket创建失败");
    }
    //2.设置具体参数
    sever_address.sin_family =AF_INET;//协议族
    sever_address.sin_port = htons(port);//端口
    sever_address.sin_addr.s_addr = INADDR_ANY;//第一种
    //sever_address.sin_addr.s_addr = inet_addr("127.0.0.1") 第二种ip
    //3.绑定套接字
    memset(&sever_address,0,sizeof(sever_address));
    res = bind(fd,(struct sockaddr*)&sever_address,sizeof(sever_address));

    if (-1 == res){
        perror("Socket绑定失败");
        close(fd);
    }
    res = listen(fd,1000);

    if (-1 == res){
        perror("Socket监听失败");
        close(fd);
    }
    printf("SoHttp：服务器启动成功 端口在：%i \n",port);
    while (1){
        //等待连接

        clientfd = accept(fd,NULL,NULL);
        //处理连接
        handClient(fd);
        //释放资源
        close(clientfd);
    }
}
void SoHttp::handClient(int fd) {
    char buff[1024*1024] = {0}; //缓存
    int res = read(fd,buff,sizeof buff);
    if(res > 0){
        printf("成功接收到数据：%s \n",buff);
    }

}