# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# define tamanhoMaximoLinha 500
typedef struct noSimples {
  struct noSimples * proximo;
  float key;
}noSimples;

typedef struct listaCircular {
  noSimples * frente;
  noSimples * costa;
} listaCircular;

typedef struct no {
  struct no * proximo;
  struct no * anterior;
  listaCircular * key;
  float limite;
} no;

typedef struct listaLigada {
  no * frente;
  no * costa;
} listaLigada;

int criarArquivo(char path[]);
int arquivoExistente(char path[]);
void liberarListaCircular(listaCircular * L);
void liberarLista(listaLigada * L);
void iniciarListaCircular(listaCircular * L);
void iniciarListaLigada(listaLigada * L);
void inserirNaListaCircular(listaCircular * L, float X);
void inserirListaLigada(listaLigada * L, float X);
void inserirKey(listaLigada * L, float X);
void mudarArquivo(listaLigada * L, FILE * fileOut, int isLast);

int criarArquivo(char caminho[]) {
  FILE * criarArquivo;
  criarArquivo = fopen(caminho, "w");
  if(criarArquivo == NULL) {
    return 0;
  }
  fclose(criarArquivo);
  return 1;
}

int arquivoExistente(char caminho[]) {
  FILE * testarArquivo;
  testarArquivo = fopen(caminho, "r");
  if(testarArquivo == NULL) {
    return 0;
  }
  fclose(testarArquivo);
  return 1;
}

void liberarListaCircular(listaCircular * L) {
  if (L == NULL) {
    return; 
  }
  noSimples * atual = L -> frente;
  noSimples * temp;
  while (atual != NULL) {
    temp = atual;
    atual = atual -> proximo;
    free(temp);
    if (atual == L -> frente) {
      break; 
    }
  }
  L -> frente = NULL; 
  L -> costa = NULL;
}

void liberarLista(listaLigada * L) {
  no * atual = L -> costa;
  no * temp;
  while (atual != NULL) {
    temp = atual;
    liberarListaCircular(temp -> key);
    atual = atual -> anterior;
    free(temp);
  }
  L -> frente = NULL;
  L -> costa = NULL;
}

void iniciarListaCircular(listaCircular * L) {
  L -> frente = NULL;
  L -> costa = NULL;
}

void iniciarListaLigada(listaLigada * L) {
  L -> frente = NULL;
  L -> costa = NULL;
}

void inserirNaListaCircular(listaCircular * L, float X) {
  noSimples * novoNo = (noSimples *)malloc(sizeof(noSimples));
  novoNo -> key = X;
  noSimples * tmp = L -> frente;
  if(tmp == NULL) {
    L -> frente = novoNo;
    L -> costa = novoNo;
    novoNo -> proximo = novoNo;
  } else {
    if(X < tmp -> key) {
      novoNo -> proximo = tmp;
      L -> frente = novoNo;
      L -> costa -> proximo = novoNo;
    } else {
      while (tmp != L -> costa && X > tmp -> proximo -> key) {
        tmp = tmp -> proximo;
      }
      novoNo -> proximo = tmp -> proximo;
      tmp -> proximo = novoNo;
      if (tmp == L -> costa) {
        L -> costa = novoNo;
      }
    }
  }
}

void inserirKey(listaLigada * L, float X) {
  no * tmp = L -> frente;
  if(tmp == NULL) {
    return;
  }
  while(tmp != NULL) {    
    if((X - tmp -> limite) <= 0.99f &&  X > tmp -> limite - 1) {
      inserirNaListaCircular(tmp -> key, X);
      break;
    }
    else if((tmp -> limite - X) <= 0.99f && X > tmp -> limite - 1 && X < tmp -> limite + 1){
      inserirNaListaCircular(tmp -> key, X);
      break;
    }
    tmp = tmp -> proximo;
  }
}

void inserirListaLigada(listaLigada * L, float X) {
  no * novoNo = (no *)malloc(sizeof(no));
  novoNo -> limite = X;
  novoNo -> key = (listaCircular*)malloc(sizeof(listaCircular));
  iniciarListaCircular(novoNo -> key);
  no * tmp = L -> frente;
  if(tmp == NULL) {
    novoNo -> anterior = NULL;
    novoNo -> proximo = NULL;
    L -> frente = novoNo;
    L -> costa = novoNo;
  } else {
    if(X < tmp -> limite) {
      novoNo -> proximo = tmp;
      novoNo -> anterior = NULL;
      tmp -> anterior = novoNo;
      L -> frente = novoNo;
    } else {
      while(X > tmp -> limite && tmp -> proximo != NULL) {
        if(tmp -> limite == X) {
          free(novoNo -> key);
          free(novoNo);
          return;
        }
        tmp = tmp -> proximo;
      }
      novoNo -> proximo = tmp;
      novoNo -> anterior = tmp -> anterior;
      if(tmp -> proximo == NULL) {
        novoNo -> anterior = tmp;
        novoNo -> proximo = NULL;
        tmp -> proximo = novoNo;
      } else {
        tmp -> anterior -> proximo = novoNo;
        tmp -> anterior = novoNo;
      }
    }
  }
}

void mudarArquivo(listaLigada * L, FILE * arquivoSaida, int ultimo) {
  no * tmp = L -> frente;  
  fprintf(arquivoSaida, "[");
  while(tmp != NULL) {
    fprintf(arquivoSaida, "%.0f", tmp -> limite );
    noSimples * X = tmp -> key -> frente;
    fputc('(',arquivoSaida);
    if(tmp -> key -> frente != NULL) {
      while (X -> proximo != tmp -> key -> frente) {
        fprintf(arquivoSaida, "%g->", X -> key);
        X = X -> proximo;
      }
      fprintf(arquivoSaida, "%g)", X -> key);
    } else {
      fprintf(arquivoSaida, ")");
    }
    tmp = tmp -> proximo;
    if(tmp != NULL) {
      fprintf(arquivoSaida, "->");
    }
  }
  if(!ultimo) {
    fprintf(arquivoSaida, "]\n");
  } else {
    fprintf(arquivoSaida, "]");
  }
}

float limitarCasasDecimais(char* str, int casas) {
    float numero = atof(str);
    float potencia = 1;
    for (int i = 0; i < casas; i++) {
        potencia *= 10;
    }
    return (roundf(numero * potencia)) / potencia;
}

int main() {
  if(!arquivoExistente("L1Q3.in")) {
    printf("> Arquivo não encontrado!");
    return EXIT_FAILURE;
  }

  if(!arquivoExistente("L1Q3.out")) {
    criarArquivo("L1Q3.out");
  }

  FILE * arquivoDeEntrada = fopen("L1Q3.in", "r");
  FILE * arquivoDeSaida = fopen("L1Q3.out", "w");
  char * linha = (char*) malloc(tamanhoMaximoLinha * (sizeof(char)));
  char * separador = " ";
  char * pedaco;

  listaLigada * principal = malloc(sizeof(listaLigada));
  iniciarListaLigada(principal);
  fgets(linha, tamanhoMaximoLinha, arquivoDeEntrada);
  while(linha != NULL) {
    pedaco = strtok(linha, separador);
    while(pedaco != NULL) {
      if(strcmp(pedaco, "LE") == 0) {
        pedaco = strtok(NULL, separador);
        while((strcmp(pedaco, "LI") != 0) && pedaco != NULL) {
          float tmp = limitarCasasDecimais(pedaco, 2);
          inserirListaLigada(principal, tmp);
          pedaco = strtok(NULL, separador);
        }
      }
      if(strcmp(pedaco, "LI") == 0) {
        pedaco = strtok(NULL, separador);
        while((strcmp(pedaco, "LE") != 0)) {
          float tmp = limitarCasasDecimais(pedaco, 2);
          inserirKey(principal, tmp);
          pedaco = strtok(NULL, separador);
          if(pedaco == NULL) {
            break;
          }
        }
      }
      pedaco = strtok(NULL, separador);
    }
    if(fgets(linha, tamanhoMaximoLinha, arquivoDeEntrada) != NULL) {
      mudarArquivo(principal, arquivoDeSaida, 0);
      liberarLista(principal);
    } else {
      mudarArquivo(principal, arquivoDeSaida, 1);
      liberarLista(principal);
      break;
    }
  }
  fclose(arquivoDeEntrada);
  fclose(arquivoDeSaida);
  free(linha);
  free(principal);
  return EXIT_SUCCESS;
}
