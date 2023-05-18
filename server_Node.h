#ifndef _SERVER_NODE_H
#define _SERVER_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IP_SIZE 16

// 定义链表节点
typedef struct Node {
    char ip[IP_SIZE];  // IP地址
    int port;  // 端口号
    int connfd;  // 连接文件描述符
    struct Node* next;  // 指向下一个节点
} Node;

// 创建新节点
Node* createNode(const char* ip, int port, int connfd);

// 添加新节点到链表
void addNode(Node** head, const char* ip, int port, int connfd);

// 删除具有特定connfd的节点
void deleteNodeByConnfd(Node** head, int connfd);

// 打印链表
void printList(Node* head);

// 删除链表
void deleteList(Node** head);



#endif
