#ifndef _SERVER_PROCESS_H
#define _SERVER_PROCESS_H

#include "status.h"
#include "server_Node.h"
/**
 * 开启服务器，包括创建sockfd，设置服务器地址，并且绑定，监听端口，并返回服务器sockfd
*/
int start_server();
/**
 * 同意连接请求，并返回acceptfd
*/
int accept_client(int sockfd,struct sockaddr_in client_addr,int client_len);
/***
 * 该函数功能是将DATA类型的结构体转换成可用用作网络发送通信的字节流。
 * 返回一个字符串首地址，根据传入的结构体。
*/
void cover_stream_From_Linux_To_Windows(DATA data,char * send_msg);
/**
 * 发送数据到客户端，没有写入的数据个数，需要send_mes和connfd
*/
void write_Client(int connfd,char *send_msg,int len);

/**
 * 将客户端发送过来的数据转化为Linux上的字节流,并存入到DATA结构体中
 * 
*/
void read_Data_From_Client(int connfd,char* recv_msg,DATA *recive_Data,int epfd,int i);

/**
 * 测试收到的DATA数据
*/
void test_Recive_Data_From_Client(DATA recive_Data);
/**
 * 收到群发消息，就走次函数，遍历所有链表，并发送数据。
*/
void forward_Message_To_All_Online_User(int connfd,DATA data);
#endif