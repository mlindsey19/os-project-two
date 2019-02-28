//
// Created by mlind on 2/25/2019.
//

#ifndef LINDSEY_2_PARENT_H
#define LINDSEY_2_PARENT_H
#define SHMKEY 63139 //shared memory key
#define BUFF_SZ (sizeof(int) * 2)
#define secWorthNancSec 999999999
char* getClockMem();
void deleteMemory(char *);
#endif //LINDSEY_2_PARENT_H
