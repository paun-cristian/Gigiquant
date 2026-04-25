#pragma once

#include "lists.h"
#include <stdio.h>

#define NR_CITIES 3

void read_data(int argc, const char *argv[]);
void find_opportunity(int argc, const char *argv[]);
void compute_randament(NODE* head);
void print_stats(NODE* head, FILE *data_out);
void read_arbitraj(NODE* top, int argc, char *argv[]);
int min_city_height(CITY_NODE** cities);
int test_num(const char* test_name);
double calculare_randament(const NODE* node_k, const NODE* node_kminus);
double compute_average(NODE *head);
double compute_volatility(NODE *head, double average);
CITY_NODE** process_cities(FILE* data_in);