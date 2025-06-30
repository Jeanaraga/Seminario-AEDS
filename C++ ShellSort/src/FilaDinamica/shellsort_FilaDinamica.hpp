#pragma once
#include <vector>
#include <stdexcept>

// Versão otimizada da FilaDinamica
template<typename T>
class FilaDinamica {
private:
    std::vector<T> dados;
    size_t inicio = 0;
    
public:
    void enqueue(const T& valor) { 
        dados.emplace_back(valor); 
    }
    
    void dequeue() {
        if (inicio >= dados.size()) 
            throw std::underflow_error("FilaDinamica vazia");
        ++inicio;
        
        // Limpa memória quando necessário
        if (inicio > dados.size() / 2) {
            dados.erase(dados.begin(), dados.begin() + inicio);
            inicio = 0;
        }
    }
    
    T& front() {
        if (inicio >= dados.size()) 
            throw std::underflow_error("FilaDinamica vazia");
        return dados[inicio];
    }
    
    size_t size() const { 
        return dados.size() - inicio; 
    }
};