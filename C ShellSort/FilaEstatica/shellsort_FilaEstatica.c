#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort_FilaEstatica.h"

void inicializarFila(Fila* f) {
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
}

int filaVazia(Fila* f) {
    return f->tamanho == 0;
}

int filaCheia(Fila* f) {
    return f->tamanho == MAX_FILA;
}

int enfileirar(Fila* f, Usuarios u) {
    if (filaCheia(f)) return 0;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->dados[f->fim] = u;
    f->tamanho++;
    return 1;
}

int desenfileirar(Fila* f, Usuarios* u) {
    if (filaVazia(f)) return 0;
    *u = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->tamanho--;
    return 1;
}

int lerCSV(const char* nomeArquivo, Fila* f) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    char linha[LINHA_MAX];
    int total = 0;

    fgets(linha, LINHA_MAX, arquivo); 

    while (fgets(linha, LINHA_MAX, arquivo) && total < MAX) {
        Usuarios u;
        if (sscanf(linha, "%d,%d,%f,%d", &u.id, &u.movieID, &u.nota, &u.timestamp) == 4) {
            if (!enfileirar(f, u)) break;
            total++;
        }
    }

    fclose(arquivo);
    return total;
}

void shellsort(Usuarios usuarios[], int n) {
    int gap, i, j;
    Usuarios temp;

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = usuarios[i];
            for (j = i; j >= gap && usuarios[j - gap].nota > temp.nota; j -= gap) {
                usuarios[j] = usuarios[j - gap];
            }
            usuarios[j] = temp;
        }
    }
}

int estaOrdenado(Usuarios usuarios[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (usuarios[i].nota > usuarios[i + 1].nota) return 0;
    }
    return 1;
}

int main() {
    Fila fila;
    inicializarFila(&fila);

    int total = lerCSV("ratings.csv", &fila);
    if (total == 0) return -1;

    Usuarios backup[MAX_FILA];
    for (int i = 0; i < total; i++) {
        desenfileirar(&fila, &backup[i]);
    }

    double soma_tempos = 0.0;

    for (int k = 0; k < 10; k++) {
        Usuarios usuarios[MAX_FILA];
        memcpy(usuarios, backup, total * sizeof(Usuarios));  // Restaura os dados

        clock_t inicio = clock();
        shellsort(usuarios, total);
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        soma_tempos += tempo;

        printf("Execução %d: %.6f segundos - %s\n", k + 1, tempo,
               estaOrdenado(usuarios, total) ? "Ordenado ✅" : "Erro ❌");
    }

    printf("\n⏱ Tempo médio (10 execuções): %.6f segundos\n", soma_tempos / 10.0);

    return 0;
}
