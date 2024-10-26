// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>
 
// ########################## TAD ArvoreAVL #################################
 
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
typedef struct noArvoreBB tipoABB;
 
// ###################### Funcoes e Procedimentos do programa ##############
//A funcão calcula qual subarvore a esquerda e a direita é maior
int maior(int a, int b)
{
    // se a (subarvore da esquerda) for maior que b(subarvore da direita) retorna a, se nao retorna b
    if(a > b)
        return a 
    else
        return b;
}
// aA função abaixo calcula a altura do no da arvore para auxiliar no calculo do fator de balanceamento
int Calcula_Altura(tipoABB *arvoreAux)
{
    if(arvoreAux == NULL)
        return 0;
    return arvoreAux->tItem.altura;
}
/* A função abaixo roda a arvore para esquerda fazendo uma rotação à direita o pB recebe a direita do A
e então a subarvore a esquerda de B vai se apontada pelo ponteiro a direita de A, e então a esquerda de B será o A*/
tipoABB *Rotacao_RR(tipoABB *arvoreAux)
{
    tipoABB *pA = arvoreAux, *pB;
    pB = pA->dir;
    pA->dir = pB->esq;
    pB->esq = pA;
    pA->tItem.altura = 1 + maior(Calcula_Altura(pA->esq), Calcula_Altura(pA->dir));
    pB->tItem.altura = 1 + maior(Calcula_Altura(pB->esq), Calcula_Altura(pB->dir));
    pA = pB;
    
    return pA;
}
/* A função abaixo roda a arvore para direita fazendo uma rotação à esquerda o pB recebe a esquerda do A
e então a subarvore a direita de B vai se apontada pelo ponteiro a esquerda de A, e então a direita de B será o A*/
tipoABB *Rotacao_LL(tipoABB *arvoreAux)
{
    tipoABB *pA = arvoreAux, *pB;
    pB = pA->esq;
    pA->esq = pB->dir;
    pB->dir = pA;
    pA->tItem.altura = 1 + maior(Calcula_Altura(pA->esq), Calcula_Altura(pA->dir));
    pB->tItem.altura = 1 + maior(Calcula_Altura(pB->esq), Calcula_Altura(pB->dir));
    pA = pB;
   
    return pA;
}
/* A função abaixo realiza uma rotação dupla à direita*/
tipoABB *Rotacao_LR(tipoABB *arvoreAux)
{
    tipoABB *pA = arvoreAux, *pB, *pC;
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
    return pA;
}
/* A função abaixo realiza uma rotação dupla à esquerda*/
tipoABB *Rotacao_RL(tipoABB *arvoreAux)
{
    tipoABB *pA = arvoreAux, *pB, *pC;
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
    return pA;
}
// A função abaixo calcula o fator de balanceamento de determinado no, fazendo a diferença da altura da esquerda menos da direita
int alturabalanceamento(tipoABB *arvoreAux)
{
    if(arvoreAux == NULL)
        return 0;
    return (Calcula_Altura(arvoreAux->esq) - Calcula_Altura(arvoreAux->dir));
}
// A função abaixo verifica a necessidade de Balancear cada nó e chama a rotação devidamente necessaria
tipoABB *Balancear(tipoABB *arvoreAux)
{
    // fb recebe o fator de balanceamento do nó
    int fb = alturaanceamento(arvoreAux);
    if (fb > 1 && alturabalanceamento(arvoreAux->esq) >= 0)
        arvoreAux = Rotacao_LL(arvoreAux);
    else if(fb < -1 && alturabalanceamento(arvoreAux->dir) <= 0)
        arvoreAux = Rotacao_RR(arvoreAux);
    else if (fb > 1 && alturabalanceamento(arvoreAux->esq) < 0)
        arvoreAux = Rotacao_LR(arvoreAux);
    else if (fb < -1 && alturabalanceamento(arvoreAux->dir) > 0)
        arvoreAux = Rotacao_RL(arvoreAux);
    return arvoreAux;
}
// A função abaixo Inicializa a arvore sendo a primeira inserção
tipoABB *Inicializa(int c, tipoABB *arvoreAux)
{
    arvoreAux = malloc(sizeof(tipoABB));
    arvoreAux->tItem.chave = c;
    arvoreAux->tItem.altura = 1;
    arvoreAux->esq = NULL;
    arvoreAux->dir = NULL;
    return arvoreAux;
}
// A função abixo insere um novo no na arvore de acordo com a posiçao correta apontada pela funcao Insere_ElementoABB
tipoABB *InsereNo(int c, tipoABB *arvoreAux)
{
    tipoABB *novoNo = malloc(sizeof(tipoABB));
    novoNo->tItem.altura = 1;
    novoNo->tItem.chave = c;
    novoNo->dir = NULL;
    novoNo->esq = NULL;
    return novoNo;
}
// A função abaixo insere um novo elemento na arvore igual a uma arvore binaria de busca, porem ao voltar de cada recursao é verificado a necessidade de balanceamento
tipoABB *Insere_ElementoABB(int chave, tipoABB *arvoreAux)
{
    if (arvoreAux == NULL)
        return InsereNo(chave, arvoreAux);
    else
    {
        if (chave < arvoreAux->tItem.chave )
            arvoreAux->esq = Insere_ElementoABB(chave, arvoreAux->esq);
        else if (chave > arvoreAux->tItem.chave)
            arvoreAux->dir = Insere_ElementoABB(chave, arvoreAux->dir);
    }
    // Na volta da recusao calcula o fator de balanceamento e altura de cada no chamado na recursao
    arvoreAux->tItem.altura = 1 + maior(Calcula_Altura(arvoreAux->esq), Calcula_Altura(arvoreAux->dir));
    // Verifica a necessidadede balancear a arvore passando o no da volta de cada recursao
    arvoreAux = Balancear(arvoreAux);
    
    return arvoreAux;
}
// Verifica o sucessor para remocao, achando o elemento mais a esquerda da subarvore da direita
tipoABB *maiorValor(tipoABB *arvoreAux)
{
    if(arvoreAux == NULL)
        return NULL;
    else if (arvoreAux->esq == NULL)
        return arvoreAux;
    else
        return maiorValor(arvoreAux->esq);
}
// Remove o nó desejado da arvore passando o sucessor para a raiz 
tipoABB *removeABB(tipoABB *arvoreAux, int chave)
{
    tipoABB *temp;
    if(arvoreAux == NULL)// arvore vazia
        return NULL;
    else if(arvoreAux->tItem.chave > chave)//a chave esta para esquerda ja que e menor que o no atual
        arvoreAux->esq = removeABB(arvoreAux->esq, chave);
    else if(arvoreAux->tItem.chave < chave)// a chave esta para direita já que é maior que o nó atual
        arvoreAux->dir = removeABB(arvoreAux->dir, chave);
    else//encontrou a chave
    {
        if ((arvoreAux->esq != NULL) && (arvoreAux->dir != NULL))//remoção de nó com filhos
        {
            temp = maiorValor(arvoreAux->dir);// acha o sucessor
            arvoreAux->tItem.chave = temp->tItem.chave;
            temp->tItem.chave = chave;
            arvoreAux->dir = removeABB(arvoreAux->dir, chave);
        }
        else if (arvoreAux->esq != NULL)// remocao com filho apenas para esquerda
        {
            temp = arvoreAux;
            arvoreAux = arvoreAux->esq;
            free(temp);
        } 
        else if (arvoreAux->dir != NULL)// remocao com filho apenas para direita
        {
            temp = arvoreAux;
            arvoreAux = arvoreAux->dir;
            free(temp);
        }
        else// remocao de folha
        {
            free(arvoreAux);
            return NULL;
        }
    }
    // na volta das recursoes recalcula a altura do no
    arvoreAux->tItem.altura = 1 + maior(Calcula_Altura(arvoreAux->esq), Calcula_Altura(arvoreAux->dir));
    // veirifica a necessidade de Balancear
    arvoreAux = Balancear(arvoreAux);
    return arvoreAux;
}
int Calcula_Altura_ABB(tipoABB *arvoreAux);
// a função abaixo pesquisa um determinado valor na arvore, flag é usada para mostra a altura do ultimo nó pesquisado, da entra da linha 3
int Pesquisa_Arvore(tipoABB *arvoreAux, int valor, int flag)
{
    int altura;
    if (arvoreAux)
    {
        if(arvoreAux->tItem.chave == valor)
        {
            if(flag != 0)// se flag != 0 calcula as alturas do no e das ramificações desse nó
            {
            altura = Calcula_Altura_ABB(arvoreAux);
            printf("%d, %d, %d", altura - 1, Calcula_Altura_ABB(arvoreAux->esq), Calcula_Altura_ABB(arvoreAux->dir));
            }
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
int Calcula_Altura_ABB(tipoABB *arvoreAux)
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
// A função abaixo desaloca a memoria de toda arvore, indo até a folha para liberar até a raiz
tipoABB *Desaloca_Memoria(tipoABB *arvoreAux)
{
    if(arvoreAux != NULL)
    {
        Desaloca_Memoria(arvoreAux->esq);
        Desaloca_Memoria(arvoreAux->dir);
        free(arvoreAux);
    }
    return NULL;
}
// ############################ Principal ###################################
 
int main()
{
    int i = 0, valor = 0, n_pesquisa = 0, tamanho, flag = 0, altura = 0;
    tipoABB *arvoreavl = NULL;
    // i é usada para chamar a funcao de Inicialização na primeira inserção
    while(valor != -1)
    {
        scanf("%d", &valor);
        if( i == 0)
        arvoreavl = Inicializa(valor, arvoreavl);
        if(valor != -1 && i != 0)
        arvoreavl = Insere_ElementoABB(valor, arvoreavl);
        i++;
    }
    altura = Calcula_Altura_ABB(arvoreavl);
    printf("%d, %d, %d\n", altura - 1, Calcula_Altura_ABB(arvoreavl->esq), Calcula_Altura_ABB(arvoreavl->dir));
    valor = 0;
    while(valor != -1)
    {
        //flag é usada para verificar se o elemento já esta na arvore e remove-lo, ou e necessário inseri-lo
        //n_pesquisa é usada para imprimir a altura do ultimo elemento a ser pesquisado no caso da linha 3 de entrada 
        scanf("%d", &valor);
        if( valor != -1)
        {
            flag = Pesquisa_Arvore(arvoreavl, valor, n_pesquisa);
            if( flag == -1 )
            arvoreavl = Insere_ElementoABB(valor, arvoreavl);
            else
            arvoreavl = removeABB(arvoreavl, valor);
        }
    }
    scanf("%d", &valor);
    valor = Pesquisa_Arvore(arvoreavl, valor, n_pesquisa);
    // se o valor for encontrado n_pesquisa recebe 1 e imprime a altura desse nó na função pesquisa
    if (valor == -1)
    printf("Valor nao encontrado\n");
    else
    {
        n_pesquisa = 1;
        valor = Pesquisa_Arvore(arvoreavl, valor, n_pesquisa);
    }
    if(arvoreavl != NULL)
    arvoreavl = Desaloca_Memoria(arvoreavl);
    return 0;
}