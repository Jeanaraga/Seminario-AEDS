#pragma once
#include <vector>
#include <stdexcept>

template<typename T>
class PilhaDinamica {
    std::vector<T> dados;

public:
    void push(const T& valor) { dados.push_back(valor); }
    void pop() {
        if (dados.empty()) throw std::underflow_error("PilhaDinamica vazia");
        dados.pop_back();
    }
    T& top() {
        if (dados.empty()) throw std::underflow_error("PilhaDinamica vazia");
        return dados.back();
    }
    size_t size() const { return dados.size(); }
};
