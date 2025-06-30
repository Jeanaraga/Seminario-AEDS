#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "shellsort_FilaEstatica.hpp"
#include "../config.hpp"

// Struct compacta - 16 bytes por usuário
struct Usuario {
    int id = 0;
    int movieID = 0;
    float nota = 0.0f;
    int timestamp = 0;
};

// Shellsort que trabalha diretamente na fila circular
template <typename T, typename Compare>
void shellsort_circular(FilaEstatica<T>& fila, Compare compare) {
    size_t n = fila.size();
    if (n <= 1) return;
    
    // Sequência de Knuth
    size_t h = 1;
    while (h < n / 3) h = 3 * h + 1;
    
    while (h >= 1) {
        for (size_t i = h; i < n; ++i) {
            T temp = fila.getAt(i);
            size_t j = i;
            
            while (j >= h && compare(temp, fila.getAt(j - h))) {
                fila.setAt(j, fila.getAt(j - h));
                j -= h;
            }
            fila.setAt(j, temp);
        }
        h /= 3;
    }
}

// Verificação de ordenação
template <typename T, typename Compare>
bool estaOrdenado(const FilaEstatica<T>& fila, Compare comp) {
    size_t n = fila.size();
    for (size_t i = 1; i < n; ++i) {
        if (comp(fila.getAt(i), fila.getAt(i - 1))) return false;
    }
    return true;
}

// Leitura otimizada do CSV
bool lerCSV_direto(const std::string& nomeArquivo, FilaEstatica<Usuario>& fila, int limite) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return false;
    }
    
    std::string linha;
    linha.reserve(128); // Reserva para evitar realocações
    std::getline(arquivo, linha); // pula cabeçalho
    
    int count = 0;
    while (std::getline(arquivo, linha) && count < limite) {
        std::stringstream ss(linha);
        std::string campo;
        Usuario u{}; // Zero-initialized
        
        if (std::getline(ss, campo, ',') && !campo.empty()) {
            u.id = std::stoi(campo);
        }
        if (std::getline(ss, campo, ',') && !campo.empty()) {
            u.movieID = std::stoi(campo);
        }
        if (std::getline(ss, campo, ',') && !campo.empty()) {
            u.nota = std::stof(campo);
        }
        if (std::getline(ss, campo, ',') && !campo.empty()) {
            u.timestamp = std::stoi(campo);
        }
        
        try {
            fila.enfileirar(u);
            count++;
        } catch (const std::runtime_error&) {
            break; // Fila cheia
        }
    }
    
    return true;
}

// Classe de teste otimizada - SEM buffer adicional
class TesteShellSortFilaEstatica {
private:
    FilaEstatica<Usuario> fila;

public:
    TesteShellSortFilaEstatica(size_t cap) : fila(cap) {}

    bool carregar(const std::string& arq, int lim) {
        return lerCSV_direto(arq, fila, lim);
    }

    double executar() {
        size_t n = fila.size();
        if (n == 0) return 0.0;
        
        auto t0 = std::chrono::high_resolution_clock::now();
        
        // Ordena diretamente na fila circular - SEM buffer adicional
        shellsort_circular(fila, [](const Usuario &a, const Usuario &b){ 
            return a.nota < b.nota; 
        });
        
        auto t1 = std::chrono::high_resolution_clock::now();
        double dt = std::chrono::duration<double>(t1 - t0).count();
        
        std::cout << "Tempo: " << std::fixed << std::setprecision(8) << dt << "s\n";
        
        bool ordenado = estaOrdenado(fila, [](const Usuario&a, const Usuario&b){
            return a.nota < b.nota;
        });
        
        std::cout << (ordenado ? "OK\n" : "ERRO\n");
        return dt;
    }
};

int main() {
    double somaTempos = 0.0;
    
    // Cria uma única instância e reutiliza
    TesteShellSortFilaEstatica teste(LIMITE);
    teste.carregar("ratings.csv", LIMITE);
    
    for (int i = 0; i < REPETICOES; ++i) {
        std::cout << "\n🔁 Execução " << i + 1 << ":\n";
        double tempo = teste.executar();
        somaTempos += tempo;
    }
    
    double media = somaTempos / REPETICOES;
    std::cout << "\n📊 Média: " << std::fixed << std::setprecision(8) 
              << media << " segundos\n";

    return 0;
}