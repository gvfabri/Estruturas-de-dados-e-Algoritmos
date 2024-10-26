/* Autor: Gabriel Victor Fabri do Carmo
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
// ########### Funções #########################
 
/*A função abaixo inicializa os dois vetores para retirar possível lixo de memória */
void Inicializa_Vetor(int *vet, int numero_pessoas)
{
    int i;
    for ( i = 0; i < numero_pessoas; i++)
    {
        *(vet + i) = 0;
    }
    return;
}
 
/* A função abaixo realiza a partição do vetor, ela recebe um pivo e desloca todos elementos menores que ele para esquerda e maiores para direita*/
int Partition(int *vet, int p, int r)
{
    int i, j, c;
    int x = *(vet + r);
    i = p - 1;
    for(j = p; j < r ;j++)// percorre o vetor para encontrar menores que o pivo
    {
        if(*(vet + j) < x)
        {
            /* Realiza o Swap*/
            i++;
            c = *(vet + i);
            *(vet + i) = *(vet + j);
            *(vet + j) = c;
        }
    }
    /* Realiza o Swap do pivo com o lugar certo dele no vetor*/
    c = *(vet + (i + 1));
    *(vet + (i + 1)) = *(vet + r);
    *(vet + r) = c;
    return i + 1;
}
 
int max(int a, int b) {
    if(a > b)
        return a;
    else
        return b;
}
 
int min(int a, int b) {
    return (a < b)?a:b;
}
 
/* A função quicksort ordena o vetor de forma recursiva, realizando a partião através do pivo*/
void QuickSort(int *vet, int p, int r, int a, int *cont_a, int *cont_b, int maior, int menor)
{
    int q;// auxiliares para contar o nível da recursão
    //int maior = *cont_a, menor = *cont_b;
    if(p < r)
    {
        q = Partition(vet, p, r);
        QuickSort(vet, p, q - 1, a, cont_a, cont_b, maior+1, menor+1);
        
        QuickSort(vet, q + 1, r, a, cont_a, cont_b, maior+1, menor+1);
        
        
    }
    if(p >= r)
    {
    if(maior > (*cont_a))
        (*cont_a) = maior;
    if(menor < (*cont_b))
        (*cont_b) = menor ;
    }
}
 
/* A função abaixo calcula a mediana de tres valores do vetor para achar um pivô melhor fugindo do pior caso de tempo de execução*/
void Mediana_Tres(int *vet, int p, int r, int q)
{
    int c;
    q = (p + r) / 2;
    q = floor(q);
    if(*(vet + p) > *(vet + r) && *(vet + p) < *(vet + q) || *(vet + p) < *(vet + r) && *(vet + p) > *(vet + q) )// caso em que a mediana é o primeiro elemento do vetor
    {
        c = *(vet + r);
        *(vet + r) = *(vet + p);
        *(vet + p) = c;
    }else if(*(vet + q) > *(vet + r) && *(vet + q) < *(vet + p) || *(vet + q) < *(vet + r) && *(vet + q) > *(vet + p))// caso em que a mediana é o elemento do meio do vetor
    {
        c = *(vet + r);
        *(vet + r) = *(vet + q);
        *(vet + q) = c;
    }
    return;
}
 
/* A função quicksort ordena o vetor de forma recursiva, realizando a partião através do pivo, a função abaixo possui o caso melhor verificando a mediana*/
void QuickSort_Mediana(int *vet, int p, int r, int b , int *cont_c, int *cont_d, int maior, int menor )
{
    int q;
    if(p < r)
    {
        Mediana_Tres(vet, p, r, q);
        q = Partition(vet, p, r);
        
        QuickSort_Mediana(vet, p, q -1, b, cont_c, cont_d, maior+1, menor+1);
        QuickSort_Mediana(vet, q + 1, r, b, cont_c, cont_d, maior+1, menor+1);
        if(p >= r)
        {
        if(maior > (*cont_c))
            (*cont_c) = maior;
        if(menor < (*cont_d))
            (*cont_d) = menor;
        }
    }
}
 
// ########### Principal ######################
 
int main()
{
    int i, *vet, *vet2, altura = 0, altura_medianadeTres = 0, p = 0, r, q=0, tamanho, a, b, cont_b = 999999, cont_a = 0, cont_c = 0, cont_d;
    int maior=0, menor=0;
    scanf("%d", &tamanho);
    vet = (int*)malloc(tamanho * sizeof(int));
    vet2 = (int*)malloc(tamanho * sizeof(int));// aloca memória
 
    Inicializa_Vetor(vet, tamanho);// inicializa os dois vetores
    Inicializa_Vetor(vet2, tamanho);
 
    for(i = 0; i < tamanho; i++)// preenche os vetores com valores
    {
        scanf("%d", (vet + i));
    }
 
    for(i=0; i < tamanho; i++)// copia os valores do primeiro vetor para o segundo
    {
        *(vet2 + i) = *(vet + i);
    }
    r = tamanho - 1;
    a = *(vet + r);
    QuickSort(vet, p, r, a, &cont_a, &cont_b, maior, menor);// chama o primeiro quicksort 
    QuickSort_Mediana(vet2, p, r, b, &cont_c, &cont_d, maior, menor);// chama o quicksort que melhora o tempo de execução
    
    if(cont_a > cont_b)// conta o nível da altura do quicksort normal
        altura = cont_a - cont_b;
    else
        altura = cont_b - cont_a;
        
    printf("%d\n", altura);
    if(cont_c > cont_d)// conta o nível da altura do quicksort com mediana de tres
            altura_medianadeTres = cont_c - cont_d;
        else
            altura_medianadeTres = cont_d - cont_c;
    printf("%d", altura_medianadeTres);
    free(vet);
    free(vet2);
    return 0;
}
