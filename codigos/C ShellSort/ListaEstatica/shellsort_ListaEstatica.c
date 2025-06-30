#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort_ListaEstatica.h"
#include <sys/resource.h>

long getMemoryKB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;  // Em KB no Linux
}   

// LISTA ESTÁTICA - Arrays globais com tamanho fixo
static Usuarios dados[LIMITE_LEITURA];
static Usuarios copia[LIMITE_LEITURA];

// ShellSort com sequência de Knuth (3k+1) em vez de n/2
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

int lerCSV(const char* nomeArquivo, Usuarios lista[]) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo\n");
        return 0;
    }
    
    char linha[100];
    int i = 0;
    
    // Pula cabeçalho
    fgets(linha, LINHA_MAX, arquivo);
    
    while (fgets(linha, LINHA_MAX, arquivo) && i < LIMITE_LEITURA) {
        sscanf(linha, "%d,%d,%f,%d", &lista[i].id, &lista[i].movieID, &lista[i].nota, &lista[i].timestamp);
        i++;
    }
    
    fclose(arquivo);
    return i;
}

int estaOrdenado(Usuarios usuarios[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (usuarios[i].nota > usuarios[i+1].nota) {
            return 0;
        }
    }
    return 1;
}

int main() {
    const char* Arquivo = "ratings.csv";
    
    // Lê o CSV apenas uma vez - usa array estático global
    int total = lerCSV(Arquivo, dados);
    if (total == 0) {
        printf("Erro ao ler arquivo ou arquivo vazio\n");
        return -1;
    }

    printf("📊 Total de registros lidos: %d\n", total);
    printf("💾 Memória após leitura: %ld KB\n", getMemoryKB());

    double tempos[10];

    for (int repeticao = 0; repeticao < 10; repeticao++) {
        // Restaura dados originais - copia array estático para array estático
        for (int i = 0; i < total; i++) {
            copia[i] = dados[i];
        }

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

    return 0;
}
