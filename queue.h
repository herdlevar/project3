#include <pthread.h>
#ifndef _queue_h
#define _queue_h

typedef struct myNode Node;

typedef struct myQueue {
	Node *front;
	Node *back;
	pthread_mutex_t frontLock;
	pthread_mutex_t backLock;
} Queue;

Queue *create();
void add(Queue *theQueue, void *theData);
void *poll(Queue *theQueue);
void *peek(Queue *theQueue);

#endif
