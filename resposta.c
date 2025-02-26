#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadlista.h"
#include "tadmatriz.h"

void processa_operacao(char *operacao, tadmatriz A, tadmatriz B, tadmatriz C, tadmatriz D){

    tadmatriz matriz = NULL;
    char arquivo[50];

    if (strcmp(operacao, "A + B") == 0) {
        printf("Processando operacao: A + B\n");
        matriz = soma(A, B);
        strcpy(arquivo, "AmaisB.txt");
    }
    else if (strcmp(operacao, "A x B") == 0) {
        printf("Processando operacao: A x B\n");
        matriz = multi(A, B);
        strcpy(arquivo, "AvezesB.txt");
    }
    else if (strcmp(operacao, "C + TD") == 0) {
        printf("Processando operacao: C + TD\n");
        tadmatriz TD = transp(D);
        matriz = soma(C, TD);
        strcpy(arquivo, "CmaistranspD.txt");
    }
    else if (strcmp(operacao, "A - B") == 0) {
        printf("Processando operacao: A - B\n");
        tadmatriz negB = neg(B);
        matriz = soma(A, negB);
        strcpy(arquivo, "AmenosB.txt");
    }
    else if (strcmp(operacao, "-A x B") == 0) {
        printf("Processando operacao: -A x B\n");
        tadmatriz negA = neg(A);
        matriz = multi(negA, B);
        strcpy(arquivo, "menosAvezesB.txt");
    }
    else if (strcmp(operacao, "A x TD") == 0) {
        printf("Processando operacao: A x TD\n");
        tadmatriz TD = transp(D);
        matriz = multi(A, TD);
        strcpy(arquivo, "AvezestranspD.txt");
    }
    else if (strcmp(operacao, "-B x TD") == 0) {
        printf("Processando operacao: -B x TD\n");
        tadmatriz negB = neg(B);
        tadmatriz TD = transp(D);
        matriz = multi(negB, TD);
        strcpy(arquivo, "menosBvezestranspD.txt");
    }


    salva(matriz, arquivo);
    libera_matriz(matriz);

}

int main(){

    tadmatriz A = carrega("A.txt");
    tadmatriz B = carrega("B.txt");
    tadmatriz C = carrega("C.txt");
    tadmatriz D = carrega("D.txt");

    if (A == NULL || B == NULL || C == NULL || D == NULL) {
        fprintf(stderr, "Erro ao carregar uma ou mais matrizes.\n");
        libera_matriz(A);
        libera_matriz(B);
        libera_matriz(C);
        libera_matriz(D);
        return 1;
    }

    FILE *arq = fopen("matops.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir matops.txt");
        return 1;
    }

    char operacao[50];
    while (fgets(operacao, sizeof(operacao), arq)) {
        operacao[strcspn(operacao, "\n")] = 0;
        if (strlen(operacao) > 0) {
            processa_operacao(operacao, A, B, C, D);
        }
    }

    fclose(arq);

    libera_matriz(A);
    libera_matriz(B);
    libera_matriz(C);
    libera_matriz(D);

    return 0;
}   