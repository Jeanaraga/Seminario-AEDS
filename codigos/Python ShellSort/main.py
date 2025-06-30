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

    resultados_lineares = {tam: {'lista': [], 'pilha': [], 'fila': []} for tam in tamanhos}
    resultados_dinamicas = {tam: {'lista_ligada': [], 'pilha_ligada': [], 'fila_ligada': []} for tam in tamanhos}

    for tam in tamanhos:
        print(f"Testando com {tam} dados...")
        for _ in range(repeticoes):
            dados = ler_csv(arquivo, tam)

            tempos_lineares = testar_estruturas_lineares(dados)
            tempos_dinamicas = testar_estruturas_dinamicas(dados)

            for nome, info in tempos_lineares.items():
                resultados_lineares[tam][nome].append(info)

            for nome, info in tempos_dinamicas.items():
                resultados_dinamicas[tam][nome].append(info)

    with open(f'{pasta_saida}/lineares.txt', 'w') as f:
        for tam in tamanhos:
            f.write(f"Tamanho: {tam}\n")
            for nome in resultados_lineares[tam]:
                tempos = [r['tempo'] for r in resultados_lineares[tam][nome]]
                memorias = [r['memoria'] for r in resultados_lineares[tam][nome]]
                tempo_medio = sum(tempos) / repeticoes
                memoria_media = sum(memorias) / repeticoes
                f.write(f"{nome}: {tempo_medio:.3f} ms | {memoria_media:.1f} KB\n")
            f.write("\n")

    with open(f'{pasta_saida}/dinamicas.txt', 'w') as f:
        for tam in tamanhos:
            f.write(f"Tamanho: {tam}\n")
            for nome in resultados_dinamicas[tam]:
                tempos = [r['tempo'] for r in resultados_dinamicas[tam][nome]]
                memorias = [r['memoria'] for r in resultados_dinamicas[tam][nome]]
                tempo_medio = sum(tempos) / repeticoes
                memoria_media = sum(memorias) / repeticoes
                f.write(f"{nome}: {tempo_medio:.3f} ms | {memoria_media:.1f} KB\n")
            f.write("\n")

    print(f"Testes concluídos. Resultados salvos em {pasta_saida}/lineares.txt e dinamicas.txt.")

if __name__ == "__main__":
    main()
