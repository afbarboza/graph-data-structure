/*
 *  list.h - interface for manipulation of adjacency
 *  list for graph data structures
 *
 *  Created on: 30 de dez. de 2020
 *  Author: Alex Barboza
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

typedef struct adjacency_list_node_t adjacency_list_node_t;

struct adjacency_list_node_t {
	int vertex_array_index;
	int weight;
	adjacency_list_node_t *next;
	adjacency_list_node_t *previous;
};

typedef struct {
	adjacency_list_node_t *head;
	adjacency_list_node_t *tail;
	int size;
} adjacency_list_t;

adjacency_list_t *list_create(void);

adjacency_list_node_t *node_create(int vertex_array_index, int weight);

void add_node_to_list(adjacency_list_node_t *node, adjacency_list_t *list);

void remove_vertex_from_list(int vertex_array_index, adjacency_list_t *list);

bool list_is_empty(adjacency_list_t *list);

void print_list(adjacency_list_t *list);

int list_size(adjacency_list_t *list);

#endif /* LIST_H_ */
