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
			if(currentJob!=NULL){
				printf("CPU executing PID %d\n",currentJob->ID);
			}
			then = time(NULL);		
		}
		else if(now-then>=currentJob->times[0][currentJob->currentPhase]){
			//Check if there are any phases left
			if(currentJob->currentPhase == currentJob->numPhase-1){
				printf("Adding PID %d to the finished queue.\n",currentJob->ID);
				add(finishedSchedule,currentJob);
			}
			// Next phase is CPU
			else if(currentJob->times[1][currentJob->currentPhase+1]==0){
				printf("Adding PID %d to the CPU queue.\n",currentJob->ID);
				currentJob->currentPhase++;
				add(cpuSchedule,currentJob);	
			}
			//Next phase is IO
			else{
				printf("Adding PID %d to the I/O queue.\n",currentJob->ID);
				currentJob->currentPhase++;
				add(ioSchedule,currentJob);
			}
			currentJob = NULL;
		}
		now = time(NULL);
	}			
	return NULL;
}
