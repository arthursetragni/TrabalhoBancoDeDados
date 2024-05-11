#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CONSULTAS 10000

typedef struct {
    int crm;
    int rg;
    char data[11]; // Tamanho 11 para armazenar YYYY-MM-DD
    char hora[9]; // Tamanho 9 para armazenar HH:MM:SS
} Consulta;

// Função para gerar uma data aleatória no formato YYYY-MM-DD
void gerarDataAleatoria(char *data) {
    int ano = 2024; // Ano entre 2000 e 2019
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

// Função para gerar uma hora aleatória no formato HH:MM:SS
void gerarHoraAleatoria(char *hora) {
    int horas = rand() % 24; // Horas entre 0 e 23
    int minutos = rand() % 60; // Minutos entre 0 e 59
    int segundos = rand() % 60; // Segundos entre 0 e 59
    sprintf(hora, "%02d:%02d:%02d", horas, minutos, segundos);
}

int main() {
    FILE *arquivo;
    arquivo = fopen("consultas.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    srand(time(NULL)); // Inicializar a semente do gerador de números aleatórios

    // Escrever o cabeçalho no arquivo CSV
    fprintf(arquivo, "crm,rg,data,hora\n");
    int rg = 20306325;

    // Gerar 10000 consultas
    for (int i = 0; i < NUM_CONSULTAS; i++) {
        Consulta consulta;
        consulta.crm = rand() % 5000 + 1000; // CRM aleatório entre 1000 e 5999
        consulta.rg = ((rand() % 100000 + 1) * 777) + rg; // RG aleatório entre 1 e 100000
        gerarDataAleatoria(consulta.data);
        gerarHoraAleatoria(consulta.hora);

        // Escrever os dados da consulta no arquivo CSV
        fprintf(arquivo, "%d,%d,%s,%s\n", consulta.crm, consulta.rg, consulta.data, consulta.hora);
    }

    // Fechar o arquivo
    fclose(arquivo);

    return 0;
}
