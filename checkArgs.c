//Mitch Lindsey
//cs4760
//2-21-19
//
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "checkArgs.h"


static void helpMenu(){
    printf("\n\t\tHelp\n");
    printf("Default - max: 4, live: 2\n");
    printf("-h show help menu\n");
    printf("-n max child processes ever\n");
    printf("-s max child alive at one time\n");
    printf("-i specify input file name\n");
    printf("-o specify output file name\n");
}

int checkArgs(char * inFilename[], char * outFilename[], int argc, char **argv, int * maxEver, int * maxAlive ){

    int c,i;

    opterr = 0;

    while ((c = getopt(argc, argv, "hi:o:s:n:")) != -1)
        switch (c) {
            case 'h':
                helpMenu();
                break;
            case 'n':
                *maxEver =  atoi(optarg);
                break;
            case 's':
                *maxAlive =  atoi(optarg);
                break;
            case 'i':
                *inFilename = optarg;
                break;
            case 'o':
                *outFilename = optarg;
                break;
            case '?':
                if (optopt == 'i' || optopt == 'o')
                    fprintf(stderr, "Options -o and -i require an argument.\n");
                else if (isprint (optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }

    for (i = optind; i < argc; i++)
        fprintf(stderr,"Non-option argument %s\n", argv[i]);
    return 0;
}