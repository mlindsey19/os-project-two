//
// Created by mlind on 2/25/2019.
//

#ifndef LINDSEY_2_PARENT_H
#define LINDSEY_2_PARENT_H
#define SHMKEY 0225201 //shared memory key
#define BUFF_SZ (sizeof(int) * 2)
#define secWorthNancSec 1000000000
char* getClockMem();
void deleteMemory(char *);
#endif //LINDSEY_2_PARENT_H
