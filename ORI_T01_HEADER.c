/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 01 - Indexação
 *
 * ========================================================================== *
 *   <<< IMPLEMENTE AQUI!!! COPIE E COLE O CONTEÚDO DESTE ARQUIVO NO AVA >>>
 * ========================================================================== */

/* Bibliotecas */
#include "ORI_T01_HEADER.h"

/* ===========================================================================
 * ================================= FUNÇÕES ================================= */


/* <<< COLOQUE AQUI OS DEMAIS PROTÓTIPOS DE FUNÇÕES, SE NECESSÁRIO >>> */


/* Funções auxiliares para o qsort.
 * Com uma pequena alteração, é possível utilizá-las no bsearch, assim, evitando código duplicado.
 * */

/* Função de comparação entre chaves do índice corredores_idx */
int qsort_corredores_idx(const void *a, const void *b) {
    return strcmp( ( (corredores_index *)a )->id_corredor, ( (corredores_index *)b )->id_corredor);
}

/* Função de comparação entre chaves do índice veiculos_idx */
int qsort_veiculos_idx(const void *a, const void *b) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp( ( (veiculos_index*)a )->id_veiculo, ( (veiculos_index*)b )->id_veiculo);
}

int qsort_string_modelo(const void *a, const void *b){
    return strcmp((char *)a, (char *)b);
}

/* Função de comparação entre chaves do índice pistas_idx */
int qsort_pistas_idx(const void *a, const void *b) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp( ( (pistas_index*)a )->id_pista, ( (pistas_index*)b )->id_pista);
}

/* Função de comparação entre chaves do índice corridas_idx */
int qsort_corridas_idx(const void *a, const void *b) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(strcmp( ( (corridas_index*)a )->ocorrencia, ( (corridas_index*)b )->ocorrencia) != 0){
		return(strcmp( ( (corridas_index*)a )->ocorrencia, ( (corridas_index*)b )->ocorrencia));
	} else {
		return(strcmp( ( (corridas_index*)a )->id_pista, ( (corridas_index*)b )->id_pista));
	}
}

/* Funções de comparação apenas entre data de ocorrencia do índice corridas_idx */
int qsort_data_idx(const void *a, const void *b){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return(strcmp( ( (corridas_index*)a )->ocorrencia, ( (corridas_index*)b )->ocorrencia));
}

/* Função de comparação entre chaves do índice nome_pista_idx */
int qsort_nome_pista_idx(const void *a, const void *b){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return(strcmp( ( (nome_pista_index*)a )->nome , ( (nome_pista_index*)b )->nome));
}

/* Função de comparação entre chaves do índice preco_veiculo_idx */
int qsort_preco_veiculo_idx(const void *a, const void *b){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int i = 0;
	if(( (preco_veiculo_index*)a )->preco == ( (preco_veiculo_index*)b )->preco)
		i = 0;
	if (( (preco_veiculo_index*)a )->preco < ( (preco_veiculo_index*)b )->preco)
		i = -1;
	if (( (preco_veiculo_index*)a )->preco > ( (preco_veiculo_index*)b )->preco)
		i = 1;
	return(i);
}

/* Função de comparação entre chaves do índice secundário de corredor_veiculos_secundario_idx */
int qsort_corredor_veiculos_secundario_idx(const void *a, const void *b){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return(strcmp( ( (corredor_veiculos_secundario_index*)a )->chave_secundaria, ( (corredor_veiculos_secundario_index*)b )->chave_secundaria));
}

/* Cria o índice respectivo */
void criar_corredores_idx() {
    if (!corredores_idx)
        corredores_idx = malloc(MAX_REGISTROS * sizeof(corredores_index));
 
    if (!corredores_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
 
    for (unsigned i = 0; i < qtd_registros_corredores; ++i) {
        Corredor c = recuperar_registro_corredor(i);
 
        if (strncmp(c.id_corredor, "*|", 2) == 0)
            corredores_idx[i].rrn = -1; // registro excluído
        else
            corredores_idx[i].rrn = i;
 
        strcpy(corredores_idx[i].id_corredor, c.id_corredor);
    }
 
    qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
    printf(INDICE_CRIADO, "corredores_idx");
}

void criar_veiculos_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	//ALOCAÇÃO
	if(!veiculos_idx)
		veiculos_idx = malloc(MAX_REGISTROS * sizeof(veiculos_index));

	if(!veiculos_idx){
		printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
	}

	for (unsigned i = 0; i  < qtd_registros_veiculos; ++i) {
		Veiculo v = recuperar_registro_veiculo(i);
		//insere/atualiza nos campos de veiculos_idx
		veiculos_idx[i].rrn = i;
		strcpy(veiculos_idx[i].id_veiculo, v.id_veiculo);
	}

	qsort(veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);
	printf(INDICE_CRIADO, "veiculos_idx");
}

void criar_pistas_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	//ALOCAÇÃO
	if(!pistas_idx)
		pistas_idx = malloc(MAX_REGISTROS * sizeof(pistas_index));

	if(!pistas_idx){
		printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
	}

	for (unsigned i = 0; i  < qtd_registros_pistas; ++i) {
		Pista p = recuperar_registro_pista(i);
		//insere/atualiza nos campos de pistas_idx
        pistas_idx[i].rrn = i;
		strcpy(pistas_idx[i].id_pista, p.id_pista);
	}

	qsort(pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx);
	printf(INDICE_CRIADO, "pistas_idx");
}

void criar_corridas_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	//ALOCAÇÃO
	if(!corridas_idx)
		corridas_idx = malloc(MAX_REGISTROS * sizeof(corridas_index));

	if(!corridas_idx){
		printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
	}

	for (unsigned i = 0; i  < qtd_registros_corridas; ++i) {
		Corrida c = recuperar_registro_corrida(i);
		//insere/atualiza nos campos de corrida_idx
        corridas_idx[i].rrn = i;
		strcpy(corridas_idx[i].id_pista, c.id_pista);
		strcpy(corridas_idx[i].ocorrencia, c.ocorrencia);
	}

	qsort(corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx);
	printf(INDICE_CRIADO, "corridas_idx");
}

void criar_nome_pista_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	//ALOCAÇÃO
	if(!nome_pista_idx)
		nome_pista_idx = malloc(MAX_REGISTROS * sizeof(nome_pista_index));

	if(!nome_pista_idx){
		printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
	}

	for (unsigned i = 0; i  < qtd_registros_pistas; ++i) {
		Pista p = recuperar_registro_pista(i);
		//insere nos campos de nome_pista_idx
		strcpy(nome_pista_idx[i].id_pista, p.id_pista);
		strcpy(nome_pista_idx[i].nome, strupr(p.nome));

	}

	qsort(nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx);
	printf(INDICE_CRIADO, "nome_pista_idx");
}

void criar_preco_veiculo_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	//ALOCAÇÃO
	if(!preco_veiculo_idx)
		preco_veiculo_idx = malloc(MAX_REGISTROS * sizeof(preco_veiculo_index));

	if(!preco_veiculo_idx){
		printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
	}

	for (unsigned i = 0; i  < qtd_registros_veiculos; ++i) {
		Veiculo v = recuperar_registro_veiculo(i);
		//insere nos campos de preco_veiculo_idx
		preco_veiculo_idx[i].preco = v.preco;
		strcpy(preco_veiculo_idx[i].id_veiculo, v.id_veiculo);

	}

	qsort(preco_veiculo_idx, qtd_registros_veiculos, sizeof(preco_veiculo_index), qsort_preco_veiculo_idx);
	printf(INDICE_CRIADO, "preco_veiculo_idx");
}

void criar_corredor_veiculos_idx() {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	//ALOCAÇÃO
	if(!corredor_veiculos_idx.corredor_veiculos_secundario_idx)
		corredor_veiculos_idx.corredor_veiculos_secundario_idx = malloc(MAX_REGISTROS * sizeof(corredor_veiculos_secundario_index));

	if(!corredor_veiculos_idx.corredor_veiculos_secundario_idx){
		printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
	}

	if(!corredor_veiculos_idx.corredor_veiculos_primario_idx)
		corredor_veiculos_idx.corredor_veiculos_primario_idx = malloc(MAX_REGISTROS * sizeof(corredor_veiculos_primario_index));

	if(!corredor_veiculos_idx.corredor_veiculos_primario_idx){
		printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
	}

	//recupera os todos os corredores
	for (unsigned i = 0; i  < qtd_registros_corredores; ++i) {
		Corredor c = recuperar_registro_corredor(i);

		// se for um registro excluído continue o loop
		if (strncmp(c.id_corredor, "*|", 2) == 0)
            continue;


		//para cada corredor recupera seus veículos
		for(int j = 0; j < 3; ++j ){
			if(strlen(c.veiculos[j]) > 0) { //verifica se a string não é vazia
        		inverted_list_insert(c.veiculos[j], c.id_corredor, &corredor_veiculos_idx);
			}
		}

	}
	
	printf(INDICE_CRIADO, "corredor_veiculos_idx");
}

/* Exibe um registro com base no RRN */
bool exibir_corredor(int rrn) {
    if (rrn < 0)
        return false;
 
    Corredor c = recuperar_registro_corredor(rrn);
 
    printf("%s, %s, %s, %s, %.2lf\n", c.id_corredor, c.nome, c.apelido, c.cadastro, c.saldo);
    return true;
}

bool exibir_veiculo(int rrn) {
    /*IMPLEMENTE A FUNÇÃO AQUI*/
	if (rrn < 0)
		return false;

	Veiculo v = recuperar_registro_veiculo(rrn);

	printf("%s, %s, %s, %s, %d, %d, %d, %.2lf\n", v.id_veiculo, v.marca, v.modelo, v.poder, v.velocidade, v.aceleracao, v.peso, v.preco);
	return true;
}

bool exibir_pista(int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (rrn < 0)
		return false;

	Pista p = recuperar_registro_pista(rrn);

	printf("%s, %s, %d, %d, %d\n", p.id_pista, p.nome, p.dificuldade, p.distancia, p.recorde);
	return true;
}

bool exibir_corrida(int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (rrn < 0)
		return false;

	Corrida c = recuperar_registro_corrida(rrn);

	printf("%s, %s, %s, %s\n", c.id_pista, c.ocorrencia, c.id_corredores, c.id_veiculos);
	return true;
}

/* Recupera do arquivo o registro com o RRN informado
 * e retorna os dados nas structs */
Corredor recuperar_registro_corredor(int rrn) {
	Corredor c;
	char temp[TAM_REGISTRO_CORREDOR + 1], *p;
	strncpy(temp, ARQUIVO_CORREDORES + (rrn * TAM_REGISTRO_CORREDOR), TAM_REGISTRO_CORREDOR);
	temp[TAM_REGISTRO_CORREDOR] = '\0';

	p = strtok(temp, ";");
	strcpy(c.id_corredor, p);
	p = strtok(NULL, ";");
	strcpy(c.nome, p);
	p = strtok(NULL, ";");
	strcpy(c.apelido, p);
	p = strtok(NULL, ";");
	strcpy(c.cadastro, p);
	p = strtok(NULL, ";");
	c.saldo = atof(p);
	p = strtok(NULL, ";");

	for(int i = 0; i < QTD_MAX_VEICULO; ++i)
		c.veiculos[i][0] = '\0';

	if(p[0] != '#') {
		p = strtok(p, "|");

		for(int pos = 0; p; p = strtok(NULL, "|"), ++pos)
			strcpy(c.veiculos[pos], p);
	}

	return c;
}

Veiculo recuperar_registro_veiculo(int rrn) {
	Veiculo v;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_VEICULO + 1], *p;
	strncpy(temp, ARQUIVO_VEICULOS + (rrn * TAM_REGISTRO_VEICULO), TAM_REGISTRO_VEICULO);
	temp[TAM_REGISTRO_VEICULO] = '\0';

	//Separa cada campo do registro e coloca no campo da struct Veículo
	p = strtok(temp, ";");
	strcpy(v.id_veiculo, p);
	p = strtok(NULL, ";");
	strcpy(v.marca, p);
	p = strtok(NULL, ";");
	strcpy(v.modelo, p);
	p = strtok(NULL, ";");
	strcpy(v.poder, p);
	p = strtok(NULL, ";");
	v.velocidade = atoi(p);
	p = strtok(NULL, ";");
	v.aceleracao = atoi(p);
	p = strtok(NULL, ";");
	v.peso = atoi(p);
	p = strtok(NULL, ";");
	v.preco = atof(p);
	
	return v;
}

Pista recuperar_registro_pista(int rrn) {
	Pista p;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_PISTA + 1], *t;
	strncpy(temp, ARQUIVO_PISTAS + (rrn * TAM_REGISTRO_PISTA), TAM_REGISTRO_PISTA);
	temp[TAM_REGISTRO_PISTA] = '\0';

	//Separa cada campo do registro e coloca no campo da struct Pista
	t = strtok(temp, ";");
	strcpy(p.id_pista, t);
	t = strtok(NULL, ";");
	strcpy(p.nome, t);
	t = strtok(NULL, ";");
	p.dificuldade = atoi(t);
	t = strtok(NULL, ";");
	p.distancia = atoi(t);
	t = strtok(NULL, ";");
	p.recorde = atoi(t); //transformar a string em int
	t = strtok(NULL, ";");

	return p;
}

Corrida recuperar_registro_corrida(int rrn) {
	Corrida c;

	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_CORRIDA + 1];
	strncpy(temp, ARQUIVO_CORRIDAS + (rrn * TAM_REGISTRO_CORRIDA), TAM_REGISTRO_CORRIDA);
	temp[TAM_REGISTRO_CORRIDA] = '\0';

	//tem tamanho fixo
	strncpy(c.id_pista, temp, TAM_ID_PISTA);
	strncpy(c.ocorrencia, temp + TAM_ID_PISTA -1, TAM_DATETIME);
	strncpy(c.id_corredores, temp + TAM_ID_PISTA - 1 + TAM_DATETIME - 1, TAM_ID_CORREDORES);
	strncpy(c.id_veiculos, temp + TAM_ID_PISTA - 1 + TAM_DATETIME - 1 + TAM_ID_CORREDORES - 1, TAM_ID_VEICULOS);
	c.id_pista[TAM_ID_PISTA - 1] = '\0';
	c.ocorrencia[TAM_DATETIME - 1] = '\0';
	c.id_corredores[TAM_ID_CORREDORES - 1] = '\0';
	c.id_veiculos[TAM_ID_VEICULOS - 1] = '\0';

	return c;
}

/* Escreve em seu respectivo arquivo na posição informada (RRN) */
void escrever_registro_corredor(Corredor c, int rrn) {
	char temp[TAM_REGISTRO_CORREDOR + 1], p[100];
	temp[0] = '\0'; p[0] = '\0';

	strcpy(temp, c.id_corredor);
	strcat(temp, ";");
	strcat(temp, c.nome);
	strcat(temp, ";");
	strcat(temp, c.apelido);
	strcat(temp, ";");
	strcat(temp, c.cadastro);
	strcat(temp, ";");
	sprintf(p, "%013.2lf", c.saldo);
	strcat(temp, p);
	strcat(temp, ";");

	for(int i = 0, k = 0; i < QTD_MAX_VEICULO; ++i) {
		if(strlen(c.veiculos[i]) > 0) {
			if (k == 0)
				k = 1;
			else
				strcat(temp, "|");
			strcat(temp, c.veiculos[i]);
		}
	}
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_CORREDOR);

	strncpy(ARQUIVO_CORREDORES + rrn*TAM_REGISTRO_CORREDOR, temp, TAM_REGISTRO_CORREDOR);
}

void escrever_registro_veiculo(Veiculo v, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_VEICULO + 1], p[100];
	temp[0] = '\0'; p[0] = '\0';

	// insere cada campo no arquivo separando-os por ";""
	strcpy(temp, v.id_veiculo);
	strcat(temp, ";");
	strcat(temp, v.marca);
	strcat(temp, ";");
	strcat(temp, v.modelo);
	strcat(temp, ";");
	strcat(temp, v.poder);
	strcat(temp, ";");
	sprintf(p, "%04d", v.velocidade);
	strcat(temp, p);
	strcat(temp, ";");
	sprintf(p, "%04d", v.aceleracao);
	strcat(temp, p);
	strcat(temp, ";");
	sprintf(p, "%04d", v.peso);
	strcat(temp, p);
	strcat(temp, ";");
	sprintf(p, "%013.2lf", v.preco);
	strcat(temp, p);
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_VEICULO);

	strncpy(ARQUIVO_VEICULOS + rrn*TAM_REGISTRO_VEICULO, temp, TAM_REGISTRO_VEICULO);
}

void escrever_registro_pista(Pista p, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_PISTA + 1], t[100];
	temp[0] = '\0'; t[0] = '\0';

	// insere cada campo no arquivo separando-os por "";""
	strcpy(temp, p.id_pista);
	strcat(temp, ";");
	strcat(temp, p.nome);
	strcat(temp, ";");
	sprintf(t, "%04d", p.dificuldade);
	strcat(temp, t);
	strcat(temp, ";");
	sprintf(t, "%04d", p.distancia);
	strcat(temp, t);
	strcat(temp, ";");
	sprintf(t, "%04d", p.recorde);
	strcat(temp, t);
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_PISTA);

	strncpy(ARQUIVO_PISTAS + rrn*TAM_REGISTRO_PISTA, temp, TAM_REGISTRO_PISTA);
}

void escrever_registro_corrida(Corrida i, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_CORRIDA + 1];
	temp[0] = '\0';

	// insere cada campo no arquivo separando-os por ";"
	strcpy(temp, i.id_pista);
	strcat(temp, i.ocorrencia);
	strcat(temp, i.id_corredores);
	strcat(temp, i.id_veiculos);
	strcat(temp, "\0");

	strpadright(temp, '#', TAM_REGISTRO_CORRIDA);

	strncpy(ARQUIVO_CORRIDAS + rrn*TAM_REGISTRO_CORRIDA, temp, TAM_REGISTRO_CORRIDA);
}

/* Funções principais */
void cadastrar_corredor_menu(char *id_corredor, char *nome, char *apelido){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	// Faz a busca
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
    corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if (found == NULL || found->rrn < 0) {
		// criação do novo corredor com os dados certos
		Corredor c;
		strcpy(c.id_corredor, id_corredor);
		strcpy(c.nome, nome);
		strcpy(c.apelido, apelido);
		c.saldo = 0;
		strcpy(c.veiculos[0], "\0");
		strcpy(c.veiculos[1], "\0");
		strcpy(c.veiculos[2], "\0");
		
		// utilizar datatime para pegar a data atual e guardar numa variavel, obs: precisa ser char cadastro
		char data[TAM_DATETIME];
		current_datetime(data);
		strcpy(c.cadastro, data);

		//escreve o corredor criado no registro de corredor
		escrever_registro_corredor(c, qtd_registros_corredores);
		
		//inserir nova tupla em corredores_idx na posição certa e depois ordenar
		strcpy(corredores_idx[qtd_registros_corredores].id_corredor, id_corredor);
		corredores_idx[qtd_registros_corredores].rrn = qtd_registros_corredores;
		qsort(corredores_idx, qtd_registros_corredores + 1, sizeof(corredores_index), qsort_corredores_idx);

		//incrementa a quantidade de registros
		printf(SUCESSO);
		qtd_registros_corredores++;
	} else {
		printf(ERRO_PK_REPETIDA, id_corredor);
	}
}

void remover_corredor_menu(char *id_corredor) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	//Faz a busca
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
    corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if (found == NULL || found->rrn < 0)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else{
		//acha registro no arquivo de corredores atraves do rrn no índice e marca registro como removido no arquivo de corredores
		Corredor c = recuperar_registro_corredor(found->rrn);
		c.id_corredor[0] = '*';
		c.id_corredor[1] = '|';
		escrever_registro_corredor(c, found->rrn);
		
		//marca como removido no índice (-1)
		found->rrn = -1;
		//OBS: qntd de registros não é decrementada pq ainda está lá, está apenas marcado como removido
		printf(SUCESSO);
	}
}

void adicionar_saldo_menu(char *id_corredor, double valor) {
	adicionar_saldo(id_corredor, valor, true);
}

void adicionar_saldo(char *id_corredor, double valor, bool flag){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	//faz a busca para achar corredor
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
    corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if (found == NULL || found->rrn < 0) {
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	} else {
		if(valor <= 0){
			printf(ERRO_VALOR_INVALIDO);
		} else{
			// recupera corredor, altera saldo e escreve novamente
			Corredor c = recuperar_registro_corredor(found->rrn);
			c.saldo = c.saldo + valor;
			escrever_registro_corredor(c, found->rrn);
			if(flag)
				printf(SUCESSO);
		}
	}
}

void comprar_veiculo_menu(char *id_corredor, char *id_veiculo) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	//busca nos índices o corredor e o veiculo para pegar seus rrn
	corredores_index index;
	veiculos_index index2;
	strcpy(index.id_corredor, id_corredor);
	strcpy(index2.id_veiculo, id_veiculo);
    corredores_index *found_corredor = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	veiculos_index *found_veiculo = busca_binaria((void*)&index2, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);
	if (found_corredor == NULL || found_corredor->rrn < 0 || found_veiculo == NULL) {
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	}
	else {
		//recuperar veiculo e corredor:
		Corredor c = recuperar_registro_corredor(found_corredor->rrn);
		Veiculo v = recuperar_registro_veiculo(found_veiculo->rrn);
		// restricao de preco
		if(c.saldo < v.preco){
			printf(ERRO_SALDO_NAO_SUFICIENTE);
		} else {
			//verifica se o veiculo já existe
			for(int i = 0; i < 3; i++) {
				if(strcmp(c.veiculos[i], v.modelo) != 0){ 
					continue;
				} else{
					printf(ERRO_VEICULO_REPETIDO, id_corredor, v.id_veiculo);
					return;
				}
			}

			// se o veiculo for "vazio" compre
			for (int i = 0; i < 3; i++) {
				if(strlen(c.veiculos[i]) > 0){
					continue;
				} else{
					//atualiza saldo e coloca veiculo como posse do corredor e escreve corredor novamente
					strcpy(c.veiculos[i], v.modelo);
					c.saldo = c.saldo - v.preco;
					escrever_registro_corredor(c, found_corredor->rrn);
					printf(SUCESSO);

					//inserção no índice corredor_veiculos_idx
					inverted_list_insert(v.modelo, c.id_corredor, &corredor_veiculos_idx);
					break;
			    }	
			}
		}
	}
}

void cadastrar_veiculo_menu(char *marca, char *modelo, char *poder, int velocidade, int aceleracao, int peso, double preco) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	// Faz a busca
	veiculos_index index;
	char id_veiculo[TAM_ID_VEICULO];
	sprintf(id_veiculo, "%07d", qtd_registros_veiculos);
	id_veiculo[TAM_ID_VEICULO-1] = '\0';
	strcpy(index.id_veiculo, id_veiculo);
    corredores_index *found = busca_binaria((void*)&index, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);
	if (found == NULL || found->rrn < 0) {
		// criação do novo veiculo com os dados certos
		Veiculo v;
		strcpy(v.id_veiculo, id_veiculo);
		strcpy(v.marca, marca);
		strcpy(v.modelo, modelo);
		strcpy(v.poder, poder);
		v.velocidade = velocidade;
		v.aceleracao = aceleracao;
		v.peso = peso;
		v.preco = preco;

		//escreve o veiculo criado no registro de veiculos
		escrever_registro_veiculo(v, qtd_registros_veiculos);
		
		//inserir nova tupla em veiculos_idx na posição certa e depois ordenar
		strcpy(veiculos_idx[qtd_registros_veiculos].id_veiculo, v.id_veiculo);
		veiculos_idx[qtd_registros_veiculos].rrn = qtd_registros_veiculos;
		qsort(veiculos_idx, qtd_registros_veiculos + 1, sizeof(veiculos_index), qsort_veiculos_idx);

		//inserir nova tupla em preco_veiculo_idx
		strcpy(preco_veiculo_idx[qtd_registros_veiculos].id_veiculo, v.id_veiculo);
		preco_veiculo_idx[qtd_registros_veiculos].preco = v.preco;
		qsort(preco_veiculo_idx, qtd_registros_veiculos + 1, sizeof(preco_veiculo_index),qsort_preco_veiculo_idx);

		//incrementa a quantidade de registros
		printf(SUCESSO);
		qtd_registros_veiculos++;
	} else {
		printf(ERRO_PK_REPETIDA, id_veiculo);
	}
}

void cadastrar_pista_menu(char *nome, int dificuldade, int distancia, int recorde){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char nometemp[TAM_MAX_NOME_PISTA];
	strcpy(nometemp, nome); 
	nome_pista_index index;
	strcpy(index.nome, strupr(nome));
    nome_pista_index *found = busca_binaria((void*)&index, nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx, false, 0);
	if (found == NULL) {
	// criação da nova pista com os dados certos
		Pista p;
		char id_pista[TAM_ID_PISTA];
		sprintf(id_pista, "%08d", qtd_registros_pistas);
		id_pista[TAM_ID_PISTA-1] = '\0';
		strcpy(p.id_pista, id_pista);
		strcpy(p.nome, nometemp);
		p.distancia = distancia;
		p.recorde = recorde;
		if(dificuldade < 0)
			p.dificuldade = 1;
		else
			p.dificuldade = dificuldade;

		//escreve a pista criada no registro de pista
		escrever_registro_pista(p, qtd_registros_pistas);
		
		//inserir nova tupla em pistas_idx na posição certa e depois ordenar
		strcpy(pistas_idx[qtd_registros_pistas].id_pista, p.id_pista);
		pistas_idx[qtd_registros_pistas].rrn = qtd_registros_pistas;
		qsort(pistas_idx, qtd_registros_pistas + 1, sizeof(pistas_index), qsort_pistas_idx);

		//inserir nova tupla em nome_pista_idx na posição certa e depois ordenar
		strcpy(nome_pista_idx[qtd_registros_pistas].nome, strupr(p.nome));
		strcpy(nome_pista_idx[qtd_registros_pistas].id_pista, p.id_pista);
		qsort(nome_pista_idx, qtd_registros_pistas + 1, sizeof(nome_pista_index), qsort_nome_pista_idx);

		//incrementa a quantidade de registros
		printf(SUCESSO);
		qtd_registros_pistas++;
	} else {
		printf(ERRO_PK_REPETIDA, nometemp);
	}
}

void executar_corrida_menu(char *id_pista, char *ocorrencia, char *id_corredores, char *id_veiculos) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/

	//verificar se a corrida já existe
	corridas_index index_corridas;
	strcpy(index_corridas.id_pista, id_pista);
	strcpy(index_corridas.ocorrencia, ocorrencia);
	corridas_index *found_corrida = busca_binaria((void*)&index_corridas, corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx, false, 0);
	if(found_corrida != NULL){
		char chave_composta[TAM_DATETIME + TAM_ID_PISTA];
        chave_composta[0] = '\0';
        strcat(chave_composta, ocorrencia);
        strcat(chave_composta, id_pista);
        printf(ERRO_PK_REPETIDA, chave_composta);
        return;
	}
	
	// verificar se pista existe
	pistas_index index_pista;
	strcpy(index_pista.id_pista, id_pista);
	pistas_index*found_pista = busca_binaria((void*)&index_pista, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, false, 0);
	if(found_pista == NULL){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		return;
	}

	//verificar se corredores existem
	corredores_index index_corredores;
	for(int i = 0; i < 6; i++) {
		strncpy(index_corredores.id_corredor, id_corredores + (i*(TAM_ID_CORREDOR-1)), TAM_ID_CORREDOR-1);
		index_corredores.id_corredor[TAM_ID_CORREDOR-1] = '\0';
		//printf("ID_CORREDOR %d: %s\n",i, index_corredores.id_corredor);
		corredores_index *found_corredor = busca_binaria((void*)&index_corredores, corredores_idx, qtd_registros_corredores, sizeof(corredores_index),qsort_corredores_idx ,false, 0);
		//printf("RETORNO DA BUSCA CORREDOR: %p\n", found_corredor);
		if(found_corredor == NULL || found_corredor->rrn == -1){
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}
	}


	//verificar se veiculos existem
	veiculos_index index_veiculos;
	for(int i = 0; i < 6; i++) {
		strncpy(index_veiculos.id_veiculo, id_veiculos + (i*(TAM_ID_VEICULO-1)), TAM_ID_VEICULO-1);
		index_veiculos.id_veiculo[TAM_ID_VEICULO-1] = '\0';
		//printf("ID_VEICULO %d: %s\n",i, index_veiculos.id_veiculo);
		veiculos_index *found_veiculo = busca_binaria((void*)&index_veiculos, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index),qsort_veiculos_idx ,false, 0);
		//printf("RETORNO DA BUSCA VEICULO: %p\n", found_veiculo);
		if(found_veiculo == NULL){
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}
	}

	//verificar se aquele corredor possui aquele carro
	char modelo_maiusculo[TAM_MAX_MODELO]; //variavel para guardar o modelo em maiusculo
	// for para percorrer os 6 corredores participando da corrida
	int flag2 = 0;
	for(int i = 0; i < 6; i++) {
		//busca binarias em cima dos parametro de id_corredores e id_veiculos para recuperar os dados do corredor e veiculo
		int flag = 0;
		strncpy(index_corredores.id_corredor, id_corredores + (i*(TAM_ID_CORREDOR-1)), TAM_ID_CORREDOR-1);
		strncpy(index_veiculos.id_veiculo, id_veiculos + (i*(TAM_ID_VEICULO-1)), TAM_ID_VEICULO-1);
		index_corredores.id_corredor[TAM_ID_CORREDOR-1] = '\0';
		index_veiculos.id_veiculo[TAM_ID_VEICULO-1] = '\0';
		corredores_index *found_corredor = busca_binaria((void*)&index_corredores, corredores_idx, qtd_registros_corredores, sizeof(corredores_index),qsort_corredores_idx ,false, 0);
		veiculos_index *found_veiculo = busca_binaria((void*)&index_veiculos, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index),qsort_veiculos_idx ,false, 0);
		// recupera corredor e veiculo
		Corredor c = recuperar_registro_corredor(found_corredor->rrn);
		Veiculo v = recuperar_registro_veiculo(found_veiculo->rrn);
		strcpy(modelo_maiusculo, v.modelo);
		strupr(modelo_maiusculo); // modelo_maiusculo agr está maiusculo
		if(found_corredor != NULL && found_corredor->rrn != -1 && found_veiculo != NULL){
			for(int j = 0; j < 3; j++){
				//printf("CARRO DO CORREDOR %d : %s\n É: %s\n", i, c.veiculos[j], v.modelo);
				if(strlen(c.veiculos[j]) > 0){
					if(strcmp(c.veiculos[j], v.modelo) == 0) {
						//corredor possui o modelo do carro
						flag = 1;
						break;
					}
				} else {
					//corredor nao tem o veiculo
					flag = 1;
					flag2 = 1;
					printf(ERRO_CORREDOR_VEICULO, c.id_corredor, v.id_veiculo);
					break;
					
				}
			}
			// caso percorra todos os 3 veiculos e não chegue no break, corredor nao tem o veiculo
			if(flag == 0){
				flag2 = 1;
				printf(ERRO_CORREDOR_VEICULO, c.id_corredor, v.id_veiculo);
				break;
			}

		}
	}

	if (flag2 == 1 )
	{
		return;
	}
	

	// Se passar nas verificações
	//cria e cadastra corrida
	Corrida co;
	strcpy(co.id_pista, id_pista);
	strcpy(co.ocorrencia, ocorrencia);
	strcpy(co.id_corredores, id_corredores);
	strcpy(co.id_veiculos, id_veiculos);
	escrever_registro_corrida(co, qtd_registros_corridas);

	//altera e ordena os indices
	strcpy(corridas_idx[qtd_registros_corridas].id_pista, co.id_pista);
	strcpy(corridas_idx[qtd_registros_corridas].ocorrencia, co.ocorrencia);
	corridas_idx[qtd_registros_corridas].rrn = qtd_registros_corridas;
	//ordena e incrementa
	qsort(corridas_idx, qtd_registros_corridas + 1, sizeof(corridas_index), qsort_corridas_idx);
	qtd_registros_corridas++;


	//define o valor total do premio e para cada colocado
	strcpy(index_pista.id_pista, id_pista);
	found_pista = busca_binaria((void*)&index_pista, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, false, 0);
	Pista p = recuperar_registro_pista(found_pista->rrn);
	double premio_total = 6 * (TX_FIXA * p.dificuldade);
	double premio1 = 0.4*premio_total;
	double premio2 = 0.3*premio_total;
	double premio3 = 0.2*premio_total;
	
	//atualiza o saldo dos 3 primeiros corredores
	strncpy(index_corredores.id_corredor, id_corredores + (0*(TAM_ID_CORREDOR-1)), TAM_ID_CORREDOR-1);
	index_corredores.id_corredor[TAM_ID_CORREDOR-1] = '\0';
	corredores_index *found_corredor = busca_binaria((void*)&index_corredores, corredores_idx, qtd_registros_corredores, sizeof(corredores_index),qsort_corredores_idx ,false, 0);
	adicionar_saldo(found_corredor->id_corredor, premio1, false);
	strncpy(index_corredores.id_corredor, id_corredores + (1*(TAM_ID_CORREDOR-1)), TAM_ID_CORREDOR-1);
	index_corredores.id_corredor[TAM_ID_CORREDOR-1] = '\0';
	found_corredor = busca_binaria((void*)&index_corredores, corredores_idx, qtd_registros_corredores, sizeof(corredores_index),qsort_corredores_idx ,false, 0);
	adicionar_saldo(found_corredor->id_corredor, premio2, false);
	strncpy(index_corredores.id_corredor, id_corredores + (2*(TAM_ID_CORREDOR-1)), TAM_ID_CORREDOR-1);
	index_corredores.id_corredor[TAM_ID_CORREDOR-1] = '\0';
	found_corredor = busca_binaria((void*)&index_corredores, corredores_idx, qtd_registros_corredores, sizeof(corredores_index),qsort_corredores_idx ,false, 0);
	adicionar_saldo(found_corredor->id_corredor, premio3, false);

	printf(SUCESSO);
	return;
	//printf(ERRO_NAO_IMPLEMENTADO, "executar_corrida_menu()");
}

/* Busca */
void buscar_corredor_id_menu(char *id_corredor) {
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
    corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, true, 0);
	if (found == NULL || found->rrn < 0)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_corredor(found->rrn);
}

void buscar_pista_id_menu(char *id_pista) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	pistas_index index;
	strcpy(index.id_pista, id_pista);
    pistas_index *found = busca_binaria((void*)&index, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, true, 0);
	if (found == NULL || found->rrn < 0)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_pista(found->rrn);
}

void buscar_pista_nome_menu(char *nome_pista) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	nome_pista_index index;
	strcpy(index.nome, strupr(nome_pista));
    nome_pista_index *found = busca_binaria((void*)&index, nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx, true, 0);
	if (found == NULL)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		buscar_pista_id_menu(found->id_pista);
}

/* Listagem */
void listar_corredores_id_menu() {
	if (qtd_registros_corredores == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
		for (unsigned int i = 0; i < qtd_registros_corredores; i++)
			exibir_corredor(corredores_idx[i].rrn);
}

void listar_corredores_modelo_menu(char *modelo){
	/*IMPLEMENTE A FUNÇÃO AQUI*/

	char modelo_maiusculo[TAM_MAX_MODELO]; //variavel para guardara o modelo em letras maiusculas
	strncpy(modelo_maiusculo, modelo, TAM_MAX_MODELO);
	strupr(modelo_maiusculo);

	//faz busca no indice secundario pelo modelo
	corredor_veiculos_secundario_index index_secundario;
	strcpy(index_secundario.chave_secundaria, modelo_maiusculo);
	corredor_veiculos_secundario_index * found = busca_binaria((void*)&index_secundario, corredor_veiculos_idx.corredor_veiculos_secundario_idx, corredor_veiculos_idx.qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx, false, 0);
	if (found != NULL){
		char chavescorredores[MAX_REGISTROS][TAM_ID_CORREDOR]; //vetor de strings para guardar IDs dos corredores
		
		//percorre a lista encadeada
		int quant = inverted_list_primary_search(chavescorredores, 1, found->primeiro_indice, NULL, &corredor_veiculos_idx);
		//ordena
		qsort(chavescorredores, quant, TAM_ID_CORREDOR, qsort_string_modelo);

		//exibir os corredores achados
		for(int j = 0; j < quant ; j++) {
			// busca de corredor pelo ID para ter acesso ao rrn
			corredores_index index_corredores;
			strcpy(index_corredores.id_corredor, chavescorredores[j]);
			corredores_index *found_corredor = busca_binaria((void*)&index_corredores, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
			if(found_corredor != NULL){
				exibir_corredor(found_corredor->rrn);
			} else{
				printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			}
		}
	} else{
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	}
}

void listar_veiculos_compra_menu(char *id_corredor) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(qtd_registros_corredores == 0 || qtd_registros_veiculos == 0){
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	}
	else{
		//busca e recupera corredor
		corredores_index index;
		veiculos_index index_v;
		strcpy(index.id_corredor, id_corredor);
    	corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
		if (found != NULL && found->rrn != -1){
			Corredor c = recuperar_registro_corredor(found->rrn);
			for (int i = 0; i < qtd_registros_veiculos; i++) {
				strcpy(index_v.id_veiculo, preco_veiculo_idx[i].id_veiculo); //usa o indice preco_veiculo para ordenar pelo preco
				veiculos_index *found_v = busca_binaria((void*)&index_v, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);
				if(found_v != NULL && found_v->rrn != -1){
					Veiculo v = recuperar_registro_veiculo(found_v->rrn);
					if(c.saldo >= v.preco) {
						exibir_veiculo(found_v->rrn);
					}
				}
			}
		}
		
	}
}

void listar_corridas_periodo_menu(char *data_inicio, char *data_fim) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	//Busca binaria com as datas de inicio e fim
	corridas_index *found_data_inicio = busca_binaria((void*)data_inicio, corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_data_idx, true, 1);
	corridas_index *found_data_fim = busca_binaria((void*)data_fim, corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_data_idx, false, -1);
	//printf("BUSCA DATA INICIO: %p\n",found_data_inicio );
	//printf("BUSCA DATA FIM: %p\n", found_data_fim);
	//verificacao
	if(found_data_inicio == NULL || found_data_fim == NULL){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	} else{
		while (found_data_inicio <= found_data_fim){
			exibir_corrida(found_data_inicio->rrn);
			found_data_inicio++;
		}
		
	}
}

/* Liberar espaço */
void liberar_espaco_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char arquivo_temp[TAM_ARQUIVO_CORREDORES + 1];
	char registro_corredor[TAM_REGISTRO_CORREDOR + 1];
	corredores_index index_corredores_temp[qtd_registros_corredores];
	int cont_registros = 0;
	int i = 0;
	Corredor c;

	// percorre toda a quantidade de registros de corredores
	while (i < qtd_registros_corredores) {
		c = recuperar_registro_corredor(i);
    
    	// verifica se o id do corredor não esta marcado como excluido
    	if (strncmp(c.id_corredor, "*|", 2) != 0) {
			//passa o registro correspondendo no arquivo para uma string
			strncpy(registro_corredor, ARQUIVO_CORREDORES + (i * TAM_REGISTRO_CORREDOR), TAM_REGISTRO_CORREDOR);
    		registro_corredor[TAM_REGISTRO_CORREDOR] = '\0';
        	// copia o registro que acabou de ser guardado para o arquivo temporario na posicao determinada por quantos registros ja foram inseridos
        	strncpy(arquivo_temp + (cont_registros * TAM_REGISTRO_CORREDOR), registro_corredor, TAM_REGISTRO_CORREDOR);
			//printf("ARQUIVO_TEMP: %s\n", arquivo_temp);
        	// define novas informacoes do indice
			strcpy(index_corredores_temp[cont_registros].id_corredor, c.id_corredor);
        	index_corredores_temp[cont_registros].rrn = cont_registros;
        	cont_registros++; // (DENTRO DO IF) so conta/incrementa para os arquivos que não estao excluidos
        	arquivo_temp[cont_registros * TAM_REGISTRO_CORREDOR] = '\0';
    	}
		
		i++;
	}

	// transcrevendo o arquivo temporario para o original
	strcpy(ARQUIVO_CORREDORES, arquivo_temp);
	qtd_registros_corredores = cont_registros; //nova quantidade de registros é a quantidade que foi reescrita

	// transcrevendo o indice temporario para o original
	for (i = 0; i < qtd_registros_corredores; i++) {
		//printf("CORREDORES_IDX: %s, %d\n INDEX TEMP: %s, %d\n", corredores_idx[i].id_corredor, corredores_idx[i].rrn, index_corredores_temp[i].id_corredor, index_corredores_temp[i].rrn);
    	corredores_idx[i] = index_corredores_temp[i];
	}
	// ordena
	qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
	printf(SUCESSO);
}

/* Imprimir arquivos de dados */
void imprimir_arquivo_corredores_menu() {
	if (qtd_registros_corredores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORREDORES);
}

void imprimir_arquivo_veiculos_menu() {
	if (qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_VEICULOS);
}

void imprimir_arquivo_pistas_menu() {
	if (qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_PISTAS);
}

void imprimir_arquivo_corridas_menu() {
	if (qtd_registros_corridas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORRIDAS);
}

/* Imprimir índices primários */
void imprimir_corredores_idx_menu() {
	if (corredores_idx == NULL || qtd_registros_corredores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_corredores; ++i)
			printf("%s, %d\n", corredores_idx[i].id_corredor, corredores_idx[i].rrn);
}

void imprimir_veiculos_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (veiculos_idx == NULL || qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_veiculos; ++i)
			printf("%s, %d\n", veiculos_idx[i].id_veiculo, veiculos_idx[i].rrn);
}

void imprimir_pistas_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (pistas_idx == NULL || qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_pistas; ++i)
			printf("%s, %d\n", pistas_idx[i].id_pista, pistas_idx[i].rrn);
}

void imprimir_corridas_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (corridas_idx == NULL || qtd_registros_corridas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_corridas; ++i)
			printf("%s, %s, %d\n", corridas_idx[i].ocorrencia, corridas_idx[i].id_pista , corridas_idx[i].rrn);
}

/* Imprimir índices secundários */
void imprimir_nome_pista_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (nome_pista_idx == NULL ||  qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_pistas; ++i)
			printf("%s, %s\n", nome_pista_idx[i].nome, nome_pista_idx[i].id_pista);
}

void imprimir_preco_veiculo_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (preco_veiculo_idx == NULL ||  qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_veiculos; ++i)
			printf("%.2lf, %s\n", preco_veiculo_idx[i].preco, preco_veiculo_idx[i].id_veiculo);
}

void imprimir_corredor_veiculos_secundario_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (corredor_veiculos_idx.corredor_veiculos_secundario_idx == NULL ||  corredor_veiculos_idx.qtd_registros_secundario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < corredor_veiculos_idx.qtd_registros_secundario; ++i)
			printf("%s, %d\n", corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].chave_secundaria, corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].primeiro_indice);
}

void imprimir_corredor_veiculos_primario_idx_menu(){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (corredor_veiculos_idx.corredor_veiculos_primario_idx == NULL ||  corredor_veiculos_idx.qtd_registros_primario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < corredor_veiculos_idx.qtd_registros_primario; ++i)
			printf("%s, %d\n", corredor_veiculos_idx.corredor_veiculos_primario_idx[i].chave_primaria, corredor_veiculos_idx.corredor_veiculos_primario_idx[i].proximo_indice);
}

/* Liberar memória e encerrar programa */
void liberar_memoria_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	//free em todos os índices
	free(corredores_idx);
	free(veiculos_idx);
	free(pistas_idx);
	free(corridas_idx);
	free(nome_pista_idx);
	free(preco_veiculo_idx);
	free(corredor_veiculos_idx.corredor_veiculos_secundario_idx);
	free(corredor_veiculos_idx.corredor_veiculos_primario_idx);
}

void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/

	//insere a chave primaria
	strcpy(t->corredor_veiculos_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);
	t->corredor_veiculos_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
	//printf("INSERE NO INDICE PRIMARIO: %s, %d\n", t->corredor_veiculos_primario_idx[t->qtd_registros_primario].chave_primaria, t->corredor_veiculos_primario_idx[t->qtd_registros_primario].proximo_indice);

	// verificar se a chave secundaria ja existe no indice secundario
	char chave_secundaria_maiuscula[t->tam_chave_secundaria + 1]; //variavel para guardar em maiusculo
	strcpy(chave_secundaria_maiuscula, chave_secundaria);
	strupr(chave_secundaria_maiuscula);
	
	int primeira_ocorrencia;

	//Procura na lista secundaria
	bool found = inverted_list_secondary_search(&primeira_ocorrencia, 0, chave_secundaria_maiuscula, t);
	if(found){
		// se já existir, percorrer a lista encadeada
		int ultima_ocorrencia; // variavel para guardar a ultima ocorrencia
		inverted_list_primary_search(NULL, 0, primeira_ocorrencia, &ultima_ocorrencia, t);
		//o proximo do antigo é o atual que está sendo inserido
		t->corredor_veiculos_primario_idx[ultima_ocorrencia].proximo_indice = t->qtd_registros_primario;
	} else {
		// se não existir, insere no índice secundário
		strcpy(t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].chave_secundaria, chave_secundaria_maiuscula);
		t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].primeiro_indice = t->qtd_registros_primario;
		//printf("INSERE NO INDICE SECUNDARIO: %s(modelo)  %d (primeiro indice)\n", t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].chave_secundaria, t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].primeiro_indice);
		t->qtd_registros_secundario++;
		// ordena indice secundario
		qsort(t->corredor_veiculos_secundario_idx, t->qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx);
	}
	t->qtd_registros_primario++;
}

bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	// Faz busca no indice secundario
	corredor_veiculos_secundario_index *found = busca_binaria(chave_secundaria, t->corredor_veiculos_secundario_idx, t->qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx, exibir_caminho, 0);

	if(found == NULL){
		*result = -1; //pode ser NULL?
		return false;
	} else{
		//pega primeira ocorrencia
		*result = found->primeiro_indice;
		return true;
	}
}

int inverted_list_primary_search(char result[][TAM_ID_CORREDOR], bool exibir_caminho, int indice, int *indice_final, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int cont = 0; //variavel que guarda qtd de chaves percorridas
	if(exibir_caminho)
		printf(REGS_PERCORRIDOS);

	while (indice != -1 || cont == 0) //mesmo se percorrer uma chave só
	{
		if(exibir_caminho) 
			printf(" %d", indice); //printa a chave
		
		if (result != NULL){
			// armazena a chave
			strcpy(result[cont], t->corredor_veiculos_primario_idx[indice].chave_primaria);
		}

		if(indice_final != NULL){
			*indice_final = indice;
		}
		indice = t->corredor_veiculos_primario_idx[indice].proximo_indice;
		
		cont++;
	}
	

	if(exibir_caminho)
		printf("\n");
	
	return cont; //retorna a quantidade de chaves encontradas
}


void* busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	
	const char *base = (const char*)base0;
	// em termos de indice de um vetor
    int minimo = 0;
    int maximo = nmemb - 1;
	int comparar;
	const void *valor; 
	int flag = 0; //flag para auxiliar no print
	int meio;

    while (maximo >= minimo) {

		if((minimo + maximo)%2 == 0){
			meio = (minimo + maximo)/2;
		} else {
			meio = (minimo+maximo)/2 + 1; //pega sempre acima
		}

		if(exibir_caminho){
			if(flag == 0){ //para printar apenas uma vez
				printf(REGS_PERCORRIDOS);
				flag++;
			}
			printf(" %d", meio);
		}
		
		//verificar se o meio é igual ao que se procura usando a funcao comparar e seus retornos
		valor = base + (size * meio); //valor na posicao do meio
		comparar = (*compar)(key, valor);

		if(comparar == 0) { //é igual
			if(exibir_caminho)
				printf("\n");
			return ((void*)valor);
		}

		if(comparar < 0) //ta na metade menor
			maximo = meio - 1;
		

		if(comparar > 0) // ta na metade maior
			minimo= meio + 1;
	}

	//para pegar a data sucessora da data solicitada
    if (retorno_se_nao_encontrado == 1)
    {

        if (comparar < 0) {
			//já é o sucessor
            if(exibir_caminho)
				printf("\n");
			return ((void *)valor);
        }

        if (meio < nmemb - 1) {
			//meio é maior que a chave
            meio++;
            valor = base + (size * meio);
            if(exibir_caminho)
				printf("\n");
			return ((void *)valor);
        }
		// é o ultimo elemento
            if(exibir_caminho)
				printf("\n");
			return NULL;
    }

	// para pegar a data antecessora da data desejada
	if (retorno_se_nao_encontrado == -1)
    {
        if (comparar > 0) {
			//já é o antecessor
			if(exibir_caminho)
				printf("\n");
            return ((void *)valor);
        }

        if (meio > 0) {
			// meio é menor que primeiro elemento
            meio--;
            valor = base + (size * meio);
			if(exibir_caminho)
				printf("\n");
            return ((void *)valor);
        }

		if(exibir_caminho)
			printf("\n");
        return NULL;
    }

	if (exibir_caminho)
		printf("\n");
	return (NULL);
}

void* busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado) {
	return busca_binaria_com_reps(key, base0, nmemb, size, compar, exibir_caminho, 0, retorno_se_nao_encontrado);
}

char *strpadright(char *str, char pad, unsigned size){
	for (unsigned i = strlen(str); i < size; ++i)
		str[i] = pad;
	str[size] = '\0';
	return str;
}
char *strupr(char *str){
	for (char *p = str; *p; ++p)
		*p = toupper(*p);
	return str;
}
char *strlower(char *str){
	for (char *p = str; *p; ++p)
		*p = tolower(*p);
	return str;
}