/*
 * queue.c
 *
 *  Created on: 10 de jan. de 2021
 *      Author: alex
 */


#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

queue_t *queue_create()
{
	queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
	queue->size = 0;
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

void queue_free(queue_t *queue)
{
	queue_node_t *tmp = queue->head;
	while (tmp != NULL) {
		queue_node_t *next = tmp->next;
		free(tmp);
		tmp = next;
	}

	free(queue);
}

void queue_insert(queue_t *queue, void *data)
{
	/* create internal node to store the needed data */
	queue_node_t *new_node = (queue_node_t *) malloc(sizeof(queue_node_t *));
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;

	/* handle special case of empty queue */
	if (queue_is_empty(queue)) {
		queue->head = new_node;
		queue->tail = new_node;
		queue->size++;
		return;
	}

	new_node->prev = queue->tail;
	queue->tail->next = new_node;
	queue->tail = new_node;
	queue->size++;
}

void *queue_remove(queue_t *queue)
{
	if (queue_is_empty(queue)) {
		fprintf(stderr, "ERROR: trying to remove from empty queue\n");
		return NULL;
	}

	queue_node_t *old_head = queue->head;
	void *data = old_head->data;

	if (queue_size(queue) == 1) {
		queue->head = NULL;
		queue->tail = NULL;
		queue->size = 0;
		free(old_head);
		return data;
	}

	queue_node_t *new_head = old_head->next;
	new_head->prev = NULL;
	queue->head = new_head;
	queue->size--;
	free(old_head);
	return data;
}

int queue_size(queue_t *queue)
{
	return queue->size;
}

bool queue_is_empty(queue_t *queue)
{
	return queue->size == 0;
}

void queue_print(queue_t *queue, void (*print_element)(void *data))
{
	queue_node_t *tmp = queue->head;
	while (tmp != NULL) {
		(*print_element)(tmp->data);
		tmp = tmp->next;
	}
}
