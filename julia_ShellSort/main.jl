using CSV
using DataFrames
using Dates
using Pkg

########### Função Shell Sort ###########
function shell_sort!(arr)
    n = length(arr)
    gap = div(n, 2)

    while gap > 0
        for i in gap+1:n
            temp = arr[i]
            j = i
            while j > gap && arr[j - gap] > temp
                arr[j] = arr[j - gap]
                j -= gap
            end
            arr[j] = temp
        end
        gap = div(gap, 2)
    end
    return arr
end

########### Estruturas Lineares ###########

# ---------- Fila ----------
struct Fila
    dados::Vector{Float64}
end

# Inserir elemento no final da fila
function push_fila!(fila::Fila, valor::Float64)
    push!(fila.dados, valor)
end

# Remover elemento do início da fila
function pop_fila!(fila::Fila)
    isempty(fila.dados) ? nothing : popfirst!(fila.dados)
end

# ---------- Pilha ----------
struct Pilha
    dados::Vector{Float64}
end

# Inserir elemento no topo da pilha
function push_pilha!(pilha::Pilha, valor::Float64)
    push!(pilha.dados, valor)
end

# Remover elemento do topo da pilha
function pop_pilha!(pilha::Pilha)
    isempty(pilha.dados) ? nothing : pop!(pilha.dados)
end

# ---------- Lista ----------
struct Lista
    dados::Vector{Float64}
end

# Inserir elemento no final da lista
function add_lista!(lista::Lista, valor::Float64)
    push!(lista.dados, valor)
end

########### Estruturas Dinâmicas ###########

# Nó da lista encadeada
mutable struct Node
    valor::Float64
    proximo::Union{Node, Nothing}
end

# Lista Encadeada
mutable struct ListaEncadeada
    cabeca::Union{Node, Nothing}
end

# Criar uma nova lista encadeada vazia
ListaEncadeada() = ListaEncadeada(nothing)

# Adicionar elemento no final da lista encadeada
function add_lista_encadeada!(lista::ListaEncadeada, valor::Float64)
    novo_no = Node(valor, nothing)
    
    if lista.cabeca === nothing
        lista.cabeca = novo_no
    else
        atual = lista.cabeca
        while atual.proximo !== nothing
            atual = atual.proximo
        end
        atual.proximo = novo_no
    end
end

# Converter lista encadeada para array
function lista_encadeada_para_array(lista::ListaEncadeada)
    arr = Float64[]
    atual = lista.cabeca
    
    while atual !== nothing
        push!(arr, atual.valor)
        atual = atual.proximo
    end
    
    return arr
end

# Converter array para lista encadeada
function array_para_lista_encadeada!(arr::Vector{Float64})
    if isempty(arr)
        return ListaEncadeada(nothing)
    end
    
    lista = ListaEncadeada(Node(arr[1], nothing))
    atual = lista.cabeca
    
    for i in 2:length(arr)
        novo_no = Node(arr[i], nothing)
        atual.proximo = novo_no
        atual = novo_no
    end
    
    return lista
end

# ... (todo o código anterior permanece igual até a função principal)

########### Função Principal ###########
function executar_shellsort_em_estruturas(caminho_csv::String, quantidade::Int)

    # Ler os dados
    println("Lendo dados...")
    df = CSV.read(caminho_csv, DataFrame; limit=quantidade)
    dados = Vector{Float64}(df.rating)
    num_dados = length(dados)  # Número real de dados lidos

    ################## Lineares ##################
    println("Trabalhando com estruturas LINEARES...")
    tempo_inicial = now()

    fila = Fila([])
    pilha = Pilha([])
    lista = Lista([])

    for v in dados
        push_fila!(fila, v)
        push_pilha!(pilha, v)
        add_lista!(lista, v)
    end

    dados_fila = copy(fila.dados)
    dados_pilha = copy(pilha.dados)
    dados_lista = copy(lista.dados)

    @time shell_sort!(dados_fila)
    @time shell_sort!(dados_pilha)
    @time shell_sort!(dados_lista)

    tempo_linear = now() - tempo_inicial

    open("resultados_lineares.csv", "w") do io
        write(io, "fila, $(join(dados_fila, ","))\n")
        write(io, "pilha, $(join(dados_pilha, ","))\n")
        write(io, "lista, $(join(dados_lista, ","))\n")
        write(io, "tempo_total, $tempo_linear\n")
        write(io, "quantidade_dados, $num_dados\n")  # Adiciona quantidade ao arquivo
    end


    ################## Dinâmicas ##################
    println("Trabalhando com estruturas DINÂMICAS...")
    tempo_inicial = now()

    lista_encadeada = ListaEncadeada()

    for v in dados
        add_lista_encadeada!(lista_encadeada, v)
    end

    dados_dinamicos = lista_encadeada_para_array(lista_encadeada)

    @time shell_sort!(dados_dinamicos)

    lista_encadeada_ordenada = array_para_lista_encadeada!(dados_dinamicos)

    tempo_dinamico = now() - tempo_inicial

    open("resultados_dinamicos.csv", "w") do io
        write(io, "lista_encadeada, $(join(dados_dinamicos, ","))\n")
        write(io, "tempo_total, $tempo_dinamico\n")
        write(io, "quantidade_dados, $num_dados\n")  # Adiciona quantidade ao arquivo
    end


    println("\n✔️ Processamento concluído.")
    println("📊 Quantidade de dados processados: $num_dados")
    println("⏳ Tempo Estruturas Lineares: $tempo_linear")
    println("⏳ Tempo Estrutura Dinâmica: $tempo_dinamico")
end

########### 🚀 Executar ###########
# 🛠️ Altere o caminho e a quantidade conforme desejar
executar_shellsort_em_estruturas("ratings.csv", 1000)