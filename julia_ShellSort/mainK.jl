using CSV
using DataFrames
using Dates

########### Função Shell Sort com Sequência de Knuth ###########
function shell_sort_knuth!(arr)
    n = length(arr)
    
    # Gerar sequência de Knuth (1, 4, 13, 40, 121, ...)
    gap = 1
    while gap < div(n, 3)
        gap = 3 * gap + 1
    end

    # Aplicar Shell Sort com gaps de Knuth
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
        gap = div(gap, 3)  # Reduz o gap na razão 1/3
    end
    return arr
end

########### Estruturas Lineares ###########

# ------ Fila ------
struct Fila
    dados::Vector{Float64}
end

function push_fila!(fila::Fila, valor::Float64)
    push!(fila.dados, valor)
end

function pop_fila!(fila::Fila)
    isempty(fila.dados) ? nothing : popfirst!(fila.dados)
end

# ------ Pilha ------
struct Pilha
    dados::Vector{Float64}
end

function push_pilha!(pilha::Pilha, valor::Float64)
    push!(pilha.dados, valor)
end

function pop_pilha!(pilha::Pilha)
    isempty(pilha.dados) ? nothing : pop!(pilha.dados)
end

# ------ Lista ------
struct Lista
    dados::Vector{Float64}
end

function add_lista!(lista::Lista, valor::Float64)
    push!(lista.dados, valor)
end

########### Estruturas Dinâmicas ###########

# ------ Nó da Lista Encadeada ------
mutable struct Node
    valor::Float64
    proximo::Union{Node, Nothing}
end

# ------ Lista Encadeada ------
mutable struct ListaEncadeada
    cabeca::Union{Node, Nothing}
end

ListaEncadeada() = ListaEncadeada(nothing)

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

function lista_encadeada_para_array(lista::ListaEncadeada)
    arr = Float64[]
    atual = lista.cabeca
    while atual !== nothing
        push!(arr, atual.valor)
        atual = atual.proximo
    end
    return arr
end

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

########### Função Principal ###########
function executar_shellsort_em_estruturas(caminho_csv::String, quantidade::Int)
    # Ler dados
    println("Lendo dados de $caminho_csv...")
    df = CSV.read(caminho_csv, DataFrame; limit=quantidade)
    dados = Vector{Float64}(df.rating)
    num_dados = length(dados)
    println("✅ Dados carregados ($num_dados registros)")

    ################## Estruturas Lineares ##################
    println("\n🔵 Processando ESTRUTURAS LINEARES...")
    tempo_inicial = now()

    # Inicializar estruturas
    fila = Fila([])
    pilha = Pilha([])
    lista = Lista([])

    # Popular estruturas
    for v in dados
        push_fila!(fila, v)
        push_pilha!(pilha, v)
        add_lista!(lista, v)
    end

    # Ordenar com Shell Sort (Knuth)
    dados_fila = copy(fila.dados)
    dados_pilha = copy(pilha.dados)
    dados_lista = copy(lista.dados)

    println("\n⏱️  Tempos de ordenação (Knuth):")
    @time shell_sort_knuth!(dados_fila)
    @time shell_sort_knuth!(dados_pilha)
    @time shell_sort_knuth!(dados_lista)

    tempo_linear = now() - tempo_inicial

    # Salvar resultados
    open("resultados_lineares_knuth.csv", "w") do io
        write(io, "estrutura,dados_ordenados\n")
        write(io, "fila,$(join(dados_fila, ","))\n")
        write(io, "pilha,$(join(dados_pilha, ","))\n")
        write(io, "lista,$(join(dados_lista, ","))\n")
        write(io, "tempo_total,$tempo_linear\n")
        write(io, "quantidade_dados,$num_dados\n")
    end

    ################## Estruturas Dinâmicas ##################
    println("\n🟢 Processando ESTRUTURA DINÂMICA (Lista Encadeada)...")
    tempo_inicial = now()

    lista_encadeada = ListaEncadeada()
    for v in dados
        add_lista_encadeada!(lista_encadeada, v)
    end

    dados_dinamicos = lista_encadeada_para_array(lista_encadeada)
    @time shell_sort_knuth!(dados_dinamicos)
    lista_encadeada_ordenada = array_para_lista_encadeada!(dados_dinamicos)

    tempo_dinamico = now() - tempo_inicial

    open("resultados_dinamicos_knuth.csv", "w") do io
        write(io, "estrutura,dados_ordenados\n")
        write(io, "lista_encadeada,$(join(dados_dinamicos, ","))\n")
        write(io, "tempo_total,$tempo_dinamico\n")
        write(io, "quantidade_dados,$num_dados\n")
    end

    ################## Resumo ##################
    println("\n📝 RESULTADOS:")
    println("- Arquivos gerados:")
    println("  • resultados_lineares_knuth.csv")
    println("  • resultados_dinamicos_knuth.csv")
    println("- Tempo total:")
    println("  ⏳ Estruturas lineares: $tempo_linear")
    println("  ⏳ Lista encadeada: $tempo_dinamico")
    println("  📊 Dados processados: $num_dados registros")
end

########### Execução ###########
println("\n🚀 Iniciando execução...")
executar_shellsort_em_estruturas("ratings.csv", 100)  # Altere a quantidade conforme necessário
println("\n✅ Programa concluído com sucesso!")