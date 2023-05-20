#include "chat_server.h"
#include <sys/epoll.h>

extern Node *net_Node;
int main(){
    struct sockaddr_in client_addr;
    int sockfd=-1;
    int connfd=-1; 
    int resp_Epoll_Num=-1;
    DATA data;
    int LENGTH=sizeof(data.status)+sizeof(data.message)+sizeof(data.username)+sizeof(data.passwd);
    char str[LENGTH];

    sockfd=start_server();
    int client_len=sizeof(client_addr);
    //定义epoll
    int epfd=epoll_create(1);
    struct epoll_event epfds[1000];
    //初始化epfds
    for(int i=0;i<1000;i++){
        epfds[i].data.fd=-1;
    }
    int epfd_Pos=-1;
    epfds[++epfd_Pos].data.fd=sockfd;
    epfds[epfd_Pos].events=EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&epfds[epfd_Pos]);

    //定义保存连接客户端的服务器地址和端口号


    //while(1){
        while(1){
            
            printList(net_Node);
            resp_Epoll_Num=epoll_wait(epfd,epfds,epfd_Pos+1,30000);
            for(int i=0;i<resp_Epoll_Num;i++){
                    if(epfds[i].data.fd==sockfd){
                        //响应的文件描述符是sockfd，说明是客户端连接过来了
                        connfd=accept_client(sockfd,client_addr,client_len);
                        //把新的connfd添加到epfds中去检测
                        epfds[++epfd_Pos].data.fd=connfd;
                        epfds[epfd_Pos].events=EPOLLIN;
                        epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&epfds[epfd_Pos]);

                    }else{
                        DATA recive_Data;
                        memset(str,0,LENGTH);

                        read_Data_From_Client( epfds[i].data.fd,str,&recive_Data);
                        test_Recive_Data_From_Client(recive_Data);

                        //发送字节序

                        //strcpy(recive_Data.message,"HELLO WORLD");
                        strcpy(recive_Data.username,"zx");
                        strcpy(recive_Data.passwd,"0829");
                        recive_Data.status[0]=LOGIN_SUCCESS;
                        recive_Data.status[1]=GROUP;
                        recive_Data.status[2]=strlen(recive_Data.message);
                        recive_Data.status[3]=strlen(recive_Data.username);
                        recive_Data.status[4]=strlen(recive_Data.passwd);

                        //char send_msg[sizeof(data.status)+sizeof(data.message)+sizeof(data.username)+sizeof(data.passwd)];
                        char send_msg[LENGTH];
                        //向客户端发送消息
                        //cover_stream_From_Linux_To_Windows(recive_Data,send_msg);
                        forward_Message_To_All_Online_User(recive_Data);
                        //int len=write(connfd,send_msg,sizeof(data.status) + sizeof(data.message) + sizeof(data.username) + sizeof(data.passwd));
                        //write_Client(epfds[i].data.fd,send_msg,LENGTH);
                    }
            }

        }

/*
    while(1){
        
        
    }
*/
}