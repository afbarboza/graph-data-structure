/*
 *  graph.h - graph type data structure manipulation interface
 *
 *  Created on: 07 de dez. de 2020
 *  Author: Alex Barboza
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

typedef struct vertex_t vertex_t;
typedef struct graph_t graph_t;

struct vertex_t {
	adjacency_list_t *list;
	int degree;
	int array_index;
	void *data;
};

struct graph_t {
	vertex_t **vertices;
	int number_edges;
	int number_vertices;
};

graph_t *graph_create();

void graph_free(graph_t *graph);

void graph_print(graph_t *graph);

vertex_t *vertex_create(void *data);

void vertex_insert_at_graph(vertex_t *vertex, graph_t *graph);

vertex_t **vertex_adjacent(vertex_t *v, graph_t *graph);

void vertex_free(vertex_t *vertex);

void edge_insert(vertex_t *u, vertex_t *v, graph_t *graph);

bool edge_exists(vertex_t *u, vertex_t *v, graph_t *graph);

void edge_remove(vertex_t *u, vertex_t *v, graph_t *graph);

void inspect_graph(graph_t *graph, void (*print_vertex)(vertex_t *vertex));

#endif /* GRAPH_H_ */
