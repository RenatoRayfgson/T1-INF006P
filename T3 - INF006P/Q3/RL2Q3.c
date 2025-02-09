#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef struct No
{
    struct No *pai;
    struct No *esquerda;
    struct No *direita; 
    int chave;
} No;

typedef struct Arvore
{
    No *raiz;
} Arvore;

No *criarNo(int chave);
Arvore *criarArvore();

void busca(No* no, FILE* arquivo, int alt, int* flag) {
    if (no == NULL) return;
    busca(no->esquerda, arquivo, alt + 1, flag);
    if (*flag != 0) fprintf(arquivo, " ");
    *flag += 1;
    fprintf(arquivo, "%d (%d)", no->chave, alt); 
    busca(no->direita, arquivo, alt + 1, flag);
}

No *buscaIterativa(No *x, int chave)
{
    while (x != NULL && x->chave != chave)
    {
        if (chave < x->chave)
        {
            x = x->esquerda;
        }
        else
        {
            x = x->direita;
        }
    }
    return x;
}

No *minimoArvore(No *x)
{
    while (x->esquerda != NULL)
    {
        x = x->esquerda;
    }
    return x;
}

No *maximoArvore(No *x)
{
    while (x->direita != NULL)
    {
        x = x->direita;
    }
    return x;
}

No *sucessorArvore(No *x)
{
    No *y;

    if (x->direita != NULL)
    {
        return minimoArvore(x->direita);
    }
    y = x->pai;
    while (y != NULL && x == y->direita)
    {
        x = y;
        y = y->pai;
    }
    return y;
}

No *predecessorArvore(No *x)
{
    No *y;
    if (x->esquerda != NULL)
    {
        return maximoArvore(x->esquerda);
    }
    y = x->pai;
    while (y != NULL && x == y->esquerda)
    {
        x = y;
        y = y->pai;
    }
    return y;
}

void inserirArvore(Arvore *a, No *z)
{
    No *y = NULL;
    No *x = a->raiz;
    while (x != NULL)
    {
        y = x;
        if (z->chave < x->chave)
        {
            x = x->esquerda;
        }
        else
        {
            x = x->direita;
        }
    }
    z->pai = y;
    if (y == NULL)
    {
        a->raiz = z;
    }
    else
    {
        if (z->chave < y->chave)
        {
            y->esquerda = z;
        }
        else
        {
            y->direita = z;
        }
    }
}

void excluirArvore(Arvore *a, No *z)
{
    No *y;
    No *x;
    if (z->esquerda == NULL || z->direita == NULL)
    {
        y = z;
    }
    else
    {
        y = sucessorArvore(z);
    }

    if (y->esquerda != NULL)
    {
        x = y->esquerda;
    }
    else
    {
        x = y->direita;
    }

    if (x != NULL)
    {
        x->pai = y->pai;
    }

    if (y->pai == NULL)
    {
        a->raiz = x;
    }
    else
    {
        if (y->pai->esquerda == y)
        {
            y->pai->esquerda = x;
        }
        else
        {
            y->pai->direita = x;
        }
    }
    if (y != z)
    {
        z->chave = y->chave;
    }
}

void inicializarNo(No *n)
{
    n->pai = NULL;
    n->esquerda = NULL;
    n->direita = NULL;
}

void inicializarArvore(Arvore *a)
{
    a->raiz = NULL;
}

No *criarNo(int chave)
{
    No *res = malloc(sizeof(No));
    inicializarNo(res);
    res->chave = chave;
    return res;
}

Arvore *criarArvore()
{
    Arvore *res = malloc(sizeof(Arvore));
    inicializarArvore(res);
    return res;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main(){
    FILE *fp_in = fopen("L2Q3.in", "r"); 
    FILE *fp_out = fopen("L2Q3.out", "w");
    char linha[1000];
    int cont = 0, flag = 0;
  
    if(fp_in == NULL)
        perror("Erro ao abrir o arquivo L2Q1.in\n");
    if(fp_out == NULL)
        perror("Erro ao abrir o arquivo L2Q1.out\n");

    while (fgets(linha, 1000, fp_in) != NULL){
        if(cont != 0)
            fprintf(fp_out, "\n");
        cont++;        
        char *token = strtok(linha, " ");
        Arvore *a = criarArvore(); 

        while (token != NULL){
            if (strcmp(token, "a") == 0) {
                token = strtok(NULL, " ");
                // inserir na árvore
                int num = atoi(token);
                No *z = criarNo(num);
                if (a->raiz == NULL) { 
                    a->raiz = z;
                } else {
                    inserirArvore(a, z);
                }
            } else if (strcmp(token, "r") == 0) {
                token = strtok(NULL, " ");
                int num = atoi(token);
                No *achou = buscaIterativa(a->raiz, num);                 
                if (achou != NULL) {
                    excluirArvore(a, achou);
                } else {                    
                    int num = atoi(token);
                    No *z = criarNo(num);
                    if (a->raiz == NULL) { 
                        a->raiz = z;
                    } else {
                        inserirArvore(a, z);
                    }
                }
            }
            token = strtok(NULL, " ");
        }
        No *no = a->raiz;
        busca(no, fp_out, 0, &flag);
        flag = 0;
    }

    fclose(fp_in);
    fclose(fp_out);
}
