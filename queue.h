/*
 * queue.h
 *
 *  Created on: 10 de jan. de 2021
 *      Author: alex
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>

typedef struct queue_node_t queue_node_t;
typedef struct queue_t queue_t;

struct queue_node_t {
	void *data;
	struct queue_node_t *next;
	struct queue_node_t *prev;
};

struct queue_t {
	int size;
	struct queue_node_t *head;
	struct queue_node_t *tail;
};

queue_t *queue_create();
void queue_free(queue_t *queue);
void queue_insert(queue_t *queue, void *data);
void *queue_remove(queue_t *queue);
int queue_size(queue_t *queue);
bool queue_is_empty(queue_t *queue);
void queue_print(queue_t *queue, void (*print_element)(void *data));

#endif /* QUEUE_H_ */
