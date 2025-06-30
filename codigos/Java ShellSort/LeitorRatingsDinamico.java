import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;
import java.io.BufferedReader;
import java.io.FileReader;

public class LeitorRatingsDinamico {
    public static List<Double> lerRatingsDinamico(String caminhoArquivo, int limite) {
        List<Double> ratings = new ArrayList<>();
        int contador = 0;

        try (BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo))) {
            String linha = br.readLine(); // pula o cabeçalho
            while ((linha = br.readLine()) != null && contador < limite) {
                String[] partes = linha.split(",");
                if (partes.length >= 3) {
                    try {
                        double nota = Double.parseDouble(partes[2]);
                        ratings.add(nota);
                        contador++;
                    } catch (NumberFormatException e) {
                        System.err.println("Erro ao converter: " + partes[2]);
                    }
                }
            }
        } catch (Exception e) {
            System.err.println("Erro na leitura: " + e.getMessage());
        }

        return ratings;
    }

    public static Stack<Double> lerRatingsPilhaDinamica(String caminho, int limite) {
        Stack<Double> pilha = new Stack<>();

        try (BufferedReader br = new BufferedReader(new FileReader(caminho))) {
            String linha = br.readLine(); // pula o cabeçalho
            int contador = 0;

            while ((linha = br.readLine()) != null && contador < limite) {
                String[] partes = linha.split(",");
                if (partes.length >= 3) {
                    double rating = Double.parseDouble(partes[2]);
                    pilha.push(rating);
                    contador++;
                }
            }
        } catch (Exception e) {
            System.err.println("Erro: " + e.getMessage());
        }

        return pilha;
    }

    public static Queue<Double> lerRatingsFila(String nomeArquivo, int limite) {
        Queue<Double> fila = new LinkedList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(nomeArquivo))) {
            String linha = br.readLine(); // cabeçalho
            int count = 0;

            while ((linha = br.readLine()) != null && count < limite) {
                String[] partes = linha.split(",");
                if (partes.length >= 3) {
                    try {
                        double rating = Double.parseDouble(partes[2]);
                        fila.add(rating);
                        count++;
                    } catch (NumberFormatException e) {
                        System.err.println("Erro na conversão: " + linha);
                    }
                }
            }
        } catch (Exception e) {
            System.err.println("Erro na leitura: " + e.getMessage());
        }

        return fila;
    }
}
