## 📚 Seminário – Algoritmo de Ordenação: Shell Sort

Este repositório contém os materiais e implementações utilizados no seminário sobre o algoritmo **Shell Sort**, conforme exigido no trabalho em equipe da disciplina de Algoritmos. O projeto explora o algoritmo Shell Sort, uma otimização do Insertion Sort que utiliza sequências de gaps para melhorar a eficiência na ordenação de dados. O trabalho inclui:

* Análise teórica das estratégias de gaps
* Implementações práticas em múltiplas linguagens (C, C++, Java, Python, Julia).
* Benchmarking de desempenho (tempo de execução e uso de memória) em diferentes estruturas de dados (listas, pilhas, filas).
* Comparações entre linguagens compiladas vs. interpretadas e estruturas lineares vs. dinâmicas.


---

### 🎯 Objetivos
<ul>
<li> Comparar estratégias de gaps:
    <ul>
     <li>
      Shell Original: $$h = \frac{n}{2}$$
     </li>
     <li>
        Knuth: $$h = \frac{3^k - 1}{2}$$
      </li>
    </ul>
</li>
 <li> Avaliar desempenho em linguagens:
  <ul>
   <li> Linguagens compiladas (C, C++, Julia, Java, Python) </li>
  </ul>
 </li>
<li> Analisar estrutura de dados:
 <ul>
  <li> Estruturas Lineares e Estruturas Dinâmicas
 </ul>
</li>
 
</ul>
 
---
### 🔍 Principais Resultados
✅ Melhor estratégia de gaps:

* Sequência de Knuth mostrou ganho de 20–30% em tempo de execução vs. Shell original.

✅ Linguagens mais eficientes:

* C++ foi a mais rápida (até 1000× mais rápida que Python para 1M de elementos).
* Python teve o pior desempenho devido ao overhead de interpretação.


---
### ⚙️ Como Executar os Códigos

Após clonar o repositório:

* Em C/C++:
  Usar o makefile com os seguintes comandos:
 ```bash
make clean
make
make run
```

* Em Java:
```bash
javac Main.java
java Main

javac UsoMem
java UsoMem
```

* Em Python:
Dentro da pasta Python Shell Sort:
  
```bash
python main.py
```

* Em Julia:
Dentro da pasta Julia Shell Sort
```bash
julia mainK.jl
```

---
### 📂 Organização do Repositório

* Cada implementação do Shell Sort está organizada por linguagem:

  * `Java-ShellSort/`
  * `Python ShellSort`
  * `Julia ShellSort`
  * `C ShellSort`
  * `C++ ShellSort`

* Dentro de cada pasta, há implementações para diferentes **estruturas de dados**:

  * Lista
  * Fila (linear e dinâmica)
  * Pilha (linear e dinâmica)
  * Vetor

---

### 📄 Apresentação

* O arquivo da apresentação em PDF está disponível no repositório:
  **`Apresentacao_Seminario_ShellSort.pdf`**

---

### ⚠️ Observação sobre o código Java

Na pasta `Java-ShellSort/`, o código foi estruturado para permitir a comparação entre diferentes estruturas.
Para isso, é necessário:

👉 **Descomentar** o trecho de código correspondente à estrutura que deseja testar
👉 **Comentar** os demais, para evitar conflitos na execução

Exemplo no `Main.java`:

```java
// ShellSortLinear.ordenar(vetor);         // Para vetor
// ShellSortLinear.ordenarFila(fila);      // Para fila
ShellSortLinear.ordenarPilha(pilha);      // Para pilha
```

---

### 🧪 Testes de Desempenho

Os testes foram executados com os seguintes tamanhos de entrada:

* 100 elementos
* 1.000 elementos
* 10.000 elementos
* 100.000 elementos
* 1.000.000 elementos

Os tempos de execução foram medidos separadamente para cada estrutura e linguagem, e os resultados foram utilizados na análise de desempenho da apresentação.

---

### 📌 Conclusões e Recomendações

* Use Shell Sort com Knuth para dados médios (1K–100K elementos) em linguagens compiladas (C/C++).

* Evite estruturas dinâmicas (listas encadeadas) se performance for crítica.

* Para grandes datasets (>1M elementos), algoritmos como QuickSort ou MergeSort são mais adequados.

---

### Referências
* CORMEN, T. H. et al. Introduction to Algorithms. 3. ed. Cambridge: MIT Press, 2009.
* KNUTH, D. E. The Art of Computer Programming. Volume 3.

---

Projeto desenvolvido por: Otávio Hiratsuka, Fabrício Quintilhiano, Jean Pedro Oliveira, Deivy Rossi.

*CEFET-MG, Divinópolis — 2025*


