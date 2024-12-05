//Equipe: Renato Rayfgson Bittencourt(20241160004) e Anna Luisa(INSERIR NUMERO DE MATRÍCULA)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Pontos{
    int x;
    int y;
    float distancia;
}Pontos;

void bubbleSort(Pontos p[], int k){
    Pontos temp;
    for(int i=0; i<k; i++){
        for(int j=0; j<k-1; j++){
            if(p[j].distancia>p[j+1].distancia){
                temp = p[j];
                p[j] = p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

int main(){
    
    FILE *fp_in = fopen("L0Q1.in","r");
    FILE *fp_out = fopen("L0Q1.out","w");

    char linha[1000];
    int contagemDeLinhas=0;
    char espaco[]=" ";
    if(fp_in == NULL || fp_out == NULL){
        printf("Nao foi possivel abrir os arquivos!");
        return EXIT_FAILURE;
    }

    while(fgets(linha, sizeof(linha), fp_in) != NULL){
        Pontos p[200];
        int contador;
        float distanciaTotal=0, distanciaAtalho=0;
        char saida[1000];
        int c=0;
        char *pedaco = strtok(linha, espaco);

        if(strcmp(pedaco, "points") == 0){ //Isso é capricho meu, tem jeito mais fácil de fazer
            pedaco = strtok(NULL,espaco);
        }
        while(pedaco != NULL){
            if(pedaco[0] == '('){
                int x,y;
                if(sscanf(pedaco, "(%d,%d)", &x, &y) == 2){ //Eu não sei se essa função vai funcionar, se nao funcionar a gente vai ter de arrumar outra forma
                    p[contador].x = x; //Ok, sscanf nao pode ser atribuído direto ele meio q faz o atoi, criei x e y por isso
                    p[contador].y = y;
                    p[contador].distancia = sqrt((float)pow(x,2) + pow(y,2));
                    contador++;
                }
            }
            pedaco = strtok(NULL, espaco);
        }
        for(int i=0; i<contador-1; i++){
            distanciaTotal =+ sqrt((float)(pow(p[i+1].x - p[i].x, 2) + pow(p[i+1].y - p[i].y, 2))); 
        }
        distanciaAtalho = sqrt((float)(pow(p[contador-1].x - p[0].x, 2)) + (pow(p[contador-1].y - p[0].y, 2)));
        
        bubbleSort(p, contador);
        
        
        sprintf(saida, (contagemDeLinhas == 0) ? "points" : "\npoints");
        while(c<contador){
            sprintf(saida, "%s (%d,%d)", saida, p[c].x, p[c].y); //Essa linha pode ter ficado um pouco confusa, mas é só um while q tá concatenando as coordenadas com a saída anterior, acredito q vá funcionar
            c++;
        }
        //Isso não tava batendo antes por que tem ser >>EXATAMENTE<< igual à saida do Dihego, contei até os espaços
        sprintf(saida, "%s distance %.2f", saida, distanciaTotal);
        sprintf(saida, "%s shortcut %.2f", saida, distanciaAtalho);
        fputs(saida, fp_out);
        contagemDeLinhas++;
    }
    fclose(fp_in);
    fclose(fp_out);    
    return 0;
}