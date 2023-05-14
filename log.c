#include "log.h"

int write_Log(LOG_MESSAGE msg){
    time_t current_time;
    time(&current_time);
    int fd=open("LOG.txt",O_WRONLY|O_APPEND|O_CREAT,0664);
    if(fd<0){
        return LOG_WRITE_FAIL;
    }
    char *str=strcat(ctime(&current_time),msg);
    int result=write(fd,str,strlen(str));
    if(result>0){
        return LOG_WRITE_SUCCESS;
    }else{
        return LOG_WRITE_FAIL;
    }
}