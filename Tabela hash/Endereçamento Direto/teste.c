#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dados {
	int matricula;
	int cep;
	char nome[25];
	int chave;
	struct Dados *prox;
};

void inserirb (struct Dados **cabeca, struct Dados **novo);
int hash_d (int matricula, int tam);
void criar_listas(struct Dados **tabela_hash, int tam);

void main (){
	struct Dados **tabela_hash = NULL;
	struct Dados *novo = NULL;
	int tam = 47;
	tabela_hash = (struct Dados **) malloc(sizeof(struct Dados) * tam);
	tabela_hash = NULL;
	//criar_listas(tabela_hash, tam);
	novo = (struct Dados *) malloc(sizeof(struct Dados));
	novo->matricula = 20160702;
	novo->cep = 55030220;
	strcpy(novo->nome, "Thomas");
	novo->chave = hash_d(novo->matricula, tam);
	novo->prox = NULL;
	inserirb(&tabela_hash[novo->chave], &novo);
}

/*void criar_listas(struct Dados **tabela_hash, int tam){
	int i;
	for (i = 0; i < tam; i++){
		tabela_hash[i] = NULL;
	}
}*/

int hash_d (int matricula, int tam){
	return matricula % tam;
}

void inserirb (struct Dados **cabeca, struct Dados **novo){
	struct Dados *temp = NULL;
	if (cabeca == NULL){
		cabeca = novo;
		return;
	}
	temp = (struct Dados *) malloc (sizeof(struct Dados));
	temp = (*cabeca);
	while (temp->prox != NULL){
		temp = temp->prox;
	}
	temp->prox = (*novo);
};
