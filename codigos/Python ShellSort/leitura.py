import csv
import time

def ler_csv(caminho, quantidade):
    dados = []
    inicio = time.time()
    with open(caminho, 'r', encoding='utf-8') as arquivo:
        leitor = csv.reader(arquivo)
        next(leitor)  # Pula o cabeçalho
        for i, linha in enumerate(leitor):
            if i >= quantidade:
                break
            if len(linha) >= 3:
                try:
                    dados.append(float(linha[2]))  # Lê apenas a terceira coluna (rating)
                    
                except ValueError:
                    continue
    fim = time.time()
    duracao_ms = (fim - inicio) * 1000
    print(f"Tempo de leitura: {duracao_ms:.3f} ms")
    return dados