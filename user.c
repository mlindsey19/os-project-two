//Mitch Lindsey
//cs4760
//2-25-19
//
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>

#include "user.h"
#include "clockMemory.h"


void main(int argc, char ** argv)
{
    int * clock;
    int duration = (int) *argv[1];
    int stopTime[2];
    int shmid = shmget (SHMKEY, sizeof(int[2]), 0777); //shared memory

    if (shmid == -1)
        perror("child - error shmid");

     clock = ( int * ) ( shmat ( shmid, 0,0));

     stopTime[0] = clock[0];
     stopTime[1] = clock[1] + duration;

     printf("%i.%i", clock[0],clock[1]);





}