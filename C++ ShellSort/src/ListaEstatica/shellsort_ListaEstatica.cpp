#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "shellsort_ListaEstatica.hpp"
#include "../config.hpp"

// Struct compacta - 16 bytes por usuário
struct Usuario {
    int id;        // 4 bytes
    int movieID;   // 4 bytes  
    float nota;    // 4 bytes
    int timestamp; // 4 bytes
};

// Shellsort otimizado que trabalha diretamente no array
template <typename T, typename Compare>
void shellsort_inplace(T* arr, size_t n, Compare compare) {
    if (n <= 1) return;
    
    // Sequência de Knuth
    size_t h = 1;
    while (h < n / 3) h = 3 * h + 1;
    
    while (h >= 1) {
        for (size_t i = h; i < n; ++i) {
            T temp = arr[i];
            size_t j = i;
            
            while (j >= h && compare(temp, arr[j - h])) {
                arr[j] = arr[j - h];
                j -= h;
            }
            arr[j] = temp;
        }
        h /= 3;
    }
}

// Verificação de ordenação
template <typename T, typename Compare>
bool estaOrdenado(const T* dados, size_t n, Compare comp) {
    for (size_t i = 1; i < n; ++i) {
        if (comp(dados[i], dados[i - 1])) return false;
    }
    return true;
}

// Leitura otimizada do CSV
bool lerCSV_direto(const std::string& nomeArquivo, ListaEstatica<Usuario>& lista, int limite) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return false;
    }
    
    std::string linha;
    std::getline(arquivo, linha); // pula cabeçalho
    
    int count = 0;
    while (std::getline(arquivo, linha) && count < limite) {
        std::stringstream ss(linha);
        std::string campo;
        Usuario u;
        
        if (std::getline(ss, campo, ',')) u.id = std::stoi(campo);
        if (std::getline(ss, campo, ',')) u.movieID = std::stoi(campo);
        if (std::getline(ss, campo, ',')) u.nota = std::stof(campo);
        if (std::getline(ss, campo, ',')) u.timestamp = std::stoi(campo);
        
        try {
            lista.inserir(u);
            count++;
        } catch (const std::runtime_error&) {
            break; // Lista cheia
        }
    }
    
    return true;
}

// Classe de teste
class TesteShellSortListaEstatica {
private:
    ListaEstatica<Usuario> lista;

public:
    TesteShellSortListaEstatica(size_t cap) : lista(cap) {}

    bool carregar(const std::string& arq, int lim) {
        return lerCSV_direto(arq, lista, lim);
    }

    double executar() {        
        auto t0 = std::chrono::high_resolution_clock::now();
        
        shellsort_inplace<Usuario>(
            lista.data(), 
            lista.size(), 
            [](const Usuario &a, const Usuario &b){ return a.nota < b.nota; }
        );
        
        auto t1 = std::chrono::high_resolution_clock::now();
        double dt = std::chrono::duration<double>(t1 - t0).count();
        
        std::cout << "Tempo: " << std::fixed << std::setprecision(8) << dt << "s\n";
        
        bool ordenado = estaOrdenado<Usuario>(
            lista.data(), 
            lista.size(), 
            [](const Usuario&a, const Usuario&b){return a.nota<b.nota;}
        );
        
        std::cout << (ordenado ? "OK\n" : "ERRO\n");
        return dt;
    }
};

int main() {
    double somaTempos = 0.0;
    
    for (int i = 0; i < REPETICOES; ++i) {
        std::cout << "\n🔁 Execução " << i + 1 << ":\n";
        
        TesteShellSortListaEstatica teste(LIMITE);
        teste.carregar("ratings.csv", LIMITE);
        double tempo = teste.executar();
        somaTempos += tempo;
    }
    
    double media = somaTempos / REPETICOES;
    std::cout << "\n📊 Média: " << std::fixed << std::setprecision(8) 
              << media << " segundos\n";

    return 0;
}