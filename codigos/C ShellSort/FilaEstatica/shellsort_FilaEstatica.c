#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort_FilaEstatica.h"

#include <sys/resource.h>

long getMemoryKB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;  // Em KB no Linux
}   

// FILA ESTÁTICA GLOBAL - evita stack overflow
static Fila filaGlobal;
static Usuarios backupGlobal[LIMITE_LEITURA];
static Usuarios trabalhoGlobal[LIMITE_LEITURA];

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
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        return 0;
    }

    char linha[LINHA_MAX];
    int total = 0;

    // Pula cabeçalho
    fgets(linha, LINHA_MAX, arquivo);

    while (fgets(linha, LINHA_MAX, arquivo) && total < LIMITE_LEITURA) {
        Usuarios u;
        if (sscanf(linha, "%d,%d,%f,%d", &u.id, &u.movieID, &u.nota, &u.timestamp) == 4) {
            if (!enfileirar(f, u)) {
                printf("Fila cheia! Máximo: %d registros\n", MAX_FILA);
                break;
            }
            total++;
        }
    }

    fclose(arquivo);
    return total;
}

// ShellSort com sequência de Knuth (3k+1) otimizada
void shellsort(Usuarios* usuarios, int n) {
    int gap = 1;
    // Calcula gap inicial da sequência de Knuth
    while (gap < n / 3) {
        gap = gap * 3 + 1;
    }

    // Aplica shellsort com gaps da sequência de Knuth
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
        if (usuarios[i].nota > usuarios[i + 1].nota) return 0;
    }
    return 1;
}

int main() {
    // Usa fila global estática
    inicializarFila(&filaGlobal);

    int total = lerCSV("ratings.csv", &filaGlobal);
    if (total == 0) {
        printf("Nenhum dado carregado\n");
        return -1;
    }

    printf("📊 Total de registros lidos: %d\n", total);
    printf("💾 Memória após leitura: %ld KB\n", getMemoryKB());

    // Desenfileira para backup estático global
    for (int i = 0; i < total; i++) {
        if (!desenfileirar(&filaGlobal, &backupGlobal[i])) {
            printf("Erro ao desenfileirar posição %d\n", i);
            return -1;
        }
    }

    double tempos[10];

    // Executa múltiplas vezes medindo o tempo
    for (int k = 0; k < 10; k++) {
        // Restaura os dados para array estático global
        for (int i = 0; i < total; i++) {
            trabalhoGlobal[i] = backupGlobal[i];
        }

        clock_t inicio = clock();
        shellsort(trabalhoGlobal, total);
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempos[k] = tempo;

        printf("Execução %d: %.6f segundos - %s\n", k + 1, tempo,
               estaOrdenado(trabalhoGlobal, total) ? "Ordenado ✅" : "Erro ❌");
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

    return 0;
}
