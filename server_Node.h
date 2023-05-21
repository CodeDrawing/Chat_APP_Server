#ifndef _SERVER_NODE_H
#define _SERVER_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "status.h"


// 创建新节点
Node* createNode(const char* ip, int port, int connfd);

// 添加新节点到链表
void addNode( const char* ip, int port, int connfd);

// 删除具有特定connfd的节点
void deleteNodeByConnfd(int connfd);

// 打印链表
void printList();

// 删除链表
void deleteList();



#endif
