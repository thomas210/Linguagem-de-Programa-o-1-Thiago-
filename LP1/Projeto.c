#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*Operações que serão utilizadas na função imprimir*/
enum Operacoes {
	RESULTADO,
	ERRO,
	ARQ_N_EXISTE,
	C_CONCLUIDO,
	R_CONCLUIDO,
	DECISAO,
	CLIENTE,
};

/*enum utilizado para saber se o horário está ou não reservado*/
enum Novo {
	SIM,
	NAO,
};

/*Struct utilizada na tabela hash das reservas, contém o tempo unix da reserva, o id do cliente que fez a reserva
o enum se ta reservado ou não e o número do quarto*/
struct Dados {
	time_t unix;
	int id;
	enum Novo reservado;
	int quarto;
};

/*struct temporária onde coloco o horário para mandar para a função*/
struct Temp {
	int dia;
	int mes;
	int ano;
	int hora;
};

/*struc para armazenamento */
struct Info {
	int id;
	int quant;
};

/*Listas de funções*/
int hash_div (time_t matricula);
int hash_a_div (time_t matricula, int n_sond);
time_t gera_unix(struct Temp *data);
void executar (const char *reservas, const char *clientes);
void imprimir (enum Operacoes tipo, struct Info *lista);
void heapmin (struct Info *vetor, int fim);
void gera_relatorio (double *freq, int total);
void heapmax (struct Info *vetor, int fim);

/*Main que só chama a função principal*/
void main (int argc, char *argv[]){
	executar(argv[1], argv[2]);
}

/*heapsort que pega o maior vlaor do vetor, no caso utilizado para saber qual cliente realizou mais reservas*/
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

/*heapsort que pega o menor valor do vetor, utilizado para saber qual o pico de reservas(qual o menor horario
atinge 30% das reservas*/
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

/*hash de divisão*/
int hash_div (time_t matricula){
	return matricula % 720;
}

/*hash de divisão com número de sondagem*/
int hash_a_div (time_t matricula, int n_sond){
	return (hash_div(matricula) + n_sond) % 720;
}

/*função que gera o tempo unix com base no horário dado*/
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

/*função que faz o relatório das frequências de horários reservados para assim saber o horário de pico
realiza a porcentagem e depois a análise combinatória*/
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
		t = -1;
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
	free(cob);
}

/*função principal, onde é analisado as escolhas e a função hash
escolha m: realiza a resreva, mas antes realiza uma busca na tabela hash para saber se aquele horário já havia sido
reservado ou não
escolha r: realizar o relatório de cliente e pico de horário
escolha p: reaiza uma busca para saber quem fez a reserva naquele horário*/
void executar (const char *reservas, const char *clientes){
	FILE *arq = NULL;
	FILE *res = NULL;
	struct Dados *lista = NULL;
	struct Info *cliente = NULL;
	struct Info busca;
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
				if (lista[chave].reservado == NAO) {
					//fscanf(arq,"%d\n", set.id);
					if (lista[chave].reservado == NAO){
						lista[chave] = set;
						lista[chave].reservado = SIM;
						imprimir(R_CONCLUIDO, cliente);
						freq[data.hora] = freq[data.hora] + 1;
						total++;
						for (i = 0; i < num; i++){
							if (lista[chave].id == cliente[i].id){
								cliente[i].quant++;
							}
						}
						i = 0;
					}
				}
				chave = hash_a_div(set.unix, i++);
			}
			if (i != 0){
				imprimir(RESULTADO, cliente);
			}
		}
		else if (escolha == 'r'){
			heapmax(cliente, num - 1);
			imprimir(CLIENTE, cliente);
			gera_relatorio(freq, total);
		}
		else if (escolha == 'p'){
			fscanf (arq, "%d\%d\%d %d %d\n", &data.dia, &data.mes, &data.ano, &data.hora, &set.quarto);
			tempo = gera_unix(&data);
			chave = hash_a_div(tempo, 0);
			i = 1;
			while ((lista[chave].unix != tempo)||(set.quarto != lista[chave].quarto)){ //Esse While é DEUS!
				chave = hash_a_div(tempo, i++);
				if (i >= 720){
					imprimir(ERRO, cliente);
				}
			}
			busca.id = lista[chave].id;
			imprimir(C_CONCLUIDO, &busca);
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
	free(cliente);
}

/*função que imprime os resultados no arquivo resposta
ARQ_N_EXISTE: não foi possível localizar o arquivo de entrada ou de clientes
RESULTADO: o horário já está reservado
ERRO: e busca da reserva com erro, pois não existe a reserva
C_CONCLUIDO: busca concluída
R_CONCLUIDO: reserva realizada
DECISAO: mostra o relatório*/
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
		fprintf (res, "A reserva não foi feita, então não pode ser localizada\n");
		return;
		case C_CONCLUIDO:
		fprintf (res, "Reserva realizada em nome do cliente ID: %d\n", lista->id);
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