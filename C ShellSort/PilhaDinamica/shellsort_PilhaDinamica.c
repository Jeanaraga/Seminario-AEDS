#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort_PilhaDinamica.h"
#include <sys/resource.h>

long getMemoryKB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;  // Em KB no Linux
}   

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
    
    // Pula o cabeçalho
    fgets(linha, LINHA_MAX, arquivo);
    
    while (fgets(linha, LINHA_MAX, arquivo) && total < LIMITE_LEITURA) {
        Usuarios u;
        sscanf(linha, "%d,%d,%f,%d", &u.id, &u.movieID, &u.nota, &u.timestamp);
        if (!empilhar(p, u)) break;
        total++;
    }
    
    fclose(arquivo);
    return total;
}

// Função para calcular a sequência de Knuth
int calcularGapKnuth(int gaps[], int n) {
    int k = 0;
    int gap = 1;
    
    // Calcula gaps da sequência de Knuth: 3^k - 1 / 2
    while (gap < n) {
        gaps[k++] = gap;
        gap = gap * 3 + 1;  // Próximo gap: 3*gap + 1
    }
    
    return k;  // Retorna quantidade de gaps
}

// ShellSort otimizado com sequência de Knuth
void shellsortKnuth(Usuarios* usuarios, int n) {
    int gap = 1;
    while (gap < n / 3) {
        gap = gap * 3 + 1;
    }

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

int estaOrdenado(Usuarios usuarios[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (usuarios[i].nota > usuarios[i + 1].nota) {
            return 0;
        }
    }
    return 1;
}

// Função para restaurar o vetor original sem malloc adicional
void restaurarVetor(Usuarios vetor[], No* topo, int total) {
    No* atual = topo;
    for (int i = total - 1; i >= 0; i--) {
        vetor[i] = atual->dado;
        atual = atual->prox;
    }
}

int main() {
    Pilha pilha;
    inicializarPilha(&pilha);

    int total = lerCSV("ratings.csv", &pilha);
    if (total == 0) return -1;

    printf("📊 Total de registros lidos: %d\n", total);
    printf("📥 Memória após leitura: %ld KB\n", getMemoryKB());

    // Aloca apenas UM vetor para trabalho
    Usuarios* vetor = malloc(total * sizeof(Usuarios));
    if (!vetor) {
        printf("Erro de memória\n");
        liberarPilha(&pilha);
        return -1;
    }

    // Inicializa o vetor com os dados originais da pilha
    restaurarVetor(vetor, pilha.topo, total);

    double tempos[10];

    printf("\n🚀 Executando ShellSort com Sequência de Knuth...\n");

    for (int exec = 0; exec < 10; exec++) {
        if (exec > 0) {
            restaurarVetor(vetor, pilha.topo, total);
        }

        clock_t inicio = clock();
        shellsortKnuth(vetor, total);
        clock_t fim = clock();

        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempos[exec] = tempo;

        printf("Execução %d: %.6f segundos - %s\n", exec + 1, tempo,
               estaOrdenado(vetor, total) ? "Ordenado ✅" : "Não ordenado ❌");
    }

    // Estatísticas de tempo
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

    // Limpeza
    free(vetor);
    liberarPilha(&pilha);

    return 0;
}
