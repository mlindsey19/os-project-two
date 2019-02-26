//Mitch Lindsey
//cs4760
//2-25-19
//


#include <stdio.h>
#include <stdlib.h>

int  readfile(const char * infile,  int array[20][3])
{
    int i, j; // iterator
    int eof;
    char * buf;
    int timeIncrement;

    FILE * fptr = fopen(infile, "r");
    if (!fptr){
        perror("could not open file");
        return 1;
    }
        eof = fscanf(fptr,"%i", &timeIncrement);

    for (i=0; i<20; i++)
        for(j=0; j < 3; j++){
            if (eof < 0)
                break;
            eof = fscanf(fptr,"%i", &array[i][j]);
        }

    return  timeIncrement; //
}
