#include <stdio.h>
#include <stdlib.h>

void merge_sort (int *lista, int inicio, int fim){
	int meio, i, j, k;
	int *temp = NULL;
	if (inicio == fim){					//O vetor já foi dividido ao seu limite
		return;
	}
	meio = (inicio + fim) / 2;
	merge_sort (lista, inicio, meio);	//Começa a realizar a divisão - "Dividir para Conquistar"
	merge_sort (lista, meio + 1, fim);
	j = meio + 1;
	k = 0;
	i = inicio;
	temp = (int *) malloc(sizeof(int) * (fim - inicio + 1));	//Alocação Dinâmica do vetor temporário
	while ((i <=meio)||(j <= fim)){		//Compara os subvetores para organizá-los em outro vetor auxiliar
		if (i > meio){					//Utiliza o sistema simples de Merge Sort. Dividir para conquistar, aqui ele raliza o "conquistar", comparar os vetores
			temp[k++] = lista[j++];
		}
		else if (j > fim){
			temp[k++] = lista[i++];
		}
		else if (lista[i] > lista[j]){
			temp[k++] = lista[j++];
		}
		else {
			temp[k++] = lista[i++];
		}
	}
	for (i = inicio; i <= fim; i++){	//Coloca os dados do vetor temporário para o vetor principal
		lista[i] = temp[i - inicio];
	}
	free(temp);	//Libera o espaço do vetor temporário
}

void PegaColocaDados (const char *arquivo){
	int cont, quant, inicio, fim, i, j, *lista, temp;
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
		merge_sort (lista, 0, quant - 1);
		fprintf (arq, "%d\n", quant);
		for (j = 0; j < quant; j++){
			fprintf (arq, "%d ", lista[j]);
		}
		fprintf (arq, "\n");
	}
	free(lista);	 //Libera o espaço do vetor principal
	fclose(doc);
	fclose(arq);
}

void main(int argc, char *argv[]){
	PegaColocaDados (argv[1]);
}