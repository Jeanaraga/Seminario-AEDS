#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include <functional>
#include <iomanip> // Para std::setprecision
#include "../FilaDinamica/shellsort_FilaDinamica.hpp"
#include "../config.hpp"

// Struct de dados
struct Usuario {
    int id;
    int movieID;
    float nota;
    int timestamp;
};

// ShellSort in-place otimizado
template <typename T>
void shellSort(std::vector<T>& dados, const std::function<bool(const T&, const T&)>& comp) {
    const int n = dados.size();
    if (n <= 1) return;

    // Sequência de Knuth otimizada
    int h = 1;
    while (h < n / 3) h = 3 * h + 1;

    while (h >= 1) {
        for (int i = h; i < n; ++i) {
            T temp = std::move(dados[i]);
            int j = i;
            while (j >= h && comp(temp, dados[j - h])) {
                dados[j] = std::move(dados[j - h]);
                j -= h;
            }
            dados[j] = std::move(temp);
        }
        h /= 3;
    }
}

// Verificação otimizada
template <typename T, typename Compare>
bool estaOrdenado(const std::vector<T>& dados, Compare comp) {
    for (size_t i = 1; i < dados.size(); ++i) {
        if (comp(dados[i], dados[i - 1])) {
            return false;
        }
    }
    return true;
}

// Leitura otimizada com reserva de memória
std::vector<Usuario> lerCSV(const std::string& nomeArquivo, int limite) {
    std::ifstream arquivo(nomeArquivo);
    std::vector<Usuario> usuarios;
    
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return usuarios;
    }

    // Reserva memória antecipadamente
    usuarios.reserve(limite);
    
    std::string linha;
    linha.reserve(128); // Reserva para linha típica
    
    std::getline(arquivo, linha); // Pula cabeçalho

    while (std::getline(arquivo, linha) && usuarios.size() < static_cast<size_t>(limite)) {
        std::stringstream ss(linha);
        std::string campo;
        Usuario u;

        std::getline(ss, campo, ',');
        u.id = std::stoi(campo);
        std::getline(ss, campo, ',');
        u.movieID = std::stoi(campo);
        std::getline(ss, campo, ',');
        u.nota = std::stof(campo);
        std::getline(ss, campo, ',');
        u.timestamp = std::stoi(campo);

        usuarios.emplace_back(std::move(u));
    }

    // Libera memória não utilizada
    usuarios.shrink_to_fit();
    return usuarios;
}

// Classe otimizada - elimina duplicação de dados
class TesteShellSortFilaDinamica {
private:
    std::vector<Usuario> dados; // Usa vetor diretamente ao invés de FilaDinamica

public:
    void carregar(const std::string& nomeArquivo, int limite) {
        dados = lerCSV(nomeArquivo, limite);
    }

    double executarOrdenacao() {
        if (dados.empty()) return 0.0;

        auto inicio = std::chrono::high_resolution_clock::now();
        
        // Ordenação in-place sem cópias extras
        shellSort<Usuario>(dados, [](const Usuario& a, const Usuario& b) {
            return a.nota < b.nota;
        });
        
        auto fim = std::chrono::high_resolution_clock::now();
        double tempo = std::chrono::duration<double>(fim - inicio).count();
        
        std::cout << "Tempo de ordenação: " << std::fixed << std::setprecision(8) << tempo << " segundos\n";

        // Verificação sem lambda extra
        if (estaOrdenado(dados, [](const Usuario& a, const Usuario& b) {
            return a.nota < b.nota;
        })) {
            std::cout << "Ordenação correta!\n";
        } else {
            std::cout << "Ordenação incorreta!\n";
        }

        return tempo;
    }
};

// Main otimizado
int main() {
    double somaTempos = 0.0;
    
    // Cria objeto uma vez fora do loop
    TesteShellSortFilaDinamica teste;
    teste.carregar("ratings.csv", LIMITE);

    for (int i = 0; i < REPETICOES; ++i) {
        std::cout << "\n🔁 Execução " << i + 1 << ":\n";
        double tempo = teste.executarOrdenacao();
        somaTempos += tempo;
    }

    const double media = somaTempos / REPETICOES;
    std::cout << "\n📊 Média de tempo de ordenação após " << REPETICOES << " execuções: "
              << std::fixed << std::setprecision(8) << media << " segundos\n";

    return 0;
}