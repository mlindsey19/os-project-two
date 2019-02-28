//Mitch Lindsey
//cs4760
//2-25-19
//

#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <assert.h>
#include <stdlib.h>
#include "readfile.h"
#include "checkArgs.h"
#include "clockMemory.h"
#include <unistd.h>

unsigned int alarm(unsigned int seconds);

void incrementClock(int * , int );
void cleanSHM();
void sigHandle(int);

char * paddr;
pid_t children[20];


int main(int argc, char **argv) {

    char * infile = "input.txt";
    char * outfile = "output.txt";
    int  maxEver = 10;
    int  maxAlive = 5;
    int active = 0;
    int total = 0;
    int run = 1;
    int i;


    checkArgs(infile, outfile,  argc,  argv,  &maxEver, &maxAlive );

    int  timeIncrement;
    int timesForChildren[20][3]; // seconds, nanoseconds, duration(ns)

    timeIncrement = readfile(infile, timesForChildren); // returns value is clock incrementation time

    pid_t oss_pid = getpid();

    int * clock;
    paddr = getClockMem();
    clock = (int *) paddr;
    clock[0] = 0;
    clock[1] = 0;

    alarm(10);
    signal(SIGINT, sigHandle);
    signal(SIGALRM, sigHandle);

    do {

        incrementClock(clock, timeIncrement);

        if (clock[0] < timesForChildren[total][0] ||
            (clock[0] <= timesForChildren[total][0] && clock[1] < timesForChildren[total][1]))
            continue;


        if (total < maxEver && active < maxAlive ) {
            if ((children[total] = fork()) < 0) {
                perror("error forking new process");
                return 1;
            }

            if (getppid() == oss_pid) {
                char durstr[10];
                sprintf(durstr, "%i", timesForChildren[total][2]);
                execl("./user", "user", durstr, NULL);
            }
            total++;
            active++;
        }
        if (active == maxAlive) {
            active--;
           // wait(NULL);
        }

        if (total == maxEver) {
            for (i = 0; i < active; i++)
                wait(NULL);
            cleanSHM();
            break;
        }


    }while(run);

    cleanSHM();
    return 0;
}
void incrementClock(int * clock, int timeIncrement){
    clock[1] += timeIncrement;
    if (clock[1] > secWorthNancSec){
        clock[0]++;
        clock[1] -= secWorthNancSec;
        assert(clock[1]< 1000000000 && "too many nanoseconds");
    }
}

void cleanSHM(){

    deleteMemory(paddr);

    int i;
    for (i = 0; i <20; i++)
        kill(children[i],SIGTERM);

}

void sigHandle(int cc){
    cleanSHM();
}