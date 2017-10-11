#include <stdio.h>
#include <stdlib.h>

struct No {
	int num;
	struct No *prox;
};

enum Operacoes {
	IMPRIMIR_TODOS,
	CONTAGEM,
	ARQ_N_EXISTE,
};

enum Tipo_Arquivo {
	NOVO,
	CONTINUAR,
};

void inserir (struct No **cabeca, struct No **novo){
	struct No *temp = NULL;
	temp = (struct No *) malloc (sizeof(struct No));
	temp = (*cabeca);
	while (temp->prox != NULL){
		temp = temp->prox;
	}
	temp->prox = (*novo);
}

void remover (struct No **cabeca){
		(*cabeca) = (*cabeca)->prox;
}

int contar (struct No **cabeca, int vazio){
	int i;
	struct No *temp = NULL;
	if (vazio == 0){
		return 0;
	}
	temp = (struct No *) malloc (sizeof(struct No));
	temp = (*cabeca);
	for (i = 0; temp != NULL; i++){
		temp = temp->prox;
	}
	return i;
}

void imprimir (struct No **cabeca, enum Operacoes modo, int cont, enum Tipo_Arquivo tipo, int vazio){
	FILE *res = NULL;
	struct No *temp = NULL;
	temp = (struct No *) malloc (sizeof(struct No));
	if (tipo == NOVO){
		res = fopen ("resposta.txt", "w");
	}
	else {
		res = fopen ("resposta.txt", "a");
	}
	switch (modo){
		case IMPRIMIR_TODOS:
		temp = (*cabeca);
		if (vazio == 0){
			fprintf (res, "Sem elemetos\n");
			return;
		}
		while (temp != NULL){
			fprintf(res, "%d ", temp->num);
			temp = temp->prox;
		}
		fprintf (res, "\n");
		return;
		case CONTAGEM:
		fprintf (res, "%d\n", cont);
		return;
		case ARQ_N_EXISTE:
		fprintf (res, "Erro ao abrir um arquivo ou ele não existe ou não foi passado por parâmetro!");
		return;
		fclose(res);
	}
}

void ler_texto(const char *arquivo){
	FILE *arq = NULL;
	char escolha;
	struct No *cabeca = NULL;
	int vazio = 0;
	enum Tipo_Arquivo modelo = NOVO;
	cabeca = (struct No *) malloc (sizeof(struct No));
	cabeca->prox = NULL;
	arq = fopen (arquivo, "r");
	if (arq == NULL){
		imprimir (&cabeca, ARQ_N_EXISTE, 0, NOVO, vazio);
		return;
	}
	while (!feof(arq)){
		struct No *set = NULL;
		set = (struct No *) malloc (sizeof(struct No));
		set->prox = NULL;
		fscanf (arq, "%c", &escolha);
		if (escolha == 'I'){
			fscanf (arq, " %d\n", &set->num);
			if (vazio == 0){
				cabeca = set;
				vazio = 1;
			}
			else {
				inserir (&cabeca, &set);
			}
		}
		else if (escolha == 'R'){
			if (vazio == 1){
				remover (&cabeca);
			}
		}
		else if (escolha == 'C'){
			int c = contar (&cabeca, vazio);
			if (modelo == NOVO){
					imprimir (&cabeca, CONTAGEM, c, NOVO, vazio);
					modelo = CONTINUAR;
				}
				else {
					imprimir (&cabeca, CONTAGEM, c, CONTINUAR, vazio);
				}
			fscanf (arq, "\n");
		}
		else if (escolha == 'P'){
			if (modelo == NOVO){
				imprimir (&cabeca, IMPRIMIR_TODOS, 0, NOVO, vazio);
				modelo = CONTINUAR;
			}
			else {
				imprimir (&cabeca, IMPRIMIR_TODOS, 0, CONTINUAR, vazio);
			}
			fscanf (arq, "\n");
		}
	}
	fclose(arq);
}

void main (int agrc, char *agrv[]){
	ler_texto (agrv[1]);
}