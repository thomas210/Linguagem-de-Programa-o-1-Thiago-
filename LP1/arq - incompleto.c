#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

enum Operacoes {
	RESULTADO,
	ERRO,
	ARQ_N_EXISTE,
	C_CONCLUIDO,
	R_CONCLUIDO,
};

enum Novo {
	SIM,
	NAO,
};

struct Dados {
	time_t unix;
	int id;
	enum Novo reservado;
	int quarto;
};

struct Temp {
	int dia;
	int mes;
	int ano;
	int hora;
};

struct Info {
	int id;
	int quant;
};

struct Reservas {
	int horario;
	int quant;
};

int hash_div (time_t matricula);
int hash_a_div (time_t matricula, int n_sond);
time_t gera_unix(struct Temp *data);
void executar (const char *reservas, const char *clientes);
void imprimir (enum Operacoes tipo);


void main (int argc, char *argv[]){
	executar(argv[1], argv[2]);
}

int hash_div (time_t matricula){
	return matricula % 720;
}

int hash_a_div (time_t matricula, int n_sond){
	return (hash_div(matricula) + n_sond) % 720;
}

time_t gera_unix(struct Temp *data){
	struct tm time;
	time.tm_mday = data->dia;
	time.tm_mon = data->mes - 1;
	time.tm_year = data->ano - 1900;
	time.tm_hour = data->hora;
	time.tm_sec = 0;
	time.tm_min = 0;
	return mktime(&time) - 10800;
}

void executar (const char *reservas, const char *clientes){
	FILE *arq = NULL;
	FILE *res = NULL;
	struct Dados *lista = NULL;
	struct Info *cliente = NULL;
	char escolha;
	int i, chave, num;
	struct Reservas *freq = NULL;
	freq = (struct Reservas *)malloc(24 * sizeof(struct Reservas));
	for (i = 0; i < 24; i++){
		freq[i].horario = i;
	}
	arq = fopen(clientes, "r");
	if (arq == NULL){
		imprimir(ARQ_N_EXISTE);
		return;
	}
	fscanf(arq, "%d\n", &num);
	cliente = (struct Info *)malloc(num * sizeof(struct Info));
	for (i = 0; i < num; i++){
		fscanf (arq, "%d ", &cliente[i].id);
		fscanf (arq, "%d\n", &cliente[i].quant);
	}
	fclose(arq);
	lista = (struct Dados *)malloc(720 * sizeof(struct Dados));
	arq = fopen(reservas, "r");
	res = fopen("resposta.txt", "w");
	fclose(res);
	if (arq == NULL){
		imprimir(ARQ_N_EXISTE);
		return;
	}
	for (i = 0; i < 720; i++){
		lista[i].reservado = NAO;
	}
	while (!feof(arq)){
		struct Dados set;
		time_t tempo;
		struct Temp data;
		fscanf(arq, "%s\n", &escolha);
		if (escolha == 'm'){
			fscanf (arq, "%d\%d\%d %d %d\n", &data.dia, &data.mes, &data.ano, &data.hora, &set.quarto);
			fscanf (arq, "%d\n", &set.id);
			set.unix = gera_unix(&data);
			chave = hash_a_div(set.unix, 0);
			i = 1;
			while ((lista[chave].unix != set.unix)||(lista[chave].quarto != set.quarto)){
				chave = hash_a_div(set.unix, i++);
				if (i > 720) {
					fscanf(arq,"%d\n", set.id);
					chave = hash_a_div(set.unix, 0);
					i = 1;
					while(lista[chave].reservado == SIM){
						chave = hash_a_div(set.unix, i++);
					}
					lista[chave] = set;
					lista[chave].reservado = SIM;
					freq[chave].quant++;
					for (i = 0; i < num; i++){
						if (lista[chave].id == cliente[i].id){
							cliente[i].quant++;
							break;
						}
					}
					imprimir(R_CONCLUIDO);
					i = 0;
					break;
				}
			}
			if (i != 0){
				imprimir(RESULTADO);
			}
		}
		else if (escolha == 'c'){
			fscanf (arq, "%d\%d\%d %d\n", &data.dia, &data.mes, &data.ano, &data.hora);
			fscanf (arq, "%d\n", &set.id);
			tempo = gera_unix(&data);
			chave = hash_a_div(tempo, 0);
			while (lista[chave].unix != tempo){
				i =1;
				chave = hash_a_div(tempo, i++);
				if (i > 720) {
					imprimir(ERRO);
					break;
				}
			}
			lista[chave].reservado = NAO;
			imprimir(C_CONCLUIDO);
		}
	}
	free(lista);
	fclose(arq);
	arq = fopen(clientes, "w");
	fprintf(arq, "%d\n", num);
	for (i = 0; i < num; i++){
		fprintf (arq, "%d ", cliente[i].id);
		fprintf (arq, "%d\n", cliente[i].quant);
	}
}

void imprimir (enum Operacoes tipo){
	FILE *res = NULL;
	res = fopen("resposta.txt", "a");
	switch(tipo){
		case ARQ_N_EXISTE:
		fprintf (res, "Erro ao abrir o arquivo ou ele não existe ou não foi passado por parâmetro!\n");
		return;
		case RESULTADO:
		fprintf(res, "O horário já está reservado\n");
		return;
		case ERRO:
		fprintf (res, "A reserva não foi feita, então não pode ser cancelada\n");
		return;
		case C_CONCLUIDO:
		fprintf (res, "Reserva cancelada\n");
		return;
		case R_CONCLUIDO:
		fprintf (res, "Reserva realizada\n");
		return;
	}
	fclose(res);
}