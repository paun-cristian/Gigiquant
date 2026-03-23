typedef struct NODE {
	double valoare;
	double randament;
	struct NODE* next;

	double (*calculate_randament)(struct NODE *);
} NODE;

NODE* read_data();
NODE* create_node();
double calculare_randament(NODE* node);
