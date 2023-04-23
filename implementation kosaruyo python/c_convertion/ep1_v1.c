//--------------------------------------------------------------
// NOME : Matheus Barbosa 
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define true 1
#define false 0
//typedef int bool;

typedef int TIPOCHAVE;

//#include "lista_ligada.c"

//#include <conio.h>
//#include <malloc.h>

// ######### ESCREVA O NROUSP AQUI
int nroUSP() {
    return 10687792;
}

// -------------------------- Inicio dos metodos para a Grafo ----------------------------------

// nos das listas de adjacencias
typedef struct adj {
	int v;
	struct adj* prox;
} NO;

// vertices
typedef struct {
	NO* inicio;
} VERTICE;

// Estrutura do grafo
VERTICE *criaGrafo(int n){
    VERTICE* g = (VERTICE *) malloc(sizeof(VERTICE)*n);
    int i;
    for (i = 0; i < n; i++)
        g[i].inicio = NULL;
    return(g);
}
/*
    Cria uma adjacencia (Aresta) alocando valores para os items passados 
*/
NO *criaNo( int v ){
    NO *temp = (NO *) malloc(sizeof(NO));
    temp->v = v;
    temp->prox = NULL;
    return(temp);
}

bool criaAresta(VERTICE *gr, int vi, int vf){

    NO *novo = criaNo(vf);
    novo->prox = gr[vi].inicio;
    gr[vi].inicio = novo;

    return(true);
}
// -------------------------- Final dos metodos para a Grafo ----------------------------------
// -------------------------- Inicio dos metodos para a lista ligada --------------------------

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

//ELIMINAR
void exibirLista(LISTA* l){
    PONT end = l->inicio;
    printf("Lista : \" ");
    while (end != NULL){
        printf("%i ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}

PONT vaiAteFinal(LISTA* l){
    PONT atual = l->inicio;
    while (atual->prox != NULL ){
        atual = atual->prox;
    }
    return atual;
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

PONT buscaSequencial(LISTA* l, TIPOCHAVE ch){
    PONT pos = l->inicio;
    while(pos != NULL){
        if (pos->reg.chave == ch) return pos;
        pos = pos->prox;
    }
    return NULL;
}

void inserir(LISTA *l, int valor){
  TIPOCHAVE ch;
  REGISTRO reg;
  reg.chave = valor;
  inserirElemListaOrd(l,reg);
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

// --------------------------  Final dos metodos para a lista ligada --------------------------
// ------------- Inicio dos metodos para a lista ligada utilizando o NO como base -------------
typedef NO* PONT_NO;

typedef struct {
    PONT_NO inicio;
}LISTA_NO;

void inicializarListaNO(LISTA_NO* l){
    l->inicio = NULL;
}

void exibirListaNO(LISTA_NO* l){
    PONT_NO end = l->inicio;
    printf("Lista : \" ");
    while (end != NULL){
        printf("%i ", end->v);
        end = end->prox;
    }
    printf("\"\n");
}

PONT_NO vaiAteFinal_NO(LISTA_NO* l){
    PONT_NO atual = l->inicio;
    while (atual->prox != NULL ){
        atual = atual->prox;
    }
    return atual;
}
void inserirFinal2_NO(LISTA_NO *l, int valor){
    PONT_NO i = (PONT_NO) malloc(sizeof(NO));
    i->v = valor;

    if (l->inicio == NULL){
        i->prox = l->inicio;
        l->inicio = i;
    }else{
        PONT_NO ultimo = vaiAteFinal_NO(l);
        ultimo->prox = i;
        i->prox = NULL;
    }
}
//trocar parametro para : (LISTA l)
void converterLISTA_P_LISTA_NO(LISTA_NO* ln, LISTA* l){
	PONT end = l->inicio;
    while (end != NULL){
		inserirFinal2_NO(ln, end->reg.chave);
        end = end->prox;
    }
}
// ------------- Final dos metodos para a lista ligada utilizando o NO como base -------------
/*
	A funcao principal para descobrir caminhos funciona com uma busca por
	profundidade onde vai adentrando os nos ate encontrar algo que seja 
	igual ao no de origem e respeite a distancia estipulada.

	Uma vez que isso acontece salva tudo em uma lista ligada de cominhos
	possiveis
*/
void caminhos_max_d_rec(VERTICE* g, int n, int x, int y,int dis ,int d, LISTA* listaDeNosVisitados,LISTA* caminhoLocal, LISTA* todosCaminhosPossiveis){
	setNode(listaDeNosVisitados, x, true);
	inserirFinal2(caminhoLocal,x);
	if ( x == y && dis <= d ){
		PONT temp = caminhoLocal->inicio;
		while ( temp != NULL){
			inserirFinal2(todosCaminhosPossiveis, temp->reg.chave);
			temp = temp->prox;
		}
	}else{
		dis = dis + 1;
		NO *adj = g[x].inicio;
		while(adj != NULL) {
			if (!getNode(listaDeNosVisitados, adj->v)){
				caminhos_max_d_rec(g,n,adj->v, y, dis, d, listaDeNosVisitados, caminhoLocal, todosCaminhosPossiveis);
			}
			adj = adj->prox;
		}
	}
	pop(caminhoLocal);
	setNode(listaDeNosVisitados, x, false);
}


// funcao principal
NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d);

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
/**/



NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d)
{
	// Lista para controle de visitados
	LISTA listaDeNosVisitados;
	inicializarLista(&listaDeNosVisitados);
	int i = 0;
	
	for(i=0;i<n;i++){
		inserir(&listaDeNosVisitados, i);
	}
	// Lista de todos caminhos possiveis concatenados
	LISTA todosCaminhosPossiveis;
	inicializarLista(&todosCaminhosPossiveis);
	// Lista para caminhos locais 
	LISTA caminhoLocal;
	inicializarLista(&caminhoLocal);
	int dis = 1;
	caminhos_max_d_rec(g ,n ,x ,y ,dis ,d ,&listaDeNosVisitados,&caminhoLocal ,&todosCaminhosPossiveis);
	LISTA_NO novo_no;
	inicializarListaNO(&novo_no);
	if (todosCaminhosPossiveis.inicio != NULL){
		converterLISTA_P_LISTA_NO(&novo_no, &todosCaminhosPossiveis);
		return novo_no.inicio;
	}
	return NULL;
}



//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
// mas nao entregue o codido de main() nem inclua nada
// abaixo deste ponto
//---------------------------------------------------------
int main()
{
	
}

