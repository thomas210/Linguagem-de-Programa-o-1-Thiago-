#include <stdio.h>
#include <stdlib.h>

struct No {
	int num;
	struct No *prox;
};

enum Operacoes {
	SUCESSO,
	IMPRIMIR_TODOS,
	ERR_REMOVER,
	CONTAGEM,
	ARQ_N_EXISTE,
};

void inserirb (struct No **cabeca, struct No **novo){
	struct No *temp = NULL;
	temp = (struct No *) malloc (sizeof(struct No));
	temp = (*cabeca);
	while (temp->prox != NULL){
		temp = temp->prox;
	}
	temp->prox = (*novo);
}

void inserirf (struct No **cabeca, struct No **novo){
	(*novo)->prox = (*cabeca);
	(*cabeca) = (*novo);
}

enum Operacoes remover (struct No **cabeca, int elemento){
	struct No *temp = NULL;
	temp = (struct No *) malloc (sizeof(struct No));
	struct No *ant = NULL;
	ant = (struct No *) malloc (sizeof(struct No));
	if ((*cabeca)->num == elemento){
		(*cabeca) = (*cabeca)->prox;
		return SUCESSO;
	}
	ant = (*cabeca);
	temp= (*cabeca)->prox;
	while (temp != NULL){
		if (temp->num == elemento){
			ant->prox = temp->prox;
			return SUCESSO;
		}
		ant = temp;
		temp = temp->prox;
	}
	return ERR_REMOVER;
}

int contar (struct No **cabeca){
	int i;
	struct No *temp = NULL;
	temp = (struct No *) malloc (sizeof(struct No));
	temp = (*cabeca);
	for (i = 0; temp != NULL; i++){
		temp = temp->prox;
	}
	return i;
}

void imprimir (struct No **cabeca, enum Operacoes modo, int cont){
	FILE *res = NULL;
	struct No *temp = NULL;
	temp = (struct No *) malloc (sizeof(struct No));
	res = fopen ("resposta.txt", "a");
	switch (modo){
		case IMPRIMIR_TODOS:
		temp = (*cabeca);
		while (temp != NULL){
			fprintf(res, "%d ", temp->num);
			temp = temp->prox;
		}
		fprintf (res, "\n");
		return;
		case ERR_REMOVER:
		fprintf (res, "X\n");
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
	cabeca = (struct No *) malloc (sizeof(struct No));
	cabeca->prox = NULL;
	arq = fopen (arquivo, "r");
	if (arq == NULL){
		imprimir (&cabeca, ARQ_N_EXISTE, 0);
		return;
	}
	fscanf (arq, "%c", &escolha);
	while (!feof(arq)){
		struct No *set = NULL;
		set = (struct No *) malloc (sizeof(struct No));
		set->prox = NULL;
		if (escolha == 'F'){
			fscanf (arq, " %d\n", &set->num);
			if (vazio == 0){
				cabeca = set;
				vazio = 1;
			}
			else {
				inserirf (&cabeca, &set);
			}
		}
		else if (escolha == 'A'){
			fscanf (arq, " %d\n", &set->num);
			if (vazio == 0){
				cabeca = set;
				vazio = 1;
			}
			else {
				inserirb (&cabeca, &set);
			}
		}
		else if (escolha == 'R'){
			enum Operacoes res;
			fscanf (arq, " %d\n", &set->num);
			res = remover (&cabeca, set->num);
			if (res == ERR_REMOVER){
				imprimir (&cabeca, ERR_REMOVER, 0);
			}
		}
		else if (escolha == 'C'){
			int c = contar (&cabeca);
			imprimir (&cabeca, CONTAGEM, c);
			fscanf (arq, "\n");
		}
		else if (escolha == 'P'){
			imprimir (&cabeca, IMPRIMIR_TODOS, 0);
			fscanf (arq, "\n");
		}
		fscanf (arq, "%c", &escolha);
	}
	fclose(arq);
}

void main (int agrc, char *agrv[]){
	ler_texto (agrv[1]);
}