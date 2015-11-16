#include "queue.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct myNode {
	Node *next;
	void *data;
} Node;

Queue *create() {
	Queue *queue = malloc(sizeof(Queue));
	Node *temp = malloc(sizeof(Node));
	temp->next = NULL;
	queue->front = queue->back = temp;
	pthread_mutex_init(&queue->frontLock, NULL);
	pthread_mutex_init(&queue->backLock, NULL);
	return queue;
}

void add(Queue *theQueue, void *theData) {
	Node *newNode = malloc(sizeof(Node));
	newNode->data = theData;
	newNode->next = NULL;
	pthread_mutex_lock(&theQueue->backLock);
	theQueue->back->next = newNode;
	theQueue->back = newNode;
	pthread_mutex_unlock(&theQueue->backLock);
}

void *poll(Queue *theQueue) {
	pthread_mutex_lock(&theQueue->frontLock);
	Node *temp = theQueue->front;
	Node *newFront = temp->next;
	if (newFront == NULL) {
		pthread_mutex_unlock(&theQueue->frontLock);
		return NULL;
	}
	void *data = theQueue->front->next->data;
	theQueue->front = newFront;
	pthread_mutex_unlock(&theQueue->frontLock);
	free(temp);
	return data;
}

