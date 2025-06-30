#pragma once
#include <vector>
#include <stdexcept>

template<typename T>
class PilhaDinamica {
private:
    std::vector<T> dados;

public:
    void push(const T& valor) { 
        dados.push_back(valor); 
    }
    
    void pop() {
        if (dados.empty()) throw std::underflow_error("PilhaDinamica vazia");
        dados.pop_back();
    }
    
    T& top() {
        if (dados.empty()) throw std::underflow_error("PilhaDinamica vazia");
        return dados.back();
    }
    
    size_t size() const { 
        return dados.size(); 
    }
    
    // NOVO: Acesso direto aos dados para ordenação
    std::vector<T>& getData() {
        return dados;
    }
    
    // NOVO: Pré-aloca capacidade para evitar realocações
    void reserve(size_t capacidade) {
        dados.reserve(capacidade);
    }
    
    // NOVO: Reduz capacidade ao tamanho atual
    void shrink_to_fit() {
        dados.shrink_to_fit();
    }
};