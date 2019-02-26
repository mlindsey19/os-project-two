//Mitch Lindsey
//cs4760
//2-25-19
//
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>

#include "child.h"
#include "parent.h"
#include <assert.h>


void child( const char * infilename,const char * outfilename,int *x, int  *pos)
{
    int p[128]; // for size - im sure there is a better way
    int shmid = shmget (SHMKEY, sizeof(p[128]), 0777); //shared memory

    if (shmid == -1)
    {
        perror("child: Error shmid");
    }

    pos = ( int * ) ( shmat ( shmid, 0, 0 ) ); // attach shared memory


}