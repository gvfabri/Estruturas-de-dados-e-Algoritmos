/* Autor: Gabriel Victor Fabri do Carmo
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
// ########### TAD Lista ########################
 
struct elemento
{
    int chave;
    struct elemento *proximo;
};
typedef struct elemento tipoElemento;
struct listaED
{
    tipoElemento *primeiro;
    tipoElemento *ultimo;
    int tamanhoLista;
};
typedef struct listaED tipoLDE;
 
 
// ########### Funções #########################
 
/* A função abaixo inicializa a lista, fazendo os ponteiros apontarem para nulo, e tamanho = 0*/
void Inicializa_Lista(tipoLDE *listaAux)
{
    listaAux->primeiro = NULL;
    listaAux->ultimo = NULL;
    listaAux->tamanhoLista = 0;
    return;
}
/* A função abaixo insere elementos na lista simplesmente ligada*/
void Insere_Elemento(tipoLDE *listaAux, int valor)
{
    tipoElemento *novoElemento = malloc(sizeof(novoElemento));//aloca memória para lista
    novoElemento->chave = valor;
    /*Se o tamanho da lista for zero insere na primeira posicao e o proximo aponta para nulo, como a lista está iniciando primeiro e ultimo aponta para o novo elemento*/ 
    if(listaAux->tamanhoLista == 0)
    {
        novoElemento->proximo = NULL;
        listaAux->primeiro = novoElemento;
        listaAux->ultimo = novoElemento;
    }
    /* Caso contrário sempre atualiza o ponteiro para o ultimo e o proximo elemento*/
    else
    {
        novoElemento->proximo = NULL;
        listaAux->ultimo->proximo = novoElemento;
        listaAux->ultimo = novoElemento;
    }
    listaAux->tamanhoLista++;
    return;
}
 
/*A função abaixo encontra o meio da lista e divide, consiste em um ponteiro avançar sempre de dois em dois até o final da lista enquanto um avança apenas uma*/
void Divide_Lista(tipoElemento *aux, tipoElemento **p, tipoElemento **q)
{
    tipoElemento *p_rapido;
    tipoElemento *p_devagar;
    p_devagar = aux;
    p_rapido = aux->proximo;
    while(p_rapido != NULL)// percorre a lista com um ponteiro avançando duas posições e um apenas uma
    {
        p_rapido = p_rapido->proximo;
        if(p_rapido != NULL)
        {
            p_devagar = p_devagar->proximo;
            p_rapido = p_rapido->proximo;
        }
    }
    *p = aux;
    *q = p_devagar->proximo;
    p_devagar->proximo = NULL;
    
}
/* A função abaixo intercala as listas divididas*/
tipoElemento *Merge(tipoElemento *a, tipoElemento *b, tipoLDE *lista)
{
    tipoElemento* listaAux = malloc(sizeof(tipoElemento));// alloca mem´ria para auxiliar na ordenação dos ponteiros
    tipoElemento* ordena = listaAux;// ponteiro auxiliar para ordenar
     if (a == NULL)//condição de parada
        return b;
    else if (b == NULL)
        return a;
    while(a != NULL && b != NULL)// o loop percorre os elementos separados comparando o menor valor do primeiro vetor com o primeiro do da direita e assim por diante
    {
        if (a->chave <= b->chave)
        {
            ordena->proximo = a;
            a = a ->proximo;
            ordena = ordena->proximo;
        }
        else
        {
            ordena->proximo = b;
            b = b->proximo;
            ordena = ordena->proximo;
        }
    }
    while (a != NULL)// mescla os valores semparados
    {
        ordena->proximo = a;
        a = a->proximo;
        ordena = ordena->proximo;
    }
    while ( b != NULL)
    {
        ordena->proximo = b;
        b = b->proximo;
        ordena = ordena->proximo;
    }
    
    /* Se o primeiro elemento de um lado da lista for maior que o outro começa por ele na lista a ordenar, 
    então o ponteiro auxiliar recebe um lado da lista e o proximo é encontrado com comparação*/
    listaAux = listaAux->proximo;
    return listaAux;
}
 
void MergeSort(tipoLDE *listaAux)
{
    tipoElemento *aux = listaAux->primeiro;
    tipoElemento *a = NULL, *b = NULL;
    if(aux == NULL || aux->proximo == NULL) return;// condição de parada
    
    Divide_Lista(aux, &a, &b);// divide a lista até deixar a lista de forma unitária
    
    MergeSort( &a);
    MergeSort( &b);
 
    // contabiliza o numero de recurções realizadas para observar qual foi o número mais profundo da recursão
 
    listaAux->primeiro =  Merge(a , b, listaAux);// intercala as frações de listas
}
 
void Imprime_Lista(tipoLDE *listaAux)
{
    tipoElemento *aux = listaAux->primeiro;
    while(aux != NULL)
    {
        printf("%d ", aux->chave);
        aux = aux->proximo;
    }
    printf("\n");
}
 
// ########### Principal ######################
 
int main()
{
    int tamanho, valor, i, h = 0;
    tipoLDE listaED;
    Inicializa_Lista(&listaED);
    scanf("%d", &tamanho);
    for(i = 0; i < tamanho; i++)
    {
        scanf("%d", &valor);
        Insere_Elemento(&listaED, valor);
    }
    MergeSort(&listaED);
    Imprime_Lista(&listaED);
    h = log10(tamanho) / log10(2); // calcula a altura da arvore de recursao do MergeSort, ou seja o nível mais profundo
    /*O nível mais profundo da arvore sempre é dado por n = 2^i, em que n é o numero de entradas e i o nivel, ou seja, i= log n na base 2*/
    h = floor(h);// arredonda o valor para baixo para melhorar a precisão da altura
    printf("%d", (h +1));
    return 0;
}