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
	int p = 5;
	int l = 6;
	add(ioSchedule, &p);
	add(ioSchedule, &l);
	printf("%d\n", *(int *)poll(ioSchedule));
	printf("%d\n", *(int *)poll(ioSchedule));
	void *temp = poll(ioSchedule);
	if (temp == NULL) {
		printf("List is empty,\n");
	}

	createSubThreads();

	int i;
	for (i = 0; i < 4; i++) {
		pthread_join(mySubThreads[i], NULL);
	}

	return 0;
}
