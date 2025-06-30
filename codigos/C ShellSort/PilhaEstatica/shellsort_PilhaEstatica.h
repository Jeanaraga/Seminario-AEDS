#ifndef SHELLSORT_PILHA_ESTATICA_H
#define SHELLSORT_PILHA_ESTATICA_H

#include "../config.h"

#define MAX_PILHA 1000000  // Tamanho máximo da pilha


typedef struct {
    int id;
    int movieID;
    float nota;
    int timestamp;
} Usuario;

typedef struct {
    Usuario dados[MAX_PILHA];
    int topo;
} Pilha;

// Funções da pilha
void inicializarPilha(Pilha* p);
int pilhaVazia(Pilha* p);
int pilhaCheia(Pilha* p);
int empilhar(Pilha* p, Usuario u);
int desempilhar(Pilha* p, Usuario* u);

// Funções do programa
int lerCSV(const char* nomeArquivo, Pilha* p);
void shellsortKnuth(Usuario* usuarios, int n);
int estaOrdenado(Usuario* usuarios, int n);

#endif // SHELLSORT_PILHA_ESTATICA_H