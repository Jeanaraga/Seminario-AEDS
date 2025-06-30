import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class ShellSortDinamico {

    public static void ordenar(List<Double> lista) {
        int n = lista.size();
        int gap = 1;

        // Geração da sequência de Knuth
        while (gap < n / 3) {
            gap = gap * 3 + 1;
        }

        while (gap > 0) {
            for (int i = gap; i < n; i++) {
                double temp = lista.get(i);
                int j = i;

                while (j >= gap && lista.get(j - gap) > temp) {
                    lista.set(j, lista.get(j - gap));
                    j -= gap;
                }

                lista.set(j, temp);
            }
            gap = (gap - 1) / 3;
        }
    }

    public static void ordenarPilha(Stack<Double> pilha) {
        int n = pilha.size();
        Double[] array = pilha.toArray(new Double[0]);

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

        // Reempilha em ordem correta (base com menor valor)
        pilha.clear();
        for (int i = n - 1; i >= 0; i--) {
            pilha.push(array[i]);
        }
    }

    public static void ordenarFila(Queue<Double> fila) {
        Double[] array = fila.toArray(new Double[0]);
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

        fila.clear();
        for (double valor : array) {
            fila.add(valor);
        }
    }
}
