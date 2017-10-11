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
	DECISAO,
	CLIENTE,
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


int hash_div (time_t matricula);
int hash_a_div (time_t matricula, int n_sond);
time_t gera_unix(struct Temp *data);
void executar (const char *reservas, const char *clientes);
void imprimir (enum Operacoes tipo, struct Info *lista);
void heapmin (struct Info *vetor, int fim);
void gera_relatorio (double *freq, int total);
void heapmax (struct Info *vetor, int fim);


void main (int argc, char *argv[]){
	executar(argv[1], argv[2]);
}


void heapmax (struct Info *vetor, int fim){
	int no = (fim + 1)/2 - 1;
	int i;
	struct Info temp;
	for (i = no; i >= 0; i--){
		int esq = 2 * i + 1;
		int dir = 2 * i + 2;
		if (dir <= fim){
			if ((vetor[esq].quant >= vetor[i].quant)&&(vetor[esq].quant >= vetor[dir].quant)){
				temp = vetor[i];
				vetor[i] = vetor[esq];
				vetor[esq] = temp;
			}
			else if ((vetor[dir].quant >= vetor[i].quant)&&(vetor[dir].quant >= vetor[esq].quant)){
				temp = vetor[i];
				vetor[i] = vetor[dir];
				vetor[dir] = temp;
			}
		}
		else if ((esq <= fim)&&(dir > fim)){
			if (vetor[esq].quant > vetor[i].quant){
				temp = vetor[i];
				vetor[i] = vetor[esq];
				vetor[esq] = temp;
			}
		}
		
	}
}

void heapmin (struct Info *vetor, int fim){
	int no = (fim + 1)/2 - 1;
	int i;
	struct Info temp;
	for (i = no; i >= 0; i--){
		int esq = 2 * i + 1;
		int dir = 2 * i + 2;
		if (dir <= fim){
			if ((vetor[esq].quant <= vetor[i].quant)&&(vetor[esq].quant <= vetor[dir].quant)){
				temp = vetor[i];
				vetor[i] = vetor[esq];
				vetor[esq] = temp;
			}
			else if ((vetor[dir].quant <= vetor[i].quant)&&(vetor[dir].quant <= vetor[esq].quant)){
				temp = vetor[i];
				vetor[i] = vetor[dir];
				vetor[dir] = temp;
			}
		}
		else if ((esq <= fim)&&(dir > fim)){
			if (vetor[esq].quant < vetor[i].quant){
				temp = vetor[i];
				vetor[i] = vetor[esq];
				vetor[esq] = temp;
			}
		}
		
	}
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

void gera_relatorio (double *freq, int total){
	double p[24];
	double a = 0;
	struct Info *cob = NULL;
	cob = (struct Info *)malloc(24 * sizeof(struct Info));
	int para = 0;
	int i, j, t = 0;
	for (i = 0; i < 24; i++){
		p[i] = freq[i]/total; 
	}
	for (j = 0; j < 24; j++){
		a = 0;
		i = j;
		t = 0;
		while (a <= 0.3) {
			a = a + p[i];
			i++;
			t++;
			if (i == 24){
				i = 0;
			}
			else if (i == j){
				a = 0.3;
			}
		}
		cob[j].id = j;
		cob[j].quant = t;
	}
	heapmin(cob, 23);
	imprimir(DECISAO, cob);
}




void executar (const char *reservas, const char *clientes){
	FILE *arq = NULL;
	FILE *res = NULL;
	struct Dados *lista = NULL;
	struct Info *cliente = NULL;
	char escolha;
	int i, chave, num;
	double freq[24];
	int total = 0;
	arq = fopen(clientes, "r");
	for (i = 0; i < 24; i++){
		freq[i] = 0;
	}
	if (arq == NULL){
		imprimir(ARQ_N_EXISTE, cliente);
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
		imprimir(ARQ_N_EXISTE, cliente);
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
					freq[data.hora] = freq[data.hora] + 1;
					total++;
					for (i = 0; i < num; i++){
						if (lista[chave].id == cliente[i].id){
							cliente[i].quant++;
							break;
						}
					}
					imprimir(R_CONCLUIDO, cliente);
					i = 0;
					break;
				}
			}
			if (i != 0){
				imprimir(RESULTADO, cliente);
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
					imprimir(ERRO, cliente);
					break;
				}
			}
			lista[chave].reservado = NAO;
			freq[data.hora] = freq[data.hora] - 1;
			total--;
			for (i = 0; i < num; i++){
						if (lista[chave].id == cliente[i].id){
							cliente[i].quant--;
							break;
						}
					}
			imprimir(C_CONCLUIDO, cliente);
		}
		else if (escolha == 'r'){
			heapmax(cliente, num - 1);
			imprimir(CLIENTE, cliente);
			gera_relatorio(freq, total);
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

void imprimir (enum Operacoes tipo, struct Info *lista){
	FILE *res = NULL;
	res = fopen("resposta.txt", "a");
	int tempo;
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
		case DECISAO:
		tempo = lista[0].id + lista[0].quant;
		if (tempo >= 24){
			tempo = tempo - 24;
		}
		fprintf (res, "O horário de pico está situado a partir de %d e vai até %d\n", lista[0].id, tempo);
		fprintf (res, "sugiro que aumente a tarifa nessa faixa de horario\n");
		return;
		case CLIENTE:
		fprintf (res, "O Cliente de ID:%d foi o cliente que mais fez reservas, com %d reservas!\n", lista[0].id, lista[0].quant);
		return;
	}
	fclose(res);
}