#include <stdio.h>
#include "data.h"
#include "tree.h"
#include "markov.h"

int main(int argc, char *argv[]) {
	int test_no = test_num(argv[1]);
	if (test_no == 0)
		return 0;

	if (test_no >= 1 && test_no <= 5)
		read_data(argc, argv);

	if (test_no >= 6 && test_no <= 10)
		find_opportunity(argc, argv);

	if (test_no >= 11 && test_no <= 15)
		create_tree(argc, argv);

	// if (test_no >= 16 && test_no <= 20)
	// 	create_markov_graph(argc, argv);

	return 0;
}