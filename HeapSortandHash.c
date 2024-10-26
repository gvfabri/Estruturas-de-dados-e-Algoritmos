/* Autor: Gabriel Victor Fabri do Carmo
 
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
 
// ########### Funções #########################
 #define TAMANHO_TABELA 1000

int tabela_hash[TAMANHO_TABELA];

int funcao_hash(int numero) {
  return numero % TAMANHO_TABELA;
}

void criar_tabela_hash(int vetor[], int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    int indice = funcao_hash(vetor[i]);
    tabela_hash[indice] = 1;
  }
}

int buscar_numero(int numero) {
  int indice = funcao_hash(numero);
  return tabela_hash[indice];
}

int Compara_Strings(char **palavras, char *ordem_palavras, int l, int i, int tamanho, int quant_letras)
{
    int verificador = 0, j = 0, k;
    char c, aux, aux2;
    for(k = 0; k <= quant_letras; k++)
    {
        c = *(ordem_palavras + k);
        aux = palavras[l][j];
        aux2 = palavras[i][j];
        if(aux == aux2)
        {
            j++;
            k = 0;
        }
        else
        {
            if(aux == c || aux == 0)
        {
            return 0;
            break;
        }
        if(aux2 == c || aux2 == 0)
        {
            return 1;
            break;
        }
        }
    }
}
void Max_HeapFy(char **palavras, char *ordem_palavras, int i, int tamanho, int quant_letras)
{
    int l, r, max, j;
    char *c;
    c = malloc(sizeof(char) * 33);
    l = 2 * i;
    r = 2 * i + 1;
    if((l <= tamanho) && Compara_Strings(palavras, ordem_palavras, l, i, tamanho, quant_letras) > 0)
        max = l;
    else
        max = i;
    if((r <= tamanho) && Compara_Strings(palavras, ordem_palavras, r, max, tamanho, quant_letras) > 0)
        max = r;
    if(max != i)
    {
        c = *(palavras + max);
        *(palavras + max) = *(palavras + i);
        *(palavras + i) = c;
        Max_HeapFy(palavras, ordem_palavras, max, tamanho, quant_letras);
    }
    
    
}
void Build_Max_Heap(char **palavras, char *ordem_palavras, int tamanho, int quant_letras)
{
    int n, i;
    n = tamanho;
    for(i = n/2; i >= 1; i--)
    {
        Max_HeapFy(palavras, ordem_palavras, i, tamanho, quant_letras);
    }
    return;
}
char *Heap_Extract_Max(char **vet, char *ordem_palavras, int tamanho, int quant_letras)
{
    char *max;
    max = malloc(sizeof(char) * 33);
    int last;
    if(tamanho < 1)
        printf("Error");
    max = vet[1];
    last = tamanho;
    *(vet + 1) = vet[last];
    tamanho--;
    Max_HeapFy(vet, ordem_palavras, 1, tamanho, quant_letras);
    return max;
    
}
void HeapSort(char **palavras, char *ordem_palavras, int tamanho, int quant_letras)
{
    int n, i , j;
    char **aux, aux2;
    aux = malloc(sizeof(char) * 33);
    for(j = 1; j < tamanho; j++)
    {
        *(aux + j) = malloc( 33 * sizeof(char));
    }
    Build_Max_Heap(palavras, ordem_palavras, tamanho, quant_letras);
    n = tamanho;
    i = n;
    while(n > 0)
    {
        *(aux + n) = Heap_Extract_Max(palavras, ordem_palavras, n, quant_letras);
        n--;
    }
    for(i = 1; i <= tamanho; i++)
    {
        printf("%s ", *(aux + i));
    }
}
void Palavra_Invalida(char **palavras, int l)
{
    printf("A palavra %s eh invalida\n", palavras[l]);
    return;
}
 
int Verifica_PalavraInavalida(char **palavras, int quant_palavras)
{
    int i, j, valor_ascii;
    for(i = 1; i < quant_palavras; i++)
    {
        for(j = 0; j < strlen(palavras[i]); j++)
        {
            valor_ascii = palavras[i][j];
        
            if(valor_ascii < 97 || valor_ascii > 122 )
            {
            Palavra_Invalida(palavras, i);
            return 1;
            }
        }
    }
    return 0;
}
// ########### Principal ######################
 
int main()
 
{
    int tamanho, *vet, i, quant_letras, quant_palavras,  flag = 0;
    char *ordem_palavras, **palavras;
 
    scanf("%d", &quant_palavras);
    scanf("%d", &quant_letras);
    
    palavras = (char**)malloc(quant_palavras * sizeof(char*));
    ordem_palavras = (char*)malloc((quant_letras  + 1)* sizeof(char));
 
    for(i = 0; i <= quant_palavras; i++)
    {
        *(palavras + i) = malloc( 33 * sizeof(char));
    }
    scanf("%s", ordem_palavras);
    for(i = 1; i <= quant_palavras; i++)
    {
        scanf("%s", *(palavras + i));
    }
    flag = Verifica_PalavraInavalida(palavras, quant_palavras);
    if(flag == 0)
    HeapSort(palavras, ordem_palavras, quant_palavras, quant_letras);
    return 0;
}

