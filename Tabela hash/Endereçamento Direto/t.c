#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dados {
	int matricula;
	int cep;
	char nome[25];
};

struct Slot {
	struct Dados aluno;
	struct Slot *prox;
};

void inserirb (struct Slot **cabeca, struct Dados **novo);
int hash_d (int matricula, int tam);

void main (){
	struct Dados *novo;
	novo->matricula = 20160702;
	novo->cep = 55030220;
	strcpy(novo->nome, "Thomas");
	struct Slot tabela_hash[59];
	inserirb(&tabela_hash[hash_d(novo->matricula, 59)], &novo);
}

int hash_d (int matricula, int tam){
	return matricula % tam;
}

void inserirb (struct Slot **cabeca, struct Dados **novo){
	struct Slot *temp = NULL;
	temp = (struct Slot *) malloc (sizeof(struct Slot));
	temp = (*cabeca);
	while (temp->prox != NULL){
		temp = temp->prox;
	}
	temp = temp->prox;
	temp->aluno = (**novo);
}