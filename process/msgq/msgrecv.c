#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/msg.h>
typedef struct{
    long type;//消息类型
    int start;
    int end;
}MSG;
int main(int argc,char *argv[])
{
    if(argc<3){
        printf("usage:%s key type\n",argv[0]);
        exit(1);
    }
    key_t key=atoi(argv[1]);
    long type=atoi(argv[2]);
   
    int msq_id;
    if((msq_id=msgget(key,0777))<0){
        perror("msgget error");
    }
    printf("msg id:%d\n",msq_id);
    MSG m;
    if(msgrcv(msq_id,&m,sizeof(MSG)-sizeof(long),type,IPC_NOWAIT)<0){
        perror("msgrcv error");
    }else{
      printf("type:%ld start: %d end: %d\n",m.type,m.start,m.end);
    }

       exit(0);


}
