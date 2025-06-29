import time
import tracemalloc
from shell_sort import shell_sort
from collections import deque

def testar_estruturas_lineares(dados):
    resultados = {}

    # Lista
    tracemalloc.start()
    lista = list(dados)
    inicio = time.time()
    shell_sort(lista)
    fim = time.time()
    memoria = tracemalloc.get_traced_memory()[1] / 1024
    tracemalloc.stop()
    resultados['lista'] = {'tempo': (fim - inicio) * 1000, 'memoria': memoria}

    # Pilha
    tracemalloc.start()
    pilha = list(dados)
    inicio = time.time()
    shell_sort(pilha)
    fim = time.time()
    memoria = tracemalloc.get_traced_memory()[1] / 1024
    tracemalloc.stop()
    resultados['pilha'] = {'tempo': (fim - inicio) * 1000, 'memoria': memoria}

    # Fila
    tracemalloc.start()
    fila = deque(dados)
    lista_fila = list(fila)
    inicio = time.time()
    shell_sort(lista_fila)
    fim = time.time()
    memoria = tracemalloc.get_traced_memory()[1] / 1024
    tracemalloc.stop()
    resultados['fila'] = {'tempo': (fim - inicio) * 1000, 'memoria': memoria}

    return resultados
