#ifndef SHELLSORT_PILHADINAMICA_H
#define SHELLSORT_PILHADINAMICA_H

#define LINHA_MAX 100
#define MAX 100

typedef struct {
    int id;
    int movieID;
    float nota;
    int timestamp;
} Usuarios;

typedef struct No {
    Usuarios dado;
    struct No* prox;
} No;

typedef struct {
    No* topo;
    int tamanho;
} Pilha;

void inicializarPilha(Pilha* p);
int empilhar(Pilha* p, Usuarios u);
int desempilhar(Pilha* p, Usuarios* u);
int estaVazia(Pilha* p);
void liberarPilha(Pilha* p);

int lerCSV(const char* nomeArquivo, Pilha* p);
void shellsort(Usuarios usuarios[], int n);
int estaOrdenado(Usuarios usuarios[], int n);

#endif
