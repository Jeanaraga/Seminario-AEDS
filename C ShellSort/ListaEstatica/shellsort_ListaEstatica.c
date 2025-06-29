#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort_ListaEstatica.h"




void shellsort(Usuarios usuarios[], int n) {
    int gap, i, j;
    Usuarios temp;

    for(gap = n/2; gap > 0; gap /= 2){
        for(i = gap; i < n; i++){
            temp = usuarios[i];
            j = i;
            while(j >= gap && usuarios[j - gap].nota > temp.nota){
                usuarios[j] = usuarios[j - gap];
                j = j - gap;
            }
            usuarios[j] = temp;
        }
    }

 
}

int lerCSV(const char* nomeArquivo, Usuarios lista[]){
    FILE* arquivo = fopen(nomeArquivo, "r");
    if(!arquivo){
        printf("Erro");
        return 0;
    }

    char linha[100];
    int i = 0;

    fgets(linha, LINHA_MAX, arquivo);

    while(fgets(linha, LINHA_MAX, arquivo) && i < MAX){
        sscanf(linha, "%d,%d,%f,%d", &lista[i].id, &lista[i].movieID, &lista[i].nota, &lista[i].timestamp);
        i++;

    }

    fclose(arquivo);

    return i;

}

int estaOrdenado(Usuarios usuarios[], int n){
    for(int i = 0; i < n - 1; i++){
        if(usuarios[i].nota > usuarios[i+1].nota){
            return 0;
        }
    }

    return 1;
}


int main() {
    const char* Arquivo = "ratings.csv";
    Usuarios* usuarios = malloc(MAX * sizeof(Usuarios));
     if (usuarios == NULL) {
    printf("Erro na alocação de memória\n");
    return -1;
    }

    int total;

    double somaTempos = 0.0;

    for (int repeticao = 0; repeticao < 10; repeticao++) {
        total = lerCSV(Arquivo, usuarios);
        if (total == 0) {
            return -1;
        }

        clock_t inicio = clock();
        shellsort(usuarios, total);
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        somaTempos += tempo;

        printf("Execução %d: %.6f segundos\n", repeticao + 1, tempo);

        if (!estaOrdenado(usuarios, total)) {
            printf("Erro: não está ordenado na execução %d!\n", repeticao + 1);
        }
    }

    double media = somaTempos / 10.0;
    printf("\nTempo médio de ordenação em 10 execuções: %.6f segundos\n", media);

    return 0;
}
