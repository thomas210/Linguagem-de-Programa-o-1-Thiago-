#include <stdio.h>
#include <stdlib.h>

int organizador(char *doc){

	FILE *txt = fopen(doc,"r"),
		 *saida = fopen("saida.txt","w");         //abrindo arquivo
	int repeticoes, lenght, *array,max,min,u,i,k;

	fscanf(txt,"%d\n", &repeticoes); // repetições 
	if (repeticoes == 0){
		return 1;
	}
	fprintf(saida, "%d\n", repeticoes );

	for(i=0;i<repeticoes;i++){
		fscanf(txt, "%d\n", &lenght); // comprimento
		fprintf(saida, "%d\n", lenght );
		array = (int*)malloc(lenght*sizeof(int)); //alocação do array

		for(k=0;k<lenght;k++){
			fscanf(txt,"%d ", &array[k]); // array preenchido
		}

		max = lenght; //?
		min = 0;
		merge(array,min,max);

		u=0;
		while(u<lenght)	fprintf(saida,"%d ",array[u++]);
		fprintf(saida,"\n");

		free(array);
	}
	fclose(txt);
	fclose(saida);
	return 0;
}


int merge(int *array, int min, int max){
	if(min < max-1){ //?
		int metade = (max+min)/2;
		merge(array,min,metade);
		merge(array,metade+1,max);
		intercalar(array,min,metade,max);
	}
	return 0;
}


int intercalar(int *array,int min,int metade,int max){
	int *temp,tamanho,inicio1,inicio2,i=0,j=0,k=0;

	tamanho = (max-min); //?
	inicio1 = min;
	inicio2 = metade; //?
	temp = (int*)malloc(tamanho*sizeof(int));

	while(inicio1 < metade && inicio2 < max){

		if(array[inicio1] <= array[inicio2]){ //se o array 1 =< que array 2 = guardar o 1
			temp[i] = array[inicio1++];

		}else{                               // se o array 2 < que array 1 = guardar o 2
			temp[i] = array[inicio2++];

		}
	i++;
	}

	while(inicio1 < metade){					  // se acabar um dos arrays e não acabar o outro passa os valores que faltam!
		temp[i++] = array[inicio1++];
	}
	while(inicio2 < max){
		temp[i++] = array[inicio2++];
	}	
	
	for(i=min;i<max;i++){
		array[i] = temp[i];
	}
	for (i = 0; i < max; i++){
		printf ("%d : %d\n", i, array[i]);
	}
	int u=0;
		while(u<max) printf("\n%d\n",array[u++]);

	free(temp);
	return 0;
}


int main(int argc,char *argv[]){
	if(argv[1] == NULL){
		return 1;
	}else{
		organizador(argv[1]);
		return 0;
	}
}


/************************************************* backup**********************************************************/


/*int intercalar(int *array,int min,int metade,int max){
	int *temp,tamanho,inicio1,inicio2,i,j,k;

	tamanho = (max-min+1);
	inicio1 = min;
	inicio2 = metade+1;
	temp = (int*)malloc(tamanho*sizeof(int));

	for(i=0;i<tamanho;i++){
		if(inicio1 < metade && inicio2 < max){

			if(array[inicio1] < array[inicio2]){ //se o array 1 < que array 2 = guardar o 1
				temp[i] = array[inicio1++];

			}else if(array[inicio2] < array[inicio1]){ // se o array 2 < que array 2 = guardar o 2
				temp[i] = array[inicio2++];

			}else{									  //são iguais. guarda o 1 
				temp[i] = array[inicio1++];
			}
		}else{

			if(inicio1 < metade){					  // se acabar um dos arrays e não acabar o outro passa os valores que faltam!
				temp[i] = array[inicio1++];
			}else{
				temp[i] = array[inicio2++];
			}

		}
	}
	for(j=0,k=min; j<tamanho;j++,k++){
		array[k] = temp[j];
	}
	int u=0;
		while(u<tamanho) printf("\n%d\n",array[u++]);

	free(temp);
	return 0;
}
*/

/*

(int x, int *number){
	int i;

	numeber = (int*)malloc(x*sizeof(int));

/*int u=0;
		while(u<lenght) printf("\n%d\n",array[u++]);
}*/