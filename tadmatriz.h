#include "tadlista.h"

typedef struct t_matriz {
    int linhas;
    int colunas;
    Lista *dados;
} *tadmatriz;

tadmatriz cria_mat(int qlinhas, int qcolunas);
void set_elem(tadmatriz matriz, int linha, int coluna, float valor);
float get_elem(tadmatriz matriz, int linha, int coluna);
int get_linhas(tadmatriz matriz);
int get_colunas(tadmatriz matriz);
tadmatriz soma(tadmatriz matrizA, tadmatriz matrizB);
tadmatriz multi(tadmatriz matrizA, tadmatriz matrizB);
tadmatriz neg(tadmatriz matriz);
tadmatriz transp(tadmatriz matrizA);
tadmatriz carrega(const char *arquivo);
tadmatriz salva(tadmatriz matriz, const char *arquivo);
void libera_matriz(tadmatriz matriz);