import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class UsoMem {
    public static void main(String[] args) {
        String arquivo = "datasets/ratings.csv";
        int quantidade = 100000;

        Runtime runtime = Runtime.getRuntime();

        // LISTA
        double[] ratingsOriginalArray = LerRatings.lerRatingsLinear(arquivo, quantidade);
        List<Double> ratingsOriginalLista = LeitorRatingsDinamico.lerRatingsDinamico(arquivo, quantidade);

        System.gc();
        double[] copiaArray = ratingsOriginalArray.clone();
        long memAntesArray = runtime.totalMemory() - runtime.freeMemory();
        ShellSortLinear.ordenar(copiaArray);
        long memDepoisArray = runtime.totalMemory() - runtime.freeMemory();
        double usoMemoriaArray = (memDepoisArray - memAntesArray) / (1024.0 * 1024.0);
        System.out.printf("Uso de memória do array: %.6f MB%n", usoMemoriaArray);

        System.gc();
        List<Double> copiaLista = new ArrayList<>(ratingsOriginalLista);
        long memAntesLista = runtime.totalMemory() - runtime.freeMemory();
        ShellSortDinamico.ordenar(copiaLista);
        long memDepoisLista = runtime.totalMemory() - runtime.freeMemory();
        double usoMemoriaLista = (memDepoisLista - memAntesLista) / (1024.0 * 1024.0);
        System.out.printf("Uso de memória da lista: %.6f MB%n", usoMemoriaLista);

        // PILHA
        PilhaLinear pilhaOriginal = LerRatings.lerRatingsPilhaLinear(arquivo, quantidade);
        Stack<Double> pilhaStackOriginal = LeitorRatingsDinamico.lerRatingsPilhaDinamica(arquivo, quantidade);

        System.gc();
        PilhaLinear copiaPilha = new PilhaLinear(quantidade);
        for (double val : pilhaOriginal.toArray()) copiaPilha.push(val);
        long memAntesPilha = runtime.totalMemory() - runtime.freeMemory();
        ShellSortLinear.ordenarPilha(copiaPilha);
        long memDepoisPilha = runtime.totalMemory() - runtime.freeMemory();
        double usoMemoriaPilha = (memDepoisPilha - memAntesPilha) / (1024.0 * 1024.0);
        System.out.printf("Uso de memória da pilha linear: %.6f MB%n", usoMemoriaPilha);

        System.gc();
        Stack<Double> copiaStack = new Stack<>();
        copiaStack.addAll(pilhaStackOriginal);
        long memAntesStack = runtime.totalMemory() - runtime.freeMemory();
        ShellSortDinamico.ordenarPilha(copiaStack);
        long memDepoisStack = runtime.totalMemory() - runtime.freeMemory();
        double usoMemoriaStack = (memDepoisStack - memAntesStack) / (1024.0 * 1024.0);
        System.out.printf("Uso de memória da pilha dinâmica: %.6f MB%n", usoMemoriaStack);

        // FILA
        FilaLinear filaOriginal = LerRatings.lerRatingsFilaLinear(arquivo, quantidade);
        Queue<Double> filaQueueOriginal = LeitorRatingsDinamico.lerRatingsFila(arquivo, quantidade);

        System.gc();
        FilaLinear copiaFila = new FilaLinear(quantidade);
        for (double val : filaOriginal.toArray()) copiaFila.enfileirar(val);
        long memAntesFila = runtime.totalMemory() - runtime.freeMemory();
        ShellSortLinear.ordenarFila(copiaFila);
        long memDepoisFila = runtime.totalMemory() - runtime.freeMemory();
        double usoMemoriaFila = (memDepoisFila - memAntesFila) / (1024.0 * 1024.0);
        System.out.printf("Uso de memória da fila linear: %.6f MB%n", usoMemoriaFila);

        System.gc();
        Queue<Double> copiaQueue = new java.util.LinkedList<>(filaQueueOriginal);
        long memAntesQueue = runtime.totalMemory() - runtime.freeMemory();
        ShellSortDinamico.ordenarFila(copiaQueue);
        long memDepoisQueue = runtime.totalMemory() - runtime.freeMemory();
        double usoMemoriaQueue = (memDepoisQueue - memAntesQueue) / (1024.0 * 1024.0);
        System.out.printf("Uso de memória da fila dinâmica: %.6f MB%n", usoMemoriaQueue);
    }
}
