// Nome: Gabriel Victor Fabri do Carmo RA: 163756

// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2

// ############################### TAD Grafo ###############################

typedef struct adjacencia
{
    int vertice;
    int peso;
    struct adjacencia *prox;//adjacencia entre os vertices
}Adjacencia;

typedef struct vertice
{
    int v; //Núm. do vért. destino da aresta
    Adjacencia *prox; //Ponteiro para próx vért. adj.
    int valor;
}Vertice;

typedef struct grafo
{
    int V, E; //V=Número de vértices, E=Número de arestas
    Vertice *adj;
}TipoGrafo;

// ############################ TAD FILA ###################################

typedef struct 
{
    int chave;// inteiro armazenado na pilha
}REGISTRO;

typedef struct aux
{
    REGISTRO reg;// registro para o próximo elemento
    struct aux* prox;
}ELEMENTO, *PONT;

typedef struct{
    PONT inicio;
    PONT fim;
}FILA;

// ###################### Funcoes e Procedimentos do programa ##############

// A função abaixo inicializa a fila auxiliar para realizar a busca em profundidade
void Inicializa_Fila(FILA *f)
{
    f->inicio = NULL;
    f->fim = NULL;
}

// A função abaixo insere elementos na fila através de um registro 
void inserirNaFila(FILA *f, REGISTRO reg)
{
    PONT novo = malloc(sizeof(ELEMENTO));// aloca memória para um nó registro
    novo->reg = reg;
    novo->prox = NULL;
    // se a fila estiver vazia insere no inicio
    if(f->inicio == NULL)
        f->inicio = novo;
    // caso ao contrário insere no final da fila
    else
        f->fim->prox = novo;
    f->fim = novo;
    return;
}

// A função abaixo remove elementos da fila de prioridade
int Exclui_Fila(FILA *f, REGISTRO* reg)
{
    // se estiver vazia não apaga nada
    if(f->inicio == NULL)
    return 0;
    // caso ao contrário remove o ultimo elemento e o oneultimo passa a ser o ultimo
    *reg = f->inicio->reg;
    PONT apagar = f->inicio;
    f->inicio = f->inicio->prox;
    free(apagar);
    if(f->inicio == NULL)
    f->fim = NULL;
}

// A função abaixo reinicializa a fila apagando tudo
void ReinicializarFila(FILA *f)
{
    PONT end = f->inicio;
    // apaga os nos do começo ao final
    while(end != NULL)
    {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
}

// A função abaixo imprime a fila de prioridade
void Imprime_Fila(FILA *f)
{
    PONT end = f->inicio;
    while(end != NULL)
    {
        printf("%d ", end->reg.chave);
        end = end->prox;
    }
}

// A função abaixo cria a adjacência entre os vertices
Adjacencia *criaAdj(int vertice, int peso)
{
    // cria ponteiro auxiliar para conectar os vertices
    Adjacencia *temp = (Adjacencia*)malloc(sizeof(Adjacencia));
    temp->vertice = vertice;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

// A função abaixo cria as arestas entre o vertices para criar um caminho no grafo
int criaAresta(TipoGrafo *grafo, int vi, int vf, int peso)
{
    // se o grafo estiver vazio não cria nada
    if(!grafo)
        return 0;
    // se o vertice final for menor que 0 ou maior/igual ao vertice inserido não cria
    if((vf < 0) || (vf >= grafo->V))
        return 0;
    // o mesmo acontece para o vertice inicial
    if((vi < 0) || (vi >= grafo->V))
        return 0;
    // chama a função para conectar os vertices
    Adjacencia *novo = criaAdj(vf, peso);
    // como o grafo deve ser inserido de forma crescente é necessário uma lista para auxiliar a encontrar a posicao adequada
    if (grafo->adj[vi].prox == NULL || novo->vertice < grafo->adj[vi].prox->vertice)
    {
        novo->prox = grafo->adj[vi].prox;
        grafo->adj[vi].prox = novo;
    }
    else
    {
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

// A função baixo cria o grafo em si, inicializando 
TipoGrafo *CriaGrafo_Inicializa(int vertice)
{
    int i;
    TipoGrafo *g = (TipoGrafo*)malloc(sizeof(TipoGrafo));// alloca memoria para a estrutura
    //cria o primeiro vertice
    g->V = vertice;
    g->E = 0;
    // inicializa as adjacencias 
    g->adj = (Vertice*)malloc( vertice * sizeof(Vertice));
    for(i=0; i < vertice; i++)
        g->adj[i].prox = NULL;
    return g;
}

// A funcao abaixo seria usada para imprimir o grafo, no exercicio em questão não é necessario imprimir
void Imprime_Grafo(TipoGrafo *grafo)
{
    int i;
    for(i = 0; i < grafo->V; i++)
    {
        printf("V%d", i);
        Adjacencia *adj = grafo->adj[i].prox;
        while(adj)
        {
            printf("v%d(%d) ", adj->vertice, adj->peso );
            adj = adj->prox;
        }
        printf("\n");
    }
}
// A função abaixo realiza a visita ao nó na busca em largura
void visitaL(TipoGrafo *grafo, int s, int *cor)
{
    // cria a inicializa uma fila de prioridade auxiliar
    FILA f;
    Inicializa_Fila(&f);
    // pinta o no visitado para cinza
    cor[s] = CINZA;
    REGISTRO *u = (REGISTRO*)malloc(sizeof(REGISTRO));
    // armazena e imprime o no inicial 
    u->chave = s;
    inserirNaFila(&f, *u);
    Imprime_Fila(&f);
    // utiliza uma fila auxiliar para percorrer os nos na busca em largura
    while(f.inicio)
    {
        // exclui o nó da fila a cada chamada
        Exclui_Fila(&f, u);
        // auxiliar para visitar as adjacencias do no
        Adjacencia *v = grafo->adj[u->chave].prox;
        while(v)
        {
            // se o no for branco pinta ele de cinza e visita todos os nos vizinhos do no chamado na busca 
            if(!cor[v->vertice])
            {
                cor[v->vertice] = CINZA;
                u->chave = v->vertice;
                inserirNaFila(&f, *u);
                printf("%d ", u->chave);
            }
            v = v->prox;
        }
    }
    free(u);
}

// A função abaixo realiza a busca em largura no grafo
void Busca_Largura(int verticei, TipoGrafo *grafo)
{
    int cor[grafo->V];
    int u;
    // pinta todos os nos de branco
    for(u=0; u < grafo->V; u++ )
    {
        cor[u] = BRANCO;
    }
    // se o nó for branco realiza a visita 
    for(u=0; u < grafo->V; u++)
    {
        if(cor[u] == BRANCO)
            visitaL(grafo, verticei, cor);
    }
}
// A função abaixo visita o nó na busca em profundidade caso o nó for branco
void visitaP(TipoGrafo *grafo, int u, int *cor)
{
    // pinta o nó de cinza
    cor[u] = CINZA;
    Adjacencia *v = grafo->adj[u].prox;
    // visita os nós adjacentes ao nó visitado
    while(v)
    {
        if(cor[v->vertice] == BRANCO)
        {
            // imprime a pilha de execução e visita os nos pintando cada no de cinza
            printf("%d ", v->vertice);
            visitaP(grafo, v->vertice, cor);
        }
        v = v->prox;
    }
    // na volta da recursao pinta todos de preto
    cor[u] = PRETO;
}

// A funcao abaixo realiza a busca em profundidade no grafo
void Busca_Profundidade(int verticei, TipoGrafo *grafo)
{
    // cria um vetor para armazenar as cores do nos visitados
    int cor[grafo->V];
    int u;
    for(u = 0; u < grafo->V; u++)// pinta todos os nos de brancos
    {
        cor[u] = BRANCO;
    }
    // começa pelo primeiro nó
        printf("%d ", verticei);
    for(u = 0; u < grafo->V; u++)
    {
        if(cor[u] == BRANCO)// se o nó for branco chava a visita
        visitaP(grafo, verticei, cor );
    }
}
void Inicializa_Busca_Minima(TipoGrafo *grafo, int *u, int *v, int s)
{
    int i;
    for(i=0; i < grafo->V; i++)
    {
        u[i] = 32768/2;
        v[i] = -1;
    }
    u[s] = 0;
}
void Relaxa(TipoGrafo *grafo, int *u, int *v, int i, int j, int restricao)
{
    Adjacencia *adj = grafo->adj[i].prox;
    while(adj && adj->vertice != j)
    {
        adj = adj->prox;
    }
    if(adj)
    {
        if(adj->peso <= restricao )
        {
            if(u[j] > u[i] + adj->peso)
            {
            u[j] = u[i] + adj->peso;
            v[j] = i;
            }
        }
    }
}
void Bellman_Ford(TipoGrafo *grafo, int s, int restricao)
{
    int i = 0, j = 0, flag = 0;
    int u[grafo->V], v[grafo->V];// u dist e v pred.
    Inicializa_Busca_Minima(grafo, u, v, s);
    
    for(i = 1; i <= grafo->V - 1; i++)
    {
        for (j = 0; j <= grafo->V - 1; j++) {
            Adjacencia *adj = grafo->adj[j].prox;
            while (adj) 
            {
                Relaxa(grafo, u, v, j, adj->vertice, restricao);
                adj = adj->prox;
            }
        }
    }
    
    for(i=0; i < grafo->V; i++)
    {
        printf("%d ", u[i]);
    }
}
// ############################ Principal ###################################
 
int main()
{
    int verticei, nos, arestas, i = 0, flag = 0, vertice, aresta, peso, restricao;
    scanf("%d", &verticei);
    scanf("%d", &restricao);
    scanf("%d", &nos);
    TipoGrafo *grafo = CriaGrafo_Inicializa(nos);
    scanf("%d", &arestas);
    // cria as arestas do grafo na inserção
    while( i < arestas)
    {
        scanf("%d %d %d", &vertice, &aresta, &peso);
        flag = criaAresta(grafo, vertice, aresta, peso);
        i++;
    }
    Bellman_Ford(grafo, verticei, restricao);
    free(grafo);
    return 0;
}


