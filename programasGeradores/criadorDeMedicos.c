#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_NOMES 100000
#define NUM_MEDICOS 5000

// Definição da struct Medico
typedef struct {
    int crm;
    char nome[50];
    int idade;
    char cidade[50];
    char especialidade[50];
    int numeroA;
} Medico;

// Array de cidades
char *cidades[] = {"Santa Luzia", "Belo Horizonte", "Ribeirão das Neves", "Contagem", "Betim"};

// Array de especialidades
char *especialidades[] = {"Neurologista", "Cardiologista", "Dermatologista", "Ortopedista", "Pediatra", "Cirurgião"};

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

int main() {
    // Abrir o arquivo para escrever
    FILE *arquivo;
    arquivo = fopen("medicos.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    // Inicializar a semente para geração de números aleatórios
    srand(time(NULL));

    // Carregar nomes do arquivo
    lerNomes();

    // Escrever o cabeçalho no arquivo CSV
    fprintf(arquivo, "crm,nome,idade,cidade,especialidade,numeroA\n");

    // Gerar 5000 médicos
    for (int i = 0; i < NUM_MEDICOS; i++) {
        Medico medico;
        medico.crm = 1000 + i; // CRM sequencial a partir de 1000
        strcpy(medico.nome, obterNomeAleatorio());
        medico.idade = rand() % 46 + 25; // Idade entre 25 e 70
        strcpy(medico.cidade, cidades[rand() % 5]); // Escolha aleatória de uma cidade
        strcpy(medico.especialidade, especialidades[rand() % 6]); // Escolha aleatória de uma especialidade
        medico.numeroA = rand() % 1000 + 1; // Número aleatório entre 1 e 1000

        // Escrever os dados do médico no arquivo CSV
        fprintf(arquivo, "%d,%s,%d,%s,%s,%d\n", medico.crm, medico.nome, medico.idade, medico.cidade, medico.especialidade, medico.numeroA);
    }

    // Fechar o arquivo
    fclose(arquivo);

    return 0;
}
