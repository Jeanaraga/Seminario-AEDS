import java.io.BufferedReader;
import java.io.FileReader;

public class LerRatings {

public static double[] lerRatingsLinear(String caminhoArquivo, int limite) {
        double[] ratings = new double[limite];
        int contador = 0;

        try (BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo))) {
            String linha = br.readLine(); // pula o cabeçalho
            while ((linha = br.readLine()) != null && contador < limite) {
                String[] partes = linha.split(",");
                if (partes.length >= 3) {
                    try {
                        double nota = Double.parseDouble(partes[2]);
                        ratings[contador++] = nota;
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

public static PilhaLinear lerRatingsPilhaLinear(String caminho, int limite) {
        PilhaLinear pilha = new PilhaLinear(limite);

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

    public static FilaLinear lerRatingsFilaLinear(String nomeArquivo, int limite) {
        FilaLinear fila = new FilaLinear(limite);

        try (BufferedReader br = new BufferedReader(new FileReader(nomeArquivo))) {
            String linha = br.readLine(); // pular cabeçalho
            int count = 0;

            while ((linha = br.readLine()) != null && count < limite) {
                String[] partes = linha.split(",");
                if (partes.length >= 3) {
                    try {
                        double rating = Double.parseDouble(partes[2]);
                        fila.enfileirar(rating);
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
