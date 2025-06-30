#ifndef FILA_ESTATICA_HPP
#define FILA_ESTATICA_HPP
#include <stdexcept>

template <typename T>
class FilaEstatica {
private:
    T* elementos;
    int frente, tras;
    size_t tamanho;
    size_t capacidade;

public:
    FilaEstatica(size_t capacidade)
        : frente(0), tras(-1), tamanho(0), capacidade(capacidade) {
        elementos = new T[capacidade];
    }
    
    ~FilaEstatica() {
        delete[] elementos;
    }
    
    void enfileirar(const T& valor) {
        if (tamanho >= capacidade) {
            throw std::runtime_error("Fila cheia");
        }
        tras = (tras + 1) % capacidade;
        elementos[tras] = valor;
        ++tamanho;
    }
    
    void desenfileirar() {
        if (tamanho == 0) {
            throw std::runtime_error("Fila vazia");
        }
        frente = (frente + 1) % capacidade;
        --tamanho;
    }
    
    T& frenteElemento() {
        if (tamanho == 0) {
            throw std::runtime_error("Fila vazia");
        }
        return elementos[frente];
    }
    
    const T& frenteElemento() const {
        if (tamanho == 0) {
            throw std::runtime_error("Fila vazia");
        }
        return elementos[frente];
    }
    
    size_t size() const {
        return tamanho;
    }
    
    bool empty() const {
        return tamanho == 0;
    }
    
    // Acesso indexado para algoritmos de ordenação
    T& getAt(size_t index) {
        if (index >= tamanho) {
            throw std::out_of_range("Índice fora do intervalo");
        }
        return elementos[(frente + index) % capacidade];
    }
    
    const T& getAt(size_t index) const {
        if (index >= tamanho) {
            throw std::out_of_range("Índice fora do intervalo");
        }
        return elementos[(frente + index) % capacidade];
    }
    
    // Método para definir valor em posição específica
    void setAt(size_t index, const T& valor) {
        if (index >= tamanho) {
            throw std::out_of_range("Índice fora do intervalo");
        }
        elementos[(frente + index) % capacidade] = valor;
    }
    
    // Método para copiar elementos linearmente (mantido para compatibilidade)
    void copiarLinear(T* destino) const {
        for (size_t i = 0; i < tamanho; ++i) {
            destino[i] = elementos[(frente + i) % capacidade];
        }
    }
};

#endif