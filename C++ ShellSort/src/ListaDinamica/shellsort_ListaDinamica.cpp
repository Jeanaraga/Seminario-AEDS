#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include <functional>
#include <iomanip>  // Para std::setprecision
#include "../ListaDinamica/shellsort_ListaDinamica.hpp"

// Struct simples
struct Usuario {
    int id;
    int movieID;
    float nota;
    int timestamp;
};

// ShellSort genérico
template <typename T>
void shellSort(std::vector<T>& dados, const std::function<bool(const T&, const T&)>& comp) {
    int n = dados.size();

    // Geração do maior h de Knuth menor que n
    int h = 1;
    while (h < n / 3)
        h = 3 * h + 1;  // h = 1, 4, 13, 40, ...

    // Shellsort com a sequência de Knuth
    while (h >= 1) {
        for (int i = h; i < n; ++i) {
            T temp = dados[i];
            int j = i;
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
bool estaOrdenado(const std::vector<T>& dados, Compare comp) {
    for (size_t i = 1; i < dados.size(); ++i) {
        if (comp(dados[i], dados[i - 1])) {
            return false;
        }
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

    std::getline(arquivo, linha); // Cabeçalho

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

        usuarios.push_back(u);
    }

    return usuarios;
}

// Classe de teste com ListaDinamica
class TesteShellSortListaDinamica {
private:
    ListaDinamica<Usuario> lista;

public:
    void carregar(const std::string& nomeArquivo, int limite) {
        auto usuarios = lerCSV(nomeArquivo, limite);
        for (const auto& u : usuarios) {
            lista.inserir(u);
        }
    }

    double executarOrdenacao() {
        std::vector<Usuario> vetor;

        for (size_t i = 0; i < lista.size(); ++i) {
            vetor.push_back(lista[i]);
        }

        auto inicio = std::chrono::high_resolution_clock::now();
        shellSort<Usuario>(vetor, [](const Usuario& a, const Usuario& b) {
            return a.nota < b.nota;
        });
        auto fim = std::chrono::high_resolution_clock::now();

        double tempo = std::chrono::duration<double>(fim - inicio).count();
        std::cout << "Tempo de ordenação: " << std::fixed << std::setprecision(8) << tempo << " segundos\n";

        if (estaOrdenado(vetor, [](const Usuario& a, const Usuario& b) {
            return a.nota < b.nota;
        })) {
            std::cout << "Ordenação correta!\n";
        } else {
            std::cout << "Ordenação incorreta!\n";
        }

        return tempo;
    }
};

// Ponto de entrada com 10 execuções e média
int main() {
    constexpr int LIMITE = 100;
    constexpr int REPETICOES = 10;
    double somaTempos = 0.0;

    for (int i = 0; i < REPETICOES; ++i) {
        std::cout << "\n🔁 Execução " << i + 1 << ":\n";
        TesteShellSortListaDinamica teste;
        teste.carregar("ratings.csv", LIMITE);
        double tempo = teste.executarOrdenacao();
        somaTempos += tempo;
    }

    double media = somaTempos / REPETICOES;
    std::cout << "\n📊 Média de tempo de ordenação após " << REPETICOES << " execuções: "
              << std::fixed << std::setprecision(8) << media << " segundos\n";

    return 0;
}
