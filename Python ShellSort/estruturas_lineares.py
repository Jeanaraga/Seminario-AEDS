import time
from shell_sort import shell_sort
from collections import deque

def testar_estruturas_lineares(dados):
    tempos = {}

    # Lista
    lista = list(dados)
    inicio = time.time()
    shell_sort(lista)
    fim = time.time()
    tempos['lista'] = (fim - inicio) * 1000

    # Pilha
    pilha = list(dados)
    inicio = time.time()
    shell_sort(pilha)
    fim = time.time()
    tempos['pilha'] = (fim - inicio) * 1000

    # Fila
    fila = deque(dados)
    lista_fila = list(fila)
    inicio = time.time()
    shell_sort(lista_fila)
    fim = time.time()
    tempos['fila'] = (fim - inicio) * 1000

    return tempos
