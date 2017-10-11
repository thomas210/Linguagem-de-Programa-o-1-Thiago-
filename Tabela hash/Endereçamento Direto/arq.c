#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dados {
	int matricula;
	char nome[25];
	int cep;
};

struct Slot {
	struct Dados *aluno;
	struct Slot *prox;
};

int hash_div (int matricula, int tam);
void inserirb (struct Slot **cabeca, struct Dados **novo);
void inserir_elemento (struct Slot **t_hash, int tam_vetor, struct Dados **aluno);

void main (){
	struct Slot **t_hash = NULL;
	int tam = 9;
	int i, chave;
	struct Dados *novo = NULL;
	novo = (struct Dados*)malloc(sizeof(struct Dados));
	t_hash = (struct Slot**)malloc(tam * sizeof(struct Slot*));
	*t_hash = (struct Slot*)malloc(tam * sizeof(struct Slot));
	for (i = 0; i < tam; i++){
		t_hash[i] = NULL;
	}
	novo->matricula = 20160101;
	strcpy(novo->nome, "Thomas");
	novo->cep = 55030220;
	chave = hash_div(novo->matricula, tam);
	inserirb(&t_hash[chave], &novo);
}

int hash_div (int matricula, int tam){
	return matricula % tam;
}

void inserirb (struct Slot **cabeca, struct Dados **novo){
	struct Slot *temp = NULL;
	temp = (struct Slot *) malloc (sizeof(struct Slot));
	temp = (*cabeca);
	if (temp == NULL){
		temp->aluno = (*novo);
		temp->prox = NULL;
		(*cabeca) = temp;
	}
	else{
		while (temp->prox != NULL){
			temp = temp->prox;
		}
		temp = temp->prox;
		temp->aluno = (*novo);
		temp->prox = NULL;
	}
}

void inserir_elemento (struct Slot **t_hash, int tam_vetor, struct Dados **novo){
	int chave = hash_div((*novo)->matricula, tam_vetor);
	inserirb(&t_hash[chave], novo);
}


