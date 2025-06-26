import json
import os
from leitura import ler_csv
from estruturas_lineares import testar_estruturas_lineares
from estruturas_dinamicas import testar_estruturas_dinamicas

def main():
    with open('config.json') as config_file:
        config = json.load(config_file)

    arquivo = config['arquivo']
    pasta_saida = config.get('saida', '.')

    os.makedirs(pasta_saida, exist_ok=True)

    tamanhos = [100, 1000, 10000, 100000,1000000]
    repeticoes = 10

    resultados_lineares = {tam: {'lista': 0, 'pilha': 0, 'fila': 0} for tam in tamanhos}
    resultados_dinamicas = {tam: {'lista_ligada': 0, 'pilha_ligada': 0, 'fila_ligada': 0} for tam in tamanhos}

    for tam in tamanhos:
        print(f"Testando com {tam} dados...")
        for _ in range(repeticoes):
            dados = ler_csv(arquivo, tam)

            tempos_lineares = testar_estruturas_lineares(dados)
            tempos_dinamicas = testar_estruturas_dinamicas(dados)

            for nome, tempo in tempos_lineares.items():
                resultados_lineares[tam][nome] += tempo

            for nome, tempo in tempos_dinamicas.items():
                resultados_dinamicas[tam][nome] += tempo

    with open(f'{pasta_saida}/lineares.txt', 'w') as f:
        for tam in tamanhos:
            f.write(f"Tamanho: {tam}\n")
            for nome in resultados_lineares[tam]:
                media = resultados_lineares[tam][nome] / repeticoes
                f.write(f"{nome}: {media:.3f} ms\n")
            f.write("\n")

    with open(f'{pasta_saida}/dinamicas.txt', 'w') as f:
        for tam in tamanhos:
            f.write(f"Tamanho: {tam}\n")
            for nome in resultados_dinamicas[tam]:
                media = resultados_dinamicas[tam][nome] / repeticoes
                f.write(f"{nome}: {media:.3f} ms\n")
            f.write("\n")

    print(f"Testes concluídos. Resultados salvos em {pasta_saida}/lineares.txt e dinamicas.txt.")

if __name__ == "__main__":
    main()
