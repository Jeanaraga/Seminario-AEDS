import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class Main {
    public static void main(String[] args) {
        String arquivo = "ratings.csv";
        int quantidade = 1000000;



        // PilhaLinear pilhaLinear = LerRatings.lerRatingsPilhaLinear("ratings.csv", 100);
        // ShellSortLinear.ordenarPilha(pilhaLinear);
        // System.out.println("Ordenado (Pilha Linear):");
        // pilhaLinear.imprimir();

        // // Pilha Dinâmica
        // Stack<Double> pilhaDinamica = LeitorRatingsDinamico.lerRatingsPilhaDinamica("ratings.csv", 100);
        // ShellSortDinamico.ordenarPilha(pilhaDinamica);
        // System.out.println("Ordenado (Pilha Dinâmica):");
        // while (!pilhaDinamica.isEmpty()) {
        //     System.out.print(pilhaDinamica.pop() + " ");
        // }
        // System.out.println();

        // LISTA 
        // Leitura fora do loop
        // double[] ratingsOriginalArray = LerRatings.lerRatingsLinear(arquivo, quantidade);
        // List<Double> ratingsOriginalLista = LeitorRatingsDinamico.lerRatingsDinamico(arquivo, quantidade);

        // double somaTempoArray = 0;
        // double somaTempoLista = 0;

        // for (int i = 0; i < 100; i++) {  
            
        //     long inicioArray = System.nanoTime();
        //     ShellSortLinear.ordenar(ratingsOriginalArray);
        //     long fimArray = System.nanoTime();
        //     somaTempoArray += (fimArray - inicioArray) / 1_000_000.0;
            
        //     long inicioLista = System.nanoTime();
        //     ShellSortDinamico.ordenar(ratingsOriginalLista);
        //     long fimLista = System.nanoTime();
        //     somaTempoLista += (fimLista - inicioLista) / 1_000_000.0;
        // }

        // System.out.printf("Tempo médio de ordenação do array: %.3f ms%n", somaTempoArray / 100);
        // System.out.printf("Tempo médio de ordenação da lista: %.3f ms%n", somaTempoLista / 100);

        // // PILHA
        // PilhaLinear pilha = LerRatings.lerRatingsPilhaLinear(arquivo, quantidade);
        // Stack<Double> pilhaStack = LeitorRatingsDinamico.lerRatingsPilhaDinamica(arquivo, quantidade);

        // double somaTempoPilha = 0;
        // double somaTempoPilhaStack = 0;

        // for (int i = 0; i < 100; i++) {
        //     long inicioPilha = System.nanoTime();
        //     ShellSortLinear.ordenarPilha(pilha);
        //     long fimPilha = System.nanoTime();
        //     somaTempoPilha += (fimPilha - inicioPilha) / 1_000_000.0;

        //     long inicioPilhaStack = System.nanoTime();
        //     ShellSortDinamico.ordenarPilha(pilhaStack);
        //     long fimPilhaStack = System.nanoTime();
        //     somaTempoPilhaStack += (fimPilhaStack - inicioPilhaStack) / 1_000_000.0;
        // }

        // System.out.printf("Tempo médio de ordenação da pilha linear: %.3f ms%n", somaTempoPilha / 100);
        // System.out.printf("Tempo médio de ordenação da pilha dinâmica: %.3f ms%n", somaTempoPilhaStack / 100);

        // // FILA
        FilaLinear fila = LerRatings.lerRatingsFilaLinear(arquivo, quantidade);
        Queue<Double> filaQueue = LeitorRatingsDinamico.lerRatingsFila(arquivo, quantidade);

        double somaTempoFila = 0;
        double somaTempoFilaQueue = 0;

        for (int i = 0; i < 100; i++) {
            long inicioFila = System.nanoTime();
            ShellSortLinear.ordenarFila(fila);
            long fimFila = System.nanoTime();
            somaTempoFila += (fimFila - inicioFila) / 1_000_000.0;

            long inicioFilaQueue = System.nanoTime();
            ShellSortDinamico.ordenarFila(filaQueue);
            long fimFilaQueue = System.nanoTime();
            somaTempoFilaQueue += (fimFilaQueue - inicioFilaQueue) / 1_000_000.0;
        }

        System.out.printf("Tempo médio de ordenação da fila linear: %.3f ms%n", somaTempoFila / 100);
        System.out.printf("Tempo médio de ordenação da fila dinâmica: %.3f ms%n", somaTempoFilaQueue / 100);
    }
}
