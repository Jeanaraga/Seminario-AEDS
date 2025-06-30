#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort_ListaDinamica.h"
#include <sys/resource.h>

long getMemoryKB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;  // Em KB no Linux
}   

// ShellSort com sequência de Knuth (3k+1) otimizada
void shellsort(Usuarios usuarios[], int n) {
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

int lerCSV(const char* nomeArquivo, Usuarios** lista) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo\n");
        return 0;
    }
    
    char linha[LINHA_MAX];
    int capacidade = 1000;
    int total = 0;
    
    *lista = malloc(capacidade * sizeof(Usuarios));
    if (*lista == NULL) {
        printf("Erro de alocação\n");
        fclose(arquivo);
        return 0;
    }
    
    // Pula cabeçalho
    fgets(linha, LINHA_MAX, arquivo);
    
    while (fgets(linha, LINHA_MAX, arquivo) && total < LIMITE_LEITURA) {
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
    const char* Arquivo = "ratings.csv";
    Usuarios* dados = NULL;

    int total = lerCSV(Arquivo, &dados);
    if (total == 0) {
        printf("Erro na leitura do arquivo\n");
        return -1;
    }

    printf("📊 Total de registros lidos: %d\n", total);
    printf("💾 Memória após leitura: %ld KB\n", getMemoryKB());

    Usuarios* copia = malloc(total * sizeof(Usuarios));
    if (copia == NULL) {
        printf("Erro na alocação de memória para cópia\n");
        free(dados);
        return -1;
    }

    double tempos[10];

    for (int repeticao = 0; repeticao < 10; repeticao++) {
        memcpy(copia, dados, total * sizeof(Usuarios));

        clock_t inicio = clock();
        shellsort(copia, total);
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempos[repeticao] = tempo;

        printf("Execução %d: %.6f segundos - %s\n", repeticao + 1, tempo,
               estaOrdenado(copia, total) ? "Ordenado ✅" : "Não ordenado ❌");
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

    free(dados);
    free(copia);
    return 0;
}
