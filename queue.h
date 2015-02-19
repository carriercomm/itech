#ifndef QUEUE_H
#define QUEUE_H

/*----- Includes without dependencies -----*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

/*----- Struct Declarations -----*/

typedef enum queue_type {
    DUMP,
    KEEP
} queue_type_t;

// List Node Struct.
typedef struct queue_node {
    void *data;
    int size;
    struct queue_node *next, *prev;
} queue_node_t;

typedef struct queue {
    queue_node_t *head, *tail, *current;
    int count, size, max;
    queue_type_t type;
    pthread_mutex_t *mutex;
    pthread_cond_t *full, *empty;
    void (*destructor)(void *);
} queue_t;

/*----- Queue Functions -----*/

queue_t *create_queue(queue_type_t type, int max, void (*destructor)(void *));
void enqueue(queue_t *q, void *data, int size);
int dequeue(queue_t *q, void *buffer, int size);
int peek(queue_t *q, void *buffer, int size);
int peek_head(queue_t *q, void *buffer, int size);
void replace(queue_t *q, void *data, int size);
void replace_head(queue_t *q, void *data, int size);
int drop(queue_t *q, void *buffer, int size);
int caught_up(queue_t *q);
int queue_head_data_size(queue_t *q);
int queue_current_data_size(queue_t *q);
void empty(queue_t *q);
void destroy_queue(queue_t *q);

/*----- Queue Node Functions -----*/

queue_node_t *create_queue_node(void *data, int size);
void destroy_queue_node(queue_node_t *node, void (*destructor)(void *));

#endif
