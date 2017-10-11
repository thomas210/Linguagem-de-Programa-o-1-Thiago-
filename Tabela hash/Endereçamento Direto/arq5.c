#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Novo {
	SIM,
	NAO,
};

enum Operacoes {
	RESULTADO,
	ERRO,
	ARQ_N_EXISTE,
};

struct Slot {
	struct Dados *aluno;
	struct Slot *prox;
};

struct Dados {
	int matricula;
	char nome[25];
	int cep;
	struct Dados *prox;
};

void inserirb (struct Slot *cabeca, struct Dados *novo);
int hash_div (int matricula);
void executar (const char *arquivo);
void imprimir (struct Slot *elemento, enum Operacoes tipo);
void pesquisa (int mat, struct Slot *lista);
void remover (struct Slot *cabeca, int elemento);


void main (int agrc, char *agrv[]){
	executar (agrv[1]);
}

void executar (const char *arquivo){	//função geral
	FILE *arq = NULL;
	FILE *res = NULL;
	struct Slot **cabeca = NULL;
	int chave,p_matricula, i = 0;
	char escolha;
	arq = fopen (arquivo, "r");
	cabeca = (struct Slot **) malloc (27 * sizeof(struct Slot*));
	*cabeca = (struct Slot *) malloc (sizeof(struct Slot));
	res = fopen ("resposta.txt", "w");
	fclose(res);
	if (arq == NULL){
		imprimir (&(*cabeca[0]), ARQ_N_EXISTE);
		return;
	}
	for (i = 0; i < 27; i++){
		cabeca[i] = NULL;
	}
	while (!feof(arq)){
		struct Dados *set = NULL;
		set = (struct Dados *) malloc (sizeof(struct Dados));
		set->prox = NULL;
		fscanf(arq, "%s\n", &escolha);
		if (escolha == 'i'){
			fscanf (arq, "%d\n", &set->matricula);
			fgets (set->nome, sizeof(set->nome), arq);
			fscanf (arq, "%d\n", &set->cep);
			set->prox = NULL;
			chave = hash_div(set->matricula);
			inserirb (&(*cabeca[chave]), set);
			printf ("Registro de numero %d inserido com sucesso\n", set->matricula);
		}
		else if (escolha == 'p'){
			fscanf (arq, "%d\n", &p_matricula);
			chave = hash_div(p_matricula);
			pesquisa (p_matricula, &(*cabeca[chave]));
		}
		else if (escolha == 'r'){
			fscanf (arq, "%d\n", &p_matricula);
			chave = hash_div(p_matricula);
		}
	}
}

void inserirb (struct Slot *cabeca, struct Dados *novo){
	struct Slot *temp = NULL;
	struct Slot *temp2 = NULL;
	temp = (struct Slot *) malloc (sizeof(struct Slot));
	temp2 = (struct Slot *) malloc (sizeof(struct Slot));
	if (cabeca == NULL){  //se a lista estiver vazia, coloca na cabeça
		cabeca->aluno = (*novo);
		return;
	}
	temp = cabeca;
	while (temp->prox != NULL){ 	//vai anadando até achar um espaço vazio
		temp = temp->prox;
	}
	(temp->prox)->aluno = novo;
}

int hash_div (int matricula){	//realiza o hash com o método da divisão
	return matricula % 27;
}


void imprimir (struct Slot *elemento, enum Operacoes tipo){
	FILE *res = NULL;
	res = fopen("resposta.txt", "a");
	switch(tipo){
		case ARQ_N_EXISTE:
		fprintf (res, "Erro ao abrir o arquivo ou ele não existe ou não foi passado por parâmetro!");
		return;
		case RESULTADO:
		fprintf(res, "Matrícula: %d\n", (elemento->aluno)->matricula);
		fprintf(res, "Nome do Aluno: %s", (elemento->aluno)->matricula);
		fprintf(res, "Cep: %d\n", (elemento->aluno)->cep);
		return;
		case ERRO:
		fprintf (res, "Erro, matrícula não encontrada\n");
		return;
	}
}

void pesquisa (int mat, struct Slot *lista){
	struct Slot *temp = NULL;
	temp = (struct Slot *) malloc (sizeof(struct Slot));
	if (lista ==  NULL) imprimir (lista, ERRO);
	else if ((lista->aluno)->matricula == mat) imprimir(lista, RESULTADO);
	else {
		pesquisa(mat, lista->prox);
	}
}

void remover (struct Slot *cabeca, int elemento){
	struct Slot *temp = NULL;
	temp = (struct Slot *) malloc (sizeof(struct Slot));
	struct Slot *ant = NULL;
	ant = (struct Slot *) malloc (sizeof(struct Slot));
	if ((cabeca->aluno)->matricula == elemento){
		cabeca = cabeca->prox;
		return;
	}
	ant = cabeca;
	temp= cabeca->prox;
	while (temp != NULL){
		if ((temp->aluno)->matricula == elemento){
			ant->prox = temp->prox;
			return;
		}
		ant = temp;
		temp = temp->prox;
	}
	imprimir(cabeca, ERRO);
}