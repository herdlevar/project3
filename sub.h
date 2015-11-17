#ifndef _sub_h
#define _sub_h

pthread_t *mySubThreads;

typedef struct job {
<<<<<<< HEAD
	int ID;
	int numPhase;
	int currentPhase;
	int **times;
	int completed;
=======
        int ID;
        int numPhase;
        int currentPhase;
        int **times;
>>>>>>> yoshit
} Job;

void createSubThreads();
void createCPUThreads();
void createioThreads();


#endif
