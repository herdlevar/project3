#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "sub.h"
#include "queue.h"

#define thread_count 4

void *myThread(void *theArg);
void freeJob(Job *theJob);
Job *createJob();

extern Queue *finishedSchedule;
extern Queue *cpuSchedule;
extern Queue *ioSchedule;

pthread_t *mySubThreads;
int jobID = 0;

void createSubThreads() {
	int i;
	mySubThreads = (pthread_t *) malloc(sizeof(pthread_t)*thread_count);
	for (i = 0; i < thread_count; i++) {
		pthread_create(&mySubThreads[i], NULL, myThread, NULL);
	}
}

void *myThread(void *theArg) {
	
	time_t now = time(NULL);
	time_t then = now;

	while (1) {
		// Create jobs and add to the ready queue here
		Job *temp = createJob();
		if(temp->times[1][0]==0){
			add(cpuSchedule, temp);
		}
		else{
			add(ioSchedule, temp);
		}
		printf("Creating a job with PID %d\n",temp->ID);
		while (then - now < 3) {
			// Chech finish queue here
			temp = poll(finishedSchedule);
			if (temp != NULL) {
				printf("Job PID %d freed!\n",temp->ID);
				freeJob(temp); 
			}
			then = time(NULL);
		}
		now = time(NULL);
	}			
		
	return NULL;
}

Job *createJob() {
	Job *job = (Job *) malloc(sizeof(Job));
	job->ID = ++jobID;
	job->currentPhase = 0;
	job->numPhase = rand()%5+1;
	job->times = (int **) malloc(sizeof(int *)*2);
	int i;
	for (i = 0; i < 2; i++) {
		job->times[i] = (int *) malloc(sizeof(int)*job->numPhase);
	}
	for (i = 0; i < job->numPhase; i++) {
		job->times[0][i] = rand()%10+1;
		job->times[1][i] = rand()%2;
	}
	return job;
}

void freeJob(Job *theJob) {
	int i;
	for (i = 0; i < 2; i++) {
		free(theJob->times[i]);
	}
	free(theJob->times);
	free(theJob);
}
