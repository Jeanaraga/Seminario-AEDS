#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort_ListaDinamica.h"


void shellsort(Usuarios usuarios[], int n) {
    int gap, i, j;
    Usuarios temp;

    for (gap = n/2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = usuarios[i];
            j = i;
            while (j >= gap && usuarios[j - gap].nota> temp.nota) {
                usuarios[j] = usuarios[j - gap];
                j -= gap;
            }
            usuarios[j] = temp;
        }
    }
}

int lerCSV(const char* nomeArquivo, Usuarios** lista) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    char linha[LINHA_MAX];
    int capacidade = 10;
    int total = 0;

    *lista = malloc(capacidade * sizeof(Usuarios));
    if (*lista == NULL) {
        printf("Erro de alocação\n");
        fclose(arquivo);
        return 0;
    }

    fgets(linha, LINHA_MAX, arquivo); 

    while (fgets(linha, LINHA_MAX, arquivo) && total < MAX) {
        if (total >= capacidade) {
            capacidade *= 2;
            Usuarios* temp = realloc(*lista, capacidade * sizeof(Usuarios));
            if (temp == NULL) {
                printf("Erro de realocação\n");
                free(*lista);
                fclose(arquivo);
                return 0;
            }
            *lista = temp;
        }
        sscanf(linha, "%d,%d,%f,%d", &(*lista)[total].id, &(*lista)[total].movieID, &(*lista)[total].nota, &(*lista)[total].timestamp);
        total++;
    }

    fclose(arquivo);
    return total;
}

int estaOrdenado(Usuarios usuarios[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (usuarios[i].nota > usuarios[i + 1].nota) {
            return 0;
        }
    }
    return 1;
}

int main() {
    double soma_tempos = 0.0;
    int total = 0;
    Usuarios* original = NULL;

    total = lerCSV("ratings.csv", &original);
    if (total == 0) {
        printf("Erro na leitura do arquivo\n");
        return -1;
    }

    for (int i = 0; i < 10; i++) {
        // Criar uma cópia para não ordenar os dados já ordenados
        Usuarios* copia = malloc(total * sizeof(Usuarios));
        if (!copia) {
            printf("Erro de alocação na cópia\n");
            free(original);
            return -1;
        }
        memcpy(copia, original, total * sizeof(Usuarios));

        clock_t inicio = clock();
        shellsort(copia, total);
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        soma_tempos += tempo;

        printf("Execução %d: %.6f segundos - %s\n", i + 1, tempo,
               estaOrdenado(copia, total) ? "Ordenado ✅" : "Erro ❌");

        free(copia);
    }

    printf("\n⏱ Tempo médio (10 execuções): %.6f segundos\n", soma_tempos / 10.0);

    free(original);
    return 0;
}
