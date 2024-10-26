// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ########################## TAD X.h ######################################
 
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

void Converte_Binario(tipoPilha *pilhaAux, tipoPilha *pilhaAux2, int valor)
{
    /* A função converte o valor dado decimal em binário e já realiza a operação
    para empilhar o binário oposto*/
    int aux;
    while(valor >= 1)
    {
        aux = valor % 2;
        valor/= 2;
        Push(pilhaAux, aux);
        if(aux == 1)
        {
            aux = 0;
            Push(pilhaAux2, aux);
        }
        else
        {
            aux = 1;
            Push(pilhaAux2, aux);
        }
    }
    return;
}
void Monta_Pilha3(tipoPilha *pilhaAux, tipoPilha *pilhaAux3)
{
    /* A função monta a pilha3 para calcular o valor do decimal oposto com base no
    primeiro binario */
    int valor;
    tipoElemento *aux3 = pilhaAux->topo;
    while(aux3 != NULL)
    {
        valor = aux3->valor;
        if(valor == 1)
        {
            valor = 0;
            Push(pilhaAux3, valor);
        }
        else
        {
            valor = 1;
            Push(pilhaAux3, valor);
        }
        aux3 = aux3->ant;
    }
    return;
}
int Converte_Decimal(tipoPilha *pilhaAux3)
{
    /* A função calcula o valor do decimal correspondente ao binário oposto*/
    int valor = 0, pot = 0;
    tipoElemento *aux3 = pilhaAux3->topo;
    while(aux3 != NULL)
    {
        valor+= aux3->valor * pow(2, pot);
        aux3 = aux3->ant;
        pot++;
    }
    return valor;
}

void Imprime_Topo(tipoPilha *pilhaAux, int elemento, tipoPilha *pilhaAux2, tipoPilha *pilhaAux3)
{
    /* A função imprime o valor indicado, a pilha que contem o numero binario, a segunda pilha que
    contem o binario invertido e a terceira que contem o decimal invertido*/
    tipoElemento *aux = pilhaAux->topo;
    tipoElemento *aux2 = pilhaAux2->topo;
    printf("%d ", elemento);
    while(aux != NULL)
    {
        printf("%d", aux->valor);
        aux = aux->ant;
    }
    printf(" ");
    while(aux2 != NULL)
    {
        printf("%d", aux2->valor);
        aux2 = aux2->ant;
    }
    printf(" %d\n", Converte_Decimal(pilhaAux3));
    return;
}

// ############################ Principal ###################################
 
int main ()
{
    /* A main inicializa todas pilhas, recebe a quantidade de operações
    e faz o procedimento para imprimir o numero decimal, binário, binário inverso, e
    decimal inverso*/
    
    int quantidade, i, elemento;
    tipoPilha pilha, pilha2, pilha3;
    Inicializa_Pilha(&pilha);
    Inicializa_Pilha(&pilha2);
    Inicializa_Pilha(&pilha3);
    scanf("%d", &quantidade);
    for(i = 0; i < quantidade; i++)
    { 
        scanf("%d", &elemento);
        Converte_Binario(&pilha, &pilha2, elemento);
        Monta_Pilha3(&pilha, &pilha3);
        Imprime_Topo(&pilha, elemento, &pilha2, &pilha3);
        Inicializa_Pilha(&pilha);
        Inicializa_Pilha(&pilha2);
        Inicializa_Pilha(&pilha3);
    }
    
    /*Ao final de cada ciclo é inicializado todas a pilhas para realizar o 
    procedimento novamente*/
    return 0;
}