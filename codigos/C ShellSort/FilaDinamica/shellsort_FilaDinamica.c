#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort_FilaDinamica.h"

#include <sys/resource.h>

long getMemoryKB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;  // Em KB no Linux
}  

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
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        return 0;
    }
    char linha[100];
    int total = 0;
    // Pula cabeçalho
    fgets(linha, sizeof(linha), arquivo);
    
    while (fgets(linha, sizeof(linha), arquivo) && total < LIMITE_LEITURA) {
        Usuarios u;
        if (sscanf(linha, "%d,%d,%f,%d", &u.id, &u.movieID, &u.nota, &u.timestamp) == 4) {
            if (!enfileirar(f, u)) break;
            total++;
        }
    }
    fclose(arquivo);
    return total;
}

void shellsortKnuth(Usuarios* usuarios, int n) {
    int gap = 1;
    // Gera gap inicial com sequência de Knuth (3k+1)
    while (gap < n / 3) {
        gap = gap * 3 + 1;
    }
    
    // Shell sort com gaps da sequência de Knuth
    while (gap >= 1) {
        for (int i = gap; i < n; i++) {
            Usuarios temp = usuarios[i];
            int j = i;
            while (j >= gap && usuarios[j - gap].nota > temp.nota) {
                usuarios[j] = usuarios[j - gap];
                j -= gap;
            }
            usuarios[j] = temp;
        }
        gap /= 3;
    }
}

int estaOrdenado(Usuarios* usuarios, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (usuarios[i].nota > usuarios[i + 1].nota) {
            return 0;
        }
    }
    return 1;
}

int main() {
    Fila fila;
    inicializarFila(&fila);

    int total = lerCSV("ratings.csv", &fila);
    if (total == 0) {
        printf("Nenhum dado carregado\n");
        return -1;
    }

    printf("📊 Total de registros lidos: %d\n", total);
    printf("💾 Memória após leitura: %ld KB\n", getMemoryKB());

    // Desenfileira uma única vez para criar backup
    Usuarios* backup = (Usuarios*)malloc(total * sizeof(Usuarios));
    if (!backup) {
        printf("Erro de alocação\n");
        return -1;
    }

    for (int i = 0; i < total; i++) {
        desenfileirar(&fila, &backup[i]);
    }

    double tempos[10];

    for (int k = 0; k < 10; k++) {
        Usuarios* usuarios = (Usuarios*)malloc(total * sizeof(Usuarios));
        if (!usuarios) {
            printf("Erro de alocação na execução %d\n", k + 1);
            break;
        }

        memcpy(usuarios, backup, total * sizeof(Usuarios));

        clock_t inicio = clock();
        shellsortKnuth(usuarios, total);
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempos[k] = tempo;

        printf("Execução %d: %.6f segundos - %s\n", k + 1, tempo,
               estaOrdenado(usuarios, total) ? "Ordenado ✅" : "Não ordenado ❌");

        free(usuarios);
    }

    // Estatísticas
    double soma = 0.0, menor = tempos[0], maior = tempos[0];
    for (int i = 0; i < 10; i++) {
        soma += tempos[i];
        if (tempos[i] < menor) menor = tempos[i];
        if (tempos[i] > maior) maior = tempos[i];
    }
    double media = soma / 10.0;

    printf("\n📈 Estatísticas:\n");
    printf("⏱ Tempo médio: %.6f segundos\n", media);
    printf("⏱ Menor tempo: %.6f s | Maior tempo: %.6f s\n", menor, maior);
    printf("💾 Memória final: %ld KB\n", getMemoryKB());

    free(backup);
    return 0;
}
