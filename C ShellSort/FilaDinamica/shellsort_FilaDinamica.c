#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort_FilaDinamica.h"

void inicializarFila(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

int filaVazia(Fila* f) {
    return f->inicio == NULL;
}

int enfileirar(Fila* f, Usuarios u) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return 0;
    novo->dados = u;
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }

    f->fim = novo;
    f->tamanho++;
    return 1;
}

int desenfileirar(Fila* f, Usuarios* u) {
    if (filaVazia(f)) return 0;
    No* temp = f->inicio;
    *u = temp->dados;
    f->inicio = temp->prox;
    if (f->inicio == NULL) f->fim = NULL;
    free(temp);
    f->tamanho--;
    return 1;
}

int lerCSV(const char* nomeArquivo, Fila* f) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    char linha[100];
    int total = 0;

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) && total < MAX) {
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

    // Aloca vetor base para backup
    Usuarios* backup = (Usuarios*)malloc(total * sizeof(Usuarios));
    if (!backup) {
        printf("Erro de alocação (backup)\n");
        return -1;
    }

    // Transfere dados da fila dinâmica para o backup
    for (int i = 0; i < total; i++) {
        desenfileirar(&fila, &backup[i]);
    }

    double tempos[10];
    Usuarios* usuarios = (Usuarios*)malloc(total * sizeof(Usuarios));
    if (!usuarios) {
        printf("Erro de alocação (usuarios)\n");
        free(backup);
        return -1;
    }

    for (int exec = 0; exec < 10; exec++) {
        memcpy(usuarios, backup, total * sizeof(Usuarios));

        clock_t inicio = clock();
        shellsort(usuarios, total);
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempos[exec] = tempo;

        printf("Execução %d: %.6f segundos - %s\n", exec + 1, tempo,
               estaOrdenado(usuarios, total) ? "Ordenado ✅" : "Não ordenado ❌");
    }

    double soma = 0.0;
    for (int i = 0; i < 10; i++) soma += tempos[i];
    double media = soma / 10.0;

    printf("\n⏱ Tempo médio de ordenação (10 execuções): %.6f segundos\n", media);

    free(usuarios);
    free(backup);
    return 0;
}
