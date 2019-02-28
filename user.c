//Mitch Lindsey
//cs4760
//2-25-19
//
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "time.h"

#include "user.h"
#include "clockMemory.h"


int main(int argc, char * argv[])
{
    int  *simclock;
    int duration = atoi(argv[1]);
    int stopTime0 = 0;
    int stopTime1 =0;
    int shmid = shmget (SHMKEY, BUFF_SZ, 0777); //shared memory

    if (shmid == -1)
        perror("child - error shmid");

    simclock = ( int * ) ( shmat ( shmid, 0, 0));

    stopTime0 = simclock[0];
    stopTime1 = (simclock[1] + duration);
    stopTime1 = stopTime1 > secWorthNancSec ? stopTime1 - secWorthNancSec : stopTime1;
    assert(stopTime1< 1000000000 && "too many nanoseconds");


    while(simclock[0] <= stopTime0 && simclock[1] < stopTime1 );
    printf("pid: %u sim clock: %is %in - terminating now\n",  getpid(),simclock[0], simclock[1]);


    exit(19);
}