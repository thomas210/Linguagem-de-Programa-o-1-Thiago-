#include <stdio.h>
#include <stdlib.h>

struct No {
	int numero;
	struct No *fe;
	struct No *fd;
	int fb;
};

struct Lista {
	struct No *no;
	struct Lista *prox;
};

/*Se a raiz não estiver vazia então ele analisa se o novo número é maior ou menor que a raiz e vai "mandando"
de acordo com o valor, se for menor aplica recursividade usando agora o filho esquerdo como raiz, caso contrário
usando o filho direito como raiz, até encontrar chegar no caso base, encontrar uma raiz "vazia" e então o novo valor
é inserido*/
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

/*A função descobre a altura da árvore, ela analisa a altura do filho esquerdo e do filho direito de cada raiz
recursivamente até chegar no casa onde a raiz da função seja NULL, e vai retornando a altura mais alta dos filhos + 1,
até chegar na raiz original, aquela que iniciou a função, e retorna o resultado obtido menos 1, durante o processo confere se
a árvore está balaneada, verificando o cálculo toda vezque retorna a altura dos filhos, caso esteja desbalanceado inicia as fnuções
de rotação e mede a nova altura daquele nó*/
int altura (struct No **raiz, struct No *original){
	int resultado;
	struct No *temp = NULL;
	temp = (struct No *) malloc (sizeof(struct No));
	if (original == NULL){
		original = (*raiz);
	}
	if ((*raiz) != NULL){
		int altura_esq = altura(&(*raiz)->fe, original);
		int altura_dir = altura(&(*raiz)->fd, original);
		(*raiz)->fb = altura_dir - altura_esq;
		resultado = ((altura_dir > altura_esq) ? altura_dir : altura_esq);
		if ((*raiz)->fb == -2){
			temp = (*raiz);
			if (((*raiz)->fe)->fb == 1) rotacao_direita_esquerda(raiz);
			else rotacao_direita(raiz);
			resultado = altura (raiz, NULL);
			if (temp == original) return resultado;
			else return resultado + 1;
		}
		else if ((*raiz)->fb == 2){
			temp = (*raiz);
			if (((*raiz)->fd)->fb == -1) rotacao_esquerda_direita(raiz);
			else rotacao_esquerda(raiz);
			resultado = altura (raiz, NULL);
			if (temp == original) return resultado;
			else return resultado + 1;
		}
		if ((*raiz) == original) return resultado;
		else return resultado + 1;
	}
	else {
		return 0;
	}
}

/*realiza a rotação em sentido horário para balancear a árvore*/
void rotacao_direita (struct No **raiz){
	struct No *aux = NULL;
	struct No *temp = NULL;
	aux = (struct No *) malloc (sizeof(struct No));
	temp = (struct No *) malloc (sizeof(struct No));
	aux = (*raiz)->fe;
	temp = aux->fd;
	aux->fd = (*raiz); 
	(*raiz)->fe = temp;
	(*raiz) = aux;
}

/*realiza a rotação em sentido anti-horário para balancear a árvore*/
void rotacao_esquerda (struct No **raiz){
	struct No *aux = NULL;
	struct No *temp = NULL;
	aux = (struct No *) malloc (sizeof(struct No));
	temp = (struct No *) malloc (sizeof(struct No));
	aux = (*raiz)->fd;
	temp = aux->fe;
	aux->fe = (*raiz); 
	(*raiz)->fd = temp;
	(*raiz) = aux;
}

/*basicamente realiza a rotação a esquerda no filho esquerdo da raiz e depois a rotação a direita na raiz*/
void rotacao_direita_esquerda (struct No **raiz){
	struct No *aux_p = NULL;
	struct No *temp_p = NULL;
	struct No *aux_f = NULL;
	struct No *temp_f = NULL;
	aux_p = (struct No *) malloc (sizeof(struct No));
	temp_p = (struct No *) malloc (sizeof(struct No));
	aux_f = (struct No *) malloc (sizeof(struct No));
	temp_f = (struct No *) malloc (sizeof(struct No));
	aux_f = ((*raiz)->fe)->fd;
	temp_f = aux_f->fe;
	aux_f->fe = ((*raiz)->fe);
	((*raiz)->fe)->fd = temp_f;
	((*raiz)->fe) = aux_f;
	aux_p = (*raiz)->fe;
	temp_p = aux_p->fd;
	aux_p->fd = (*raiz); 
	(*raiz)->fe = temp_p;
	(*raiz) = aux_p;
}

/*basicamente realiza a rotação a direita no filho direito da raiz e depois a rotação a esquerda na raiz*/
void rotacao_esquerda_direita (struct No **raiz){
	struct No *aux_p = NULL;
	struct No *temp_p = NULL;
	struct No *aux_f = NULL;
	struct No *temp_f = NULL;
	aux_p = (struct No *) malloc (sizeof(struct No));
	temp_p = (struct No *) malloc (sizeof(struct No));
	aux_f = (struct No *) malloc (sizeof(struct No));
	temp_f = (struct No *) malloc (sizeof(struct No));
	aux_f = ((*raiz)->fd)->fe;
	temp_f = aux_f->fd;
	aux_f->fd = ((*raiz)->fd);
	((*raiz)->fd)->fe = temp_f;
	((*raiz)->fe) = aux_f;
	aux_p = (*raiz)->fd;
	temp_p = aux_p->fe;
	aux_p->fe = (*raiz); 
	(*raiz)->fd = temp_p;
	(*raiz) = aux_p;
}

/*Função que auxilia na impressão dos valores, vai emfileirando os elementos, na ordem first in first out*/
void inserir_fila (struct Lista **fila, struct No *elemento){
	if (*fila == NULL){
		*fila = (struct Lista *) malloc (sizeof(struct Lista));
		(*fila)->no = elemento;
		(*fila)->prox = NULL;
	}
	else inserir_fila(&(*fila)->prox, elemento);
}

/*Função que auxilia na impressão dos valores, vai desemfileirando os elementos, na ordem first in first out*/
struct No *retirar_fila (struct Lista **fila){
	struct Lista *cabeca = NULL;
	cabeca = (struct Lista *) malloc (sizeof(struct Lista));
	cabeca = (*fila);
	(*fila) = (*fila)->prox;
	return cabeca->no;
}

/*realiza a impressão dos elementos, ele imprime a raiz, e enfileira os seus filhos, depois desenfileira um elemento e
realiza a impressão recursivamente até que a fila esteja vazia, caso a raiz seja NULL é colocado um X no arquivo*/
void imprimir (struct No *raiz, struct Lista **fila){
	if (raiz == NULL){
		printf("X ");
		return;
	}
	printf ("%d ", raiz->numero);
	inserir_fila (fila, raiz->fe);
	inserir_fila (fila, raiz->fd);
	while ((*fila) != NULL){
		imprimir (retirar_fila(fila), fila);
	}
}

void main (){
	struct No *raiz = NULL;
	struct No *t = NULL;
	struct No *h = NULL;
	struct No *o = NULL;
	struct No *m = NULL;
	struct No *a = NULL;
	struct No *s = NULL;
	struct Lista *fila = NULL;
	int alt;
	raiz = (struct No *) malloc (sizeof(struct No));
	t = (struct No *) malloc (sizeof(struct No));
	h = (struct No *) malloc (sizeof(struct No));
	o = (struct No *) malloc (sizeof(struct No));
	m = (struct No *) malloc (sizeof(struct No));
	a = (struct No *) malloc (sizeof(struct No));
	s = (struct No *) malloc (sizeof(struct No));
	raiz->fe = NULL;
	raiz->fd = NULL;
	raiz = NULL;
	t->numero = 20;
	t->fe = NULL;
	t->fd = NULL;
	h->numero = 6;
	h->fe = NULL;
	h->fd = NULL;
	o->numero = 22;
	o->fe = NULL;
	o->fd = NULL;
	m->numero = 7;
	m->fe = NULL;
	m->fd = NULL;
	a->numero = 5;
	a->fe = NULL;
	a->fd = NULL;
	s->numero = 8;
	s->fe = NULL;
	s->fd = NULL;
	inserir (&raiz, t);
	inserir (&raiz, h);
	inserir (&raiz, o);
	inserir (&raiz, m);
	inserir (&raiz, a);
	inserir (&raiz, s);
	alt = altura (&raiz, NULL);
	imprimir (raiz, &fila);
}