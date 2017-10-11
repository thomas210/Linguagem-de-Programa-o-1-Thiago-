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

struct Dados {
	int matricula;
	char nome[25];
	int cep;
	struct Dados *prox;
	enum Novo cond;
};

void inserirb (struct Dados *cabeca, struct Dados *novo);
int hash_div (int matricula);
void executar (const char *arquivo);
void imprimir (struct Dados *elemento, enum Operacoes tipo);
void pesquisa (int mat, struct Dados *lista);
void remover (struct Dados *cabeca, int elemento);


void main (int agrc, char *agrv[]){
	executar (agrv[1]);
}

void inserirb (struct Dados *cabeca, struct Dados *novo){
	struct Dados *temp = NULL;
	temp = (struct Dados *) malloc (sizeof(struct Dados));
	if (cabeca->cond == SIM){
		cabeca = novo;
		return;
	}
	temp = cabeca;
	while (temp->prox != NULL){
		temp = temp->prox;
	}
	temp->prox = novo;
}

int hash_div (int matricula){
	return matricula % 27;
}

void executar (const char *arquivo){
	FILE *arq = NULL;
	FILE *res = NULL;
	struct Dados *cabeca = NULL;
	struct Dados *set = NULL;
	int chave,p_matricula, i = 0;
	char escolha;
	res = fopen ("resposta.txt", "w");
	fclose(res);
	arq = fopen (arquivo, "r");
	cabeca = (struct Dados *) malloc (27 * sizeof(struct Dados));
	if (arq == NULL){
		imprimir (&cabeca[i], ARQ_N_EXISTE);
		return;
	}
	set = (struct Dados *) malloc (sizeof(struct Dados));
	set->prox = NULL;
	for (i = 0; i < 27; i++){
		cabeca[i].cond = SIM;
	}
	while (!feof(arq)){
		fscanf(arq, "%s\n", &escolha);
		if (escolha == 'i'){
			fscanf (arq, "%d\n", &set->matricula);
			fgets (set->nome, sizeof(set->nome), arq);
			fscanf (arq, "%d\n", &set->cep);
			set->prox = NULL;
			chave = hash_div(set->matricula);
			inserirb (&cabeca[chave], set);
			printf ("Registro de numero %d inserido com sucesso\n", set->matricula);
		}
		else if (escolha == 'p'){
			fscanf (arq, "%d\n", &p_matricula);
			chave = hash_div(p_matricula);
			pesquisa (p_matricula, &cabeca[chave]);
		}
		else if (escolha == 'r'){
			fscanf (arq, "%d\n", &p_matricula);
			chave = hash_div(p_matricula);
			
		}
	}
}

void imprimir (struct Dados *elemento, enum Operacoes tipo){
	FILE *res = NULL;
	res = fopen("resposta.txt", "a");
	switch(tipo){
		case ARQ_N_EXISTE:
		fprintf (res, "Erro ao abrir o arquivo ou ele não existe ou não foi passado por parâmetro!");
		return;
		case RESULTADO:
		fprintf(res, "Matrícula: %d\n", elemento->matricula);
		fprintf(res, "Nome do Aluno: %s", elemento->matricula);
		fprintf(res, "Cep: %d\n", elemento->cep);
		return;
		case ERRO:
		fprintf (res, "Erro, matrícula não encontrada\n");
		return;
	}
}

void pesquisa (int mat, struct Dados *lista){
	struct Dados *temp = NULL;
	temp = (struct Dados *) malloc (sizeof(struct Dados));
	if (lista->cond ==  SIM) imprimir (lista, ERRO);
	else if (lista->matricula == mat) imprimir(lista, RESULTADO);
	else {
		pesquisa(mat, lista->prox);
	}
}

void remover (struct Dados *cabeca, int elemento){
	struct Dados *temp = NULL;
	temp = (struct Dados *) malloc (sizeof(struct Dados));
	struct Dados *ant = NULL;
	ant = (struct Dados *) malloc (sizeof(struct Dados));
	if (cabeca->matricula == elemento){
		cabeca = cabeca->prox;
		return;
	}
	ant = cabeca;
	temp= cabeca->prox;
	while (temp != NULL){
		if (temp->matricula == elemento){
			ant->prox = temp->prox;
			return;
		}
		ant = temp;
		temp = temp->prox;
	}
	imprimir(cabeca, ERRO);
}