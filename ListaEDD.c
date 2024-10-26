// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>
 
// ########################## TAD ListaEDD ######################################
 
struct elemento
{
    int numero;
    struct elemento *proximo;
    struct elemento *ant;
};
typedef struct elemento tipoElemento;
struct listaED{
    tipoElemento *primeiroElemento;
    tipoElemento *ultimoElemento;
    int tamanhoLista;
};
typedef struct listaED tipoLDDE;
 
// ###################### Funcoes e Procedimentos do programa ##############
 
void Inicializa(tipoLDDE *listaAux)
{
    listaAux->primeiroElemento = NULL;
    listaAux->ultimoElemento = NULL;
    listaAux->tamanhoLista = 0;
    return;
}
 
void Insere_Novo_Elemento(tipoLDDE *listaAux, int valor)
{
    int flag = 1;
    tipoElemento *novoElemento = malloc(sizeof(tipoElemento));
    novoElemento->numero = valor;
    if(listaAux->tamanhoLista == 0)
    {
        novoElemento->proximo = NULL;
        novoElemento->ant = NULL;
        listaAux->primeiroElemento = novoElemento;
        listaAux->ultimoElemento = novoElemento;
        listaAux->tamanhoLista++;
    }
    else
    {
        novoElemento->proximo = NULL;
        novoElemento->ant = listaAux->ultimoElemento;
        listaAux->ultimoElemento->proximo = novoElemento;
        listaAux->ultimoElemento = novoElemento;
        listaAux->tamanhoLista++;
    }
    return;
}
 
void Insere_Nova_Jogada(tipoLDDE *listaAux, int valor, int posicao)
{
    int i = 0;
    tipoElemento *aux = listaAux->primeiroElemento, *ante;
    tipoElemento *novoElemento = malloc(sizeof(tipoElemento));
    novoElemento->numero = valor;
    while(i < posicao)
    {
            ante = aux;
            aux = aux->proximo;
            i++;
    }
    if( aux == listaAux->primeiroElemento)
    {
        novoElemento->ant = NULL;
        novoElemento->proximo = listaAux->primeiroElemento;
        listaAux->primeiroElemento = novoElemento;
    }
    else if( aux == listaAux->ultimoElemento)
    {
        novoElemento->proximo = NULL;
        novoElemento->ant = listaAux->ultimoElemento;
        listaAux->ultimoElemento->proximo = novoElemento;
        listaAux->ultimoElemento = novoElemento;
    }
    else
    {
        novoElemento->ant = ante;
        novoElemento->proximo = ante->proximo;
        ante->proximo = novoElemento;
        if (aux != NULL)
        aux->ant = novoElemento;
    }
    listaAux->tamanhoLista++;
    return;
}
void Remove_Elemento(tipoLDDE *listaAux, tipoElemento *pos)
{
    int flag = 1;
    tipoElemento *remover = NULL;
    tipoElemento *aux = listaAux->primeiroElemento;
    //printf("%d ", valor);
    if(pos == listaAux->primeiroElemento)
    {
        remover = listaAux->primeiroElemento;
        if(listaAux->tamanhoLista <= 1)
        listaAux->primeiroElemento = NULL;
        else
        {
        listaAux->primeiroElemento = remover->proximo;
        listaAux->primeiroElemento->ant = NULL;
        free(remover);
        }
        listaAux->tamanhoLista--;
        flag = 0;
    }
    else if(pos == listaAux->ultimoElemento)
    {
        while(aux->proximo != NULL)
            aux = aux->proximo;
        remover = aux;
        if(remover->ant == NULL)
        listaAux->primeiroElemento = remover->proximo;
        else
        {
        remover->ant->proximo = NULL;
        listaAux->ultimoElemento = remover->ant;
        listaAux->tamanhoLista--;
        free(remover);
        }
    }
    else
    {
        while(aux->proximo != NULL && aux != pos)
        {
            aux = aux->proximo;
        }
        remover = aux;
        remover->ant->proximo = remover->proximo;
        remover->proximo->ant = remover->ant;
        listaAux->tamanhoLista--;
        free(remover);
        }
    return;
}
void Verifica_Somatorio(tipoLDDE *listaAux)
{
    int i=0;
    tipoElemento *pos1, *pos2, *pos3;
    tipoElemento *prox = NULL, *ant = NULL;
    tipoElemento *aux = listaAux->primeiroElemento;
    if(listaAux->tamanhoLista > 2)
    {
    while(i < listaAux->tamanhoLista && aux != NULL)
    {
        if (aux != NULL )
        {
        prox = aux->proximo;
        ant = aux->ant;
        }
        if(aux != NULL && aux->proximo != NULL && aux->ant != NULL)
        {
            if(aux->numero + prox->numero + ant->numero == 10)
            {
            pos1 = ant;
            pos2 = aux;
            pos3 = prox;
            Remove_Elemento(listaAux, pos1);
            Remove_Elemento(listaAux, pos2);
            Remove_Elemento(listaAux, pos3);
            }
        }
        aux = aux->proximo;
        i++;
    }
    if(listaAux->tamanhoLista > 2)
    {
    aux = listaAux->primeiroElemento;
    aux = aux->proximo;
    if (listaAux->primeiroElemento->numero + aux->numero + aux->proximo->numero == 10)
    {
        pos1 = listaAux->primeiroElemento;
        pos2 = aux;
        pos3 = aux->proximo;
        Remove_Elemento(listaAux, pos1);
        Remove_Elemento(listaAux, pos2);
        Remove_Elemento(listaAux, pos3);
    }
    else
    {
        aux = listaAux->ultimoElemento->ant;
    if (listaAux->ultimoElemento->numero + aux->numero + aux->ant->numero == 10)
    {
        pos1 = listaAux->ultimoElemento;
        pos2 = aux;
        pos3 = aux->ant;
        Remove_Elemento(listaAux, pos1);
        Remove_Elemento(listaAux, pos2);
        Remove_Elemento(listaAux, pos3);
    }
    else if(listaAux->primeiroElemento->numero + listaAux->ultimoElemento->numero + listaAux->ultimoElemento->ant->numero == 10)
    {
        pos1 = listaAux->primeiroElemento;
        pos2 = listaAux->ultimoElemento;
        pos3 = listaAux->ultimoElemento->ant;
        Remove_Elemento(listaAux, pos1);
        Remove_Elemento(listaAux, pos2);
        Remove_Elemento(listaAux, pos3);
    }
    else 
    {
        prox = listaAux->primeiroElemento->proximo;
        if(listaAux->primeiroElemento->numero + prox->numero + listaAux->ultimoElemento->numero == 10)
    {
        pos1 = listaAux->primeiroElemento;
        pos2 = prox;
        pos3 = listaAux->ultimoElemento;
        Remove_Elemento(listaAux, pos1);
        Remove_Elemento(listaAux, pos2);
        Remove_Elemento(listaAux, pos3);
    }
    }
    }
    }
    }
    return;
}
void Imprime_Valores(tipoLDDE *listaAux)
{
    tipoElemento *aux = listaAux->primeiroElemento;
    if (listaAux->tamanhoLista > 0)
    {
    while(aux != NULL)
    {
        printf("%d ", aux->numero);
        aux = aux->proximo;
    }
    printf("\n");
    }
    return;
}
 
void Resultado(tipoLDDE *listaAux)
{
    if(listaAux->tamanhoLista == 0)
    printf("ganhou\n");
    else
    printf("perdeu\n");
    return;
}
// ############################ Principal ###################################
 
int main ()
{
    int i, valor, posicao;
    tipoLDDE listaEDD;
    Inicializa(&listaEDD);
    for(i = 0; i < 10; i++)
    {
    scanf("%d", &valor);
    Insere_Novo_Elemento(&listaEDD, valor);
    }
    Imprime_Valores(&listaEDD);
    for(i = 0; i < 5; i++)
    {
        scanf("%d %d", &valor, &posicao);
        Insere_Nova_Jogada(&listaEDD, valor, posicao);
        Verifica_Somatorio(&listaEDD);
        Imprime_Valores(&listaEDD);
    }
    Resultado(&listaEDD);
return 0;
}