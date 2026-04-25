#pragma once

#define MAX_SYM_LEN 5
#define MAX_SYMS 10
#define MAX_DAYS 10
#define MAX_BUFFER_SIZE 100

#include <stdbool.h>
/*
	Move n stocks according to their increase/decrease
	Create an array to day k value for each action
	Move the action array dependent on their price
	!No need to stock the actual value in the tree
	!No need to have a StockList* next field
	!No need for depth field, take the symetrical nodes ?
	At last, BFS + analyzing the order in the root to print
	as asked
*/

typedef struct StockList {
	char symbol[MAX_SYM_LEN];
	int sym_id;
} StockList;

typedef struct TREENODE {
	StockList* stocks;
	struct TREENODE* left;
	struct TREENODE* right;
	int stock_no;
} TREENODE;

TREENODE* create_tree_node();
void insert_symbols(char buffer[], TREENODE* root);
void create_tree(int argc, const char *argv[]);
void free_tree(TREENODE* root);
void insert_values(char buffer[], char movements[], double prev_day[],
				   double curr_day[], int action_nr, int day);
void disperse_actions(TREENODE* root, char movements[],
					  int days, int curr_day, int pos);
void show_matches(TREENODE* root, FILE* out, const char sequence[MAX_DAYS],
				  const char sym[MAX_SYM_LEN], bool pairs[MAX_SYMS][MAX_SYMS],
				  int sym_no, int day, int days);
