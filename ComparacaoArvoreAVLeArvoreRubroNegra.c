// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>
 
// ########################## TAD ArvoreAVL e AVP #################################
 
struct itemA
{
    int chave;
    int altura;
};
typedef struct itemA item;
struct noArvoreBB
{
    item tItem;
    struct noArvoreBB *esq;
    struct noArvoreBB *dir;
};
typedef struct noArvoreBB tipoAVL;

struct itemB
{
    int chave;
    int altura;
};
typedef struct itemB itemb;
struct noArvoreBBVP
{
    itemb tItem;
    struct noArvoreBBVP *esq;
    struct noArvoreBBVP *dir;
    int cor;
};
typedef struct noArvoreBBVP tipoAVP;

// ###################### Funcoes e Procedimentos do programa ##############

//A funcão calcula qual subarvore a esquerda e a direita é maior
int maior(int a, int b)
{
    // se a (subarvore da esquerda) for maior que b(subarvore da direita) retorna a, se nao retorna b
    if(a > b)
        return a; 
    else
        return b;
}
// aA função abaixo calcula a altura do no da arvore para auxiliar no calculo do fator de balanceamento
int Calcula_Altura(tipoAVL *arvoreAux)
{
    if(arvoreAux == NULL)
        return 0;
    return arvoreAux->tItem.altura;
}
/* A função abaixo roda a arvore para esquerda fazendo uma rotação à direita o pB recebe a direita do A
e então a subarvore a esquerda de B vai se apontada pelo ponteiro a direita de A, e então a esquerda de B será o A*/
tipoAVL *Rotacao_RR(tipoAVL *arvoreAux, int *quant_rot)
{
    tipoAVL *pA = arvoreAux, *pB;
    pB = pA->dir;
    pA->dir = pB->esq;
    pB->esq = pA;
    pA->tItem.altura = 1 + maior(Calcula_Altura(pA->esq), Calcula_Altura(pA->dir));
    pB->tItem.altura = 1 + maior(Calcula_Altura(pB->esq), Calcula_Altura(pB->dir));
    pA = pB;
    (*quant_rot)++;
    return pA;
}
/* A função abaixo roda a arvore para direita fazendo uma rotação à esquerda o pB recebe a esquerda do A
e então a subarvore a direita de B vai se apontada pelo ponteiro a esquerda de A, e então a direita de B será o A*/
tipoAVL *Rotacao_LL(tipoAVL *arvoreAux, int *quant_rot)
{
    tipoAVL *pA = arvoreAux, *pB;
    pB = pA->esq;
    pA->esq = pB->dir;
    pB->dir = pA;
    pA->tItem.altura = 1 + maior(Calcula_Altura(pA->esq), Calcula_Altura(pA->dir));
    pB->tItem.altura = 1 + maior(Calcula_Altura(pB->esq), Calcula_Altura(pB->dir));
    pA = pB;
   (*quant_rot)++;
    return pA;
}
/* A função abaixo realiza uma rotação dupla à direita*/
tipoAVL *Rotacao_LR(tipoAVL *arvoreAux, int *quant_rot)
{
    tipoAVL *pA = arvoreAux, *pB, *pC;
    pB = pA->esq;
    pC = pB->dir;
    pB->dir = pC->esq;
    pC->esq = pB;
    pA->esq = pC->dir;
    pC->dir = pA;
    //recalcula a altura de cada nó
 
    pA->tItem.altura = 1 + maior(Calcula_Altura(pA->esq), Calcula_Altura(pA->dir));
    pB->tItem.altura = 1 + maior(Calcula_Altura(pB->esq), Calcula_Altura(pB->dir));
    pC->tItem.altura = 1 + maior(Calcula_Altura(pC->esq), Calcula_Altura(pC->dir));
 
    pA = pC;
    (*quant_rot)++;
    return pA;
}
/* A função abaixo realiza uma rotação dupla à esquerda*/
tipoAVL *Rotacao_RL(tipoAVL *arvoreAux, int *quant_rot)
{
    tipoAVL *pA = arvoreAux, *pB, *pC;
    pB = pA->dir;
    pC = pB->esq;
    pB->esq = pC->dir;
    pC->dir = pB;
    pA->dir = pC->esq;
    pC->esq = pA;
    //recalcula a altura de cada nó
    
    pA->tItem.altura = 1 + maior(Calcula_Altura(pA->esq), Calcula_Altura(pA->dir));
    pB->tItem.altura = 1 + maior(Calcula_Altura(pB->esq), Calcula_Altura(pB->dir));
    pC->tItem.altura = 1 + maior(Calcula_Altura(pC->esq), Calcula_Altura(pC->dir));
    pA = pC;
    (*quant_rot)++;
    return pA;
}
int Cor(tipoAVP *arvoreAux)
{
    if(arvoreAux == NULL)
        return 0;
    else
        return arvoreAux->cor;
}
tipoAVP *Troca_Cor(tipoAVP *arvoreAux, int *quant_cor)
{
    printf("a%d b%d c%d", arvoreAux->cor, arvoreAux->esq->cor, arvoreAux->dir->cor);
    (*quant_cor)++;
    if(arvoreAux->cor == 1)
        arvoreAux->cor = 0;
    else
        arvoreAux->cor = 1;
    if(arvoreAux->esq != NULL)
    {
        if(arvoreAux->esq->cor == 1)
            arvoreAux->esq->cor = 0;
        else
            arvoreAux->esq->cor = 1;
        (*quant_cor)++;
    }
    if(arvoreAux->dir != NULL)
    {
        if(arvoreAux->dir->cor == 1)
            arvoreAux->dir->cor = 0;
        else
            arvoreAux->dir->cor = 1;
        (*quant_cor)++;
    }
    return arvoreAux;
}
tipoAVP *Rotacao_Esquerda(tipoAVP *arvoreAux, int *quant_rot, int *quant_cor)
{
    tipoAVP *pA = arvoreAux, *pB;
    pB = pA->dir;
    pA->dir = pB->esq;
    pB->esq = pA;
    (*quant_rot)++;
    return pB;
}

tipoAVP *Rotacao_Direita(tipoAVP *arvoreAux, int *quant_rot, int *quant_cor)
{
    tipoAVP *pA = arvoreAux, *pB;
    pB = pA->esq;
    pA->esq = pB->dir;
    pB->dir = pA;
    (*quant_rot)++;
    return pB;
}
tipoAVP *Rotacao_Esquerda_S(tipoAVP *arvoreAux, int *quant_rot, int *quant_cor)
{
    tipoAVP *pA = arvoreAux->dir, *pB;
    pB = pA->esq;
    pA->esq = pB->dir;
    pB->dir = pA;
    arvoreAux->dir = pB;
    (*quant_rot)++;
    return arvoreAux;
}

tipoAVP *Rotacao_Direita_S(tipoAVP *arvoreAux, int *quant_rot, int *quant_cor)
{
    int c = arvoreAux->tItem.chave;
    tipoAVP *pA = arvoreAux->esq, *pB;
    pB = pA->dir;
    pA->dir = pB->esq;
    pB->esq = pA;
    arvoreAux->esq = pB;
    (*quant_rot)++;
    return arvoreAux;
}
// A função abaixo calcula o fator de balanceamento de determinado no, fazendo a diferença da altura da esquerda menos da direita
int alturabalanceamento(tipoAVL *arvoreAux)
{
    if(arvoreAux == NULL)
        return 0;
    return (Calcula_Altura(arvoreAux->esq) - Calcula_Altura(arvoreAux->dir));
}
// A função abaixo verifica a necessidade de Balancear cada nó e chama a rotação devidamente necessaria
tipoAVL *Balancear(tipoAVL *arvoreAux, int *quant_rot)
{
    // fb recebe o fator de balanceamento do nó
    int fb = alturabalanceamento(arvoreAux);
    if (fb > 1 && alturabalanceamento(arvoreAux->esq) >= 0)
        arvoreAux = Rotacao_LL(arvoreAux, quant_rot);
    else if(fb < -1 && alturabalanceamento(arvoreAux->dir) <= 0)
        arvoreAux = Rotacao_RR(arvoreAux, quant_rot);
    else if (fb > 1 && alturabalanceamento(arvoreAux->esq) < 0)
        arvoreAux = Rotacao_LR(arvoreAux, quant_rot);
    else if (fb < -1 && alturabalanceamento(arvoreAux->dir) > 0)
        arvoreAux = Rotacao_RL(arvoreAux, quant_rot);
    return arvoreAux;
}
// A função abaixo Inicializa a arvore sendo a primeira inserção
tipoAVL *Inicializa(int c, tipoAVL *arvoreAux)
{
    arvoreAux = malloc(sizeof(tipoAVL));
    arvoreAux->tItem.chave = c;
    arvoreAux->tItem.altura = 1;
    arvoreAux->esq = NULL;
    arvoreAux->dir = NULL;
    return arvoreAux;
}
tipoAVP *InicializaAVP(int c, tipoAVP *arvoreAux)
{
    return NULL;
}
// A função abixo insere um novo no na arvore de acordo com a posiçao correta apontada pela funcao Insere_ElementoABB
tipoAVL *InsereNo(int c, tipoAVL *arvoreAux)
{
    tipoAVL *novoNo = malloc(sizeof(tipoAVL));
    novoNo->tItem.altura = 1;
    novoNo->tItem.chave = c;
    novoNo->dir = NULL;
    novoNo->esq = NULL;
    return novoNo;
}
tipoAVP *InsereNoAVP(tipoAVP *arvoreAux, int c, int *resp)
{
    tipoAVP *novoNo = malloc(sizeof(tipoAVP));
    novoNo->tItem.chave = c;
    novoNo->cor = 1;
    novoNo->dir = NULL;
    novoNo->esq = NULL;
    *resp = 1;
    return novoNo;
}
// A função abaixo insere um novo elemento na arvore igual a uma arvore binaria de busca, porem ao voltar de cada recursao é verificado a necessidade de balanceamento
tipoAVL *Insere_ElementoAVL(int chave, tipoAVL *arvoreAux, int *quant_rot_avl)
{
    if (arvoreAux == NULL)
        return InsereNo(chave, arvoreAux);
    else
    {
        if (chave < arvoreAux->tItem.chave )
            arvoreAux->esq = Insere_ElementoAVL(chave, arvoreAux->esq, quant_rot_avl);
        else if (chave > arvoreAux->tItem.chave)
            arvoreAux->dir = Insere_ElementoAVL(chave, arvoreAux->dir, quant_rot_avl);
    }
    // Na volta da recusao calcula o fator de balanceamento e altura de cada no chamado na recursao
    arvoreAux->tItem.altura = 1 + maior(Calcula_Altura(arvoreAux->esq), Calcula_Altura(arvoreAux->dir));
    // Verifica a necessidadede balancear a arvore passando o no da volta de cada recursao
    arvoreAux = Balancear(arvoreAux, quant_rot_avl);
    
    return arvoreAux;
}
void Imprime_ArvoreAVP(tipoAVP *arvoreAux);
tipoAVP *Insere_ElementoAVP(int chave, tipoAVP *arvoreAux, int *quant_cor, int *quant_rot_avp)
{
    int resp, d = 0, a = 0, b = 0;
    //Verifica a necessidadede balancear a arvore passando o no da volta de cada recursao
    int c = 0;
    if(arvoreAux == NULL)
        return InsereNoAVP(arvoreAux, chave, &resp);
    else
    {
    if (chave < arvoreAux->tItem.chave )
        arvoreAux->esq = Insere_ElementoAVP(chave, arvoreAux->esq, quant_cor, quant_rot_avp);
    else if (chave > arvoreAux->tItem.chave)
        arvoreAux->dir = Insere_ElementoAVP(chave, arvoreAux->dir, quant_cor, quant_rot_avp);
    }
    int chaves = arvoreAux->tItem.chave; 
    if(arvoreAux->dir != NULL)
        if(arvoreAux->dir->dir != NULL)
        a = Cor(arvoreAux->dir->dir);
    if(arvoreAux->esq != NULL)
        if(arvoreAux->esq->esq != NULL)
        b = Cor(arvoreAux->esq->esq);
    if(arvoreAux->esq != NULL)
        if(arvoreAux->esq->dir != NULL)
        d = Cor(arvoreAux->esq->dir);
    if(arvoreAux->dir != NULL)
        if(arvoreAux->dir->esq != NULL)
        c = Cor(arvoreAux->dir->esq);
    if(Cor(arvoreAux->esq) == 1 && Cor(arvoreAux->dir) == 1 && ( a == 1 || b == 1 || d == 1 || c == 1) )
        arvoreAux = Troca_Cor(arvoreAux, quant_cor);
    if((Cor(arvoreAux->esq) == 1 && Cor(arvoreAux->dir)) == 0)
    {
        if(Cor(arvoreAux->esq) == 1 && Cor(arvoreAux->esq->dir) == 1)
        {
            arvoreAux = Rotacao_Direita_S(arvoreAux, quant_rot_avp, quant_cor);
        }
        if(Cor(arvoreAux->esq) == 1 && Cor(arvoreAux->esq->esq) == 1)
        {
            arvoreAux = Rotacao_Direita(arvoreAux, quant_rot_avp, quant_cor);
            arvoreAux->cor = !arvoreAux->cor;
            (*quant_cor)++;
            arvoreAux->dir->cor = !arvoreAux->dir->cor;
            (*quant_cor)++;
        }
    }
    if (Cor(arvoreAux->dir) == 1 && Cor(arvoreAux->esq) == 0)
    {
        printf("Antes\n");
        Imprime_ArvoreAVP(arvoreAux);
        if(Cor(arvoreAux->dir) == 1 && Cor(arvoreAux->dir->esq) == 1)
        {
            arvoreAux = Rotacao_Esquerda_S(arvoreAux, quant_rot_avp, quant_cor);
            printf("Rot simples\n");
            Imprime_ArvoreAVP(arvoreAux);
        }
        if(Cor(arvoreAux->dir) == 1 && Cor(arvoreAux->dir->dir) == 1)
        {
            arvoreAux = Rotacao_Esquerda(arvoreAux, quant_rot_avp, quant_cor);
            arvoreAux->cor = !arvoreAux->cor;
            (*quant_cor)++;
            arvoreAux->esq->cor = !arvoreAux->esq->cor;
            (*quant_cor)++;
            printf("Rot formal\n");
            Imprime_ArvoreAVP(arvoreAux);
        }  
    }
    
    return arvoreAux;
}
int Calcula_Altura_ABB(tipoAVL *arvoreAux);
// a função abaixo pesquisa um determinado valor na arvore, flag é usada para mostra a altura do ultimo nó pesquisado, da entra da linha 3
int Pesquisa_Arvore(tipoAVL *arvoreAux, int valor, int flag)
{
    int altura;
    if (arvoreAux)
    {
        if(arvoreAux->tItem.chave == valor)
        {
            altura = Calcula_Altura_ABB(arvoreAux);
            return arvoreAux->tItem.chave;
        }
        int resultado_esq = Pesquisa_Arvore(arvoreAux->esq, valor, flag);
        if( resultado_esq != -1)
            return resultado_esq;
        
        int resultado_dir = Pesquisa_Arvore(arvoreAux->dir, valor, flag);
        if( resultado_dir != -1)
            return resultado_dir;
    }
    return -1;
}
// A função abaixo calcula a altura de determinado nó da arvore 
int Calcula_Altura_ABB(tipoAVL *arvoreAux)
{
    if(arvoreAux == NULL)
        return 0;
    else
    {
        int esq = Calcula_Altura_ABB(arvoreAux->esq);
        int dir = Calcula_Altura_ABB(arvoreAux->dir);
        if(esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}
int Calcula_Altura_AVP(tipoAVP *arvoreAux)
{
    if(arvoreAux == NULL)
        return 0;
    else
    {
        int esq = Calcula_Altura_AVP(arvoreAux->esq);
        int dir = Calcula_Altura_AVP(arvoreAux->dir);
        if(esq > dir)
                return esq + 1;
        else 
                return dir + 1;
    }
}
int Calcula_Altura_Negra(tipoAVP *arvoreAux)
{
    if(arvoreAux == NULL)
        return 0;
    else
    {
        int esq = Calcula_Altura_AVP(arvoreAux->esq);
        int dir = Calcula_Altura_AVP(arvoreAux->dir);
        if(esq > dir)
            if(arvoreAux->cor == 0)
                return esq + 1;
            else 
                return esq;
        else 
            if(arvoreAux->cor == 0)
                return dir + 1;
            else return dir;
    }
}
// A função abaixo desaloca a memoria de toda arvore, indo até a folha para liberar até a raiz
tipoAVL *Desaloca_Memoria(tipoAVL *arvoreAux)
{
    if(arvoreAux != NULL)
    {
        Desaloca_Memoria(arvoreAux->esq);
        Desaloca_Memoria(arvoreAux->dir);
        free(arvoreAux);
    }
    return NULL;
}
// A função abaixo desaloca a memoria de toda arvore Rubro-Negra, indo até a folha para liberar até a raiz
tipoAVP *Desaloca_MemoriaAVP(tipoAVP *arvoreAux)
{
    if(arvoreAux != NULL)
    {
        Desaloca_MemoriaAVP(arvoreAux->esq);
        Desaloca_MemoriaAVP(arvoreAux->dir);
        free(arvoreAux);
    }
    return NULL;
}
void Imprime_Arvore(tipoAVL *arvoreAux)
{
    if (arvoreAux)
    {
        Imprime_Arvore(arvoreAux->dir);
         printf("%d %d\n", arvoreAux->tItem.chave, arvoreAux->tItem.altura);
        Imprime_Arvore(arvoreAux->esq);
    }
    return;
}
void Imprime_ArvoreAVP(tipoAVP *arvoreAux)
{
    if (arvoreAux)
    {
        Imprime_ArvoreAVP(arvoreAux->dir);
         printf("%d %d\n", arvoreAux->tItem.chave, arvoreAux->cor);
        Imprime_ArvoreAVP(arvoreAux->esq);
    }
    return;
}
// ############################ Principal ###################################
 
int main()
{
    int i = 0, valor = 0, n_pesquisa = 0, tamanho, flag = 0, altura = 0, quant_cor = 0, quant_rot_avl = 0, quant_rot_avp = 0;
    tipoAVL *arvoreavl = NULL;
    tipoAVP *arvorevp = NULL;
    // i é usada para chamar a funcao de Inicialização na primeira inserção
    while(valor != -1)
    {
        scanf("%d", &valor);
        if( i == 0)
        {
            arvoreavl = Inicializa(valor, arvoreavl);
            arvorevp = InicializaAVP(valor, arvorevp);
        }
        if( valor != -1)
        arvorevp = Insere_ElementoAVP(valor, arvorevp, &quant_cor, &quant_rot_avp);
        if(arvorevp->cor == 1)
        {
            arvorevp->cor = 0;
        }
        Imprime_ArvoreAVP(arvorevp);
        if(valor != -1 && i != 0)
        {
            arvoreavl = Insere_ElementoAVL(valor, arvoreavl, &quant_rot_avl);
        }
        i++;
    }
    altura = Calcula_Altura_ABB(arvoreavl);
    printf("%d, %d, %d\n", altura - 1, Calcula_Altura_ABB(arvoreavl->esq), Calcula_Altura_ABB(arvoreavl->dir));
    altura = Calcula_Altura_Negra(arvorevp);
    printf("%d\n", altura);
    altura = Calcula_Altura_AVP(arvorevp);
    printf("%d, %d, %d\n", altura - 1, Calcula_Altura_AVP(arvorevp->esq), Calcula_Altura_AVP(arvorevp->dir));

    Imprime_Arvore(arvoreavl);
    Imprime_ArvoreAVP(arvorevp);
    printf("%d, %d, %d\n", quant_cor, quant_rot_avp, quant_rot_avl);
    if(arvoreavl != NULL)
    arvoreavl = Desaloca_Memoria(arvoreavl);
    return 0;
}

