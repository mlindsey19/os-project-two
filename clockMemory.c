//
// Created by mlind on 2/25/2019.
//

#include <sys/shm.h>
#include <stdio.h>
#include "clockMemory.h"



char * getClockMem(){
    char * paddr;
    int shmid = shmget (SHMKEY, BUFF_SZ, 0777 | IPC_CREAT);

    if (shmid == -1)
        perror("parent - error shmid");

    paddr = ( char * ) ( shmat ( shmid, 0,0));

    return paddr;
}

void deleteMemory(char * paddr){
    shmdt(paddr);
}