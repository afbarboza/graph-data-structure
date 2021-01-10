#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "list.h"
#include "graph.h"
#include "queue.h"

typedef struct vertex_data_t vertex_data_t;

struct vertex_data_t {
	bool visited;
	char *label;
};

void print_element(void *data)
{
	int *value = (int *) data;
	printf(" %d  ", *value);
}

void print_vertex(vertex_t *vertex)
{
	vertex_data_t *data =  (vertex_data_t *) vertex->data;
	printf("%s | ", data->label);
}

void explore_vertex(vertex_t *vertex)
{
	vertex_data_t *data =  (vertex_data_t *) vertex->data;
	data->visited = true;
	print_vertex(vertex);
}

bool is_explored(vertex_t *vertex)
{
	vertex_data_t *data =  (vertex_data_t *) vertex->data;
	return data->visited;
}

void breadth_first_search(graph_t *graph, vertex_t *start_vertex)
{
	/* mark starting vertex as explored */
	explore_vertex(start_vertex);

	/* create queue and initialize it with start vertex */
	queue_t *queue = queue_create();
	queue_insert(queue, start_vertex);

	int i = 0;
	int degree_v = 0;
	vertex_t **neighbors = NULL;
	while (!queue_is_empty(queue)) {
		vertex_t *v = (vertex_t *) queue_remove(queue);

		/* for each edge in adjacency list of current vertex v, do */
		degree_v = v->degree;
		neighbors = vertex_adjacent(v, graph);
		for (i = 0; i < degree_v; i++) {

			/* if some neighbor of v is not explored, then */
			if (!is_explored(neighbors[i])) {
				/* mark the vertex as explore */
				explore_vertex(neighbors[i]);

				/* insert the current neighbor at the end of our queue */
				queue_insert(queue, neighbors[i]);
			}
		}
	}

}

int main(void)
{
	int i = 0;
	graph_t *graph = graph_create();

	vertex_data_t *data1 = (vertex_data_t *) malloc(sizeof(vertex_data_t));
	data1->visited = false;
	data1->label = "s";

	vertex_data_t *data2 = (vertex_data_t *) malloc(sizeof(vertex_data_t));
	data2->visited = false;
	data2->label = "a";

	vertex_data_t *data3 = (vertex_data_t *) malloc(sizeof(vertex_data_t));
	data3->visited = false;
	data3->label = "b";

	vertex_data_t *data4 = (vertex_data_t *) malloc(sizeof(vertex_data_t));
	data4->visited = false;
	data4->label = "c";

	vertex_data_t *data5 = (vertex_data_t *) malloc(sizeof(vertex_data_t));
	data5->visited = false;
	data5->label = "d";

	vertex_data_t *data6 = (vertex_data_t *) malloc(sizeof(vertex_data_t));
	data6->visited = false;
	data6->label = "e";

	vertex_t *vs = vertex_create(data1);
	vertex_t *va = vertex_create(data2);
	vertex_t *vb = vertex_create(data3);
	vertex_t *vc = vertex_create(data4);
	vertex_t *vd = vertex_create(data5);
	vertex_t *ve = vertex_create(data6);

	vertex_insert_at_graph(vs, graph);
	vertex_insert_at_graph(va, graph);
	vertex_insert_at_graph(vb, graph);
	vertex_insert_at_graph(vc, graph);
	vertex_insert_at_graph(vd, graph);
	vertex_insert_at_graph(ve, graph);

	edge_insert(vs, vb, graph);
	edge_insert(vs, ve, graph);
	edge_insert(vb, vc, graph);
	edge_insert(vc, va, graph);
	edge_insert(va, ve, graph);
	edge_insert(ve, vd, graph);
	edge_insert(vc, vd, graph);

	breadth_first_search(graph, vs);
	graph_free(graph);
	return 0;
}
