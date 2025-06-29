#ifndef SHELLSORT_PILHAESTATICA_H
#define SHELLSORT_PILHAESTATICA_H

#define MAX_PILHA 1000
#define LINHA_MAX 100
#define MAX 100

typedef struct {
    int id;
    int movieID;
    float nota;
    int timestamp;
} Usuarios;

typedef struct {
    Usuarios dados[MAX_PILHA];
    int topo;
} Pilha;

void inicializarPilha(Pilha* p);
int empilhar(Pilha* p, Usuarios u);
int desempilhar(Pilha* p, Usuarios* u);
int estaVazia(Pilha* p);
int estaCheia(Pilha* p);

int lerCSV(const char* nomeArquivo, Pilha* p);
void shellsort(Usuarios usuarios[], int n);
int estaOrdenado(Usuarios usuarios[], int n);

#endif
