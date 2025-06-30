#pragma once
#include <vector>
#include <stdexcept>

template<typename T>
class ListaDinamica {
private:
    std::vector<T> dados;

public:
    void inserir(const T& valor) { 
        dados.push_back(valor); 
    }
    
    void removerUltimo() {
        if (dados.empty()) throw std::underflow_error("ListaDinamica vazia");
        dados.pop_back();
    }
    
    T& operator[](size_t pos) {
        if (pos >= dados.size()) throw std::out_of_range("Posição inválida");
        return dados[pos];
    }
    
    const T& operator[](size_t pos) const {
        if (pos >= dados.size()) throw std::out_of_range("Posição inválida");
        return dados[pos];
    }
    
    size_t size() const { 
        return dados.size(); 
    }
    
    bool empty() const {
        return dados.empty();
    }
    
    // Acesso direto aos dados para ordenação in-place
    T* data() { 
        return dados.data(); 
    }
    
    const T* data() const { 
        return dados.data(); 
    }
    
    // Reserva capacidade para evitar realocações
    void reservar(size_t capacidade) {
        dados.reserve(capacidade);
    }
    
    // Otimização: inserção direta no final sem verificações extras
    void inserir_rapido(const T& valor) {
        dados.emplace_back(valor);
    }
};