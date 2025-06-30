#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/resource.h>
#include "shellsort_PilhaEstatica.h"

// Dados estáticos
Usuario dados[LIMITE_LEITURA];
Usuario trabalho[LIMITE_LEITURA];

// Shellsort com sequência de Knuth
void shellsortKnuth(Usuario* usuarios, int n) {
    int gap = 1;
    while (gap < n / 3) {
        gap = gap * 3 + 1;
    }

    while (gap >= 1) {
        for (int i = gap; i < n; i++) {
            Usuario temp = usuarios[i];
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

int estaOrdenado(Usuario* usuarios, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (usuarios[i].nota > usuarios[i + 1].nota) {
            return 0;
        }
    }
    return 1;
}

int lerCSVDireto(const char* nomeArquivo, Usuario* dados, int* total) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        return 0;
    }

    char linha[LINHA_MAX];
    int count = 0;

    fgets(linha, LINHA_MAX, arquivo); // Pula cabeçalho

    while (fgets(linha, LINHA_MAX, arquivo) && count < LIMITE_LEITURA) {
        if (sscanf(linha, "%d,%d,%f,%d",
                   &dados[count].id,
                   &dados[count].movieID,
                   &dados[count].nota,
                   &dados[count].timestamp) == 4) {
            count++;
        }
    }

    fclose(arquivo);
    *total = count;
    return count;
}

long getMemoryKB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

int main() {
    int total = 0;

    printf("Carregando dados...\n");
    if (!lerCSVDireto("ratings.csv", dados, &total)) {
        printf("Erro ao carregar dados\n");
        return -1;
    }

    printf("Dados carregados: %d\n", total);
    printf("💾 Memória após carregar: %ld KB\n", getMemoryKB());

    double somaTempos = 0.0;

    for (int k = 0; k < 10; k++) {
        // Cópia dos dados para vetor de trabalho
        memcpy(trabalho, dados, total * sizeof(Usuario));

        clock_t inicio = clock();
        shellsortKnuth(trabalho, total);
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        somaTempos += tempo;

        printf("Execução %d: %.6f segundos - %s\n", k + 1, tempo,
               estaOrdenado(trabalho, total) ? "Ordenado ✅" : "Não ordenado ❌");
    }

    printf("\n⏱ Tempo médio: %.6f segundos\n", somaTempos / 10.0);
    printf("💾 Memória final: %ld KB\n", getMemoryKB());

    return 0;
}
