#include "server_Node.h"


// 创建新节点
Node* createNode(const char* ip, int port) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strncpy(newNode->ip, ip, IP_SIZE);
    newNode->port = port;
    newNode->next = NULL;
    return newNode;
}

// 添加新节点到链表
void addNode(Node** head, const char* ip, int port) {
    Node* newNode = createNode(ip, port);
    newNode->next = *head;
    *head = newNode;
}

// 打印链表
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("IP: %s, Port: %d\n", temp->ip, temp->port);
        temp = temp->next;
    }
}

// 删除链表
void deleteList(Node** head) {
    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

