#ifndef __PV_H
#define __PV_H
extern int I(int semnums,int value);
extern void P(int semid,int semnum,int value);
extern void V(int semid,int semnum,int value);
extern void D(int semid);
#endif
