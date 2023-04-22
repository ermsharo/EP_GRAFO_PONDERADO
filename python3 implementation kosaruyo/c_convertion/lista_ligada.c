
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
    //outros campos
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    bool marcado;
    struct aux* prox;
}ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT inicio;
    PONT ultimo;
}LISTA;

void inicializarLista(LISTA* l){
    l->inicio = NULL;
    l->ultimo = NULL;
}

int tamanho(LISTA* l){
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL){
        tam++;
        end = end->prox;
    } 
    return tam;
}

void exibirLista(LISTA* l){
    PONT end = l->inicio;
    printf("Lista : \" ");
    while (end != NULL){
        printf("%i ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}

PONT buscaSequencial(LISTA* l, TIPOCHAVE ch){
    PONT pos = l->inicio;
    while(pos != NULL){
        if (pos->reg.chave == ch) return pos;
        pos = pos->prox;
    }
    return NULL;
}

PONT buscaSequencialExc(LISTA* l, TIPOCHAVE ch, PONT* ant){
    *ant = NULL;
    PONT atual = l->inicio;
    while ((atual != NULL ) && (atual->reg.chave < ch)){
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (atual->reg.chave == ch)) return atual;
    return NULL;
}

bool inserirElemListaOrd(LISTA* l, REGISTRO reg){
    TIPOCHAVE ch = reg.chave;
    PONT ant, i;
    i = buscaSequencialExc(l,ch,&ant);
    if (i != NULL) return false;
    i = (PONT) malloc(sizeof(ELEMENTO));
    i->reg = reg;
    if (ant == NULL){
        i->prox = l->inicio;
        l->inicio = i;
    } else {
        i->prox = ant->prox;
        ant->prox = i;
    }
    return true;
}
PONT vaiAteFinal(LISTA* l){
    PONT atual = l->inicio;
    while (atual->prox != NULL ){
        atual = atual->prox;
    }
    return atual;
}
void inserirFinal2(LISTA *l, int valor){
    TIPOCHAVE ch;
    REGISTRO reg;
    reg.chave = valor;
    PONT i = (PONT) malloc(sizeof(ELEMENTO));
    i->reg = reg;

    if (l->inicio == NULL){
        i->prox = l->inicio;
        l->inicio = i;
    }else{
        PONT ultimo = vaiAteFinal(l);
        ultimo->prox = i;
        i->prox = NULL;
    }
}

bool excluirElemLista(LISTA* l, TIPOCHAVE ch){
    PONT ant, i;
    i = buscaSequencialExc(l, ch, &ant);

    if (i == NULL) return false;
    if (ant == NULL) l->inicio = i->prox;
    else ant->prox = i->prox;
    free(i);
    return true;
}
bool excluir(LISTA* l, TIPOCHAVE ch){
    /**/
    if (l->inicio == NULL){
        return false;
    } else if (l->inicio->reg.chave == ch){
        PONT exc = l->inicio;
        l->inicio = l->inicio->prox;
        free(exc);
        return true;
    } else {
    
        PONT atual = l->inicio;
        PONT anterior;

        //printf("Poping : %d \n", atual->reg.chave);

        while (atual != NULL){
            //printf("in this : %d \n", atual->reg.chave);
            if (atual->reg.chave == ch){
                
                anterior->prox = atual->prox;
                free(atual);
                return true;
            }
            anterior = atual;
            atual = atual->prox; 
        }
        return false;
    }
    return false;
    /**/
}
 
void reinicializarLista(LISTA* l){
    PONT end = l->inicio;
    while (end != NULL){
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->inicio = NULL;
}

void inserir(LISTA *l, int valor){
  TIPOCHAVE ch;
  REGISTRO reg;
  reg.chave = valor;
  inserirElemListaOrd(l,reg);
}

bool pop(LISTA* l){
    //exibirLista(l);
    if (l->inicio == NULL){
        //printf("Nothing to pop \n");
        return false;
    }else if (l->inicio->prox == NULL){
        //printf("Pop first\n");
        bool b = false;
        b = excluirElemLista(l, l->inicio->reg.chave );
        return true;
    }else if ( l->inicio != NULL){
        PONT end = l->inicio ;

        while (end->prox != NULL){
            end = end->prox;
        }
        //printf("Poping : %d \n", end->reg.chave);
        excluir(l, end->reg.chave);
        //exibirLista(l);
        return true;
    }
    return false;
}

void setNode(LISTA *l, TIPOCHAVE ch, bool estado){
    PONT temp = buscaSequencial(l, ch);
    if ( temp != NULL){
        temp->marcado = estado;
    }
    
}
bool getNode(LISTA *l, TIPOCHAVE ch){
    PONT temp = buscaSequencial(l, ch);
    if ( temp != NULL){
        //printf("%i , %i ", temp->marcado, temp->reg.chave);
        return temp->marcado;
    }else {
        return false;
    }
}
int main(){

    LISTA lista;
    inicializarLista(&lista);

    inserirFinal2(&lista, 1);
    inserirFinal2(&lista, 3);
    inserirFinal2(&lista, 2);
    exibirLista(&lista);

    return 0;
}
/*
int main(){
    LISTA lista;
    inicializarLista(&lista);
    
    inserirFinal(&lista, 1);
    exibirLista(&lista);
    inserirFinal(&lista, 2);
    exibirLista(&lista);
    inserirFinal(&lista, 3);
    exibirLista(&lista);
    inserirFinal(&lista, 4);
    exibirLista(&lista);
    inserirFinal(&lista, 5);
    exibirLista(&lista);
    inserirFinal(&lista, 1);
    exibirLista(&lista);
    inserirFinal(&lista, 2);
    exibirLista(&lista);
    inserirFinal(&lista, 4);
    exibirLista(&lista);
    

    inserirFinal2(&lista, 8);
    exibirLista(&lista);
    inserirFinal2(&lista, 8);
    exibirLista(&lista);
    inserirFinal2(&lista, 8);
    exibirLista(&lista);
    */
   /*PONT test = vaiAteFinal(&lista);
    printf(" FINAL : %i ", test->reg.chave);

    bool test = excluir(&lista, 3);
    exibirLista(&lista);
    test = excluir(&lista, 4);
    exibirLista(&lista);
    pop(&lista); 
    exibirLista(&lista);
    pop(&lista); 
    exibirLista(&lista);
    test = excluir(&lista, 5);
    exibirLista(&lista);
    test = excluir(&lista, 1);
    exibirLista(&lista);
    test = excluir(&lista, 2);
    exibirLista(&lista);
    test = excluir(&lista, 2);
    exibirLista(&lista);
    
    pop(&lista); // pop 4
    exibirLista(&lista);
    pop(&lista); // pop 3
    exibirLista(&lista);
    pop(&lista); // pop 2
    exibirLista(&lista);
    pop(&lista); // pop 1
    exibirLista(&lista);
    pop(&lista); // pop 1
    exibirLista(&lista);
 
}*/
/**/


