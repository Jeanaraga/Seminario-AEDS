#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort_PilhaDinamica.h"

void inicializarPilha(Pilha* p) {
    p->topo = NULL;
    p->tamanho = 0;
}

int estaVazia(Pilha* p) {
    return p->topo == NULL;
}

int empilhar(Pilha* p, Usuarios u) {
    No* novo = malloc(sizeof(No));
    if (!novo) return 0;

    novo->dado = u;
    novo->prox = p->topo;
    p->topo = novo;
    p->tamanho++;
    return 1;
}

int desempilhar(Pilha* p, Usuarios* u) {
    if (estaVazia(p)) return 0;

    No* temp = p->topo;
    *u = temp->dado;
    p->topo = temp->prox;
    free(temp);
    p->tamanho--;
    return 1;
}

void liberarPilha(Pilha* p) {
    Usuarios lixo;
    while (!estaVazia(p)) {
        desempilhar(p, &lixo);
    }
}

int lerCSV(const char* nomeArquivo, Pilha* p) {
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
        sscanf(linha, "%d,%d,%f,%d", &u.id, &u.movieID, &u.nota, &u.timestamp);
        if (!empilhar(p, u)) break;
        total++;
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
            j = i;
            while (j >= gap && usuarios[j - gap].nota > temp.nota) {
                usuarios[j] = usuarios[j - gap];
                j -= gap;
            }
            usuarios[j] = temp;
        }
    }
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
    Pilha pilha;
    inicializarPilha(&pilha);

    int total = lerCSV("ratings.csv", &pilha);
    if (total == 0) return -1;

    // Cria vetor de backup a partir da pilha
    Usuarios* backup = malloc(total * sizeof(Usuarios));
    if (!backup) {
        printf("Erro de memória\n");
        liberarPilha(&pilha);
        return -1;
    }

    No* atual = pilha.topo;
    for (int i = total - 1; i >= 0; i--) {
        backup[i] = atual->dado;
        atual = atual->prox;
    }

    double tempos[10];
    Usuarios* vetor = malloc(total * sizeof(Usuarios));
    if (!vetor) {
        printf("Erro de memória\n");
        free(backup);
        liberarPilha(&pilha);
        return -1;
    }

    for (int exec = 0; exec < 10; exec++) {
        memcpy(vetor, backup, total * sizeof(Usuarios));

        clock_t inicio = clock();
        shellsort(vetor, total);
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempos[exec] = tempo;

        printf("Execução %d: %.6f segundos - %s\n", exec + 1, tempo,
               estaOrdenado(vetor, total) ? "Ordenado ✅" : "Não ordenado ❌");
    }

    double soma = 0;
    for (int i = 0; i < 10; i++) soma += tempos[i];
    double media = soma / 10.0;

    printf("\n⏱ Tempo médio de ordenação (10 execuções): %.6f segundos\n", media);

    free(vetor);
    free(backup);
    liberarPilha(&pilha);

    return 0;
}
