import time
from shell_sort import shell_sort


class Node:
    def __init__(self, valor):
        self.valor = valor
        self.prox = None


class ListaLigada:
    def __init__(self):
        self.inicio = None

    def append(self, valor):
        novo = Node(valor)
        if not self.inicio:
            self.inicio = novo
        else:
            atual = self.inicio
            while atual.prox:
                atual = atual.prox
            atual.prox = novo

    def to_list(self):
        atual = self.inicio
        resultado = []
        while atual:
            resultado.append(atual.valor)
            atual = atual.prox
        return resultado

    def from_list(self, lista):
        self.inicio = None
        for item in lista:
            self.append(item)

    def sort(self):
        lista = self.to_list()
        shell_sort(lista)
        self.from_list(lista)


class PilhaLigada:
    def __init__(self):
        self.topo = None

    def push(self, valor):
        novo = Node(valor)
        novo.prox = self.topo
        self.topo = novo

    def to_list(self):
        atual = self.topo
        resultado = []
        while atual:
            resultado.append(atual.valor)
            atual = atual.prox
        return resultado

    def from_list(self, lista):
        self.topo = None
        for item in reversed(lista):
            self.push(item)

    def sort(self):
        lista = self.to_list()
        shell_sort(lista)
        self.from_list(lista)


class FilaLigada:
    def __init__(self):
        self.inicio = None
        self.fim = None

    def enqueue(self, valor):
        novo = Node(valor)
        if not self.fim:
            self.inicio = novo
            self.fim = novo
        else:
            self.fim.prox = novo
            self.fim = novo

    def to_list(self):
        atual = self.inicio
        resultado = []
        while atual:
            resultado.append(atual.valor)
            atual = atual.prox
        return resultado

    def from_list(self, lista):
        self.inicio = None
        self.fim = None
        for item in lista:
            self.enqueue(item)

    def sort(self):
        lista = self.to_list()
        shell_sort(lista)
        self.from_list(lista)


def testar_estruturas_dinamicas(dados):
    tempos = {}

    # Lista ligada
    lista = ListaLigada()
    for d in dados:
        lista.append(d)
    inicio = time.time()
    lista.sort()
    fim = time.time()
    tempos['lista_ligada'] = (fim - inicio) * 1000

    # Pilha ligada
    pilha = PilhaLigada()
    for d in dados:
        pilha.push(d)
    inicio = time.time()
    pilha.sort()
    fim = time.time()
    tempos['pilha_ligada'] = (fim - inicio) * 1000

    # Fila ligada
    fila = FilaLigada()
    for d in dados:
        fila.enqueue(d)
    inicio = time.time()
    fila.sort()
    fim = time.time()
    tempos['fila_ligada'] = (fim - inicio) * 1000

    return tempos
