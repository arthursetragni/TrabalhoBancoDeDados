#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define NUM_NOMES 100000
#define NUM_FUNCIONARIOS 2000

typedef struct {
    int rg;
    char nome[50]; // Mudança: Usar array de caracteres para armazenar o nome
    char idade[11];
    char cidade[50]; // Mudança: Usar array de caracteres para armazenar a cidade
    double salario;
} Funcionario;

char *cidades[] = {"Santa Luzia", "Belo Horizonte", "Ribeirão das Neves", "Contagem", "Betim"};

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
    int ano = rand() % (1999 - 1944 + 1) + 1944; // Ano entre 2000 e 2019
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
    arquivo = fopen("funcionarios.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    // Inicializar a semente para geração de números aleatórios
    srand(time(NULL));

    // Carregar nomes do arquivo
    lerNomes();

    // Escrever o cabeçalho no arquivo CSV
    fprintf(arquivo, "rg,nome,idade,cidade,salario\n");

    // Gerar 2000 funcionários
    int rg = 10702325;
    for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
        Funcionario funcionario;
        funcionario.rg = rg + (i * 21); // RG sequencial começando em 10702325 e aumentando de 21 em 21
        strcpy(funcionario.nome, obterNomeAleatorio());
        gerarDataAleatoria(funcionario.idade);// Idade entre 1 e 99
        strcpy(funcionario.cidade, cidades[rand() % 5]); // Escolha aleatória de uma cidade
        funcionario.salario = (rand() % 1201 + 1300) * 1.0; // Salário entre 1300 e 2500

        // Escrever os dados do funcionário no arquivo CSV
        fprintf(arquivo, "%d,%s,%s,%s,%.2lf\n", funcionario.rg, funcionario.nome, funcionario.idade, funcionario.cidade, funcionario.salario);
    }

    // Fechar o arquivo
    fclose(arquivo);

    return 0;
}
