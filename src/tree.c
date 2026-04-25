#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

static bool last_pair = false;

TREENODE* create_tree_node() {
	TREENODE* new = (TREENODE* )calloc(1, sizeof(TREENODE));
	if (!new)
		exit(-1);

	new->left = NULL;
	new->right = NULL;
	new->stock_no = 0;
	new->stocks = (StockList* )calloc(MAX_SYMS, sizeof(StockList));
	if (!new->stocks) {
		free(new);
		exit(-1);
	}

	return new;
}
/*
Introduce in a char[] the order of node placing, as in
lrl, lll, rrr etc.
we know that for a node k the number of movements for it is the number of days
we reduce the time complexity from O(n^2) - iteration on values[][]
to O(n) - iteration through char[] and building the tree
so first 10 chars will be for day 1
next 10 for day 2
and so on
*/
void create_tree(int argc, const char* argv[]) {
	TREENODE* root = create_tree_node();

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
	char buffer[MAX_BUFFER_SIZE];
	char movements[MAX_SYMS * MAX_DAYS] = {0};
	int action_nr = 0, days = 0;
	double prev_day[MAX_DAYS] = {0};
	double curr_day[MAX_DAYS] = {0};

	while (fgets(buffer, MAX_BUFFER_SIZE, data_in) != NULL) {
		if (!isdigit(buffer[0])) {
			insert_symbols(buffer, root);
		}
		else {
			insert_values(buffer, movements, prev_day, curr_day, action_nr, days);
			days++;
		}
	}

	for (int i = 0; i < root->stock_no; ++i)
		disperse_actions(root, movements, days - 1, 0, i);

	bool pairs[MAX_SYMS][MAX_SYMS] = {false};
	last_pair = false;

	for (int i = 0; i < root->stock_no; ++i)
		show_matches(root, data_out, movements + i * MAX_DAYS,
					 root->stocks[i].symbol,pairs, root->stocks[i].sym_id, 0, days - 1);

	free_tree(root);
	fclose(data_in);
	fclose(data_out);
}

void insert_symbols(char buffer[], TREENODE* root) {
	char *p = strtok(buffer, ",");
	if (!p)
		exit(-1);

	int action_nr = 0;
	while (p) {
		p[strcspn(p, "\r\n")] = '\0';
		root->stocks[action_nr].sym_id = action_nr;
		///printf("%d - %s\n", action_nr, p); -> good
		strcpy(root->stocks[action_nr++].symbol, p);
		p = strtok(NULL, ",");
	}
	root->stock_no = action_nr;
}

void insert_values(char buffer[], char movements[], double prev_day[],
				   double curr_day[], int action_nr, int day) {

	char *p = strtok(buffer, ",");
	if (!p)
		exit(-1);

	if (day == 0) {
		int stock_nr = 0;
		while (p) {
			curr_day[stock_nr++] = atof(p);
			p = strtok(NULL, ",");
		}
	}
	else {
		int stock_nr = 0;
		while (p) {
			prev_day[stock_nr] = curr_day[stock_nr];
			curr_day[stock_nr] = atof(p);
			if (curr_day[stock_nr] >= prev_day[stock_nr]) { //right
				movements[stock_nr * MAX_DAYS + (day - 1)] = 'r';
			}
			else { // left
				movements[stock_nr * MAX_DAYS + (day - 1)] = 'l';
			}
			stock_nr++;
			p = strtok(NULL, ",");
		}
	}
}

// building the tree
void disperse_actions(TREENODE* root, char movements[],
					  int days, int curr_day, int pos) {
	if (curr_day >= days)
		return;

	if (root->stocks[pos].symbol[0] == '\0')
		return;
	
	if (movements[pos * MAX_DAYS + curr_day] == 'r') {
		if (root->right == NULL)
			root->right = create_tree_node();
		int curr_node_stock_no = root->stocks[pos].sym_id;

		if (root->right->stocks[curr_node_stock_no].symbol[0] == '\0')
			root->right->stock_no++;
		strcpy(root->right->stocks[curr_node_stock_no].symbol,
			   root->stocks[pos].symbol);
		root->right->stocks[curr_node_stock_no].sym_id = root->stocks[pos].sym_id;
		disperse_actions(root->right, movements, days,
						 curr_day + 1, pos);
	}
	else {
		if (root->left == NULL)
			root->left = create_tree_node();
		int curr_node_stock_no = root->stocks[pos].sym_id;

		if (root->left->stocks[curr_node_stock_no].symbol[0] == '\0')
			root->left->stock_no++;
		strcpy(root->left->stocks[curr_node_stock_no].symbol,
			   root->stocks[pos].symbol);
		root->left->stocks[curr_node_stock_no].sym_id = root->stocks[pos].sym_id;
		disperse_actions(root->left, movements, days,
						 curr_day + 1, pos);
	}
}

//go with the given sequence, if it s not null ok, if it is GG
void show_matches(TREENODE* root, FILE* out, const char sequence[MAX_DAYS],
				  const char sym[MAX_SYM_LEN], bool pairs[MAX_SYMS][MAX_SYMS],
				  int sym_no, int day, int days) {
	if (root == NULL)
		return;

	if (day == days) {
		for (int i = 0; i < MAX_SYMS; ++i) {
			if (root->stocks[i].symbol[0] == '\0')
				continue;

			int curr_stock_id = root->stocks[i].sym_id;
			if (pairs[sym_no][curr_stock_id] == false) {
				if (last_pair)
					fprintf(out, "\n");
				fprintf(out, "%s-%s", sym, root->stocks[i].symbol);
				last_pair = true;
				pairs[curr_stock_id][sym_no] = pairs[sym_no][curr_stock_id] = true;
			}
		}
		return;
	}

	if (sequence[day] == 'l')
		show_matches(root->right, out, sequence, sym, pairs, sym_no, day + 1, days);
	else
		show_matches(root->left, out, sequence, sym, pairs, sym_no, day + 1, days);
}

void free_tree(TREENODE* root) {
	if (root == NULL)
		return;

	free_tree(root->right);
	TREENODE* left = root->left;
	free(root->stocks);
	free(root);
	free_tree(left);
}
