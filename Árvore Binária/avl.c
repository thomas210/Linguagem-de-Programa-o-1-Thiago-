/************************************* AVL ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct No{ //Struct com os dados e os filhos
	int numero;
	int balance;
	struct No *fesq;
	struct No *fdir;
};

struct Lista{
	struct No *no;
	struct Lista *prox;
};


void inserir(struct No **raiz, struct No *novo,int inf){ // inserir
	novo->numero = inf;
	if((*raiz) != NULL){ //teste de folha
		printf("\t Raiz =  %d\n", (*raiz)->numero );
		if((*raiz)->numero > novo->numero){ //saber se o futuro filho será dir ou esq e chama recursivamente [inserir()]
			inserir(&(*raiz)->fesq,novo,inf);
		}
		else{
			inserir(&(*raiz)->fdir,novo,inf);
		}
	}
	else{ //adc novo no na arvore
		(*raiz) = (struct No*)malloc(sizeof(struct No));
		(*raiz)->numero = inf;
		(*raiz)->fesq = NULL;
		(*raiz)->fdir = NULL;
		altura(&(*raiz));
	}
}

void rotacaoDD(struct No **raiz){ // direito direito
	struct No *temp;
	temp = (struct No*)malloc(sizeof(struct No));
	printf(" \t R DD  =  %d \n", (*raiz)->numero );
	temp = (*raiz)->fdir;
	(*raiz)->fdir = temp->fesq;
	temp->fesq = (*raiz);
	(*raiz)->balance = altura(&(*raiz));
	temp->balance = altura(&(temp));
	(*raiz) = temp;
}

void rotacaoEE(struct No **raiz){// esquerdo esquerdo
	struct No *temp;
	temp = (struct No*)malloc(sizeof(struct No));
	temp = (*raiz)->fesq;
	(*raiz)->fesq = temp->fdir;
	temp->fdir = (*raiz);
	(*raiz)->balance = altura(&(*raiz));
	temp->balance = altura(&temp);
	(*raiz) = temp;
	
}

void rotacaoDE(struct No **raiz){ //Direito Esquerdo
	rotacaoEE(&(*raiz)->fdir);
	rotacaoDD(&(*raiz));
}

void rotacaoED(struct No **raiz){//Esquerdo Direito
	rotacaoDD(&(*raiz)->fesq);
	rotacaoEE(&(*raiz));
}


int altura(struct No **raiz){
    if ((*raiz) == NULL) return 0;
    int alt_esq = altura(&(*raiz)->fesq);
    int alt_dir = altura(&(*raiz)->fdir);
    struct No *temp =(struct No*)malloc(sizeof(struct No));
    (*raiz)->balance = (alt_esq - alt_dir);
    printf("balance do no %d\n", (*raiz)->balance );
    if (abs((*raiz)->balance) > 1){
    	printf("ALTURA\n");
    	if((*raiz)->balance >0){
    		temp = (*raiz)->fesq;
    		if(temp->balance >0){
    			rotacaoEE(&(*raiz));
    		}else{
    			rotacaoED(&(*raiz));
    		}
    	}else{
    		temp = (*raiz)->fdir;
    		if(temp->balance >0){
    			rotacaoDE(&(*raiz));
    		}else{
    			rotacaoDD(&(*raiz));
    		}
    	}
	}
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

/*int altura(struct No **raiz){// altura está com erro de loop infinito ao processar o segundo dado
	int altura_dir,altura_esq;
	if(*raiz == NULL){ //teste de folha
		return 0;
	}
	else{
		altura_esq = altura(&(*raiz)->fesq);
		altura_dir = altura(&(*raiz)->fdir);
		(*raiz)->balance = (altura_esq - altura_dir);
		printf("%d   ",altura_dir);//print para teste
			return 1 + (altura_esq > altura_dir)? altura_esq : altura_dir;
	}
}*/


void leitura(char *entrada){ // leitura
	int i,quantidade,inf;

	struct No *raiz = NULL;
	struct No *new = NULL;
	struct Lista *lista = NULL;

	FILE *txt = NULL;
	raiz = NULL;
	new = (struct No*)malloc(sizeof(struct No));// New Nó
	if(txt = fopen(entrada,"r")){				
		fscanf(txt,"%d\n",&quantidade); //quantidade de numeros

		for(i=0;i<quantidade;i++){	// enquanto não acabar os numeros...
			fscanf(txt,"%d ",&inf); //leia do arquivo de entrada
			printf(" \n");
			inserir(&(raiz),new,inf); //chame inserir
		}
	}
	fclose(txt);

	imprimir(&raiz,lista);
}

void enfileirar(struct Lista **fila,struct No *no){
	if((*fila) == NULL){
		*fila = (struct Lista*)malloc(sizeof(struct Lista));
		(*fila)->no = no;
		(*fila)->prox = NULL;
		return;
	}
	enfileirar(&(*fila)->prox,no);
}

struct No * desenfileirar(struct Lista **fila){
	struct Lista *cabeca = (*fila);
	(*fila) = (*fila)->prox;
	struct No *resultado = cabeca->no;
	free(cabeca);
	return resultado;
}

int imprimir(struct No **raiz,struct Lista *fila){
	struct No* var = (struct No* )malloc(sizeof(struct No));
	FILE *novo;
	novo = fopen("resposta.txt","w");
	if(*raiz == NULL){
		fprintf(novo,"X");
		return;
	}
	printf("%d\n", (*raiz)->numero );
	fprintf(novo,"%d ",(*raiz)->numero);
	enfileirar(&fila,(*raiz)->fesq);
	enfileirar(&fila,(*raiz)->fdir);
	while(fila){
		var = desenfileirar(&fila);
		imprimir(&var,fila);
	}
}


	
int main(int argc,char *argv[]){
	char *entrada;
	if(argv[1] != NULL){
		char *entrada = argv[1];
		leitura(entrada);
	}
	else{
		return 1;
	}
	
}