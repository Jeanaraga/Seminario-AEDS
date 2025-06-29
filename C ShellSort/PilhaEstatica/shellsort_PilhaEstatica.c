#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort_PilhaEstatica.h"

void inicializarPilha(Pilha* p) {
    p->topo = -1;
}

int estaVazia(Pilha* p) {
    return p->topo == -1;
}

int estaCheia(Pilha* p) {
    return p->topo == MAX_PILHA - 1;
}

int empilhar(Pilha* p, Usuarios u) {
    if (estaCheia(p)) return 0;
    p->topo++;
    p->dados[p->topo] = u;
    return 1;
}

int desempilhar(Pilha* p, Usuarios* u) {
    if (estaVazia(p)) return 0;
    *u = p->dados[p->topo];
    p->topo--;
    return 1;
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
        if (estaCheia(p)) break;

        Usuarios u;
        sscanf(linha, "%d,%d,%f,%d", &u.id, &u.movieID, &u.nota, &u.timestamp);
        empilhar(p, u);
        total++;
    }

    fclose(arquivo);
    return total;
}

void shellsort(Usuarios usuarios[], int n) {
    int gap, i, j;
    Usuarios temp;

    for (gap = n/2; gap > 0; gap /= 2) {
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
    if (total == 0) {
        return -1;
    }

    Usuarios original[MAX_PILHA];
    for (int i = 0; i <= pilha.topo; i++) {
        original[i] = pilha.dados[i];
    }

    double somaTempos = 0.0;

    for (int exec = 0; exec < 10; exec++) {
        Usuarios vetor[MAX_PILHA];
        // Copia os dados originais para o vetor de ordenação
        for (int i = 0; i < total; i++) {
            vetor[i] = original[i];
        }

        clock_t inicio = clock();
        shellsort(vetor, total);
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        somaTempos += tempo;

        // Se quiser, pode imprimir o tempo de cada execução
        printf("Execução %d: %.6f segundos\n", exec + 1, tempo);

        if (!estaOrdenado(vetor, total)) {
            printf("Deu errado na execução %d\n", exec + 1);
        }
    }

    printf("Tempo médio de ordenação em 10 execuções: %.6f segundos\n", somaTempos / 10);

    return 0;
}
