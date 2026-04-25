// Create adjacent matrix -> graph
// Adjacent matrix but not with fixed columns, meaning that
// Node with value i can have adjacents from i to k
// And node with value j can have adjacents form j to p
// Access with matrix[i] -> have to move elements (space efficient)

#pragma once

#include <stdio.h>

#define MAX_REFS 50

typedef struct MARKOV_NODE {
	float interval;
	int next_nodes_no;
	struct MARKOV_NODE** next_nodes;
} MARKOV_NODE;

typedef struct MARKOV_MATRIX {
	int* adjacent_nodes;
	int node_count;
} MARKOV_MATRIX;

MARKOV_NODE* create_markov_node();
MARKOV_MATRIX* create_markov_matrix(size_t element_count);
void create_markov_graph();
void free_markov_node();
void free_markov_graph(MARKOV_NODE* start);
void read_data_markov(FILE* data_in, int* observations, float* interval_size, int* days,
			   float* p_start, float* p_target);