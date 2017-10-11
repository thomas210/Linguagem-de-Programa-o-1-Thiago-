#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Enum criado para a função impressão para tratamento de erro 
quanto ao arquivo não existir ou o registro não exixtir*/
enum Operacoes {
	RESULTADO,
	ERRO,
	ARQ_N_EXISTE,
};

/*Struct utilizada na tabela hash e para pegar os dados da tabela*/
struct Dados {
	int matricula;
	char nome[25];
	int cep;
	struct Dados *prox;
};

//Assinatura de funções
void inserirb (struct Dados **cabeca, struct Dados *novo);
int hash_div (int matricula);
void executar (const char *arquivo);
void imprimir (struct Dados **elemento, enum Operacoes tipo);
void pesquisa (int mat, struct Dados **lista);
void remover (struct Dados **cabeca, int elemento);

void main (int argc, char *argv[]){
	executar (argv[1]);
}

/*Função que realiza todo o procedimento, 
é como se fosse a "main" do algoritmo, para que nada seja realizado na main
Declara as variáveis; coloca todas as posições da tabela hash(declarada como cabeca) como NULL; e realiza a opreção
dependendo da opção escolhido no arquivo de entrada(inserir, pesquisa, remover)
Inserir: recebe os valores pelo arquivo e chama a função inserir;
Pesuisar: Recebe o número de matrícula e chama a função pesquisa;
Remover: Recebe o número de matrícula e chama a função remover*/
void executar (const char *arquivo){	//função geral
	FILE *arq = NULL;
	FILE *res = NULL;
	struct Dados **cabeca = NULL;
	int chave,p_matricula, i = 0;
	char escolha;
	arq = fopen (arquivo, "r");
	cabeca = (struct Dados **) malloc (27 * sizeof(struct Dados*));
	*cabeca = (struct Dados *) malloc (sizeof(struct Dados));
	res = fopen ("resposta.txt", "w");	// <-Gambiarra: Abrir e fechar o arquivo de resposta para apagar o antigo, caso exista. Muitos problemas em realizar isso pela função
	fclose(res);
	if (arq == NULL){
		imprimir (&cabeca[0], ARQ_N_EXISTE);
		return;
	}
	for (i = 0; i < 27; i++){
		cabeca[i] = NULL;
	}
	while (!feof(arq)){
		struct Dados *set = NULL;
		set = (struct Dados *) malloc (sizeof(struct Dados));
		set->prox = NULL;
		fscanf(arq, "%s\n", &escolha);
		if (escolha == 'i'){
			fscanf (arq, "%d\n", &set->matricula);
			fgets (set->nome, sizeof(set->nome), arq);
			fscanf (arq, "%d\n", &set->cep);
			set->prox = NULL;
			chave = hash_div(set->matricula);
			if (cabeca[chave] == NULL) {	// <-Gambiarra: Caso a cabeca esteja em NULL, já preenche com o set, não estava send possível realizar isso na função própria
				cabeca[chave] = set;
			}
			else {
				inserirb (&cabeca[chave], set);
			}
		}
		else if (escolha == 'p'){
			fscanf (arq, "%d\n", &p_matricula);
			chave = hash_div(p_matricula);
			pesquisa (p_matricula, &cabeca[chave]);
		}
		else if (escolha == 'r'){
			fscanf (arq, "%d\n", &p_matricula);
			chave = hash_div(p_matricula);
			remover(&cabeca[chave], p_matricula);
		}
	}
	fclose(arq);
	free(cabeca);
}

/*Função para inserir na lista
Essa função recebe a lista e o novo elemento, basicamente ela vai procurando até encontrar o último
elemento da lista e coloca o novo elemento no final*/
void inserirb (struct Dados **cabeca, struct Dados *novo){
	struct Dados *temp = NULL;
	temp = (struct Dados *) malloc (sizeof(struct Dados));
	if (cabeca == NULL){ 
		(*cabeca) = novo;
		temp = NULL;
		return;
	}
	temp = (*cabeca);
	while (temp->prox != NULL){
		temp = temp->prox;
	}
	temp->prox = novo;
	temp = NULL;
}

/*Função Geradora Chave por Resto
Essa função retorna a chave que será utilizada na função hash, o valor é obtido por meio do resto da divisão
entre a matrícula e um número(nesse caso 27)*/
int hash_div (int matricula){
	return matricula % 27;
}

/*Função pesquisa do registro
A função recebe como parâmetro o número de matrícula e a lista correspondente a chave a partir daí 
procura dentre os elementos da lista o correto,chamando assim a função imprimir com o modo RESULTADO, 
caso não encontre, chama a função imprimir porém com o modo ERRO*/
void pesquisa (int mat, struct Dados **lista){
	struct Dados *temp = NULL;
	temp = (struct Dados *) malloc (sizeof(struct Dados));
	temp = (*lista);
	while (temp != NULL) {
		if (temp->matricula == mat){
			imprimir(&temp, RESULTADO);
			return;
		}
		temp = temp->prox;
	}
	imprimir(lista, ERRO);
}

/*Função remover
A função recebe como parâmetro o número de matrícula e a lista correspondente a chave e remove o registro
correspondente, caso ele exista*/
void remover (struct Dados **cabeca, int elemento){
	struct Dados *temp = NULL;
	temp = (struct Dados *) malloc (sizeof(struct Dados));
	struct Dados *ant = NULL;
	ant = (struct Dados *) malloc (sizeof(struct Dados));
	if ((*cabeca)->matricula == elemento){
		(*cabeca) = (*cabeca)->prox;
		return;
	}
	ant = (*cabeca);
	temp= (*cabeca)->prox;
	while (temp != NULL){
		if (temp->matricula == elemento){
			ant->prox = temp->prox;
			return;
		}
		ant = temp;
		temp = temp->prox;
	}
	imprimir(cabeca, ERRO);
}

/*Função Imprimir
Essa função realiz a operação dependendo do modo:
RESULTADO: vai imprimir no arquivo resposta o resultado da pesquisa feita;
ARQ_N_EXISTE: vai imprimir uma mensagem de erro informando erro na leitura do arquivo de entrada;
ERRO: o registro que foi solicitado para a busca não existe*/
void imprimir (struct Dados **elemento, enum Operacoes tipo){
	FILE *res = NULL;
	res = fopen("resposta.txt", "a");
	switch(tipo){
		case ARQ_N_EXISTE:
		fprintf (res, "Erro ao abrir o arquivo ou ele não existe ou não foi passado por parâmetro!");
		return;
		case RESULTADO:
		fprintf(res, "Matrícula: %d\n", (*elemento)->matricula);
		fprintf(res, "Nome do Aluno: %s", (*elemento)->nome);
		fprintf(res, "Cep: %d\n", (*elemento)->cep);
		return;
		case ERRO:
		fprintf (res, "Erro, matrícula não encontrada\n");
		return;
	}
}