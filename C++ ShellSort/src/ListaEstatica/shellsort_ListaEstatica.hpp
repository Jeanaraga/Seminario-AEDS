#ifndef SHELLSORT_LISTA_ESTATICA_HPP
#define SHELLSORT_LISTA_ESTATICA_HPP
#include <stdexcept>

template <typename T>
class ListaEstatica {
private:
    T* elementos;
    size_t tamanho;
    size_t capacidade;

public:
    ListaEstatica(size_t capacidade)
        : tamanho(0), capacidade(capacidade) {
        elementos = new T[capacidade];
    }

    ~ListaEstatica() {
        delete[] elementos;
    }

    void inserir(const T& valor) {
        if (tamanho >= capacidade) {
            throw std::runtime_error("Lista cheia");
        }
        elementos[tamanho++] = valor;
    }

    T& get(size_t i) {
        if (i >= tamanho) {
            throw std::runtime_error("Índice inválido");
        }
        return elementos[i];
    }
    
    const T& get(size_t i) const {
        if (i >= tamanho) {
            throw std::runtime_error("Índice inválido");
        }
        return elementos[i];
    }

    size_t size() const {
        return tamanho;
    }

    bool empty() const {
        return tamanho == 0;
    }

    // Acesso direto aos elementos para ordenação in-place
    T* data() { return elementos; }
    const T* data() const { return elementos; }
};

#endif