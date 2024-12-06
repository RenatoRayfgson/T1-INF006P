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

void bubbleSort(Pontos ponto[], int k){//"Ai, mas bubbleSort é ruim demais", eu sei, Dihego, mas eu sei de cor e ele é um método de organização estável, juro que não vai comprometer nesse código <3
    Pontos temp;
    for(int i=0; i<k; i++){
        for(int j=0; j<k-1; j++){
            if(ponto[j].distancia>ponto[j+1].distancia){
                temp = ponto[j];
                ponto[j] = ponto[j+1];
                ponto[j+1]=temp;
            }
        }
    }
}

void criarSaida(FILE *fp_out, Pontos ponto[], int contador, float distanciaTotal, float distanciaAtalho, int contagemDeLinhas){ //Pra deixar menos poluído fiz uma função q cria a saída direto
    char saida[1000]="";
    int c=0;

    sprintf(saida, (contagemDeLinhas == 0) ? "points" : "\npoints");
    
    while(c<contador){
        sprintf(saida, "%s (%d,%d)", saida, ponto[c].x, ponto[c].y); //Essa linha pode ter ficado um pouco confusa, mas é só um while q tá concatenando as coordenadas com a saída anterior, acredito q vá funcionar
        c++;
    }

    sprintf(saida, "%s distance %.2f", saida, distanciaTotal);
    sprintf(saida, "%s shortcut %.2f", saida, distanciaAtalho);

    fputs(saida, fp_out);
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
        Pontos ponto[200];
        int contador=0;
        float distanciaTotal=0, distanciaAtalho=0;       
        char *pedaco = strtok(linha, espaco);

        if(strcmp(pedaco, "points") == 0){ //Isso é capricho meu, tem jeito mais fácil de fazer
            pedaco = strtok(NULL,espaco);
        }
        while(pedaco != NULL){
            if(pedaco[0] == '('){
                int x,y;
                if(sscanf(pedaco, "(%d,%d)", &x, &y) == 2){ //Eu não sei se essa função vai funcionar, se nao funcionar a gente vai ter de arrumar outra forma
                    ponto[contador].x = x; //Ok, sscanf nao pode ser atribuído direto no struct, ele meio q faz o atoi, criei x e y por isso
                    ponto[contador].y = y;
                    ponto[contador].distancia = sqrt((float)pow(x,2) + pow(y,2));
                    contador++;
                }
            }
            pedaco = strtok(NULL, espaco);
        }
        distanciaAtalho = sqrt((float)(pow(ponto[contador-1].x - ponto[0].x, 2)) + (pow(ponto[contador-1].y - ponto[0].y, 2)));
        
        for(int i=0; i<contador-1; i++){
            distanciaTotal += sqrt((float)(pow(ponto[i+1].x - ponto[i].x, 2) + pow(ponto[i+1].y - ponto[i].y, 2))); 
        }
        
        bubbleSort(ponto, contador);     
        criarSaida(fp_out, ponto, contador, distanciaTotal, distanciaAtalho, contagemDeLinhas);
        contagemDeLinhas++;
    }
    fclose(fp_in);
    fclose(fp_out);
    printf("Tarefa concluida com sucesso!");    
    return 0;
}