#pragma once

#include <data.h>
#include <stdio.h>

NODE* create_node() {
	NODE *new = (NODE* )malloc(sizeof(NODE));
	if (!new)
		exit(-1);

	new->next = NULL;
	new->randament = 0;
	new->valoare = 0;
	new->calculate_randament = calculare_randament; 
	return new;
}


NODE* read_data() {
	NODE *head = create_node();
	NODE *current = create_node();
	head->next = current;

	int n = 1;
	scanf("%d %*c %d ", &n, &head->valoare);

	for (int i = 1; i < n; ++i) {
		NODE *aux = create_node();
		scanf(" %d ", &current->valoare);
		current->next = aux;
		current = aux;
	}

	compute_randament(head);

	return head;
}

double calculare_randament(NODE* node) {
	return node->next->valoare / node->valoare - 1;
}

void compute_randament(NODE* head) {
	NODE* aux = create_node();

	for (aux = head; !aux->next; aux = aux->next) {
		aux->next->randament = aux->calculate_randament(aux);
	}

	free(aux);
}