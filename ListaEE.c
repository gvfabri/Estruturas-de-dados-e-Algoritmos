/******************************************************************************
 
                            BIBLIOTECAS
 
*******************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// ListaEE.H
struct info
{
    int valor;
    int proximo;
};
typedef struct info tipoInfo;
struct ListaEE
{
    int tamanhoLista;
    int primeiro;
    int ultimo;
    int posLivre[10];
    tipoInfo elemento[10];
    int quantAnos[8];
};
typedef struct ListaEE Lista;
 
// ############ FUNÇÕES  #############
 
void Inicializa(Lista *minhaLista)
{
    int i;
    minhaLista->tamanhoLista = 0;
    minhaLista->primeiro = -1;
    minhaLista->ultimo = -1;
    for (i=0; i < 10; i++)
    {
        minhaLista->elemento[i].valor = 0;
        minhaLista->elemento[i].proximo = -1;
        minhaLista->posLivre[i] = 1;
    }
    for (i=0; i < 8; i++)
    {
        minhaLista->quantAnos[i] = 0;
    }
    return;
}
int ProximaposLivre(Lista *minhaLista)
{
    int i;
    for (i=0; i < 10; i++)
    {
        if (minhaLista->posLivre[i] == 1)
        return i;
    }
    return -1;
}
void Quantidade_por_Ano(Lista *minhaLista, int posicao)
{
    int i;
        if ( minhaLista->elemento[posicao].valor >= 66000 && minhaLista->elemento[posicao].valor < 76000)
        minhaLista->quantAnos[0]++;
        if ( minhaLista->elemento[posicao].valor >= 76000 && minhaLista->elemento[posicao].valor < 86000)
        minhaLista->quantAnos[1]++;
        if (minhaLista->elemento[posicao].valor >= 86000 && minhaLista->elemento[posicao].valor < 96000)
        minhaLista->quantAnos[2]++;
        if ( minhaLista->elemento[posicao].valor >= 96000 && minhaLista->elemento[posicao].valor < 106000)
        minhaLista->quantAnos[3]++;
        if ( minhaLista->elemento[posicao].valor >= 106000 && minhaLista->elemento[posicao].valor < 116000)
        minhaLista->quantAnos[4]++;
        if (minhaLista->elemento[posicao].valor >= 116000 && minhaLista->elemento[posicao].valor < 126000)
        minhaLista->quantAnos[5]++;
        if (minhaLista->elemento[posicao].valor >= 126000 && minhaLista->elemento[posicao].valor < 136000)
        minhaLista->quantAnos[6]++;
        if (minhaLista->elemento[posicao].valor >= 136000 && minhaLista->elemento[posicao].valor < 146000)
        minhaLista->quantAnos[7]++;
    return;
}
void Imprime_Elementos(Lista *minhaLista);
void Insere_Elemento(Lista *minhaLista, int posicao, int ra)
{
    int i=0, j = 0, aux = 0;
    if(minhaLista->tamanhoLista < 10)
    {
    if ( posicao != -1)
    {
        minhaLista->elemento[posicao].valor = ra;
        if (minhaLista->tamanhoLista == 0 )
        {
            minhaLista->primeiro = posicao;
            minhaLista->elemento[posicao].proximo = -1;
            minhaLista->tamanhoLista++;
            minhaLista->ultimo = posicao;
            minhaLista->posLivre[posicao] = 0;
        }
        else if( minhaLista->elemento[posicao].valor > minhaLista->elemento[minhaLista->primeiro].valor && minhaLista->elemento[posicao].valor < minhaLista->elemento[minhaLista->ultimo].valor)
        { 
            for ( i = minhaLista->primeiro; minhaLista->elemento[posicao].valor > minhaLista->elemento[i].valor; i = minhaLista->elemento[i].proximo)
            {
                aux = minhaLista->elemento[i].proximo;
            }
            while (j < minhaLista->tamanhoLista)
                {
                    if (minhaLista->elemento[j].proximo == i)
                    break;
                    j++;
                }
            minhaLista->elemento[j].proximo = posicao;
            minhaLista->elemento[posicao].proximo = aux;
            minhaLista->tamanhoLista++;
            minhaLista->posLivre[posicao] = 0;
        }
        else if( minhaLista->elemento[posicao].valor < minhaLista->elemento[minhaLista->primeiro].valor )
        {
            minhaLista->elemento[posicao].proximo = minhaLista->primeiro;    
            minhaLista->primeiro = posicao;
            minhaLista->tamanhoLista++;
            minhaLista->posLivre[posicao] = 0;
        }
        else if( minhaLista->elemento[posicao].valor > minhaLista->elemento[minhaLista->ultimo].valor )
        {
            minhaLista->elemento[minhaLista->ultimo].proximo = posicao;
            minhaLista->elemento[posicao].proximo = -1;
            minhaLista->tamanhoLista++;
            minhaLista->ultimo = posicao;
            minhaLista->posLivre[posicao] = 0;
        }
    }
    Quantidade_por_Ano(minhaLista, posicao);
    }
    else
    printf("lista cheia\n");
    Imprime_Elementos(minhaLista);
    return;
}
void Remove_Elemento(Lista *minhaLista, int ra)
{
    int i, vazio=0, valor, j=0;
    for (i=0; i < 10; i++)
    {
        if( minhaLista->elemento[i].valor == ra)
        {
            if(i == minhaLista->primeiro)
            {
                minhaLista->elemento[i].valor = 0;
                minhaLista->primeiro = minhaLista->elemento[i].proximo;
                minhaLista->posLivre[i] = 1;
                minhaLista->tamanhoLista--;
            }
            else if( i == minhaLista->ultimo )
            {
                while (j < minhaLista->tamanhoLista)
                {
                    if (minhaLista->elemento[j].proximo == i)
                    break;
                    j++;
                }
                minhaLista->elemento[i].valor = 0;
                minhaLista->ultimo = j;
                minhaLista->elemento[j].proximo = -1;
                minhaLista->posLivre[i] = 1;
                minhaLista->tamanhoLista--;
            }
            else
            {
                while (j < minhaLista->tamanhoLista)
                {
                    if (minhaLista->elemento[j].proximo == i)
                    break;
                    j++;
                }
                minhaLista->elemento[i].valor = 0;
                minhaLista->elemento[j].proximo = minhaLista->elemento[i].proximo;
                minhaLista->posLivre[i] = 1;
                minhaLista->tamanhoLista--;
            }
        }
        else
        vazio++;
    }
    if (vazio == 10)
    {
        printf("nao existe\n");
    }
    Imprime_Elementos(minhaLista);
    return;
}

void Imprime_Elementos(Lista *minhaLista)
{
    int i, j;
    for (i = minhaLista->primeiro; i != -1; i = minhaLista->elemento[i].proximo )
    {
            printf("%d ", minhaLista->elemento[i].valor);
    }
    printf("\n");
    return;
}

void Imprime_por_Ano(Lista *minhaLista)
{
    int i, ano = 2011;
    for (i=0; i < 8; i++)
    {
        printf("%d: %d\n", ano+i, minhaLista->quantAnos[i]);
    }
    return;
}
 
// ########### PRINCIPAL ############
 
int main()
{
    int quant, i = 0, opcao, ra;
    Lista minhaLista;
    Inicializa(&minhaLista);
    scanf("%d", &quant);
    while (i < quant)
    {
        scanf("%d %d", &opcao, &ra);
        if(opcao == 1)
        {
            Insere_Elemento(&minhaLista, ProximaposLivre(&minhaLista), ra);
        }
        if (opcao == 2)
        {
            Remove_Elemento(&minhaLista, ra);
        }
        i++;
    }
    Imprime_por_Ano(&minhaLista);
    return 0;
}