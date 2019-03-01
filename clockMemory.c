//
// Created by mlind on 2/25/2019.
//

#include <sys/shm.h>
#include <stdio.h>
#include "clockMemory.h"

static int shmid;

char * getClockMem(){
    char * paddr;
     shmid = shmget (SHMKEY, BUFF_SZ, 0777 | IPC_CREAT);

    if (shmid == -1)
        perror("parent - error shmid");

    paddr = ( char * ) ( shmat ( shmid, 0,0));

    return paddr;
}

void deleteMemory(char * paddr){
    int er;

    shmctl(shmid, IPC_RMID, NULL);
    if((er = shmdt(paddr)) == -1){
        perror("err shmdt:");
    }
}