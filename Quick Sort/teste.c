#include <stdio.h>
#include <stdlib.h>

/*void quicksort (int *vetor, int inicio, int fim){
	int pivo, meio;
	meio = (inicio + fim)/2;
	pivo = escolher_pivo (vetor[inicio], vetor[fim], vetor[meio]);
}*/

int escolher_pivo (int inicio, int fim, int meio){
	if (((inicio > meio)&&(inicio < fim))||((inicio < meio)&&(inicio > fim))){
		return inicio;
	}
	else if (((fim > meio)&&(fim < inicio))||((fim < meio)&&(fim > inicio))){
		return fim;
	}
	else {
		return meio;
	}
}

void main (){
	int pivo = escolher_pivo(5,5,8);
	printf ("%d", pivo);
}