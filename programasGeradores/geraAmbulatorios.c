#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Abrir o arquivo para escrever
    FILE *arquivo;
    arquivo = fopen("ambulatorios.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    // Inicializar a semente para geração de números aleatórios
    srand(time(NULL));

    fprintf(arquivo, "numeroA, andar, capacidade\n");
    for (int i = 1; i <= 1000; i++) {
        // Gerar um número aleatório entre 1 e 6 para o andar
        int andar = rand() % 6 + 1;
        // Gerar um número aleatório entre 5 e 60 para a capacidade
        int capacidade = rand() % 56 + 5; // Isso vai de 5 a 60

        // Escrever os dados no arquivo
        fprintf(arquivo, "%d, %d, %d\n", i, andar, capacidade);
    }

    // Fechar o arquivo
    fclose(arquivo);

    return 0;
}

