## 📚 Seminário – Algoritmo de Ordenação: Shell Sort

Este repositório contém os materiais e implementações utilizados no seminário sobre o algoritmo **Shell Sort**, conforme exigido no trabalho em equipe da disciplina de Algoritmos.

---

### 📂 Organização do Repositório

* Cada implementação do Shell Sort está organizada por linguagem:

  * `Java-ShellSort/`

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
