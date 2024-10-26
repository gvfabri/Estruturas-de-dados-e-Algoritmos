#include <stdio.h>
#include <stdlib.h>

//########### Funções #########################

int Busca_Valor(int valor_encontrar, int *valores, int inicio, int fim)
{
    int meio = (inicio + fim)/ 2;
    if(inicio > fim)
        return 0;
    if(valores[meio] == valor_encontrar)
        return meio;
    if(valores[meio] < valor_encontrar)
        return Busca_Valor(valor_encontrar, valores, meio-1, fim);
    else
        return Busca_Valor(valor_encontrar, valores, inicio, meio+1);
}

// ########### Principal ######################

int main()
{
    int tamanho, *valores, valor, valor_encontrar, i, valor_encontrado = 0, inicio, fim;
    scanf("%d", &tamanho);
    valores = (int*)malloc( tamanho * sizeof(int));
    for(i = 0; i < tamanho; i++)
    {
        scanf("%d", &valor);
        valores[i] = valor;
    }
    scanf("%d", &valor_encontrar);
    fim =  tamanho;
    valor_encontrado = Busca_Valor(valor_encontrar, valores, inicio, fim);
    if(valor_encontrado > 0)
        printf("%d", valor_encontrado);
    else
        printf("%d nao foi encontrado", valor_encontrar);
    return 0;
}