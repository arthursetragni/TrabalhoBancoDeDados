#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_NOMES 100000
#define NUM_PACIENTES 100000

typedef struct {
    int rg;
    char nome[50];
    char idade[11];
    char cidade[50];
    char doenca[50];
} Paciente;

char *cidades[] = {"Santa Luzia", "Belo Horizonte", "Ribeirão das Neves", "Contagem", "Betim"};

char *doencas[] = {"pneumonia", "dengue", "cancer", "catapora", "covid-19", "artrite", "fibromialgia", "febre amarela", "gripe", "virose"};

// Array de nomes
char nomes[NUM_NOMES][50];

// Função para ler nomes do arquivo e armazenar no array
void lerNomes() {
    // Abrir o arquivo de nomes
    FILE *arquivo;
    arquivo = fopen("NationalNames.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de nomes.");
        exit(1);
    }

    // Ler os nomes do arquivo e armazenar no array
    for (int i = 0; i < NUM_NOMES; i++) {
        fgets(nomes[i], 50, arquivo);
        // Remover o caractere de nova linha, se presente
        nomes[i][strlen(nomes[i]) - 2] = '\0';
    }

    fclose(arquivo);
}

// Função para escolher um nome aleatório do array
char *obterNomeAleatorio() {
    return nomes[rand() % NUM_NOMES];
}

void gerarDataAleatoria(char *data) {
    int ano = rand() % (2024 - 1944 + 1) + 1944; // Ano entre 2000 e 2019
    int mes = rand() % 12 + 1; // Mês entre 1 e 12
    int dia;
    if (mes == 2) {
        // Se for fevereiro, ajustar para até 28 dias
        dia = rand() % 28 + 1;
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        // Se for abril, junho, setembro ou novembro, ajustar para até 30 dias
        dia = rand() % 30 + 1;
    } else {
        // Para os outros meses, até 31 dias
        dia = rand() % 31 + 1;
    }
    sprintf(data, "%d-%02d-%02d", ano, mes, dia);
}  

int main() {
    // Abrir o arquivo para escrever
    FILE *arquivo;
    arquivo = fopen("pacientes.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    // Inicializar a semente para geração de números aleatórios
    srand(time(NULL));

    // Carregar nomes do arquivo
    lerNomes();

    // Escrever o cabeçalho no arquivo CSV
    fprintf(arquivo, "rg,nome,idade,cidade,doenca\n");

    // Gerar 100000 pacientes
    int rg = 20306325;
    for (int i = 0; i < NUM_PACIENTES; i++) {
        Paciente paciente;
        paciente.rg = rg + (i * 777); // RG sequencial começando em 56789234 e aumentando de 777 em 777
        strcpy(paciente.nome, obterNomeAleatorio());
        gerarDataAleatoria(paciente.idade); // Idade entre 1 e 99
        strcpy(paciente.cidade, cidades[rand() % 5]); // Escolha aleatória de uma cidade
        strcpy(paciente.doenca, doencas[rand() % 10]); // Escolha aleatória de uma doença

        // Escrever os dados do paciente no arquivo CSV
        fprintf(arquivo, "%d,%s,%s,%s,%s\n", paciente.rg, paciente.nome, paciente.idade, paciente.cidade, paciente.doenca);
    }

    // Fechar o arquivo
    fclose(arquivo);

    return 0;
}
