// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ########################## TAD Arvore.h ######################################

struct descendente
{
    char nome[100];
    char pai[100];
    char gen;
    int nascimento;
};
typedef struct descendente Pessoa;
struct noArvoreBB
{
    Pessoa chave;
    struct noArvoreBB *esq;
    struct noArvoreBB *dir;
};
typedef struct noArvoreBB tipoABB;

// ###################### Funcoes e Procedimentos do programa ##############

void Inicializa(int nascimento, char nome[100], char gen, tipoABB *arvoreAux)
{
    strcpy(arvoreAux->chave.nome, nome);
    arvoreAux->chave.gen = gen;
    arvoreAux->chave.nascimento = nascimento;
    arvoreAux->esq = NULL;
    arvoreAux->dir = NULL;
    return;
}
tipoABB *InsereNo(char nome[100], char gen, int nascimento, char pai[100])
{
    tipoABB *novo = malloc(sizeof(tipoABB));
    strcpy(novo->chave.nome, nome);
    strcpy(novo->chave.pai, pai);
    novo->chave.gen = gen;
    novo->chave.nascimento = nascimento;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}
void Insere_ElementoABB(char nome[100], char gen, int nascimento, char pai[], tipoABB *arvoreAux)
{
    tipoABB *aux;
    if (arvoreAux)
    {
        if (strcmp(arvoreAux->chave.nome, pai) == 0)
        {
            if (nascimento > arvoreAux->chave.nascimento && nascimento > 2011)
            {
                if (arvoreAux->esq == NULL)
                    arvoreAux->esq = InsereNo(nome, gen, nascimento, pai);
                else if (arvoreAux->dir == NULL)
                    arvoreAux->dir = InsereNo(nome, gen, nascimento, pai);
                else
                    Insere_ElementoABB(nome, gen, nascimento, pai, arvoreAux->esq);
            }
            else if(nascimento > arvoreAux->chave.nascimento)
            {
                if(gen == 'F')
                {
                if (arvoreAux->dir == NULL)
                    arvoreAux->dir = InsereNo(nome, gen, nascimento, pai);
                else if (arvoreAux->esq == NULL)
                    {
                    arvoreAux->esq = InsereNo(nome, gen, nascimento, pai);
                    if(arvoreAux->esq->chave.gen == 'F' && arvoreAux->dir->chave.gen == 'F')
                    {
                        if(arvoreAux->esq->chave.nascimento > arvoreAux->dir->chave.nascimento)
                        {
                            aux = arvoreAux->esq;
                            arvoreAux->esq = arvoreAux->dir;
                            arvoreAux->dir = aux;
                        }
                    }
                    }
                else
                    Insere_ElementoABB(nome, gen, nascimento, pai, arvoreAux->esq);
                }
                else
                {
                    if (arvoreAux->esq == NULL)
                        arvoreAux->esq = InsereNo(nome, gen, nascimento, pai);
                    else if (arvoreAux->dir == NULL)
                        arvoreAux->dir = InsereNo(nome, gen, nascimento, pai);
                    else
                        Insere_ElementoABB(nome, gen, nascimento, pai, arvoreAux->esq);
                }
            }
        }
        else
        {
            if (arvoreAux)
            {
                Insere_ElementoABB(nome, gen, nascimento, pai, arvoreAux->esq);
                Insere_ElementoABB(nome, gen, nascimento, pai, arvoreAux->dir);
            }
        }
    }
    return;
}

tipoABB *removeNo(tipoABB *arvoreAux)
{
    tipoABB *aux;
    aux = arvoreAux;
    free(aux);
    return NULL;
}

tipoABB *removeABB(tipoABB *arvoreAux, char nome[100])
{
    tipoABB *temp, *aux;
    if (arvoreAux == NULL)
        return NULL;
    if( strcmp(arvoreAux->chave.nome, nome) == 0)
    {
        if(arvoreAux->esq != NULL && arvoreAux->dir != NULL)
        {
        temp = arvoreAux;
        while(temp->esq != NULL)
            temp = temp->esq;
        aux = arvoreAux;
        while(aux->esq != temp)
            aux = aux->esq;
        aux->esq = removeNo(aux->esq);
        if(aux->dir != NULL)
            aux->dir = removeNo(aux->dir);
        aux = arvoreAux;
        if(arvoreAux->esq != NULL && arvoreAux->dir != NULL)
        {
        while(aux->esq != NULL)
            aux = removeABB(arvoreAux, nome);
        }
        }
        free(arvoreAux);
        return NULL;
    }
    else
    if(arvoreAux)
    {
        arvoreAux->esq = removeABB(arvoreAux->esq, nome);
        arvoreAux->dir = removeABB(arvoreAux->dir, nome);
    }
    return arvoreAux;
}
void Imprime_Arvore(tipoABB *arvoreAux)
{
    if (arvoreAux)
    {
        printf("%s\n", arvoreAux->chave.nome);
        Imprime_Arvore(arvoreAux->esq);
        Imprime_Arvore(arvoreAux->dir);
    }
    return;
}

// ############################ Principal ###################################

int main()
{
    int quantidade, nascimento, i = 0, opcao;
    char gen, nome[100], pai[100];
    tipoABB arvore;
    tipoABB *aux;
    scanf("%s %c %d", nome, &gen, &nascimento);
    Inicializa(nascimento, nome, gen, &arvore);
    scanf("%d", &quantidade);
    while (i < quantidade)
    {
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            scanf("%s %c %d %s", nome, &gen, &nascimento, pai);
            Insere_ElementoABB(nome, gen, nascimento, pai, &arvore);
        }
        else
        {
            scanf("%s", nome);
            aux = removeABB(&arvore, nome);
        }
        i++;
    }
    Imprime_Arvore(&arvore);
    return 0;
}