#include <stdio.h>
#include <stdlib.h>

struct No {
	int num;
	struct No *prox;
};

int remover (struct No **cabeca, int elemento){
	struct No *temp = NULL;
	struct No *ant = NULL;
	if ((*cabeca)->num == elemento){
		(*cabeca) = (*cabeca)->prox;
		return;
	}
	temp = (struct No *) malloc (sizeof(struct No));
	ant = (struct No *) malloc (sizeof(struct No));
	ant = (*cabeca);
	temp= (*cabeca)->prox;
	while (temp != NULL){
		if (temp->num == elemento){
			ant->prox = temp->prox;
			free(temp);
			free(ant);
			return 0;
		}
		else {
			ant = temp;
			temp = temp->prox;
		}
	}
	free(temp);
	free(ant);
	return 1;
}

void inserirb (struct No **cabeca, struct No **novo){
	struct No *temp = NULL;
	temp = (struct No *) malloc (sizeof(struct No));
	temp = (*cabeca);
	while (temp->prox != NULL){
		temp = temp->prox;
	}
	temp->prox = (*novo);
	free(temp);
}

void main (){
	struct No *cabeca = NULL;
	cabeca = (struct No *) malloc(sizeof(struct No));
	struct No *re = NULL;
	re = (struct No *) malloc(sizeof(struct No));
	struct No *bu = NULL;
	bu = (struct No *) malloc(sizeof(struct No));
	cabeca->num = 5;
	cabeca->prox = re;
	re->num = 7;
	re->prox = NULL;
	bu->num = 2;
	bu->prox = NULL;
	inserirb (&cabeca, &bu);
	printf ("%d %d %d", cabeca->num, (cabeca->prox)->num, ((cabeca->prox)->prox)->num);
	
}