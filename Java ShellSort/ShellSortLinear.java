public class ShellSortLinear {

    public static void ordenar(double[] vetor) {
        int n = vetor.length;
        int gap = 1;

        // Inicializa gap com sequência de Knuth
        while (gap < n / 3) {
            gap = gap * 3 + 1;
        }

        while (gap > 0) {
            for (int i = gap; i < n; i++) {
                double temp = vetor[i];
                int j = i;

                while (j >= gap && vetor[j - gap] > temp) {
                    vetor[j] = vetor[j - gap];
                    j -= gap;
                }

                vetor[j] = temp;
            }
            gap = (gap - 1) / 3;
        }
    }

    public static void ordenarPilha(PilhaLinear pilha) {
        int n = pilha.tamanho();
        double[] array = pilha.toArray();

        int gap = 1;
        while (gap < n / 3) {
            gap = gap * 3 + 1;
        }

        while (gap > 0) {
            for (int i = gap; i < n; i++) {
                double temp = array[i];
                int j = i;

                while (j >= gap && array[j - gap] > temp) {
                    array[j] = array[j - gap];
                    j -= gap;
                }

                array[j] = temp;
            }
            gap = (gap - 1) / 3;
        }

        pilha.limpar();
        for (int i = n - 1; i >= 0; i--) {
            pilha.push(array[i]);
        }
    }

    public static void ordenarFila(FilaLinear fila) {
        double[] array = fila.toArray();
        int n = array.length;

        int gap = 1;
        while (gap < n / 3) {
            gap = gap * 3 + 1;
        }

        while (gap > 0) {
            for (int i = gap; i < n; i++) {
                double temp = array[i];
                int j = i;

                while (j >= gap && array[j - gap] > temp) {
                    array[j] = array[j - gap];
                    j -= gap;
                }

                array[j] = temp;
            }
            gap = (gap - 1) / 3;
        }

        fila.limpar();
        for (double valor : array) {
            fila.enfileirar(valor);
        }
    }
}
