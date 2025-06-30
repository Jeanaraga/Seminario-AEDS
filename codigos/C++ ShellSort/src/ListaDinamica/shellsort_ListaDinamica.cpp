#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "shellsort_ListaDinamica.hpp"
#include "../config.hpp"

// Struct compacta - 16 bytes por usuário
struct Usuario {
    int id;        // 4 bytes
    int movieID;   // 4 bytes  
    float nota;    // 4 bytes
    int timestamp; // 4 bytes
};

// ShellSort otimizado que trabalha diretamente no array
template <typename T, typename Compare>
void shellSort_inplace(T* dados, size_t n, Compare comp) {
    if (n <= 1) return;
    
    // Sequência de Knuth
    size_t h = 1;
    while (h < n / 3) h = 3 * h + 1;

    while (h >= 1) {
        for (size_t i = h; i < n; ++i) {
            T temp = dados[i];
            size_t j = i;
            
            while (j >= h && comp(temp, dados[j - h])) {
                dados[j] = dados[j - h];
                j -= h;
            }
            dados[j] = temp;
        }
        h /= 3;
    }
}

// Verificação de ordenação
template <typename T, typename Compare>
bool estaOrdenado(const T* dados, size_t n, Compare comp) {
    for (size_t i = 1; i < n; ++i) {
        if (comp(dados[i], dados[i - 1])) {
            return false;
        }
    }
    return true;
}

// Leitura otimizada do CSV
bool lerCSV_direto(const std::string& nomeArquivo, ListaDinamica<Usuario>& lista, int limite) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return false;
    }

    lista.reservar(limite);
    
    std::string linha;
    std::getline(arquivo, linha); // Pula cabeçalho

    int count = 0;
    while (std::getline(arquivo, linha) && count < limite) {
        std::stringstream ss(linha);
        std::string campo;
        Usuario u;

        if (std::getline(ss, campo, ',')) u.id = std::stoi(campo);
        if (std::getline(ss, campo, ',')) u.movieID = std::stoi(campo);
        if (std::getline(ss, campo, ',')) u.nota = std::stof(campo);
        if (std::getline(ss, campo, ',')) u.timestamp = std::stoi(campo);

        lista.inserir_rapido(u);
        count++;
    }

    return true;
}

// Classe de teste
class TesteShellSortListaDinamica {
private:
    ListaDinamica<Usuario> lista;

public:
    bool carregar(const std::string& nomeArquivo, int limite) {
        return lerCSV_direto(nomeArquivo, lista, limite);
    }

    double executarOrdenacao() {
        auto inicio = std::chrono::high_resolution_clock::now();
        
        shellSort_inplace<Usuario>(
            lista.data(), 
            lista.size(), 
            [](const Usuario& a, const Usuario& b) {
                return a.nota < b.nota;
            }
        );
        
        auto fim = std::chrono::high_resolution_clock::now();
        
        double tempo = std::chrono::duration<double>(fim - inicio).count();
        
        std::cout << "Tempo: " << std::fixed << std::setprecision(8) 
                  << tempo << "s\n";

        bool ordenado = estaOrdenado<Usuario>(
            lista.data(), 
            lista.size(), 
            [](const Usuario& a, const Usuario& b) {
                return a.nota < b.nota;
            }
        );

        std::cout << (ordenado ? "OK\n" : "ERRO\n");
        return tempo;
    }
};

int main() {
    double somaTempos = 0.0;

    for (int i = 0; i < REPETICOES; ++i) {
        std::cout << "\n🔁 Execução " << i + 1 << ":\n";
        
        TesteShellSortListaDinamica teste;
        teste.carregar("ratings.csv", LIMITE);
        double tempo = teste.executarOrdenacao();
        somaTempos += tempo;
    }

    double media = somaTempos / REPETICOES;
    std::cout << "\n📊 Média: " << std::fixed << std::setprecision(8) 
              << media << " segundos\n";

    return 0;
}