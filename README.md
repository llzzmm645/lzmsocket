# lzmsocket.h 使用指南

## 前置知识

地址：IP地址、或者是域名

端口：0~65535的一个数字

注意：

* 若函数返回套接字类型，则失败时会返回-1；
若函数返回布尔类型，则成功时返回true，失败时会返回false

* 编译时请加上参数 `-lws2_32`
  
* 请先运行服务端，再运行客户端

## 服务器端和客户端共用函数

``` c++
SOCKET init();
```

该函数无参数，用于初始化套接字（**必须在所有函数之前运行**）

会返回服务器端或客户端套接字

---

``` c++
bool sendmsg(SOCKET s, char buf[], int size);
```

该函数有三个参数，分别是对方的套接字，传输的数据缓冲区，缓冲区长度（可以通过sizeof(缓冲区)获取）

该函数将一段消息发送至另一端

---

``` c++
bool getmsg(SOCKET s, char buf[], int size);
```

参数定义详见sendmsg函数

该函数获取另一端发来的消息

---

``` c++
int closesocket(SOCKET s);
```

该函数有一个参数，将要关闭的套接字

该函数关闭套接字

---

``` c++
bool cleansocket();
```

该函数清理windows套接字资源（**必须在所有套接字关闭之后运行**）

---

``` c++
int getlasterror();
```

该函数获取运行错误的原因

## 服务器端

``` c++
bool init_server(SOCKET s,int port);
```

该函数有两个参数，分别是服务器端套接字以及端口号

该函数将某一端口绑定至套接字

---

``` c++
SOCKET getclient(SOCKET s,SOCKADDR_IN *client_addr);
```

该函数有两个参数，分别是服务器端套接字以及客户端地址类型所存入的地址

会返回连接至服务器的客户端套接字

## 客户端

``` c++
bool connect_server(SOCKET s, char addr[], int port)
```

该函数有三个参数，分别是客户端套接字、服务器地址与端口

该函数将客户端连接至服务端

## 示例程序

服务器端：

``` c++
#include "lzmsocket.h"
#include <stdio.h>
int main(){
    SOCKET s=init();
    if(s==SOCKET_ERROR){
        printf("Error");
        cleansocket();
        return 0;
    }
    if(!init_server(s,8080)){
        printf("Error");
        closesocket(s);
        cleansocket();
        return 0;
    }
    SOCKADDR_IN caddr;
    SOCKET c=getclient(s,&caddr);
    if(c==INVALID_SOCKET){
        printf("Error");
        closesocket(s);
        cleansocket();
        return 0;
    }
    char buf[]="this is a test";
    sendmsg(c,buf,sizeof(buf));
    printf("OK");
    closesocket(s);
    closesocket(c);
    cleansocket();
    return 0;
}
```

客户端：

``` c++
#include "lzmsocket.h"
#include <stdio.h>
int main(){
    SOCKET s=init();
    if(!connect_server(s,"127.0.0.1",8080)){
        printf("Error");
        return 0;
    }
    char buf[80]={0};
    getmsg(s,buf,sizeof(buf));
    printf("%s",buf);
    closesocket(s);
    cleansocket();
    return 0;
}
```
