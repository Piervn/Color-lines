#include "kulki.h"


int isFull(queue* Q)
{
    return (Q->size == Q->capacity);
}

int isEmpty(queue* Q)
{
    return (Q->size == 0);
}

queue* createQueue(int capacity)
{
    queue* Q = (queue*)malloc(sizeof(queue));
    Q->capacity = capacity;
    Q->front = Q->size = 0;

    // This is important, see the enqueue
    Q->rear = capacity - 1;
    Q->array = (int*)malloc(Q->capacity * sizeof(int));
    return Q;
}

void enqueue(queue* Q, int item)
{
    if (isFull(Q))
        return;
    Q->rear = (Q->rear + 1) % Q->capacity;
    Q->array[Q->rear] = item;
    Q->size = Q->size + 1;
    //printf("%d enqueued to queue\n", item);
}

int dequeue(queue* Q)
{
    if (isEmpty(Q)) return INT_MIN;
    int item = Q->array[Q->front];
    Q->front = (Q->front + 1) % Q->capacity;
    Q->size = Q->size - 1;
    return item;
}



