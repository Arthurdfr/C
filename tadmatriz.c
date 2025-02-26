#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadlista.h"
#include "tadmatriz.h"

void libera_matriz(tadmatriz matriz) {
    if (matriz != NULL) {
        for (int i = 0; i < matriz->linhas; i++) {
            free(matriz->dados[i]);
        }
        free(matriz->dados);
        free(matriz);
    }
}

tadmatriz cria_mat(int qlinhas, int qcolunas){

    /*cria e retorna uma struct dinâmica do tipo tadmatriz. tcria_mat retorna uma matriz cheia de zeros (listas com tamanho igual a colunas de zeros)*/
    
    tadmatriz matriz = (tadmatriz)malloc(sizeof(struct t_matriz));
    if (matriz == NULL) {
        return NULL;
    }

    matriz->linhas = qlinhas;
    matriz->colunas = qcolunas;

    matriz->dados = (Lista *)malloc(qlinhas * sizeof(Lista));
    if (matriz->dados == NULL) {
        free(matriz);
        return NULL;
    }

    for (int i = 0; i < qlinhas; i++) {
        matriz->dados[i] = new_lista();
        for (int j = 0; j < qcolunas; j++) {
            appendLista(matriz->dados[i], 0);
        }
    }

    return matriz;
}

void set_elem(tadmatriz matriz, int linha, int coluna, float valor){
    
    /*modifica o valor do elemento da matriz na posição linha (posição no vetor dinâmico) e coluna (posição na lista) fornecidos.*/
    
    float *ptr = (float*)malloc(sizeof(float));
    if (ptr == NULL) {
        return;
    }
    *ptr = valor;
    t_dado numero = (void*)ptr;

    t_dado *valor_antigo = removeLista(matriz->dados[linha], coluna);
    if (valor_antigo != NULL) {
        free(valor_antigo);
    }

    matriz->dados[linha] = insereLista(matriz->dados[linha], numero, coluna);
}


float get_elem(tadmatriz matriz, int linha, int coluna){

    /*retorna o valor do elemento linha(posição no vetor dinâmico) e coluna (posição na lista) armazenado na matriz.*/

    float *valor = (float*)elemLista(matriz->dados[linha], coluna);;
    
    return *valor;
}

int get_linhas(tadmatriz matriz){
    
    /*retorna o valor da quantidade de linhas da matriz.*/

    return matriz->linhas;
}
int get_colunas(tadmatriz matriz){

    /*retorna o valor da quantidade de colunas da matriz.*/

    return matriz->colunas;
}

tadmatriz soma(tadmatriz matrizA, tadmatriz matrizB){
    
    /*cria e retorna uma nova tad matriz com a
    soma dos tad matriz A e B passados como parâmetros de entrada. Tanto os parâmetros de
    entrada quanto o valor retornado na saída devem ser tad matrizes. Caso as matrizes de entrada
    não possam ser somadas, retornar o valor NULL. Use os métodos get_elem e set_elem para
    acessar os elementos dos tadmatriz.*/

    if((matrizA->linhas == matrizB->linhas) && (matrizA->colunas == matrizB->colunas)){
        tadmatriz matrizC = cria_mat(matrizA->linhas, matrizA->colunas);
        if (matrizC == NULL) {
            return NULL;
        }
        for(int i = 0; i < matrizA->linhas; i++){
            for(int j = 0; j < matrizA->colunas; j++){
            
                float valor = get_elem(matrizA, i, j) + get_elem(matrizB, i, j);
                set_elem(matrizC, i, j, valor);
            }
        }

        return matrizC;
    }

    else{
        return NULL;
    }
}

tadmatriz multi(tadmatriz matrizA, tadmatriz matrizB){

    /*cria e retorna uma nova tad matriz com a
    multiplicação matricial dos tad matriz A e B passados como parâmetros de entrada. Tando os
    parâmetros de entrada quanto o valor retornado na saída devem ser tad matrizes. Caso as
    matrizes de entrada não possam ser multiplicadas, retornar o valor NULL. Use os métodos
    get_elem e set_elem para acessar os elementos dos tadmatriz.*/

    if(matrizA->colunas == matrizB->linhas){
        tadmatriz matrizC = cria_mat(matrizA->linhas, matrizB->colunas);
        if (matrizC == NULL) {
            return NULL;
        }
        for (int i = 0; i < matrizA->linhas; i++) {
            for (int j = 0; j < matrizB->colunas; j++) {
                float soma = 0.0;
                for (int k = 0; k < matrizA->colunas; k++) {
                    soma += (get_elem(matrizA, i, k)) * (get_elem(matrizB, k, j));
                }
                set_elem(matrizC, i, j, soma);
            }
        }

        return matrizC;
    }

    else{
        return NULL;
    }
}

tadmatriz neg(tadmatriz matriz){

    /*multiplica por menos um (-1) os valores da tad matriz de
    entrada. Retorna a própria matriz de entrada com os valores modificados. Use os métodos
    get_elem e set_elem para acessar os elementos do tadmatriz.*/

    tadmatriz negA = cria_mat(matriz->linhas, matriz->colunas);
    if (negA == NULL) {
        return NULL;
    }
    for(int i = 0; i < matriz->linhas; i++){
        for(int j = 0; j < matriz->colunas; j++){

            set_elem(negA, i, j, get_elem(matriz, i, j)*(-1));
        }
    }
    
    return negA;
}

tadmatriz transp(tadmatriz matrizA){
    /*retorna uma nova tad matriz equivalente à transposta da tad
    matriz de entrada, tadA. Use os métodos get_elem e set_elem para acessar os elementos do
    tadmatriz.*/

    tadmatriz matrizT = cria_mat(matrizA->colunas, matrizA->linhas);
    if (matrizT == NULL) {
        return NULL;
    }
    for (int i = 0; i < matrizA->linhas; i++) {
        for (int j = 0; j < matrizA->colunas; j++) {
            set_elem(matrizT, j, i, get_elem(matrizA, i, j));
        }
    }

    return matrizT;
}

tadmatriz carrega(const char *arquivo){
    /*carrega uma matriz numérica a partir do arquivo de
    nome passado como parâmetro de entrada. Retorna uma tad matriz com os valores vindos do
    arquivo. O formato do arquivo é o mesmo usado nos arquivos fornecidos pelo Professor.*/

    FILE *arq = fopen(arquivo, "r");
    if (arq == NULL) {
    return NULL;
    }

    int linhas = 0, colunas = 0;
    char linha[1000];
    
    while (fgets(linha, sizeof(linha), arq)) {
        char *temp = linha;
        while (*temp == ' ' || *temp == '\t') temp++;
    
        if (*temp != '\n' && *temp != '\0') {
            if (linhas == 0) {
                char *token = strtok(linha, " \t\n");
                while (token != NULL) {
                    colunas++;
                    token = strtok(NULL, " \t\n");
                }
            }
            linhas++;
        }
    }
    
    rewind(arq);
    
    tadmatriz matriz = cria_mat(linhas, colunas);
    if (matriz == NULL) {
        fclose(arq);
        return NULL;
    }
    
    for (int i = 0; i < linhas; i++) {
        if (!fgets(linha, sizeof(linha), arq)) {
            libera_matriz(matriz);
            fclose(arq);
            return NULL;
        }
        
        char *token = strtok(linha, " \t\n");
        for (int j = 0; j < colunas; j++) {
            if (token == NULL) {
                libera_matriz(matriz);
                fclose(arq);
                return NULL;
            }
            float valor = atof(token);
            set_elem(matriz, i, j, valor);
            token = strtok(NULL, " \t\n");
        }
    }
    
    fclose(arq);
    return matriz;
}

tadmatriz salva(tadmatriz matriz, const char *arquivo){

    /*salva a tad matriz tadA no arquivo texto
    de nome igual ao fornecido no segundo parâmetro. Retorna a prórpria tad matriz tadA. O formato
    do arquivo é o mesmo usado nos arquivos fornecidos pelo Professor. Use os métodos get_elem
    e set_elem para acessar os elementos dos tadmatriz.*/

    if (matriz == NULL) {
        return NULL;
    }

    FILE *arq = fopen(arquivo, "w");
    if (arq == NULL) {
        return NULL;
    }

    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {

            float valor = get_elem(matriz, i, j);
            fprintf(arq, "\t%.2f", valor);
        }
        fprintf(arq, "\n");
    }

    fclose(arq);

    return matriz;
}