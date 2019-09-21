#include<sys/shm.h>
#include<sys/sem.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>	
typedef struct{
	int val;
	int semid;
}Storage;
void init(Storage *s)
{
	assert(s!=NULL);
	if((s->semid=semget(IPC_PRIVATE,2,IPC_CREAT|IPC_EXCL|0777))<0){
		perror("semget error");
		exit(1);
	}
	union semun{
		int val;
		struct semid_ds *ds;
		unsigned short *array;
	};
	union semun un;
	unsigned short array[2]={0,0};
	un.array=array;
	if(semctl(s->semid,0,SETALL,un)<0){
		perror("semctl error");
		exit(1);
	}
}
void destroy(Storage *s)
{
	assert(s!=NULL);
	if(semctl(s->semid,0,IPC_RMID,NULL)<0){
		perror("semctl error");
		exit(1);	
	}
}
void write(Storage *s,int val)
{
	s->val=val;
	printf("%d write %d\n",getpid(),val);
	struct sembuf ops_v[1]={{0,1,SEM_UNDO}};
	struct sembuf ops_p[1]={{1,-1,SEM_UNDO}};
	if(semop(s->semid,ops_v,1)<0){
		perror("semop error");
	}
	if(semop(s->semid,ops_p,1)<0){
		perror("semop error");
	}
}
void read(Storage *s)
{
	assert(s!=NULL);
	struct sembuf ops_p[1]={{0,-1,SEM_UNDO}};
	struct sembuf ops_v[1]={{1,1,SEM_UNDO}};
	if(semop(s->semid,ops_p,1)<0){
		perror("semop error");
	}
		printf("%d read %d\n",getpid(),s->val);

	if(semop(s->semid,ops_v,1)<0){
		perror("semop error");
	}
	
}
int main(void)
{
	int shmid;
	if((shmid=shmget(IPC_PRIVATE,sizeof(Storage),IPC_CREAT|IPC_EXCL|0777))<0)
	{
		perror("shmget error");
		exit(1);
	}
	Storage *s=(Storage*)shmat(shmid,0,0);
	if(s==(Storage*)-1){
		perror("shmat error");
		exit(1);
	}
	init(s);
	pid_t pid;
	if((pid=fork())<0){
		perror("fork error");
		exit(1);
	}else if(pid>0)
		{
			int i=1;
			for(;i<100;i++){
				write(s,i);
			}
			wait(0);
			destroy(s);
			shmdt(s);
			shmctl(shmid,IPC_RMID,NULL);
		}else //chile process
		{
			int i=1;
			for(;i<100;i++){
				read(s);
			}
			shmdt(s);
		}

	exit(0);
}
