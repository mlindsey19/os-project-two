//Mitch Lindsey
//cs4760
//2-25-19
//

#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include "readfile.h"
#include "checkArgs.h"
#include "clockMemory.h"

int main(int argc, char **argv) {

    char * infile = "input.txt";
    char * outfile = "output.txt";
    int  maxEver = 4;
    int  maxAlive = 2;
    int active = 0;
    int total = 0;

    checkArgs(infile, outfile,  argc,  argv,  &maxEver, &maxAlive );

    int  timeIncrement;
    int timesForChildren[20][3]; // seconds, nanoseconds, duration(ns)

    timeIncrement = readfile(infile, timesForChildren); // returns value is clock incrementation time

    pid_t oss_pid = getpid();
    pid_t cpid;


    int  clock[2]= {0,0};
    getClockMem(clock);
    if (active < maxAlive)
        do {
            clock[1] += timeIncrement;
            if (clock[1] > 999999999){
                clock[0]++;
                clock[1] = clock[1] - 999999999;
            }

            if (getpid() == oss_pid) {
                if ((cpid = fork()) < 0) {
                    perror("error forking new process");
                    return 1;
                } else {
                    if (cpid == 0)
                        execl("/user", "user", timesForChildren[total][2], NULL);
                }
            }

        }while(0);
    return 0;
}