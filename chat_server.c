#include "chat_server.h"

int main(){
    struct sockaddr_in client_addr;
    int sockfd=-1;
    int connfd=-1; 
    char str[MAX_MESSAGE_LENGTH];

    sockfd=start_server();
    //while(1){
        int client_len=sizeof(client_addr);
        connfd=accept_client(sockfd,client_addr,client_len);

    while(1){
        printf("进入。。。。。\n");
 
        memset(str,0,MAX_MESSAGE_LENGTH);
        int read_count=read(connfd,str,MAX_MESSAGE_LENGTH);
        printf("recive message: ");
        DATA dataee;
        memcpy(&dataee,str,sizeof(dataee));
        for (int i = 0; i < 5; i++)
        {
            dataee.status[i]=ntohl(dataee.status[i]);
            /* code */
        }
        printf("dataee.status[0] %d\n",dataee.status[0]);
        printf("dataee.status[1] %d\n",dataee.status[1]);
        printf("dataee.status[2] %d\n",dataee.status[2]);
        printf("dataee.status[3] %d\n",dataee.status[3]);
        printf("dataee.status[4] %d\n",dataee.status[4]);
        
        printf("message ============== %s\n",dataee.message);
        printf("username ============== %s\n",dataee.username);
        printf("passwd ============== %s\n",dataee.passwd);
        if(read_count==0){
            write_Log("客户端离开\n");
            exit(-1);
        }
        printf("%s\n",str);

        memset(str,0,MAX_MESSAGE_LENGTH);

        //发送字节序
        DATA data;
        strcpy(data.message,"HELLO WORLD");

        strcpy(data.username,"zx");

        strcpy(data.passwd,"0829");
        data.status[0]=LOGIN_SUCCESS;
        data.status[1]=REQ_LOGIN;
 
        data.status[2]=strlen(data.message);
        data.status[3]=strlen(data.username);
        data.status[4]=strlen(data.passwd);
        int LENGTH=sizeof(data.status)+sizeof(data.message)+sizeof(data.username)+sizeof(data.passwd);
        //char send_msg[sizeof(data.status)+sizeof(data.message)+sizeof(data.username)+sizeof(data.passwd)];
        char send_msg[LENGTH];
        //向客户端发送消息
        cover_stream_From_Linux_To_Windows(data,send_msg);

        //int len=write(connfd,send_msg,sizeof(data.status) + sizeof(data.message) + sizeof(data.username) + sizeof(data.passwd));
        int len=write_Client(connfd,send_msg,LENGTH);
        if(len<0){
            write_Log("发送数据失败\n");
            exit(SERVER_ERR);
        }else{
            write_Log("发送数据成功\n");
        }
    }
}