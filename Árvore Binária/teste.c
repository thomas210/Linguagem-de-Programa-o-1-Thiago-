#include <stdio.h>
#include <stdlib.h>

struct No {
	int numero;
	struct No *fe;
	struct No *fd;
	int fb;
};

void inserir (struct No **raiz, struct No *novo){
	if ((*raiz) != NULL){
		if ((*raiz)->numero > novo->numero){
			inserir (&(*raiz)->fe, novo);
		}
		else {
			inserir(&(*raiz)->fd, novo);
		}
	}
	else {
		(*raiz) = novo;
		(*raiz)->fe = NULL;
		(*raiz)->fd = NULL;
	}
}

int altura (struct No **raiz, struct No *original){
	if (original == NULL){
		original = (*raiz);
	}
	if ((*raiz) != NULL){
		int altura_esq = altura(&(*raiz)->fe, original);
		int altura_dir = altura(&(*raiz)->fd, original);
		(*raiz)->fb = altura_dir - altura_esq;
		if ((*raiz)->fb == -2){
			rotacao_direita (&raiz);
			//altura (&(*raiz), NULL);
		}
		if (altura_esq > altura_dir){
			if ((*raiz) == original){
				return altura_esq;
			}
			return 1 + altura_esq;
		}
		else {
			if ((*raiz) == original){
				return altura_dir;
			}
			return 1 + altura_dir;
		}
	}
	else {
		return 0;
	}
}

/*void rotacao_direita (struct No **raiz){
	struct No *aux = NULL;
	struct no *temp = NULL;
	aux = (struct No *) malloc (sizeof(struct No));
	temp = (struct No *) malloc (sizeof(struct No));
	aux = (*raiz)->fe;
	temp = aux->fd;
	aux->fd = (*raiz); 
	(*raiz)->fe = temp;
	(*raiz) = aux;
}*/

/*int altura (struct No **raiz, struct No *original){
	if (original == NULL){
		original = (*raiz);
	}
	if (raiz == NULL){
		return 0;
	}
	else {
		int altura_esq = altura(&(*raiz)->fe, original);
		int altura_dir = altura(&(*raiz)->fd, original);
		(*raiz)->fb = altura_dir - altura_esq;
		if ((*raiz)->fb == 2){
			rotacao_esquerda(raiz);
			return altura(raiz, NULL);
		}
		else if ((*raiz)->fb == -2){
			rotacao_direita(raiz);
			return altura(raiz, NULL);
		}	
		if (altura_esq > altura_dir){
			if ((*raiz) == original){
				return altura_esq;
			}
			return 1 + altura_esq;
		}
		else {
			if ((*raiz) == original){
				return altura_dir;
			}
			return 1 + altura_dir;
		}
	}
}*/

void rotacao_direita(struct No **raiz){
	struct No *aux = NULL;
	struct No *temp = NULL;
	aux = (struct No *) malloc (sizeof(struct No));
	temp = (struct No *) malloc (sizeof(struct No));
	aux = (*raiz)->fe;
	temp = aux->fd;
	aux->fd = (*raiz); 
	(*raiz)->fe = temp;
	(*raiz) = aux;
	//free(aux);
	//free(temp);
}
/*
void rotacao_esquerda(struct No **raiz){
	struct No *aux = NULL;
	struct No *temp = NULL;
	aux = (struct No *) malloc (sizeof(struct No));
	temp = (struct No *) malloc (sizeof(struct No));
	aux = (*raiz)->fd;
	temp = aux->fe;
	aux->fe = (*raiz);
	(*raiz)->fd = temp;
	(*raiz) = aux;
	//free(aux);
	//free(temp);
}*/


void main (){
	struct No *raiz = NULL;
	struct No *t = NULL;
	struct No *h = NULL;
	struct No *o = NULL;
	int alt;
	raiz = (struct No *) malloc (sizeof(struct No));
	t = (struct No *) malloc (sizeof(struct No));
	h = (struct No *) malloc (sizeof(struct No));
	o = (struct No *) malloc (sizeof(struct No));
	raiz->fe = NULL;
	raiz->fd = NULL;
	raiz = NULL;
	t->numero = 7;
	t->fe = NULL;
	t->fd = NULL;
	h->numero = 5;
	h->fe = NULL;
	h->fd = NULL;
	o->numero = 4;
	o->fe = NULL;
	o->fd = NULL;
	inserir (&raiz, t);
	inserir (&raiz, h);
	inserir (&raiz, o);
	alt = altura (&raiz, NULL);
}