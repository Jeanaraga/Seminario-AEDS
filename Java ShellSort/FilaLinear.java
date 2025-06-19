public class FilaLinear {
    private double[] dados;
    private int inicio, fim, tamanho;

    public FilaLinear(int capacidade) {
        dados = new double[capacidade];
        inicio = 0;
        fim = 0;
        tamanho = 0;
    }

    public boolean enfileirar(double valor) {
        if (tamanho < dados.length) {
            dados[fim] = valor;
            fim = (fim + 1) % dados.length;
            tamanho++;
            return true;
        }
        return false;
    }

    public double desenfileirar() {
        double valor = dados[inicio];
        inicio = (inicio + 1) % dados.length;
        tamanho--;
        return valor;
    }

    public double[] toArray() {
        double[] array = new double[tamanho];
        for (int i = 0; i < tamanho; i++) {
            array[i] = dados[(inicio + i) % dados.length];
        }
        return array;
    }

    public void limpar() {
        inicio = 0;
        fim = 0;
        tamanho = 0;
    }

    public int tamanho() {
        return tamanho;
    }

    public void imprimir() {
        for (int i = 0; i < tamanho; i++) {
            System.out.print(dados[(inicio + i) % dados.length] + " ");
        }
        System.out.println();
    }
}
