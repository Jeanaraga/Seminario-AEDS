import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class Main {
    public static void main(String[] args) {
        String arquivo = "datasets/ratings.csv";
        int quantidade = 100;

        // LISTA
        double[] ratingsOriginalArray = LerRatings.lerRatingsLinear(arquivo, quantidade);
        List<Double> ratingsOriginalLista = LeitorRatingsDinamico.lerRatingsDinamico(arquivo, quantidade);

        double somaTempoArray = 0;
        double somaTempoLista = 0;

        for (int i = 0; i < 100; i++) {

            double[] copiaArray = ratingsOriginalArray.clone();
            List<Double> copiaLista = new ArrayList<>(ratingsOriginalLista);

            long inicioArray = System.nanoTime();
            ShellSortLinear.ordenar(copiaArray);
            long fimArray = System.nanoTime();
            somaTempoArray += (fimArray - inicioArray) / 1_000_000.0;

            long inicioLista = System.nanoTime();
            ShellSortDinamico.ordenar(copiaLista);
            long fimLista = System.nanoTime();
            somaTempoLista += (fimLista - inicioLista) / 1_000_000.0;
        }

        System.out.printf("Tempo médio de ordenação do array: %.3f ms%n", somaTempoArray / 100);
        System.out.printf("Tempo médio de ordenação da lista: %.3f ms%n", somaTempoLista / 100);


        // PILHA
        // PilhaLinear pilhaOriginal = LerRatings.lerRatingsPilhaLinear(arquivo, quantidade);
        // Stack<Double> pilhaStackOriginal = LeitorRatingsDinamico.lerRatingsPilhaDinamica(arquivo, quantidade);

        // double somaTempoPilha = 0;
        // double somaTempoPilhaStack = 0;

        // for (int i = 0; i < 100; i++) {
        //     PilhaLinear copiaPilha = new PilhaLinear(quantidade);
        //     for (double val : pilhaOriginal.toArray()) {
        //         copiaPilha.push(val);
        //     }

        //     Stack<Double> copiaPilhaStack = new Stack<>();
        //     copiaPilhaStack.addAll(pilhaStackOriginal);

        //     long inicioPilha = System.nanoTime();
        //     ShellSortLinear.ordenarPilha(copiaPilha);
        //     long fimPilha = System.nanoTime();
        //     somaTempoPilha += (fimPilha - inicioPilha) / 1_000_000.0;

        //     long inicioPilhaStack = System.nanoTime();
        //     ShellSortDinamico.ordenarPilha(copiaPilhaStack);
        //     long fimPilhaStack = System.nanoTime();
        //     somaTempoPilhaStack += (fimPilhaStack - inicioPilhaStack) / 1_000_000.0;
        // }

        // System.out.printf("Tempo médio de ordenação da pilha linear: %.3f ms%n", somaTempoPilha / 100);
        // System.out.printf("Tempo médio de ordenação da pilha dinâmica: %.3f ms%n", somaTempoPilhaStack / 100);

        // FILA
        // FilaLinear filaOriginal = LerRatings.lerRatingsFilaLinear(arquivo, quantidade);
        // Queue<Double> filaQueueOriginal = LeitorRatingsDinamico.lerRatingsFila(arquivo, quantidade);

        // double somaTempoFila = 0;
        // double somaTempoFilaQueue = 0;

        // for (int i = 0; i < 100; i++) {
        //     FilaLinear copiaFila = new FilaLinear(quantidade);
        //     for (double val : filaOriginal.toArray()) {
        //         copiaFila.enfileirar(val);
        //     }

        //     Queue<Double> copiaFilaQueue = new java.util.LinkedList<>(filaQueueOriginal);

        //     long inicioFila = System.nanoTime();
        //     ShellSortLinear.ordenarFila(copiaFila);
        //     long fimFila = System.nanoTime();
        //     somaTempoFila += (fimFila - inicioFila) / 1_000_000.0;

        //     long inicioFilaQueue = System.nanoTime();
        //     ShellSortDinamico.ordenarFila(copiaFilaQueue);
        //     long fimFilaQueue = System.nanoTime();
        //     somaTempoFilaQueue += (fimFilaQueue - inicioFilaQueue) / 1_000_000.0;
        // }

        // System.out.printf("Tempo médio de ordenação da fila linear: %.3f ms%n", somaTempoFila / 100);
        // System.out.printf("Tempo médio de ordenação da fila dinâmica: %.3f ms%n", somaTempoFilaQueue / 100);

    }
}
