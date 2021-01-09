#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "graph.h"

void print_vertex(vertex_t *vertex)
{
	printf("%s | ", (char *) vertex->data);
}

int main(void)
{
	/* create graph */
	graph_t *graph = graph_create();

	/* create vertices */
	vertex_t *v1 = vertex_create("1");
	vertex_t *v2 = vertex_create("2");
	vertex_t *v3 = vertex_create("3");
	vertex_t *v4 = vertex_create("4");
	vertex_t *v5 = vertex_create("5");
	vertex_t *v6 = vertex_create("6");
	vertex_t *v7 = vertex_create("7");
	vertex_t *v9 = vertex_create("9");

	/* insert vertices in graph */
	vertex_insert_at_graph(v1, graph);
	vertex_insert_at_graph(v2, graph);
	vertex_insert_at_graph(v3, graph);
	vertex_insert_at_graph(v4, graph);
	vertex_insert_at_graph(v5, graph);
	vertex_insert_at_graph(v6, graph);
	vertex_insert_at_graph(v7, graph);
	vertex_insert_at_graph(v9, graph);

	/* create the edges */
	edge_insert(v1, v5, graph);
	edge_insert(v1, v4, graph);
	edge_insert(v1, v6, graph);
	edge_insert(v1, v3, graph);
	edge_insert(v1, v7, graph);

	edge_insert(v2, v9, graph);
	edge_insert(v2, v5, graph);
	edge_insert(v2, v7, graph);

	edge_insert(v3, v1, graph);
	edge_insert(v3, v7, graph);
	edge_insert(v3, v6, graph);

	edge_insert(v4, v6, graph);
	edge_insert(v4, v5, graph);
	edge_insert(v4, v1, graph);

	edge_insert(v5, v2, graph);
	edge_insert(v5, v7, graph);
	edge_insert(v5, v4, graph);
	edge_insert(v5, v1, graph);

	edge_insert(v6, v1, graph);
	edge_insert(v6, v3, graph);
	edge_insert(v6, v4, graph);
	edge_insert(v6, v9, graph);

	edge_insert(v7, v5, graph);
	edge_insert(v7, v2, graph);
	edge_insert(v7, v1, graph);
	edge_insert(v7, v3, graph);

	edge_insert(v9, v2, graph);
	edge_insert(v9, v6, graph);

	/* inspect the graph */
	inspect_graph(graph, &print_vertex);

	/* remove elements */

	/* inspect graph */

	return 0;
}
