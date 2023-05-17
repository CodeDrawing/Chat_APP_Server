#include "chat_server.h"

int main(){
    struct sockaddr_in client_addr;
    int sockfd=-1;
    int connfd=-1; 
    DATA data;
    int LENGTH=sizeof(data.status)+sizeof(data.message)+sizeof(data.username)+sizeof(data.passwd);
    char str[LENGTH];

    //定义保存连接客户端的服务器地址和端口号
    Node *net_Node=NULL;
    sockfd=start_server();
    //while(1){
        int client_len=sizeof(client_addr);
        connfd=accept_client(sockfd,client_addr,client_len,net_Node);

    while(1){
        DATA recive_Data;
        memset(str,0,LENGTH);

        read_Data_From_Client(connfd,str,&recive_Data);


        //发送字节序

        strcpy(data.message,"HELLO WORLD");
        strcpy(data.username,"zx");
        strcpy(data.passwd,"0829");
        data.status[0]=LOGIN_SUCCESS;
        data.status[1]=REQ_LOGIN;
        data.status[2]=strlen(data.message);
        data.status[3]=strlen(data.username);
        data.status[4]=strlen(data.passwd);

        //char send_msg[sizeof(data.status)+sizeof(data.message)+sizeof(data.username)+sizeof(data.passwd)];
        char send_msg[LENGTH];
        //向客户端发送消息
        cover_stream_From_Linux_To_Windows(data,send_msg);

        //int len=write(connfd,send_msg,sizeof(data.status) + sizeof(data.message) + sizeof(data.username) + sizeof(data.passwd));
        write_Client(connfd,send_msg,LENGTH);
        
    }
}