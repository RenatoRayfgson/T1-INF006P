//Equipe: Renato Rayfgson Bittencourt(20241160004) e Anna Luisa Santos de Sousa(20232160040)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef struct no{
    struct no* esquerda;
    struct no* direita;
    int valor;
    int somaDireita;
    int somaEsquerda;
}no;

typedef no* arvoreBinaria;

arvoreBinaria* criaArvore();

arvoreBinaria* criaArvore(){
    arvoreBinaria* raiz = (arvoreBinaria*)malloc(sizeof(arvoreBinaria));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void destruirNo(no* no){
    if(no == NULL)
        return;
    destruirNo(no->esquerda);
    destruirNo(no->direita);
    free(no);
    no = NULL;
}

void destruirArvore(arvoreBinaria* raiz){
    if(*raiz == NULL)
        return;
    destruirNo(*raiz);
    free(raiz);
}

no* busca(no* atual, no* mae, int valor, int atualizarSomas){
    if(atual == NULL)
        return mae;
    mae = atual;
    if(valor < atual->valor){
        if(atualizarSomas)
            atual->somaEsquerda += valor;
        return busca(atual->esquerda, mae, valor, atualizarSomas);
    } else if(valor > atual->valor){
        if(atualizarSomas)
            atual->somaDireita += valor;
        return busca(atual->direita, mae, valor, atualizarSomas);
    } else
        return NULL;
}

void inserir(arvoreBinaria* raiz, int valor){
    no* novoNo = (no*)malloc(sizeof(no));
    novoNo->direita = NULL;
    novoNo->esquerda = NULL;
    novoNo->valor = valor;
    novoNo->somaDireita = 0;
    novoNo->somaEsquerda = 0;

    if(*raiz == NULL){
        *raiz = novoNo;
        return;
    }

    no* atual = *raiz;
    no* mae = atual;
    mae = busca(atual, mae, valor, 0);
    if(mae == NULL)
        return;

    if(valor < atual->valor || valor > atual->valor)
        atual = busca(atual, mae, valor, 1);
    else
        atual = NULL;

    if(atual != NULL){
        if(valor < atual->valor){
            atual->esquerda = novoNo;
        } else if(valor > atual->valor){
            atual->direita = novoNo;
        }    
    } else
        free(novoNo);   
}

int* emOrdem(arvoreBinaria* raiz, FILE* arquivo, int* contador){
    if(*raiz == NULL){
        *contador += 1;
        return contador;
    }

    emOrdem(&((*raiz)->esquerda), arquivo, contador);

    if((*raiz)->esquerda == NULL && (*raiz)->direita == NULL){
        if(*contador == 1)
            fprintf(arquivo, "%d (0)", (*raiz)->valor); 
        else
            fprintf(arquivo, " %d (0)", (*raiz)->valor);
    } else if((*raiz)->esquerda == NULL){
        if(*contador == 1)
            fprintf(arquivo, "%d (%d)", (*raiz)->valor, (*raiz)->somaDireita);
        else
            fprintf(arquivo, " %d (%d)", (*raiz)->valor, (*raiz)->somaDireita);
    } else if((*raiz)->direita == NULL){
        if(*contador == 1)
            fprintf(arquivo, "%d (%d)", (*raiz)->valor, (0 - (*raiz)->somaEsquerda));    
        else
            fprintf(arquivo, " %d (%d)", (*raiz)->valor, (0 - (*raiz)->somaEsquerda));
    } else {
        if(*contador == 1)
            fprintf(arquivo, "%d (%d)", (*raiz)->valor, ((*raiz)->somaDireita - (*raiz)->somaEsquerda));
        else
            fprintf(arquivo, " %d (%d)", (*raiz)->valor, ((*raiz)->somaDireita - (*raiz)->somaEsquerda));            
    }

    emOrdem(&((*raiz)->direita), arquivo, contador);
}

int main(){
    FILE* arquivoEntrada = fopen("L2Q2.in", "r");
    FILE* arquivoSaida = fopen("L2Q2.out", "w");

    if(arquivoSaida == NULL || arquivoEntrada == NULL){
        printf("ERRO AO ABRIR ARQUIVOS");
        return 0;
    }

    arvoreBinaria* raiz = criaArvore();  
    char linha[256], *token;
    int numero, contadorLinhas = 0;
    int contador = 0;

    while(fgets(linha, 256, arquivoEntrada) != NULL){
        token = strtok(linha, " ");
        if(contadorLinhas != 0)
            fprintf(arquivoSaida, "\n");

        while(token != NULL){
            numero = atoi(token);
            inserir(raiz, numero);
            token = strtok(NULL, " ");
        }

        emOrdem(raiz, arquivoSaida, &contador);
        destruirArvore(raiz);
        raiz = criaArvore(); 

        contadorLinhas++;
        contador = 0;
    }

    destruirArvore(raiz);
    return 1;
}
