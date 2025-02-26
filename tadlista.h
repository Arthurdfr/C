#ifndef ___BSI_ED_2024_1_LISTA__

#define ___BSI_ED_2024_1_LISTA__

/* PRIVADO: NÃO PODE SER ALTERADO */
typedef void *t_dado;

typedef struct tipo_no {
  t_dado dado;
  struct tipo_no *anterior;
  struct tipo_no *proximo;
} * t_no;

typedef struct tipo_lista {
  t_no primeiro;
  t_no ultimo;
  int tamanho;
} * Lista;

Lista new_lista();
int lenLista(Lista l);
Lista appendLista(Lista l, t_dado d);
t_dado elemLista(Lista l, int pos);
Lista insereLista(Lista l, t_dado dado, int pos);
t_dado removeLista(Lista l, int pos);

#endif