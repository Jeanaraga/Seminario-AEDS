#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include <functional>
#include <iomanip> // para setprecision
#include <stdexcept>

// ============================
// Struct do usuário
// ============================
struct Usuario {
    int id;
    int movieID;
    float nota;
    int timestamp;
};

// ============================
// Pilha Estática alocada no heap
// ============================
template <typename T>
class PilhaEstatica {
private:
    T* elementos;
    int topo;
    size_t capacidade;

public:
    PilhaEstatica(size_t capacidade)
        : topo(-1), capacidade(capacidade) {
        elementos = new T[capacidade];
    }

    ~PilhaEstatica() {
        delete[] elementos;
    }

    void push(const T& valor) {
        if (static_cast<size_t>(topo + 1) >= capacidade) {
            throw std::runtime_error("Pilha cheia");
        }
        elementos[++topo] = valor;
    }

    void pop() {
        if (topo < 0) {
            throw std::runtime_error("Pilha vazia");
        }
        --topo;
    }

    T& top() {
        if (topo < 0) {
            throw std::runtime_error("Pilha vazia");
        }
        return elementos[topo];
    }

    size_t size() const {
        return static_cast<size_t>(topo + 1);
    }

    bool empty() const {
        return topo == -1;
    }
};

// ============================
// Shellsort genérico
// ============================
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

// ============================
// Verificação da ordenação
// ============================
template <typename T, typename Compare>
bool estaOrdenado(const std::vector<T>& dados, Compare comp) {
    for (size_t i = 1; i < dados.size(); ++i) {
        if (comp(dados[i], dados[i - 1])) {
            return false;
        }
    }
    return true;
}

// ============================
// Leitura do CSV
// ============================
std::vector<Usuario> lerCSV(const std::string& nomeArquivo, int limite) {
    std::ifstream arquivo(nomeArquivo);
    std::vector<Usuario> usuarios;
    std::string linha;

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return usuarios;
    }

    std::getline(arquivo, linha);  // pula cabeçalho

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

// ============================
// Classe de teste com PilhaEstatica
// ============================
class TesteShellSortPilhaEstatica {
private:
    PilhaEstatica<Usuario> pilha;

public:
    TesteShellSortPilhaEstatica(size_t capacidade)
        : pilha(capacidade) {}

    void carregar(const std::string& nomeArquivo, int limite) {
        auto usuarios = lerCSV(nomeArquivo, limite);
        for (const auto& u : usuarios) {
            pilha.push(u);
        }
    }

    double executarOrdenacao() {
        std::vector<Usuario> vetor;

        while (!pilha.empty()) {
            vetor.push_back(pilha.top());
            pilha.pop();
        }

        auto inicio = std::chrono::high_resolution_clock::now();
        shellsort<Usuario>(vetor, [](const Usuario& a, const Usuario& b) {
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

// ============================
// Função principal
// ============================
int main() {
    constexpr int LIMITE = 100;
    constexpr int REPETICOES = 10;
    double somaTempos = 0.0;

    for (int i = 0; i < REPETICOES; ++i) {
        std::cout << "\n🔁 Execução " << i + 1 << ":\n";
        TesteShellSortPilhaEstatica teste(LIMITE);
        teste.carregar("ratings.csv", LIMITE);
        double tempo = teste.executarOrdenacao();
        somaTempos += tempo;
    }

    double media = somaTempos / REPETICOES;
    std::cout << "\n📊 Média de tempo de ordenação após " << REPETICOES << " execuções: "
              << std::fixed << std::setprecision(8) << media << " segundos\n";

    return 0;
}
