#include "server_Node.h"

extern Node *net_Node;

// 创建新节点
Node* createNode(const char* ip, int port, int connfd) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    strncpy(newNode->ip, ip, IP_SIZE);
    newNode->port = port;
    newNode->connfd = connfd;
    newNode->next = NULL;

    return newNode;
}

// 添加新节点到链表
void addNode(Node** head, const char* ip, int port, int connfd) {
    Node* newNode = createNode(ip, port, connfd);
    newNode->next = net_Node;
    net_Node = newNode;
}

// 删除具有特定connfd的节点
void deleteNodeByConnfd(Node** head, int connfd) {
    Node* temp = net_Node, *prev;

    // 如果头节点本身就持有要删除的 connfd
    if (temp != NULL && temp->connfd == connfd) {
        *head = temp->next;
        free(temp);
        return;
    }

    // 搜索要删除的 connfd
    while (temp != NULL && temp->connfd != connfd) {
        prev = temp;
        temp = temp->next;
    }

    // 如果connfd未在链表中找到
    if (temp == NULL) return;

    // 将节点从链表中断开
    prev->next = temp->next;

    free(temp);  // 释放内存
}

// 打印链表
void printList() {
    Node* temp = net_Node;
    while (temp != NULL) {
        printf("IP: %s, Port: %d, Connfd: %d\n", temp->ip, temp->port, temp->connfd);
        temp = temp->next;
    }
}

// 删除链表
void deleteList() {
    Node* current = net_Node;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    net_Node = NULL;
}
