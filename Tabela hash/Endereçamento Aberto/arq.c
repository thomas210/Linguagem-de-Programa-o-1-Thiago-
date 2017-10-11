#include <stdio.h>
#include <stdlib.h>

enum Operacoes {
	RESULTADO,
	ERRO,
	ARQ_N_EXISTE,
};

enum Novo {
	SIM,
	NAO,
};

struct Dados {
	int matricula;
	char nome[25];
	int cep;
	enum Novo cond;
};

int hash_div (int matricula){
	return matricula % 27;
}

int hash_a_div (int matricula, int n_sond){
	return (hash_div(matricula) + n_sond) % 27;
}

void executar (const char *arquivo);
void imprimir (struct Dados lista, enum Operacoes tipo);

void main (int argc, char *argv[]){
	executar(argv[1]);
}

void executar (const char *arquivo){
	FILE *arq = NULL;
	FILE *res = NULL;
	struct Dados *lista = NULL;
	char escolha;
	int i, chave;
	lista = (struct Dados *)malloc(27 * sizeof(struct Dados));
	arq = fopen(arquivo, "r");
	res = fopen("resposta.txt", "w");
	fclose(res);
	if (arq == NULL){
		imprimir(lista[0], ARQ_N_EXISTE);
		return;
	}
	for (i = 0; i < 27; i++){
		lista[i].cond = SIM;
	}
	while (!feof(arq)){
		struct Dados set;
		int p_matricula;
		fscanf(arq, "%s\n", &escolha);
		if (escolha == 'i'){
			fscanf (arq, "%d\n", &set.matricula);
			fgets (set.nome, sizeof(set.nome), arq);
			fscanf (arq, "%d\n", &set.cep);
			chave = hash_a_div(set.matricula, 0);
			while(lista[chave].cond == NAO){
				i = 1;
				chave = hash_a_div(set.matricula, i++);
			}
			lista[chave] = set;
			lista[chave].cond = NAO;
			printf("Insercao concluida\n");
		}
		else if (escolha == 'p'){
			fscanf(arq, "%d\n", &p_matricula);
			printf("%d\n", p_matricula);
			chave = hash_a_div(p_matricula, 0);
			while (lista[chave].matricula != p_matricula){
				i = 1;
				chave = hash_a_div(p_matricula, i++);
				if (i > 27) {
					imprimir(lista[0], ERRO);
					break;
				}
			}
			imprimir(lista[chave], RESULTADO);
			printf("pesquisa concluida\n");
		}
		else if (escolha == 'r'){
			fscanf(arq, "%d\n", p_matricula);
			chave = hash_a_div(p_matricula, 0);
			while (lista[chave].matricula != p_matricula){
				i =1;
				chave = hash_a_div(p_matricula, i++);
				if (i > 27) {
					imprimir(lista[0], ERRO);
					break;
				}
			}
			lista[chave].cond = SIM;
			printf("remocao concluida");
		}
	}
}

void imprimir (struct Dados lista, enum Operacoes tipo){
	FILE *res = NULL;
	res = fopen("resposta.txt", "w");
	switch(tipo){
		case ARQ_N_EXISTE:
		fprintf (res, "Erro ao abrir o arquivo ou ele não existe ou não foi passado por parâmetro!");
		return;
		case RESULTADO:
		fprintf(res, "Matrícula: %d\n", lista.matricula);
		fprintf(res, "Nome do Aluno: %s", lista.nome);
		fprintf(res, "Cep: %d\n", lista.cep);
		return;
		case ERRO:
		fprintf (res, "Erro, matrícula não encontrada\n");
		return;
	}
}