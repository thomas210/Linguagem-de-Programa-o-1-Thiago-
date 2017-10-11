#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void heapmin (int *vetor, int fim){
	int no = (fim + 1)/2 - 1;
	int i, temp;
	for (i = no; i >= 0; i--){
		int esq = 2 * i + 1;
		int dir = 2 * i + 2;
		if (dir <= fim){
			if ((vetor[esq] <= vetor[i])&&(vetor[esq] <= vetor[dir])){
				temp = vetor[i];
				vetor[i] = vetor[esq];
				vetor[esq] = temp;
			}
			else if ((vetor[dir] <= vetor[i])&&(vetor[dir] <= vetor[esq])){
				temp = vetor[i];
				vetor[i] = vetor[dir];
				vetor[dir] = temp;
			}
		}
		else if ((esq <= fim)&&(dir > fim)){
			if (vetor[esq] < vetor[i]){
				temp = vetor[i];
				vetor[i] = vetor[esq];
				vetor[esq] = temp;
			}
		}
		
	}
	temp = vetor[0];
	vetor[0] = vetor[fim];
	vetor[fim] = temp;
}

void ordenacao (int *vetor, int fim, int vezes){
	int i;
	int quant = fim + 1;
	for (i = 1; i <=vezes; i++){
		quant = quant - 1;
		heapmin(vetor, quant);
	}
}

void PegaColocaDados (const char *arquivo){
	int cont, quant, fim, i, j, *lista, temp, vezes;
	FILE *doc = NULL;
	FILE *arq = NULL;
	doc = fopen(arquivo, "r");
	arq = fopen ("resposta.txt", "w");
	if (doc == NULL){						//Caso o arquivo de entrada não exista ou ocorra erro na su leitura, o programa para e coloca uma mensagem de erro no arquivo de saída
		fprintf (arq, "Erro na leitura do arquivo ou o arquivo não existe");
		return;
	}
	fscanf (doc, "%d\n", &cont);
	fprintf (arq, "%d\n", cont);
	for (i = 1; i <= cont; i++){
		fscanf (doc, "%d\n", &quant);
		lista = (int *) malloc(sizeof(int) * quant); //Alocação Dinâmica do vetor principal
		for (j = 0; j < quant; j++){				//coloca os elementos do vetor do arquivo para o array
			fscanf (doc, "%d ", &lista[j]);
		}
		fscanf(doc, "%d\n", &vezes);
		fim = quant-1;
		ordenacao(lista, fim, vezes);
		fprintf (arq, "%d\n", vezes);
		for (j = fim; j > fim-vezes; j--){
			fprintf (arq, "%d ", lista[j]);
		}
		fprintf(arq, "\n");
	}
	free(lista);	 //Libera o espaço do vetor principal
	fclose(doc);
	fclose(arq);
}

void main(int argc, char *argv[]){
	PegaColocaDados (argv[1]);
}