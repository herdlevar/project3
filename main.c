#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "sub.h"

extern pthread_t *mySubThreads;

Queue *cpuSchedule;
Queue *ioSchedule;
Queue *finishedSchedule;

int main(int argc, char *argv[]) {
	cpuSchedule = create();
	ioSchedule = create();
	finishedSchedule = create();
	void *temp = poll(ioSchedule);
	if (temp == NULL) {
		printf("List is empty,\n");
	}

	createSubThreads();
	createCPUThreads();

	int i;
	for (i = 0; i < 4; i++) {
		pthread_join(mySubThreads[i], NULL);
	}

	return 0;
}
