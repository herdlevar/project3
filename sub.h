#ifndef _sub_h
#define _sub_h

pthread_t *mySubThreads;

typedef struct job {
        int ID;
        int numPhase;
        int currentPhase;
        int **times;
} Job;

void createSubThreads();
void createCPUThreads();
void createioThreads();


#endif
