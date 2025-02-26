#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadlista.h"

Lista new_lista() {
  Lista l = (Lista)malloc(sizeof(struct tipo_lista));
  l->primeiro = NULL;
  l->ultimo = NULL;
  l->tamanho = 0;
  return l;
}

int lenLista(Lista l) { return l->tamanho; }

Lista appendLista(Lista l, t_dado d) {
  t_no no = (t_no)malloc(sizeof(struct tipo_no));
  no->dado = d;
  no->anterior = NULL;
  no->proximo = NULL;

  if (l->tamanho == 0) {
    l->primeiro = no;
    l->ultimo = no;
  } else {
    l->ultimo->proximo = no;
    no->anterior = l->ultimo;
    l->ultimo = no;
  }
  l->tamanho++;

  return l;
}

t_dado elemLista(Lista l, int pos) {
  t_no aux;
  int cont = 0;

  if ((pos >= 0) && (pos < l->tamanho) && (l->tamanho > 0)) {
    aux = l->primeiro;
    for (cont = 0; cont < pos; cont++) {
      aux = aux->proximo;
    }
    return aux->dado;
  } else
    return NULL;
}

Lista insereLista(Lista l, t_dado dado, int pos) {
  if ((pos >= 0) && (pos <= l->tamanho)) {
    // O primeiro nó de uma lista vazia ou um novo último nó..
    if ((l->tamanho == 0) || (pos == l->tamanho))
      appendLista(l, dado);
    else { // lista não é vazia
      // Um nó SEMPRE precisa ser criado.
      t_no novo_noh = (t_no)malloc(sizeof(struct tipo_no));
      novo_noh->anterior = NULL;
      novo_noh->proximo = NULL;

      // Dados NÃO são encadeados na lista.
      // Dados são encapsulados no nó, nós é que são encadeados na lista.
      novo_noh->dado = dado;

      // Nesse ponto, independente da posição, a lista ganhará um nó adicional.
      l->tamanho++;

      if (pos == 0) { // insere na primeira posição de uma lista não vazia.
        novo_noh->proximo = l->primeiro;
        l->primeiro->anterior = novo_noh;
        l->primeiro = novo_noh;
      } else { // insere entre a 2a posição e a última, inclusive.
        t_no aux;
        int cont = 0;

        // Alcança o nó corrente na posição pos da lista.
        aux = l->primeiro;
        for (cont = 0; cont < pos; cont++) {
          aux = aux->proximo;
        }

        // O novo nó se conecta à lista
        novo_noh->anterior = aux->anterior;
        novo_noh->proximo = aux;

        // Os elementos da lista se conectam ao novo nó.
        aux->anterior->proximo = novo_noh;
        aux->anterior = novo_noh;
      }
    }
  }
  return l;
} // fim insereLista

t_dado removeLista(Lista l, int pos) {
  if ((pos >= 0) && (pos < l->tamanho) && (l->tamanho != 0)) {
    /* pos válida para remoção */
    if (pos == 0) {          // remove o primeiro nó
      if (l->tamanho == 1) { // remove o primeiro nó de uma lista de 1 nó apenas
        t_dado aux = l->primeiro->dado;
        free(l->ultimo);
        l->primeiro = NULL;
        l->ultimo = NULL;
        l->tamanho--;
        return aux;
      }
      // remove o primeiro nó de uma lista com mais de 1 nó.
      t_dado bkp_dado = l->primeiro->dado;
      t_no bkp_no = l->primeiro;

      l->primeiro = bkp_no->proximo;
      l->primeiro->anterior = NULL;
      l->tamanho--;

      free(bkp_no);
      return bkp_dado;
    } else {
      if (pos ==
          l->tamanho -
              1) { // remove o último nó de uma lista (com 1 ou mias de 1 nó)
        t_no bkp_no = l->ultimo;
        t_dado bkp_dado = l->ultimo->dado;

        l->ultimo = bkp_no->anterior;
        l->ultimo->proximo = NULL;
        l->tamanho--;

        free(bkp_no);
        return bkp_dado;
      } else { // remove nó entre primeiro e último de uma lista com mais de 1
               // nó.
        t_no bkp_no = l->primeiro;
        t_dado bkp_dado;

        int cont;
        for (cont = 0; cont < pos; cont++) {
          bkp_no = bkp_no->proximo;
        }

        bkp_dado = bkp_no->dado;

        bkp_no->anterior->proximo = bkp_no->proximo;
        bkp_no->proximo->anterior = bkp_no->anterior;
        l->tamanho--;

        free(bkp_no);
        return bkp_dado;
      }
    }
  } else
    return NULL; // <= apenas temporariamente
}
