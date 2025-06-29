#ifndef SHELLSORT_FILADINAMICA_H
#define SHELLSORT_FILADINAMICA_H

#define MAX 100

typedef struct {
    int id;
    int movieID;
    float nota;
    int timestamp;
} Usuarios;

typedef struct No {
    Usuarios dados;
    struct No* prox;
} No;

typedef struct {
    No* inicio;
    No* fim;
    int tamanho;
} Fila;

void inicializarFila(Fila* f);
int filaVazia(Fila* f);
int enfileirar(Fila* f, Usuarios u);
int desenfileirar(Fila* f, Usuarios* u);
int lerCSV(const char* nomeArquivo, Fila* f);
void shellsort(Usuarios usuarios[], int n);
int estaOrdenado(Usuarios usuarios[], int n);

#endif
