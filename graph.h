/*
 * graph.h
 *
 *  Created on: 7 de jan. de 2021
 *      Author: alex
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct vertex_t vertex_t;
typedef struct graph_t graph_t;

struct vertex_t {
	adjacency_list_t *list;
	int degree;
};

struct graph_t {
	vertex_t *vertices;
	int number_edges;
	int number_vertices;
};

graph_t *graph_create();

void graph_free(graph_t *graph);

void graph_print(graph_t *graph);

vertex_t *vertex_create();

void vertex_insert_at_graph(vertex_t *vertex, graph_t *graph);

vertex_t *vertex_adjacent(vertex_t *v, graph_t *graph);

void edge_insert(vertex_t *u, vertex_t *v, graph_t *graph);

bool edge_exists(vertex_t *u, vertex_t *v, graph_t *graph);

void edge_remove(vertex_t *u, vertex_t *v, graph_t *graph);

#endif /* GRAPH_H_ */
