/*
 gcc -o pv.o -c pv.c±àÒë³ÉÄ£¿é
*/

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<sys/sem.h>
#include"pv.h"
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
int I(int semnums,int value)
{
	int semid;
	semid=semget(IPC_PRIVATE,semnums,IPC_CREAT|IPC_EXCL|0777);
	if(semid<0){
	return -1;
	}
	union semun un;
	unsigned short *array=(unsigned short*)calloc(semnums,sizeof(unsigned short));
	int i;
	for(i=0;i<semnums;i++){
		array[i]=value;
	}
	un.array=array;
	if(semctl(semid,0,SETALL,un)<0){
		perror("semctl error");
		return -1;
	}
	free(array);
	return semid;
	
}
 void P(int semid,int semnum,int value)
{
	assert(value>=0);
	struct sembuf ops[]={{semnum,-value,SEM_UNDO}};
	if(semop(semid,ops,sizeof(ops)/sizeof(struct sembuf))<0){
	perror("semop error");
	}
}
 void V(int semid,int semnum,int value)
{
	assert(value>=0);
	struct sembuf ops[]={{semnum,value,SEM_UNDO}};
	if(semop(semid,ops,sizeof(ops)/sizeof(struct sembuf))<0){
	perror("semop error");
	}
}
 void D(int semid)
{
	if(semctl(semid,0,IPC_RMID,NULL)<0){
		perror("semctl error");
	}
}


