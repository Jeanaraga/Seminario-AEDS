#pragma once
#include <deque>
#include <stdexcept>

template<typename T>
class FilaDinamica {
    std::deque<T> dados;

public:
    void enqueue(const T& valor) { dados.push_back(valor); }
    void dequeue() {
        if (dados.empty()) throw std::underflow_error("FilaDinamica vazia");
        dados.pop_front();
    }
    T& front() {
        if (dados.empty()) throw std::underflow_error("FilaDinamica vazia");
        return dados.front();
    }
    size_t size() const { return dados.size(); }
};
