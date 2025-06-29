#ifndef PILHA_ESTATICA_HEAP_HPP
#define PILHA_ESTATICA_HEAP_HPP

#include <stdexcept> // Para std::runtime_error

template <typename T>
class PilhaEstatica {
private:
    T* elementos;           // Vetor alocado no heap
    int topo;               // Índice do topo da pilha
    size_t capacidade;      // Capacidade máxima da pilha

public:
    // Construtor
    PilhaEstatica(size_t capacidade)
        : topo(-1), capacidade(capacidade) {
        elementos = new T[capacidade];
    }

    // Destrutor
    ~PilhaEstatica() {
        delete[] elementos;
    }

    // Insere elemento no topo
    void push(const T& valor) {
        if (static_cast<size_t>(topo + 1) >= capacidade) {
            throw std::runtime_error("Pilha cheia");
        }
        elementos[++topo] = valor;
    }

    // Remove o elemento do topo
    void pop() {
        if (topo < 0) {
            throw std::runtime_error("Pilha vazia");
        }
        --topo;
    }

    // Retorna o elemento do topo
    T& top() {
        if (topo < 0) {
            throw std::runtime_error("Pilha vazia");
        }
        return elementos[topo];
    }

    // Retorna o número de elementos na pilha
    size_t size() const {
        return static_cast<size_t>(topo + 1);
    }

    // Verifica se está vazia
    bool empty() const {
        return topo == -1;
    }

    // Retorna a capacidade máxima
    size_t getCapacidade() const {
        return capacidade;
    }
};

#endif // PILHA_ESTATICA_HEAP_HPP
