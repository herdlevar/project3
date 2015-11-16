#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "sub.h"
#include "queue.h"

#define thread_count 8

void *mycpuThread(void *theArg);

extern Queue *finishedSchedule;
extern Queue *cpuSchedule;
extern Queue *ioSchedule;

pthread_t *myCPUThreads;

void createCPUThreads() {
	int i;
	myCPUThreads = (pthread_t *) malloc(sizeof(pthread_t)*thread_count);
	for (i = 0; i < thread_count; i++) {
		pthread_create(&myCPUThreads[i], NULL, mycpuThread, NULL);
	}
}

void *mycpuThread(void *theArg) {
	Job *currentJob = NULL;
	
	time_t now = time(NULL);
	time_t then = now;
	
	while (1) {
		if(currentJob==NULL){
			currentJob = poll(cpuSchedule);
			then = time(NULL);		
		}
		else if(then-now>=currentJob->times[0][currentJob->currentPhase]){
			//Check if there are any phases left
			if(currentJob->currentPhase == currentJob->numPhase-1){
				add(finishedSchedule,currentJob);
			}
			// Next phase is CPU
			else if(currentJob->times[1][currentJob->currentPhase+1]==0){
				currentJob->currentPhase++;
				add(cpuSchedule,currentJob);	
			}
			//Next phase is IO
			else{
				currentJob->currentPhase++;
				add(ioSchedule,currentJob);
			}
			currentJob = NULL;
		}
		now = time(NULL);
	}			
	return NULL;
}
