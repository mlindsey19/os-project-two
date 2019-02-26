//Mitch Lindsey
//cs4760
//2-25-19
//

#include <stdio.h>
#include "readfile.h"
#include "checkArgs.h"

int main(int argc, char **argv) {

    char * infile = "input.txt";
    char * outfile = "output.txt";
    int * maxEver = 0;
    int * maxAlive = 0;

    checkArgs(infile, outfile,  argc,  argv,  maxEver, maxAlive );

    int  timeIncrement;
    int timesForChildren[20][3]; // seconds, nanoseconds, duration(ns)

    timeIncrement = readfile(infile, timesForChildren); // returns value is clock incrementation time


    return 0;
}