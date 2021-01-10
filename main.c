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
	printf("%s | ", (char *) vertex->data);
}

int main(void)
{
	int i = 0;
	queue_t *queue = queue_create();

	srand(time(NULL));
	for (i = 0; i < 30; i++) {
		int *data = (int *) malloc(sizeof(int));
		*data = rand() % 100;
		printf("%d inserting %d\n", i, *data);
		queue_insert(queue, data);
	}

	for (i = 0; i < 30; i++) {
		int *data = (int *) queue_remove(queue);
		print_element(data);
		free(data);
		printf(" [%d] \n", queue->size);
	}

	queue_free(queue);

	return 0;
}
