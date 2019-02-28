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


void incrementClock(int * , int );
void cleanSHM();
void sigHandle(int);
void sigchild();

char * paddr;
pid_t children[20];
int active = 0;
int * clock;
int  maxEver = 20;




int main(int argc, char **argv) {

    char * infile = "input.txt";
    char * outfile = "output.txt";
    int  maxActive = 2;
    int total = 0;
    int run = 1;
int i;
    for(i=0; i<20; i++)
        children[i] = 0;

    checkArgs(infile, outfile,  argc,  argv,  &maxEver, &maxActive );
    printf("n %i   s %i\n", maxEver, maxActive);

    maxActive = maxActive > 20 ? 20 :maxActive;
    maxEver = maxEver > 20 ? 20 :maxEver;

    int  timeIncrement;
    int timesForChildren[20][3]; // seconds, nanoseconds, duration(ns)

    timeIncrement = readfile(infile, timesForChildren); // returns value is clock incrementation time

    pid_t oss_pid = getpid();

    paddr = getClockMem();
    clock = (int *) paddr;
    clock[0] = 0;
    clock[1] = 0;

    alarm(10);
    signal(SIGINT, sigHandle);
    signal(SIGALRM, sigHandle);
    signal(SIGCHLD, sigchild);

    do {

        incrementClock(clock, timeIncrement);

        if (clock[0] < timesForChildren[total][0] ||
            (clock[0] <= timesForChildren[total][0] && clock[1] < timesForChildren[total][1]))
            continue;


        if (total < maxEver && active < maxActive ) {
            if ((children[total] = fork()) < 0) {
                perror("error forking new process");
                return 1;
            }
            char durstr[10];
            sprintf(durstr, "%i", timesForChildren[total][2]);
            if (getppid() == oss_pid)
                execl("./user", "user", durstr, NULL);
            printf("simTime: %is_%in - childpid: %u - duration: %s\n", clock[0],clock[1], children[total], durstr);
            total++;
            active++;
        }


        if (total == maxEver) {
            cleanSHM();
            break;
        }


    }while(run);


    return 0;
}
void incrementClock(int * clock, int timeIncrement){
    clock[1] += timeIncrement;
    if (clock[1] > secWorthNancSec){
        clock[0]++;
        clock[1] -= secWorthNancSec;
        assert(clock[1]<= secWorthNancSec && "too many nanoseconds");
    }
}

void cleanSHM(){
    deleteMemory(paddr);
    int i;
    pid_t pid;
    for (i=0; i < maxEver; i++)
       pid = waitpid(children[i], NULL, WNOHANG) ;
        kill(pid, SIGTERM);

}

void sigHandle(int cc){
    cleanSHM();
}
void sigchild(){
    active--;
    pid_t pid;
    pid = wait(NULL);
    printf("term pid:%u at %is %in\n",pid, clock[0], clock[1]);
};

