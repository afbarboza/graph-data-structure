/*
 *  list.c - implementation of double linked list
 *  used at graph data structure
 *
 *  Created on: 30 de dez. de 2020
 *  Author: Alex Barboza
 */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

adjacency_list_t *list_create(void)
{
	adjacency_list_t *list = (adjacency_list_t *) malloc(sizeof(adjacency_list_t));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}

adjacency_list_node_t *node_create(int vertex_array_index, int weight)
{
	adjacency_list_node_t *node = (adjacency_list_node_t *) malloc(sizeof(adjacency_list_node_t));
	node->vertex_array_index = vertex_array_index;
	node->weight = weight;
	node->next = NULL;
	node->previous = NULL;
	return node;
}

bool list_is_empty(adjacency_list_t *list)
{
	return (list->head == NULL && list->tail == NULL);
}

void add_node_to_list(adjacency_list_node_t *node, adjacency_list_t *list)
{
	/* increase list size by one */
	list->size += 1;

	/* adding to empty list */
	if (list_is_empty(list)) {
		list->head = node;
		list->tail = node;
		return;
	}

	/* list already has elements */
	node->previous = list->tail;
	list->tail->next = node;
	list->tail = node;
}

bool is_head_list(int vertex_array_index, adjacency_list_t *list)
{
	int head_vertex_array_index = list->head->vertex_array_index;
	return (head_vertex_array_index == vertex_array_index);
}

void remove_head_list(int vertex_array_index, adjacency_list_t *list)
{
	adjacency_list_node_t *new_head = list->head->next;
	list->head = new_head;

	if (new_head != NULL) {
		new_head->previous = NULL;
	}
}

bool is_tail_list(int vertex_array_index, adjacency_list_t *list)
{
	int tail_vertex_array_index = list->tail->vertex_array_index;
	return (tail_vertex_array_index == vertex_array_index);
}

void remove_tail_list(int vertex_array_index, adjacency_list_t *list)
{
	adjacency_list_node_t *new_tail = list->tail->previous;
	new_tail->next = NULL;
	list->tail = new_tail;
}

void remove_vertex_from_list(int vertex_array_index, adjacency_list_t *list)
{
	/* trying to remove from empty list */
	if (list_is_empty(list)) {
		return;
	}

	/* handle especial case with lists with one element only */
	if (list_size(list) == 1) {
		list->head = NULL;
		list->tail = NULL;
		list->size = 0;
		return;
	}

	/* trying to remove the head */
	if (is_head_list(vertex_array_index, list)) {
		remove_head_list(vertex_array_index, list);
		list->size -= 1;
		return;
	}

	/* trying to remove the tail */
	if (is_tail_list(vertex_array_index, list)) {
		remove_tail_list(vertex_array_index, list);
		list->size -= 1;
		return;
	}

	/* trying to remove from middle */
	adjacency_list_node_t *tmp = list->head;
	while (tmp != NULL) {
		int current_vertex_index = tmp->vertex_array_index;
		if (current_vertex_index == vertex_array_index) {
			/* we found the element which must be removed */
			adjacency_list_node_t *previous = tmp->previous;
			adjacency_list_node_t *next = tmp->next;

			previous->next = next;
			next->previous = previous;

			list->size -= 1;

			return;
		}

		/* we did not found yet, keep looking ahead */
		tmp = tmp->next;
	}
}

void print_list(adjacency_list_t *list)
{
	/* trying to print empty list */
	if (list_is_empty(list)) {
		return;
	}

	adjacency_list_node_t *tmp = list->head;
	while (tmp != NULL) {
		printf("%d\t", tmp->vertex_array_index);
		tmp = tmp->next;
	}
}

int list_size(adjacency_list_t *list)
{
	return list->size;
}
