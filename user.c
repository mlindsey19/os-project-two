//Mitch Lindsey
//cs4760
//2-25-19
//
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "user.h"
#include "clockMemory.h"


int main(int argc, char * argv[])
{
    int  *clock;
    int duration = atoi(argv[1]);
    int stopTime0 = 0;
    int stopTime1 =0;
    int shmid = shmget (SHMKEY, BUFF_SZ, 0777); //shared memory

    if (shmid == -1)
        perror("child - error shmid");

    clock = ( int * ) ( shmat ( shmid, 0, 0));

    stopTime0 = clock[0];
    stopTime1 = (clock[1] + duration);
    stopTime1 = stopTime1 > secWorthNancSec ? stopTime1 - secWorthNancSec : stopTime1;
    assert(stopTime1< 1000000000 && "too many nanoseconds");


    printf("%i.%i\n", clock[0],clock[1]);

    printf("%i.%i\n", stopTime0,stopTime1);
    sleep(2);
    clock = ( int * ) ( shmat ( shmid, 0, 0));
    printf("%i.%i\n", clock[0],clock[1]);





    while(clock[0] <= stopTime0 && clock[1] < stopTime1 );
    exit(1);
    return 0;
}