/* Autor: Gabriel Victor Fabri do Carmo
*/
#include <stdio.h>
#include <stdlib.h>
 
// ########### Funções #########################
 
/*A função abaixo inicializa os dois vetores, o vetor de numero de microrganismos e o vetor de potencia de cada dose */
void Inicializa_Vetor(int *vet, int numero_pessoas)
{
    int i;
    for ( i = 0; i < numero_pessoas; i++)
    {
        *(vet + i) = 0;
    }
    return;
}
 
/* A função abaixo faz a leitura de cada valor de microrganismo e potencia de dose em cada vetor*/
void Preenche_Vetor(int *vet, int numero_pessoas)
{
    int i;
    for (i = 0; i < numero_pessoas; i++)
    {
        scanf("%d", (vet + i));
    }
    return;
}
 
/* A função abaixo faz a ordenação do vetor como um algoritmo Bubble Sort*/
void Insertion_Sort(int *vet, int numero_pessoas)
{
    int i, j, c;
    for( j = 0; j < numero_pessoas; j++)
    {
        c = vet[j];
        i = j - 1;
        while( i > 0 && vet[i] > c)
        {
            vet[i + 1] = vet[i];
            i--;
            vet[i + 1] = c;
        }
    }

    return;
}
 
/* A função verifica se é possível curar todos com as potencias de doses no momento*/
int Verifica_Cura(int *vet_microrganismos, int *vet_potencia, int numero_pessoas)
{
    int i, flag = 0;
    for(i = 0; i < numero_pessoas; i++)// verifica se alguma pessoa tem mais microrganismos do que a potencia da dose disponível
    {
        if(*(vet_microrganismos + i) >= *(vet_potencia + i))
        flag = 1;
    }
    return flag;
}
 
 
// ########### Principal ######################
 
int main()
{
    int numero_pessoas, *vet_microrganismos, *vet_potencia, i, possibilidade_cura = 0;
    scanf("%d", &numero_pessoas);
    vet_potencia = (int*)malloc( numero_pessoas * sizeof(int));
    vet_microrganismos = (int*)malloc( numero_pessoas * sizeof(int));
    
    Inicializa_Vetor(vet_microrganismos, numero_pessoas);
    Inicializa_Vetor(vet_potencia, numero_pessoas);
    /*Le todos os valores de microrganismos e potencia de doses*/
    Preenche_Vetor(vet_microrganismos, numero_pessoas);
    Preenche_Vetor(vet_potencia, numero_pessoas);
    /* Ordena os vetores por Bubble Sort*/
    Insertion_Sort(vet_microrganismos, numero_pessoas);
    Insertion_Sort(vet_potencia, numero_pessoas);
    
    possibilidade_cura = Verifica_Cura(vet_microrganismos, vet_potencia, numero_pessoas);
    if( possibilidade_cura)
        printf("nao");
    else
        printf("sim");
    for (i = 0; i < numero_pessoas; i++)
    {
        printf("%d ", *(vet_microrganismos + i));
    }
    for (i = 0; i < numero_pessoas; i++)
    {
        printf("%d ", *(vet_potencia + i));
    }
    free(vet_microrganismos);
    free(vet_potencia);
    return 0;
}