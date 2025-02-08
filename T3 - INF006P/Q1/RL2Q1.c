//Equipe: Renato Rayfgson Bittencourt(20241160004) e Anna Luisa Santos de Sousa(20232160040) 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef struct no{
    struct no* esquerda;
    int num;
    struct no* direita;
    int alt;
}no;

typedef no* avbin;

typedef struct saida{
    int valor;
    int alt;
    int ant;
}saida;

avbin* criaArvore();
no* busca(no* atual, int valor, no* ant, int alt);
saida inserir(avbin* raiz, FILE* arquivoSaida, int valor);
void destruirNo(no* no);
void destruirArvore(avbin* raiz);

avbin* criaArvore(){
    avbin* raiz = (avbin*)malloc(sizeof(avbin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

no* busca(no* atual, int valor, no* ant, int alt){
    if(atual == NULL){
        ant->alt = alt;
        return ant;
    }
    ant = atual;
    if(valor < atual->num){
        busca(atual->esquerda, valor, ant, alt+1);
    }else{
        busca(atual->direita, valor, ant, alt+1);
    }
}

saida inserir(avbin* raiz, FILE* arquivoSaida, int valor){
    int alt = 0;
    saida saida;
    no* novo = (no*)malloc(sizeof(no)); 
    novo->direita = NULL;
    novo->esquerda = NULL;
    novo->num = valor;
    if(*raiz == NULL){
        *raiz = novo;
        fprintf(arquivoSaida, "0");
        saida.valor = novo->num;
        saida.alt = 0;
        return saida;
    }
    no* atual = *raiz;
    if(valor < atual->num)
        atual = busca(atual->esquerda, valor, atual, alt);
    else
        atual = busca(atual->direita, valor, atual, alt);
    if(valor < atual->num){
        atual->esquerda = novo;
        fprintf(arquivoSaida, " %d", atual->alt+1);
        saida.valor = novo->num;
        saida.alt = atual->alt+1;
        return saida; 
    }
    else{
        atual->direita = novo;
        fprintf(arquivoSaida, " %d", atual->alt+1);
        saida.valor = novo->num;
        saida.alt = atual->alt+1;
        return saida;
    }
}

void destruirNo(no* no){
    if(no == NULL)
        return;
    destruirNo(no->esquerda);
    destruirNo(no->direita);
    free(no);
    no = NULL;
}

void destruirArvore(avbin* raiz){
    if(*raiz == NULL)
        return;
    destruirNo(*raiz);
    free(raiz);
}

int main()
{
    FILE* arquivoEntrada = fopen("L2Q1.in", "r");
    FILE* arquivoSaida = fopen("L2Q1.out", "w");
    if(arquivoSaida == NULL || arquivoEntrada == NULL){
        printf("ERRO AO ABRIR ARQUIVOS");
        return 0;
    }
    avbin* raiz = criaArvore();
    char linha[256], *token;
    int num, ant, cont = 0, cont2 = 0;
    saida saida, maior;
    maior.valor = -100000;
    while(fgets(linha, 256, arquivoEntrada) != NULL){
        token = strtok(linha, " ");
        if(cont != 0)
            fprintf(arquivoSaida, "\n");
        while(token != NULL){
            cont2++;
            num = atoi(token);
            saida = inserir(raiz, arquivoSaida, num);
            token = strtok(NULL, " ");
            if(maior.valor < saida.valor){
                maior.valor = saida.valor;
                maior.alt = saida.alt;
                maior.ant = ant;
            }
            ant = num;
        }
        if(cont2 == 1)     
        fprintf(arquivoSaida, " max %d alt %d pred NaN", maior.valor, maior.alt);
      else
        fprintf(arquivoSaida, " max %d alt %d pred %d", maior.valor, maior.alt, maior.ant);
        cont2 = 0;
        cont++;
        maior.valor = -100000;
        destruirArvore(raiz);
        avbin* raiz = criaArvore();
    }
    destruirArvore(raiz);
    return 0;
}
