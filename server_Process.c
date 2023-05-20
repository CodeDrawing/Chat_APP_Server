#include "server_Process.h"
extern Node *net_Node;
/***
 * 返回sockfd
*/
int start_server(){
    struct sockaddr_in server_add;
    memset(&server_add,0,sizeof(server_add));
    server_add.sin_addr.s_addr=INADDR_ANY;
    server_add.sin_family=AF_INET;
    server_add.sin_port=htons(8085);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        write_Log("SOCKFD创建失败\n");
        exit(SERVER_ERR);
    }else{
        write_Log("SOCKFD创建成功\n");
    }
    //绑定
    if(bind(sockfd,(struct sockaddr *)&server_add,sizeof(server_add))!=0){
        write_Log("服务器绑定地址失败\n");
        exit(SERVER_ERR);
    }else{
        write_Log("服务器绑定地址成功\n");
    }
    //监听
    if(listen(sockfd,5)!=0){
        write_Log("监听端口失败\n");
        exit(SERVER_ERR);
    }else{
        write_Log("监听端口成功\n");
    }
    return sockfd;
    
}

int accept_client(int sockfd,struct sockaddr_in client_addr,int client_len){
    int connfd=accept(sockfd,(struct sockaddr*)&client_addr,&client_len);
    if(connfd<0){
        write_Log("服务器同意连接失败\n");
        exit(SERVER_CONNECT_ERR);
    }else{
        char str[128];
        sprintf(str,"服务器连接成功，来自IP: %s",inet_ntoa(client_addr.sin_addr));
        addNode(&net_Node,inet_ntoa(client_addr.sin_addr),client_addr.sin_port,connfd);
        write_Log(str);
    }
    return connfd;
}
void cover_stream_From_Linux_To_Windows(DATA data,char * send_msg){
        uint32_t status_0=htonl(data.status[0]);
        uint32_t status_1=htonl(data.status[1]);
        uint32_t status_2=htonl(data.status[2]);
        uint32_t status_3=htonl(data.status[3]);
        uint32_t status_4=htonl(data.status[4]);
//        char send_mes[sizeof(data.status)+sizeof(data.message)+sizeof(data.username)+sizeof(data.passwd)];
        memset(send_msg,0,sizeof(send_msg));
        char *ptr = send_msg;
        memcpy(ptr, &status_0, sizeof(status_0));
        ptr += sizeof(status_0);
        memcpy(ptr, &status_1, sizeof(status_1));
        ptr += sizeof(status_1);
        memcpy(ptr, &status_2, sizeof(status_2));
        ptr += sizeof(status_2);
        memcpy(ptr, &status_3, sizeof(status_3));
        ptr += sizeof(status_3);
        memcpy(ptr, &status_4, sizeof(status_4));
        ptr += sizeof(status_4);
        memcpy(ptr, data.message, sizeof(data.message));
        ptr += sizeof(data.message);
        memcpy(ptr, data.username, sizeof(data.username));
        ptr += sizeof(data.username);
        memcpy(ptr, data.passwd, sizeof(data.passwd));
        ptr += sizeof(data.passwd);
    
}

void write_Client(int connfd,char *send_msg,int len){
     int write_Len=write(connfd,send_msg,len);
     if(write_Len<0){
            write_Log("发送数据失败\n");
            exit(SERVER_ERR);
        }else{
            write_Log("发送数据成功\n");
    }
}
void read_Data_From_Client(int connfd,char* recv_msg,DATA *recive_Data){
    int recive_Data_Size=sizeof(*recive_Data);
    int read_count=recv(connfd,recv_msg,recive_Data_Size,0);
    if(read_count==0){
        printf("客户端断开连接\n");
        write_Log("客户端离开\n");
    }
    memcpy(recive_Data,recv_msg,recive_Data_Size);
    for (int i = 0; i < 5; i++)
    {
        recive_Data->status[i]=ntohl(recive_Data->status[i]);
        /* code */
    }
}

void test_Recive_Data_From_Client(DATA recive_Data){
    printf("recive_Data.status[0] %d\n",recive_Data.status[0]);
    printf("recive_Data.status[1] %d\n",recive_Data.status[1]);
    printf("recive_Data.status[2] %d\n",recive_Data.status[2]);
    printf("recive_Data.status[3] %d\n",recive_Data.status[3]);
    printf("recive_Data.status[4] %d\n",recive_Data.status[4]);
    
    printf("message ============== %s\n",recive_Data.message);
    printf("username ============== %s\n",recive_Data.username);
    printf("passwd ============== %s\n",recive_Data.passwd);
}
void forward_Message_To_All_Online_User(DATA data){
    int LENGTH=sizeof(data.status)+sizeof(data.message)+sizeof(data.username)+sizeof(data.passwd);
    char str[LENGTH];
    cover_stream_From_Linux_To_Windows(data,str);
    Node* temp = net_Node;
    while (temp != NULL) {
        printf("向: IP: %s, Port: %d, Connfd: %d 发送数据  \n", temp->ip, temp->port, temp->connfd);
        write_Client(temp->connfd,str,LENGTH);
        temp = temp->next;
    }
}