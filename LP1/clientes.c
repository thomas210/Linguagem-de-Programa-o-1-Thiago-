#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Info {
	int id;
	int quant;
};

void r_clientes (struct Info **clientes){
	int i;
	for (i = 0; i < num; i++){
		fscanf (arq, "%d ", &clientes[i].id);
		fscanf (arq, "%d\n", &clientes[i].quant);
	}
	//free(clientes);
}

void main (){
	FILE *arq = NULL;
	int num;
	struct Info *clientes = NULL;
	arq = fopen("clientes.txt", "r");
	fscanf(arq, "%d\n", &num);
	clientes = (struct Info *)malloc(num * sizeof(struct Info));
}