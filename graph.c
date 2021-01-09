/*
 *  graph.c - implementation of graph data structure
 *
 *  Created on: 07 de dez. de 2020
 *  Author: Alex Barboza
 */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "graph.h"
#include "list.h"

graph_t *graph_create()
{
	graph_t *new_graph = (graph_t *) malloc(sizeof(graph_t));
	new_graph->number_edges = 0;
	new_graph->number_vertices = 0;
	new_graph->vertices = NULL;
	return new_graph;
}

vertex_t *vertex_create(void *data)
{
	vertex_t *new_vertex = (vertex_t *) malloc(sizeof(vertex_t));
	new_vertex->list = list_create();
	new_vertex->degree = 0;
	new_vertex->array_index = -1;
	new_vertex->data = data;
	return new_vertex;
}

void vertex_insert_at_graph(vertex_t *vertex, graph_t *graph)
{
	int new_graph_size = graph->number_vertices + 1;
	graph->vertices = (vertex_t **) realloc(graph->vertices, new_graph_size * sizeof(vertex_t *));
	graph->vertices[graph->number_vertices] = vertex;
	vertex->array_index = graph->number_vertices;
	graph->number_vertices = new_graph_size;
}

vertex_t **vertex_adjacent(vertex_t *v, graph_t *graph)
{
	/* step 1: get the list of adjacent vertices from adjacency list */
	adjacency_list_t *adjacents = v->list;

	/* step 2: create array to store all the vertices which will be found */
	int number_adjacents = 0;
	vertex_t **adjacent_vertices = NULL;

	/* step 3: for each vertex found on the list, add its address to the  array  */
	adjacency_list_node_t *tmp = adjacents->head;
	while (tmp != NULL) {
		adjacent_vertices = (vertex_t **) reallocarray(adjacent_vertices, number_adjacents + 1, sizeof(vertex_t *));
		adjacent_vertices[number_adjacents] = graph->vertices[tmp->vertex_array_index];
		number_adjacents++;
		tmp = tmp->next;
	}

	/* step 4: return the final array */
	return adjacent_vertices;
}

void edge_insert(vertex_t *u, vertex_t *v, graph_t *graph)
{
	/* get reference to the list */
	adjacency_list_t *list_u = u->list;
	adjacency_list_t *list_v = v->list;

	/*we cannot allow multigraphs here  */
	adjacency_list_node_t *adjacent_to_u = list_u->head;
	while (adjacent_to_u != NULL) {
		if (adjacent_to_u->vertex_array_index == v->array_index) {
			fprintf(stderr, "ERROR: parallel edges are not allowed in the current implementation\n");
			return;
		}
		adjacent_to_u = adjacent_to_u->next;
	}

	adjacency_list_node_t *adjacent_to_v = list_v->head;
	while (adjacent_to_v != NULL) {
		if (adjacent_to_v->vertex_array_index == u->array_index) {
			fprintf(stderr, "ERROR: parallel edges are not allowed in the current implementation\n");
			return;
		}
		adjacent_to_v = adjacent_to_v->next;
	}

	/* make v adjacent to u */
	adjacency_list_node_t *node_v = node_create(v->array_index, INT_MAX);
	add_node_to_list(node_v, list_u);

	/* make u adjacent to v */
	adjacency_list_node_t *node_u = node_create(u->array_index, INT_MAX);
	add_node_to_list(node_u, list_v);

	graph->number_edges++;
}

bool edge_exists(vertex_t *u, vertex_t *v, graph_t *graph)
{
	bool u_is_connected_to_v = false;
	bool v_is_connected_to_u = false;

	adjacency_list_node_t *adjacent_to_u = u->list->head;
	while (adjacent_to_u != NULL) {
		if (adjacent_to_u->vertex_array_index == v->array_index) {
			u_is_connected_to_v = true;
		}
	}

	adjacency_list_node_t *adjacent_to_v = v->list->head;
	while (adjacent_to_v != NULL) {
		if (adjacent_to_v->vertex_array_index == u->array_index) {
			v_is_connected_to_u = true;
		}
	}

	if (u_is_connected_to_v == true && v_is_connected_to_u == false) {
		fprintf(stderr, "ERROR: inconsistency found while probing for edges\n");
		exit(EXIT_FAILURE);
	}

	if (u_is_connected_to_v == false && v_is_connected_to_u == true) {
			fprintf(stderr, "ERROR: inconsistency found while probing for edges\n");
			exit(EXIT_FAILURE);
	}

	return (u_is_connected_to_v && v_is_connected_to_u);
}

void edge_remove(vertex_t *u, vertex_t *v, graph_t *graph)
{
	/* get reference to the list */
	adjacency_list_t *list_u = u->list;
	adjacency_list_t *list_v = v->list;

	adjacency_list_node_t *adjacent_to_u = list_u->head;
	while (adjacent_to_u != NULL) {
		if (adjacent_to_u->vertex_array_index == v->array_index) {
			remove_vertex_from_list(v->array_index, list_u);
		}

		adjacent_to_u = adjacent_to_u->next;
	}

	adjacency_list_node_t *adjacent_to_v = list_v->head;
	while (adjacent_to_v != NULL) {
		if (adjacent_to_v->vertex_array_index == u->array_index) {
			remove_vertex_from_list(u->array_index, list_v);
			graph->number_edges--;
		}

		adjacent_to_v = adjacent_to_v->next;
	}
}

void inspect_graph(graph_t *graph, void (*print_vertex)(vertex_t *vertex))
{
	int i = 0;
		vertex_t **vertices = graph->vertices;

		for (i = 0; i < graph->number_vertices; i++) {
			vertex_t *tmp = vertices[i];
			(*print_vertex)(tmp);

			adjacency_list_t *list = tmp->list;
			adjacency_list_node_t *neighbor = list->head;
			while (neighbor != NULL) {
				int neighbor_index = neighbor->vertex_array_index;
				(*print_vertex)(vertices[neighbor_index]);
				neighbor = neighbor->next;
			}
			printf("\n");
		}

		printf("number of nodes: %d\n", graph->number_vertices);
		printf("number of edges: %d\n", graph->number_edges);
}
