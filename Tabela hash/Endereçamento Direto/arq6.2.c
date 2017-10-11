#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
	int cond;
};

void inserirb (struct Dados **cabeca, struct Dados *novo);
int hash_div (int matricula);
void executar (const char *arquivo);
void imprimir (struct Dados **elemento, enum Operacoes tipo);
void pesquisa (int mat, struct Dados **lista);
void remover (struct Dados **cabeca, int elemento);


void main (int agrc, char *agrv[]){
	executar (agrv[1]);
}

void executar (const char *arquivo){	//função geral
	FILE *arq = NULL;
	FILE *res = NULL;
	struct Dados **cabeca = NULL;
	int chave,p_matricula, i = 0;
	char escolha;
	arq = fopen (arquivo, "r");
	cabeca = (struct Dados **) malloc (27 * sizeof(struct Dados*));
	*cabeca = (struct Dados *) malloc (sizeof(struct Dados));
	res = fopen ("resposta.txt", "w");
	fclose(res);
	if (arq == NULL){
		imprimir (&cabeca[0], ARQ_N_EXISTE);
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
			if (cabeca[chave] == NULL) {
				cabeca[chave] = set;
			}
			else {
				inserirb (&cabeca[chave], set);
			}
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
			remover(&cabeca[chave], p_matricula);
			printf ("Registro de numero %d removido com sucesso\n", p_matricula);
		}
	}
}

void inserirb (struct Dados **cabeca, struct Dados *novo){
	struct Dados *temp = NULL;
	temp = (struct Dados *) malloc (sizeof(struct Dados));
	if (cabeca == NULL){  //se a lista estiver vazia, coloca na cabeça
		(*cabeca) = novo;
		temp = NULL;
		return;
	}
	temp = (*cabeca);
	while (temp->prox != NULL){ 	//vai anadando até achar um espaço vazio
		temp = temp->prox;
	}
	temp->prox = novo;
	temp = NULL;
}

int hash_div (int matricula){	//realiza o hash com o método da divisão
	return matricula % 27;
}


void imprimir (struct Dados **elemento, enum Operacoes tipo){
	FILE *res = NULL;
	res = fopen("resposta.txt", "a");
	switch(tipo){
		case ARQ_N_EXISTE:
		fprintf (res, "Erro ao abrir o arquivo ou ele não existe ou não foi passado por parâmetro!");
		return;
		case RESULTADO:
		fprintf(res, "Matrícula: %d\n", (*elemento)->matricula);
		fprintf(res, "Nome do Aluno: %s", (*elemento)->nome);
		fprintf(res, "Cep: %d\n", (*elemento)->cep);
		return;
		case ERRO:
		fprintf (res, "Erro, matrícula não encontrada\n");
		return;
	}
}

void pesquisa (int mat, struct Dados **lista){
	struct Dados *temp = NULL;
	temp = (struct Dados *) malloc (sizeof(struct Dados));
	//if (lista ==  NULL) imprimir (lista, ERRO);
	//temp = (*lista)->prox;
	temp = (*lista);
	while (temp != NULL) {
		if (temp->matricula == mat){
			imprimir(&temp, RESULTADO);
			return;
		}
		temp = temp->prox;
	}
	imprimir(lista, ERRO);
}

void remover (struct Dados **cabeca, int elemento){
	struct Dados *temp = NULL;
	temp = (struct Dados *) malloc (sizeof(struct Dados));
	struct Dados *ant = NULL;
	ant = (struct Dados *) malloc (sizeof(struct Dados));
	if ((*cabeca)->matricula == elemento){
		(*cabeca) = (*cabeca)->prox;
		return;
	}
	ant = (*cabeca);
	temp= (*cabeca)->prox;
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