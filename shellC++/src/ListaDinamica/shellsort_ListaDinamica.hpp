#pragma once
#include <vector>

template<typename T>
class ListaDinamica {
    std::vector<T> dados;

public:
    void inserir(const T& valor) { dados.push_back(valor); }
    void removerUltimo() {
        if (dados.empty()) throw std::underflow_error("ListaDinamica vazia");
        dados.pop_back();
    }
    T& operator[](size_t pos) {
        if (pos >= dados.size()) throw std::out_of_range("Posição inválida");
        return dados[pos];
    }
    size_t size() const { return dados.size(); }
};
