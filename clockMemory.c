//
// Created by mlind on 2/25/2019.
//

#include <sys/shm.h>
#include <stdio.h>
#include "clockMemory.h"

static char * paddr;

void getClockMem(int * clock){

    int shmid = shmget (SHMKEY, sizeof(int[2]), 0777 | IPC_CREAT);

    if (shmid == -1)
        perror("parent - error shmid");

    clock = ( int * ) ( shmat ( shmid, 0,0));
}

void deleteMemory(){
    shmdt(paddr);
}