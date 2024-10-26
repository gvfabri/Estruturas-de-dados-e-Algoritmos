// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>
 
// ########################## TAD ListaLDE.h ######################################
 
struct elemento
{
    float valor;
    float lucro;
    int quantidade;
    int id;
    struct elemento *proximo;
};
typedef struct elemento tipoElemento;
struct listaED{
    tipoElemento *primeiroElemento;
    tipoElemento *ultimoElemento;
    int tamanhoLista;
};
typedef struct listaED tipoLDE;
 
// ###################### Funcoes e Procedimentos do programa ##############
 
void Inicializa(tipoLDE *listaAux)
{
    listaAux->primeiroElemento = NULL;
    listaAux->ultimoElemento = NULL;
    listaAux->tamanhoLista = 0;
    return;
}
 
void Insere_Novo_Produto(tipoLDE *listaAux, int id, int quantidade, float preco)
{
    int flag = 1;
    tipoElemento *aux = listaAux->primeiroElemento;
    tipoElemento *novoElemento = malloc(sizeof(tipoElemento));
    tipoElemento *inicioElemento = listaAux->primeiroElemento;
    while(inicioElemento != NULL)
    {
        if (id == inicioElemento->id)
        flag = 0;
        inicioElemento = inicioElemento->proximo;
    }
    if (flag == 1)
    {
    novoElemento->valor = preco;
    novoElemento->id = id;
    novoElemento->quantidade = quantidade;
    if(listaAux->tamanhoLista == 0)
    {
        novoElemento->proximo = NULL;
        listaAux->primeiroElemento = novoElemento;
        listaAux->ultimoElemento = novoElemento;
    }
    else if( novoElemento->valor > listaAux->primeiroElemento->valor )
    {
        //printf("%f", listaAux->primeiroElemento->valor);
        //listaAux->primeiroElemento->valor = novoElemento->valor;
        novoElemento->proximo = listaAux->primeiroElemento;
        listaAux->primeiroElemento = novoElemento;
    }
    else if( novoElemento->valor < listaAux->ultimoElemento->valor)
    {
        novoElemento->proximo = NULL;
        listaAux->ultimoElemento->proximo = novoElemento;
        listaAux->ultimoElemento = novoElemento;
    }
    else if ( novoElemento->valor > listaAux->ultimoElemento->valor && novoElemento->valor < listaAux->primeiroElemento->valor)
    {
        while (aux->proximo != NULL && novoElemento->valor < aux->proximo->valor )
            aux = aux->proximo;
            novoElemento->proximo = aux->proximo;
            aux->proximo = novoElemento;
    }
    listaAux->tamanhoLista++;
    }
    else
    printf("ja existe\n");
    return;
}
 
void Aumenta_Quantidade_Produto(tipoLDE *listaAux, int id, int quantAdc)
{
    int flag = 1; 
    tipoElemento *aux = listaAux->primeiroElemento;
    while(aux != NULL)
    {
        if ( id == aux->id)
        {
            aux->quantidade += quantAdc;
            flag = 0;
            break;
        }
        aux = aux->proximo;
    }
    if (flag == 1)
    printf("nao existe\n");
    return;
}
 
void Compra_Produto(tipoLDE *listaAux, int id)
{
    int flag = 1; 
    tipoElemento *aux = listaAux->primeiroElemento;
    while(aux != NULL)
    {
        if ( id == aux->id)
        {
            if (aux->quantidade)
            {
            aux->lucro += aux->valor;
            aux->quantidade--;
            flag = 0;
            }
            else 
            flag = 2;
        }
        aux = aux->proximo;
    }
    if (flag == 1)
    {
        printf("nao existe\n");
    }
    else if (flag == 2)
        printf("nao existe\n");
    return;
}
 
void Exclui_Produto(tipoLDE *listaAux, int id)
{
    int flag = 1;
    tipoElemento *remover = NULL;
    tipoElemento *aux = listaAux->primeiroElemento;
    if(id == listaAux->primeiroElemento->id)
    {
        remover = listaAux->primeiroElemento;
        listaAux->primeiroElemento = remover->proximo;
        listaAux->tamanhoLista--;
        free(remover);
        flag = 0;
    }
    else if(id == listaAux->ultimoElemento->id)
    {
        remover = listaAux->ultimoElemento;
        listaAux->ultimoElemento = remover->proximo;
        listaAux->tamanhoLista--;
        free(remover);
        flag = 0;
    }
    else
    {
    while(aux != NULL)
    {
        if ( id == aux->id)
        {
            remover = aux->proximo;
            aux->proximo = remover->proximo;
            flag = 0;
            listaAux->tamanhoLista--;
            free(remover);
            break;
        }
        aux = aux->proximo;
    }
    }
    if(flag == 1 )
    printf("nao existe\n");
    return;
}
 
void Imprime_Valores(tipoLDE *listaAux)
{
    tipoElemento *aux = listaAux->primeiroElemento;
    while(aux != NULL)
    {
        printf("%d %f\n", aux->id, aux->lucro);
        aux = aux->proximo;
    }
    return;
}
 
// ############################ Principal ###################################
 
int main ()
{
    int quantidade, i = 0, opcao, id = 0, quant = 0, quantAdc = 0; 
    float preco;
    tipoLDE listaED;
    Inicializa(&listaED);
    scanf("%d ", &quantidade);
    while(i < quantidade)
    {
        scanf("%d ", &opcao);
        if( opcao == 1)
        {
            scanf("%d %d %f", &id, &quant, &preco);
            Insere_Novo_Produto(&listaED, id, quant, preco);
        }
        else if( opcao == 2)
        {
            scanf("%d %d", &id, &quantAdc);
            Aumenta_Quantidade_Produto(&listaED, id, quantAdc);
        }
        else if( opcao == 3)
        {
            scanf("%d", &id);
            Compra_Produto(&listaED, id);
        }
        else if( opcao == 4)
        {
            scanf("%d", &id);
            Exclui_Produto(&listaED, id);
        }
        i++;
 
    }
    Imprime_Valores(&listaED);
return 0;
}