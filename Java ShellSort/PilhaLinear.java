public class PilhaLinear {
    private double[] dados;
    private int topo;

    public PilhaLinear(int capacidade) {
        dados = new double[capacidade];
        topo = -1;
    }

    public boolean push(double valor) {
        if (topo < dados.length - 1) {
            dados[++topo] = valor;
            return true;
        }
        return false;
    }

    public double pop() {
        return dados[topo--];
    }

    public int tamanho() {
        return topo + 1;
    }

    public void limpar() {
        topo = -1;
    }

    public double[] toArray() {
        double[] array = new double[topo + 1];
        for (int i = 0; i <= topo; i++) {
            array[i] = dados[i];
        }
        return array;
    }

    public void imprimir() {
        for (int i = topo; i >= 0; i--) {
            System.out.print(dados[i] + " ");
        }
        System.out.println();
    }
}
