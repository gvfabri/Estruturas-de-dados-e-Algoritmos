// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>

#define N 100
#define false 0
#define true 1

#define BRANCO 0
#define CINZA 1
#define PRETO 2

// ############################### TAD Grafo ###############################

typedef struct adjacencia
{
    int vertice;
    int peso;
    struct adjacencia *prox;
}Adjacencia;

typedef struct vertice
{
    int v; //Núm. do vért. destino da aresta
    Adjacencia *prox; //Ponteiro para próx vért. adj.
    int valor;
}Vertice;

typedef struct graph
{
    int V, E; //V=Número de vértices, E=Número de arestas
    Vertice *adj;
}TipoGrafo;

// ############################ TAD FILA ###################################

typedef struct 
{
    int chave;
}REGISTRO;
typedef struct aux
{
    REGISTRO reg;
    struct aux* prox;
}ELEMENTO, *PONT;
typedef struct{
    PONT inicio;
    PONT fim;
}FILA;

// ####################### TAD Pilha #######################################
struct elemento
{
  int valor;
  struct elemento *ant;
};
typedef struct elemento tipoElemento;
struct pilha
{
    int tamanhoPilha;
    tipoElemento *topo;
};
typedef struct pilha tipoPilha;

// ###################### Funcoes e Procedimentos do programa ##############

void Inicializa_Fila(FILA *f)
{
    f->inicio = NULL;
    f->fim = NULL;
}

int tamanhoFila(FILA *f)
{
    PONT end = f->inicio;
    int tam = 0;
    while(end != NULL)
    {
        tam++;
        end = end->prox;
    }
    return tam;
}

void inserirNaFila(FILA *f, REGISTRO reg)
{
    PONT novo = malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    novo->prox = NULL;
    if(f->inicio == NULL)
    f->inicio = novo;
    else
    f->fim->prox = novo;
    f->fim = novo;
    return;
}

int Exclui_Fila(FILA *f, REGISTRO* reg)
{
    if(f->inicio == NULL)
    return 0;
    *reg = f->inicio->reg;
    PONT apagar = f->inicio;
    f->inicio = f->inicio->prox;
    free(apagar);
    if(f->inicio == NULL)
    f->fim = NULL;
}

void ReinicializarFila(FILA *f)
{
    PONT end = f->inicio;
    while(end != NULL)
    {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
}

void Imprime_Fila(FILA *f)
{
    PONT end = f->inicio;
    while(end != NULL)
    {
        printf("%d ", end->reg.chave);
        end = end->prox;
    }
}

void Inicializa_Pilha(tipoPilha *pilhaAux)
{
    // inicializa o tamanho da pilha e o ponteiro do topo
    pilhaAux->tamanhoPilha = 0;
    pilhaAux->topo = NULL;
    return;
}

void Push(tipoPilha *pilhaAux, int valor)
{
    /* A função empilha um novo elemento na lista */
    tipoElemento *novoElemento = malloc(sizeof(tipoElemento));
    novoElemento->valor = valor;
    if(pilhaAux->tamanhoPilha == 0)
    {
        pilhaAux->topo = novoElemento;
    }
    else
    {
        novoElemento->ant = pilhaAux->topo;
        pilhaAux->topo = novoElemento;
    }
    pilhaAux->tamanhoPilha++;
    return;
}

void Imprime_Topo(tipoPilha *pilhaAux)
{
    /* A função imprime o valor indicado, a pilha que contem o numero binario, a segunda pilha que
    contem o binario invertido e a terceira que contem o decimal invertido*/
    tipoElemento *aux = pilhaAux->topo;
    while(aux != NULL)
    {
        printf("%d ", aux->valor);
        aux = aux->ant;
    }
    return;
}

Adjacencia *criaAdj(int vertice, int peso)
{
    Adjacencia *temp = (Adjacencia*)malloc(sizeof(Adjacencia));
    temp->vertice = vertice;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

int criaAresta(TipoGrafo *grafo, int vi, int vf, int peso)
{
    if(!grafo)
        return 0;
    if((vf < 0) || (vf >= grafo->V))
        return 0;
    if((vi < 0) || (vi >= grafo->V))
        return 0;
    Adjacencia *novo = criaAdj(vf, peso);
    
    if (grafo->adj[vi].prox == NULL || novo->vertice < grafo->adj[vi].prox->vertice) {
        novo->prox = grafo->adj[vi].prox;
        grafo->adj[vi].prox = novo;
    } else {
        // Percorrer a lista até encontrar a posição correta de inserção
        Adjacencia *atual = grafo->adj[vi].prox;
        Adjacencia *anterior = NULL;
        
        while (atual != NULL && novo->vertice > atual->vertice) {
            anterior = atual;
            atual = atual->prox;
        }
        
        // Inserir o novo nó na posição correta
        novo->prox = atual;
        anterior->prox = novo;
    }
    
    grafo->E++;
    return 1;
}

TipoGrafo *CriaGrafo(int vertice)
{
    int i;
    TipoGrafo *g = (TipoGrafo*)malloc(sizeof(TipoGrafo));
    g->V = vertice;
    g->E = 0;
    g->adj = (Vertice*)malloc( vertice * sizeof(Vertice));
    for(i=0; i < vertice; i++)
        g->adj[i].prox = NULL;
    return g;
}

void Imprime_Grafo(TipoGrafo *grafo)
{
    int i;
    for(i = 0; i < grafo->V; i++)
    {
        printf("V%d", i);
        Adjacencia *adj = grafo->adj[i].prox;
        while(adj)
        {
            printf("v%d(%d) ", adj->vertice, adj->peso);
            adj = adj->prox;
        }
        printf("\n");
    }
}

void visitaL(TipoGrafo *grafo, int s, int *expl)
{
    FILA f;
    Inicializa_Fila(&f);
    expl[s] = true;
    REGISTRO *u = (REGISTRO*)malloc(sizeof(REGISTRO));
    u->chave = s;
    inserirNaFila(&f, *u);
    Imprime_Fila(&f);
    while(f.inicio)
    {
        Exclui_Fila(&f, u);
        Adjacencia *v = grafo->adj[u->chave].prox;
        while(v)
        {
            if(!expl[v->vertice])
            {
                expl[v->vertice] = true;
                u->chave = v->vertice;
                inserirNaFila(&f, *u);
                
            }
            v = v->prox;
        }
        Imprime_Fila(&f);
    }
    free(u);
}
void Busca_Largura(int verticei, TipoGrafo *grafo)
{
    int expl[grafo->V];
    int u;
    for(u=0; u < grafo->V; u++ )
    {
        expl[u] = false;
    }
    for(u=0; u < grafo->V; u++)
    {
        if(!expl[u])
            visitaL(grafo, verticei, expl);
    }
}

void visitaP(TipoGrafo *grafo, int u, int *cor, tipoPilha *pilha)
{
    cor[u] = CINZA;
    Adjacencia *v = grafo->adj[u].prox;
    while(v)
    {
        if(cor[v->vertice] == BRANCO)
        {
            printf("%d ", v->vertice);
            visitaP(grafo, v->vertice, cor, pilha);
        }
        v = v->prox;
    }
    cor[u] = PRETO;
}

void Busca_Profundidade(int verticei, TipoGrafo *grafo)
{
    int cor[grafo->V];
    tipoPilha pilha;
    Inicializa_Pilha(&pilha);
    int u;
    for(u = 0; u < grafo->V; u++)
    {
        cor[u] = BRANCO;
    }
    for(u = 0; u < grafo->V; u++)
    {
        if(cor[u] == BRANCO)
        visitaP(grafo, verticei, cor, &pilha);
    }
}

// ############################ Principal ###################################
 
int main()
{
    int verticei, nos, arestas, i = 0, flag = 0, vertice, aresta;
    scanf("%d", &verticei);
    scanf("%d", &nos);
    TipoGrafo *grafo = CriaGrafo(nos);
    scanf("%d", &arestas);
    while( i < arestas)
    {
        scanf("%d %d", &vertice, &aresta);
        flag = criaAresta(grafo, vertice, aresta, 0);
        i++;
    }
    printf("LARG ");
    Busca_Largura(verticei, grafo);
    printf("PROF ");
    Busca_Profundidade(verticei, grafo);
    printf("\n");
    Imprime_Grafo(grafo);
    free(grafo);
    return 0;
}


