#ifndef _STATUS_H
#define _STATUS_H
//头文件
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>




#define MAX_MESSAGE_LENGTH 1024

// 常量定义：是否已读消息
#define HAS_READ_MESSAGE 1
#define NOT_READ_MESSAGE 2

// 常量定义：是否在线
#define ONLINE 6
#define NOT_ONLINE 7

// 常量定义：登录状态
#define LOGINED 11
#define UNLOGIN 12
#define LOGIN_SUCCESS 13
#define LOGIN_FAIL 14

// 常量定义：发送消息类
#define GROUP 16
#define PEOPLE 17

// 常量定义：错误码
//服务器
#define SERVER_WRITE_ERR 21
#define SERVER_READ_ERR 22
#define SERVER_CONNECT_ERR 23
#define SERVER_QUERY_ERR 24
#define SERVER_INSERT_ERR 25
#define SERVER_ERR 26
#define SERVER_START_ERROR 27
//客户端
#define CLIENT_CONNECT_ERR 31
#define CLIENT_WRITE_ERR 32
#define CLIENT_READ_ERR 33


// 常量定义：请求类型码
#define REQ_LOGIN 41
#define REQ_SEND_GROUP 42
#define REQ_SEND_PEOPLE 43
#define REQ_LOGINOUT 44
#define REQ_HISTORY 45
#define REQ_QUERY_LIST 46
#define REQ_REGISTER 47

// 常量定义：回应类型码
#define RES_SEND_GROUP 61
#define RES_SEND_PEOPLE 62
#define RES_ERROR 63
#define RES_OPERATE_SUCCESS 64
#define RES_OPERATE_FAIL 65
#define RES_REGISTER_SUCCESS 66
#define RES_REGISTER_FAIL 67
#define RES_EXIT_SUCCESS 68
#define RES_EXIT_FAIL 69
#define RES_LOGIN_SUCESS 70
#define RES_LOGIN_FAIL 71

// 常量定义：日志码
#define LOG_WRITE_SUCCESS 81
#define LOG_WRITE_FAIL 82


typedef  char USERNAME[30];
typedef char PASSWD[30];
typedef char MSG[MAX_MESSAGE_LENGTH];
typedef int STATUS;
typedef char *LOG_MESSAGE;



typedef struct sendMessage{
  STATUS status[5];
  MSG message;
  USERNAME username;
  PASSWD passwd;
}DATA;
#endif