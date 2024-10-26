/* Autor: Gabriel Victor Fabri do Carmo */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
 
// ########### Funções #########################
void Inicializa_Vetor(int *vet, int tamanho)
{
    int i;
    for ( i = 0; i < tamanho; i++)
    {
        *(vet + i) = 0;
    }
    return;
}
void Verifica_Letra_Maiuscula(char **palavras, int quant_palavras)
{
    int i, j, aux = 0;
    char c;
    for(i = 0; i < quant_palavras; i++ )
    {
        for( j = 0; j < strlen(palavras[i]); j ++)
        {
            aux = palavras[i][j];
            if(aux < 97)
            {
                palavras[i][j] = aux + 32;
            }
        }
    }
}
void Completa_Palavras(char **palavras, int quant_palavras)
{
    int i, j;
    for(i = 0; i < quant_palavras; i++ )
    {
        for( j = strlen(palavras[i]); j <= 20; j ++)
        {
            palavras[i][j] = ' ';
        }
    }
}
int Alinha_Palavras(char **palavras, int quant_palavras)
{
    int tam = 0, i;
    for(i = 0; i < quant_palavras; i++)
    {
        if(strlen(palavras[i]) > tam)
        tam = strlen(palavras[i]);
    }
    Completa_Palavras(palavras, quant_palavras);
    return tam;
}
int Calcula_K(char **vet, int d, int tamanho)
{
    int i, k = 0;
    for(i = 0; i < tamanho; i++)
    {
        if(vet[i][d] > k)
        {
            k = vet[i][d];
        }
    }
    return k;
}
void CountingSort(char **a, char **b, int d, int tamanho)
{
    int *vet, i ,j, aux = 0;
    vet = malloc(sizeof(int) * 123);
    for(i = 0; i <= 123; i++)
    {
        vet[i] = 0;
    }
    for(j = 0; j < tamanho; j++)
    {
        vet[(int)a[j][d]]++;
    }
    for(i = 1; i <= 123; i++)
    {
        vet[i] = vet[i] + vet[i - 1];
    }
    for(j = tamanho - 1 ; j >= 0; j--)
    {
        aux = vet[(int)a[j][d]] - 1;
        strcpy(b[aux], a[j]);
        vet[(int)a[j][d]]--;
    }
    for(i = 97; i <= 123  ; i++)
    {
        printf("%d ", *(vet + i));
    }
    printf("\n");
    for(i = 0; i < tamanho; i++)
    {
        strcpy(a[i], b[i]);
    }
}

void Radix_Sort(char **a, char **b, int tamanho, int d)
{
    int i;
    for(d = d - 1 ; d >= 0; d--)
    {
        CountingSort(a, b, d, tamanho);
    }
}

// ########### Principal ######################
 
int main()
{
    int tamanho, *vet, i, quant_letras = 27, quant_palavras, maior_palavra;
    char *ordem_palavras, **palavras, **aux;
 
    scanf("%d", &quant_palavras);
 
    palavras = (char **)malloc(quant_palavras * sizeof(char *)); // alloca memoria
    ordem_palavras = (char *)malloc((quant_letras) * sizeof(char));
    aux = (char **)malloc(quant_palavras * sizeof(char *)); // alloca memoria
 
    for (i = 0; i <= quant_palavras; i++)
    {
        *(palavras + i) = malloc(21 * sizeof(char));
    }
    
    for (i = 0; i <= quant_palavras; i++)
    {
        *(aux + i) = malloc(21 * sizeof(char));
    }
    
    scanf("%s", ordem_palavras);
    
    for (i = 0; i < quant_palavras; i++)
    {
        scanf("%s", palavras[i]);
    }
    Verifica_Letra_Maiuscula(palavras, quant_palavras);
    for (i = 0; i < quant_palavras; i++) // imprime o vetor de palavras ordenado
    {
        printf("%s.\n", *(palavras + i));
    }
    maior_palavra = Alinha_Palavras(palavras, quant_palavras);
    printf("%d\n", maior_palavra);
    
    Radix_Sort(palavras, aux, quant_palavras, maior_palavra);
    
    for (i = 0; i < quant_palavras; i++) // imprime o vetor de palavras ordenado
    {
        printf("%s\n", *(palavras + i));
    }
    
    return 0;
}

