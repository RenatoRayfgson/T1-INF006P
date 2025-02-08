//Equipe: Renato Rayfgson Bittencourt(20241160004) e Anna Luisa Santos de Sousa(20232160040) 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
  int numero;
  struct No *proximo;
} No;

typedef struct {
  No *inicio;
  int soma;
} lista;

No *criacao_no(int numero) {
  No *novo_no = (No *)malloc(sizeof(No));
  novo_no->numero = numero;
  novo_no->proximo = NULL;
  return novo_no;
}

void inserir_numero(lista *lista, int numero) {
  No *novo_no = criacao_no(numero);
  lista->soma += numero;
  if (lista->inicio == NULL || lista->inicio->numero > numero) {
    novo_no->proximo = lista->inicio;
    lista->inicio = novo_no;
    return;
  }
  No *atual_num = lista->inicio;
  while (atual_num->proximo != NULL && atual_num->proximo->numero < numero) {
    atual_num = atual_num->proximo;
  }
  novo_no->proximo = atual_num->proximo;
  atual_num->proximo = novo_no;
}

void liberar_memoria(No *inicio) {
  No *atual_num = inicio;
  while (atual_num != NULL) {
    No *temp = atual_num;
    atual_num = atual_num->proximo;
    free(temp);
  }
}

int comparacao_listas(const void *a, const void *b) {
  int soma_a = ((lista *)a)->soma;
  int soma_b = ((lista *)b)->soma;

  if (soma_a > soma_b) {
    return 1;
  } else if (soma_a < soma_b) {
    return -1;
  } else {
    return 0;
  }
}

void ordenar_listas(lista listas[], int total_listas, int (*comparar)(const void *, const void *)) {
    for (int i = 0; i < total_listas - 1; i++) {
        for (int j = 0; j < total_listas - 1 - i; j++) {
            if (comparar(&listas[j], &listas[j + 1]) > 0) {
                lista temp = listas[j];
                listas[j] = listas[j + 1];
                listas[j + 1] = temp;
            }
        }
    }
}

int main() {
  FILE *arquivo_entrada = fopen("L1Q1.in", "r");
  FILE *arquivo_saida = fopen("L1Q1.out", "w");
  if (arquivo_entrada == NULL || arquivo_saida == NULL) {
    printf("Erro ao abrir os arquivos.\n");
    return 1;
  }

  lista listas[100];
  int total_listas = 0;
  char palavra[10];
  int valor;

  while (fscanf(arquivo_entrada, "%s", palavra) != EOF) {
    if (strcmp(palavra, "start") == 0) {
      listas[total_listas].inicio = NULL;
      listas[total_listas].soma = 0;
      while (fscanf(arquivo_entrada, "%d", &valor) == 1) {
        inserir_numero(&listas[total_listas], valor);
      }
      total_listas++;
    } else {
      fgetc(arquivo_entrada); 
    }
  }
  ordenar_listas(listas, total_listas, comparacao_listas);

  for (int i = 0; i < total_listas; i++) {
    fprintf(arquivo_saida, "start");
    No *atual = listas[i].inicio;
    while (atual != NULL) {
        fprintf(arquivo_saida, " %d", atual->numero);
        atual = atual->proximo;
    }
    fprintf(arquivo_saida, "\n");
    liberar_memoria(listas[i].inicio);
  }

  fclose(arquivo_entrada);
  fclose(arquivo_saida);
  return 0;
}
