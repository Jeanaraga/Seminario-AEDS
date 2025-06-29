// ============================
// main_lista_estatica.cpp
// ============================
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "shellsort_ListaEstatica.hpp"

struct Usuario {
    int id;
    int movieID;
    float nota;
    int timestamp;
};

// Shellsort genérico
template <typename T, typename Compare>
void shellsort(std::vector<T>& vetor, Compare compare) {
    int n = vetor.size();
    int h = 1;
    while (h < n / 3) h = 3 * h + 1;
    while (h >= 1) {
        for (int i = h; i < n; ++i) {
            T temp = vetor[i];
            int j = i;
            while (j >= h && compare(temp, vetor[j - h])) {
                vetor[j] = vetor[j - h];
                j -= h;
            }
            vetor[j] = temp;
        }
        h /= 3;
    }
}

// Verificação da ordenação
template <typename T, typename Compare>
bool estaOrdenado(const std::vector<T>& dados, Compare comp) {
    for (size_t i = 1; i < dados.size(); ++i) {
        if (comp(dados[i], dados[i - 1])) return false;
    }
    return true;
}

// Leitura do CSV
std::vector<Usuario> lerCSV(const std::string& nomeArquivo, int limite) {
    std::ifstream arquivo(nomeArquivo);
    std::vector<Usuario> usuarios;
    std::string linha;
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return usuarios;
    }
    std::getline(arquivo, linha); // pula cabeçalho
    while (std::getline(arquivo, linha) && usuarios.size() < static_cast<size_t>(limite)) {
        std::stringstream ss(linha);
        std::string campo;
        Usuario u;
        std::getline(ss, campo, ','); u.id = std::stoi(campo);
        std::getline(ss, campo, ','); u.movieID = std::stoi(campo);
        std::getline(ss, campo, ','); u.nota = std::stof(campo);
        std::getline(ss, campo, ','); u.timestamp = std::stoi(campo);
        usuarios.push_back(u);
    }
    return usuarios;
}

class TesteShellSortListaEstatica {
private:
    ListaEstatica<Usuario> lista;
public:
    TesteShellSortListaEstatica(size_t cap) : lista(cap) {}
    void carregar(const std::string& arq, int lim) {
        auto v = lerCSV(arq, lim);
        for (auto& u : v) lista.inserir(u);
    }
    double executar() {
        std::vector<Usuario> v;
        for (size_t i = 0; i < lista.size(); ++i) v.push_back(lista.get(i));
        auto t0 = std::chrono::high_resolution_clock::now();
        shellsort<Usuario>(v, [](const Usuario &a, const Usuario &b){ return a.nota < b.nota; });
        auto t1 = std::chrono::high_resolution_clock::now();
        double dt = std::chrono::duration<double>(t1 - t0).count();
        std::cout << "Tempo (lista): " << std::fixed << std::setprecision(8) << dt << "s\n";
        std::cout << (estaOrdenado<Usuario>(v, [](const Usuario&a, const Usuario&b){return a.nota<b.nota;}) ? "OK\n" : "ERRO\n");
        return dt;
    }
};

int main() {
    const int LIM = 100;
    const int REP = 10;
    double soma = 0;
    for (int i = 0; i < REP; ++i) {
        std::cout << "Execucao " << i+1 << "\n";
        TesteShellSortListaEstatica t(LIM);
        t.carregar("ratings.csv", LIM);
        soma += t.executar();
    }
    std::cout << "Média lista: " << std::fixed << std::setprecision(8) << soma/REP << "s\n";
    return 0;
}