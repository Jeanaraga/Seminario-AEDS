#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include <iomanip> // para setprecision
#include <stdexcept>
#include "../PilhaEstatica/shellsort_PilhaEstatica.hpp"
#include "../config.hpp"

// ============================
// Struct do usuário
// ============================
struct Usuario {
    int id;
    int movieID;
    float nota;
    int timestamp;
};

void imprimirMemoria() {
    std::ifstream status("/proc/self/status");
    std::string linha;
    while (std::getline(status, linha)) {
        if (linha.find("VmRSS") != std::string::npos || linha.find("VmSize") != std::string::npos)
            std::cout << linha << std::endl;
    }
}

// ============================
// Classe de teste com PilhaEstatica
// ============================
class TesteShellSortPilhaEstatica {
private:
    PilhaEstatica<Usuario> pilha;

public:
    TesteShellSortPilhaEstatica(size_t capacidade)
        : pilha(capacidade) {}

    // NOVO: Carrega direto na pilha, sem vector intermediário
    void carregar(const std::string& nomeArquivo, int limite) {
        std::ifstream arquivo(nomeArquivo);
        std::string linha;

        if (!arquivo.is_open()) {
            std::cerr << "Erro ao abrir o arquivo.\n";
            return;
        }

        std::getline(arquivo, linha);  // pula cabeçalho

        int count = 0;
        while (std::getline(arquivo, linha) && count < limite) {
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

            pilha.push(u);  // Diretamente na pilha!
            count++;
        }
    }

    double executarOrdenacao() {
        if (pilha.empty()) {
            std::cout << "Pilha vazia!\n";
            return 0.0;
        }

        // Ordena diretamente na pilha (sem criar vector)
        auto inicio = std::chrono::high_resolution_clock::now();
        
        // Acessar dados diretamente da pilha
        Usuario* dados = pilha.getData();
        size_t n = pilha.size();
        
        // Shellsort direto no array da pilha
        int h = 1;
        while (h < static_cast<int>(n) / 3) h = 3 * h + 1;

        while (h >= 1) {
            for (int i = h; i < static_cast<int>(n); ++i) {
                Usuario temp = dados[i];
                int j = i;
                while (j >= h && temp.nota < dados[j - h].nota) {
                    dados[j] = dados[j - h];
                    j -= h;
                }
                dados[j] = temp;
            }
            h /= 3;
        }
        
        auto fim = std::chrono::high_resolution_clock::now();

        double tempo = std::chrono::duration<double>(fim - inicio).count();
        std::cout << "Tempo de ordenação: " << std::fixed << std::setprecision(8) << tempo << " segundos\n";

        // Verificação da ordenação
        bool ordenado = true;
        for (size_t i = 1; i < n; ++i) {
            if (dados[i].nota < dados[i-1].nota) {
                ordenado = false;
                break;
            }
        }
        
        if (ordenado) {
            std::cout << "Ordenação correta!\n";
        } else {
            std::cout << "Ordenação incorreta!\n";
        }

        return tempo;
    }
};

// ============================
// Função principal
// ============================
int main() {
    
    double somaTempos = 0.0;

    for (int i = 0; i < REPETICOES; ++i) {
        std::cout << "\n🔁 Execução " << i + 1 << ":\n";
        TesteShellSortPilhaEstatica teste(LIMITE);
        teste.carregar("ratings.csv", LIMITE);
        double tempo = teste.executarOrdenacao();
        somaTempos += tempo;
    }

    imprimirMemoria();

    double media = somaTempos / REPETICOES;
    std::cout << "\n📊 Média de tempo de ordenação após " << REPETICOES << " execuções: "
              << std::fixed << std::setprecision(8) << media << " segundos\n";

    return 0;
}