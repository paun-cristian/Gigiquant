#include <stdio.h>
#include <stdlib.h>
#include "markov.h"

MARKOV_NODE* create_markov_node() {
	MARKOV_NODE* new = (MARKOV_NODE* )malloc(sizeof(MARKOV_NODE));
	if (!new)
		exit(-1);

	new->interval = 0.0;
	new->next_nodes_no = 0;
	new->next_nodes = (MARKOV_NODE** )malloc(MAX_REFS * sizeof(MARKOV_NODE* ));
	if (!new->next_nodes) {
		free(new);
		exit(-1);
	}
	return new;
}

MARKOV_MATRIX* create_markov_matrix(size_t element_count) {
	MARKOV_MATRIX* matrix = (MARKOV_MATRIX* )calloc(1, sizeof(MARKOV_MATRIX));
	if (!matrix)
		exit(-1);

	matrix->node_count = 0;
	matrix->adjacent_nodes = calloc(element_count, sizeof(int));
	if (!matrix->adjacent_nodes) {
		free(matrix);
		exit(-1);
	}

	return matrix;
}

void read_data_markov(FILE* data_in, int* observations, float* interval_size, int* days,
					  float* p_start, float* p_target) {

	if (fscanf(data_in, "%d", observations) != 1) {
		exit(-1);
	}

	fscanf(data_in, "%f", interval_size);
	fscanf(data_in, "%d", days);
	fscanf(data_in, "%f", p_start);
	fscanf(data_in, "%f", p_target);

	MARKOV_MATRIX* matrix = create_markov_matrix(*observations);

	float from_interval = 0.0, to_interval = 0.0;
	fscanf(data_in, "%f", &from_interval);
		
	for (size_t i = 1; i < *observations; ++i) {
		fscanf(data_in, "%f", &to_interval);
		int from_node = (int)(from_interval - *p_start) / (int)(*interval_size); // transposing the interval so size is more manageable
		int from_node_count = matrix[from_node].node_count++;
		int to_node = (int)(to_interval - *p_start) / (int)(*interval_size);

		matrix[from_node].adjacent_nodes[from_node_count] = to_node;
		from_interval = to_interval;	
	}

}

void create_markov_graph(int argc, const char* argv[]) {
	MARKOV_NODE* start = create_markov_node();
	if (argc < 3)
	exit(-1);
	
	FILE *data_in = fopen(argv[1], "rt");
	FILE* data_out = fopen(argv[2], "wt");
	
	if (data_in == NULL) {
		fclose(data_out);
		exit(-1);
	}
	if (data_out == NULL) {
		fclose(data_in);
		exit(-1);
	}
	
	size_t observations = 0; 
	int days = 0;
	float interval_size = 0.0, p_start = 0.0, p_target = 0.0;
	
	read_data_markov(data_in, &observations, &interval_size, &days, &p_start, &p_target);
	start->interval = p_start;
}