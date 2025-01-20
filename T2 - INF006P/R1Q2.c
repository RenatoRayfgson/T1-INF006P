//Equipe: Renato Rayfgson Bittencourt(20241160004) e Anna Luisa Santos de Sousa(20232160040) 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 100
#define MAX_NAME 50
#define MAX_LINE 200

typedef struct {
    char names[MAX_STACK][MAX_NAME];
    int top;
} Pilha;

void push(Pilha *p, char name[MAX_NAME], FILE *fout) {
    int pops = 0;

    while (p->top > 0 && strcmp(p->names[p->top - 1], name) > 0) {
        p->top--;
        pops++;
    }

    if (pops > 0) {
        fprintf(fout, " %dx-pop", pops);
    }

    strcpy(p->names[p->top++], name);
    fprintf(fout, " push-%s", name);

    for (int i = p->top - pops; i < p->top; i++) {
        fprintf(fout, " push-%s", p->names[i]);
    }
}

int main() {
    FILE *f_in = fopen("L1Q2.in", "r");
    FILE *f_out = fopen("L1Q2.out", "w");
    if (!f_in || !f_out) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    Pilha pilha;
    pilha.top = 0;
    char name[MAX_NAME];
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), f_in)) {
        char *token = strtok(line, " \n");

        while (token != NULL) {
            strcpy(name, token);
            push(&pilha, name, f_out);
            token = strtok(NULL, " \n");
        }
        fprintf(f_out, "\n");  
    }

    fclose(f_in);
    fclose(f_out);
    return 0;
}
