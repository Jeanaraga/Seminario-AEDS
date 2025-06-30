using CSV
using DataFrames
using Dates
using Base

########### Função Shell Sort com Sequência de Knuth ###########
function shell_sort_knuth!(arr)
    n = length(arr)
    gap = 1
    while gap < div(n, 3)
        gap = 3 * gap + 1
    end
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
        gap = div(gap, 3)
    end
    return arr
end

########### Função para medir tempo e memória com precisão ###########
function medir_tempo_memoria_precisao(funcao::Function)
    # Força garbage collection antes da medição
    GC.gc()
    
    # Mede tempo
    tempo_s = @elapsed resultado = funcao()
    tempo_ms = tempo_s * 1000.0
    
    # Mede memória do resultado
    memoria_bytes = Base.summarysize(resultado)
    
    return tempo_ms, memoria_bytes, resultado
end

function formatar_tempo(tempo_ms)
    if tempo_ms < 0.001
        return "$(round(tempo_ms * 1000, digits=3)) μs"
    else
        return "$(round(tempo_ms, digits=6)) ms"
    end
end

function formatar_memoria(bytes)
    if bytes < 1024
        return "$(bytes) B"
    elseif bytes < 1024^2
        return "$(round(bytes/1024, digits=2)) KB"
    elseif bytes < 1024^3
        return "$(round(bytes/(1024^2), digits=2)) MB"
    else
        return "$(round(bytes/(1024^3), digits=2)) GB"
    end
end

########### Estruturas Lineares ###########
struct Fila
    dados::Vector{Float64}
end

function push_fila!(fila::Fila, valor::Float64)
    push!(fila.dados, valor)
end

function pop_fila!(fila::Fila)
    isempty(fila.dados) ? nothing : popfirst!(fila.dados)
end

struct Pilha
    dados::Vector{Float64}
end

function push_pilha!(pilha::Pilha, valor::Float64)
    push!(pilha.dados, valor)
end

function pop_pilha!(pilha::Pilha)
    isempty(pilha.dados) ? nothing : pop!(pilha.dados)
end

struct Lista
    dados::Vector{Float64}
end

function add_lista!(lista::Lista, valor::Float64)
    push!(lista.dados, valor)
end

########### Estruturas Dinâmicas ###########
mutable struct Node
    valor::Float64
    proximo::Union{Node, Nothing}
end

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

mutable struct FilaEncadeada
    inicio::Union{Node, Nothing}
    fim::Union{Node, Nothing}
end

FilaEncadeada() = FilaEncadeada(nothing, nothing)

function enqueue!(fila::FilaEncadeada, valor::Float64)
    novo_no = Node(valor, nothing)
    if fila.inicio === nothing
        fila.inicio = novo_no
        fila.fim = novo_no
    else
        fila.fim.proximo = novo_no
        fila.fim = novo_no
    end
end

mutable struct PilhaEncadeada
    topo::Union{Node, Nothing}
end

PilhaEncadeada() = PilhaEncadeada(nothing)

function push_pilha_encadeada!(pilha::PilhaEncadeada, valor::Float64)
    novo_no = Node(valor, pilha.topo)
    pilha.topo = novo_no
end

########### Funções de conversão para array ###########
function estrutura_encadeada_para_array(estrutura)
    arr = Float64[]
    if isa(estrutura, ListaEncadeada)
        atual = estrutura.cabeca
    elseif isa(estrutura, FilaEncadeada)
        atual = estrutura.inicio
    elseif isa(estrutura, PilhaEncadeada)
        atual = estrutura.topo
    end
    
    while atual !== nothing
        push!(arr, atual.valor)
        atual = atual.proximo
    end
    return arr
end

########### Função Principal ###########
function executar_shellsort_em_estruturas(caminho_csv::String, quantidade::Int)
    df = CSV.read(caminho_csv, DataFrame; limit=quantidade)
    dados = Vector{Float64}(df.rating)
    num_dados = length(dados)
    
    # Preparando estruturas lineares
    fila_linear = Fila(copy(dados))
    pilha_linear = Pilha(copy(dados))
    lista_linear = Lista(copy(dados))
    
    # Preparando estruturas dinâmicas
    lista_encadeada = ListaEncadeada()
    fila_encadeada = FilaEncadeada()
    pilha_encadeada = PilhaEncadeada()
    
    for v in dados
        add_lista_encadeada!(lista_encadeada, v)
        enqueue!(fila_encadeada, v)
        push_pilha_encadeada!(pilha_encadeada, v)
    end
    
    # Medindo memória das estruturas antes da ordenação
    memoria_fila_linear = Base.summarysize(fila_linear)
    memoria_pilha_linear = Base.summarysize(pilha_linear)
    memoria_lista_linear = Base.summarysize(lista_linear)
    
    memoria_lista_dinamica = Base.summarysize(lista_encadeada)
    memoria_fila_dinamica = Base.summarysize(fila_encadeada)
    memoria_pilha_dinamica = Base.summarysize(pilha_encadeada)
    
    # Testes com estruturas lineares
    dados_fila_linear = copy(fila_linear.dados)
    dados_pilha_linear = copy(pilha_linear.dados)
    dados_lista_linear = copy(lista_linear.dados)
    
    tempo_fila_linear, _, _ = medir_tempo_memoria_precisao(() -> shell_sort_knuth!(dados_fila_linear))
    tempo_pilha_linear, _, _ = medir_tempo_memoria_precisao(() -> shell_sort_knuth!(dados_pilha_linear))
    tempo_lista_linear, _, _ = medir_tempo_memoria_precisao(() -> shell_sort_knuth!(dados_lista_linear))
    
    # Testes com estruturas dinâmicas
    tempo_lista_dinamica, _, _ = medir_tempo_memoria_precisao(() -> begin
        dados_temp = estrutura_encadeada_para_array(lista_encadeada)
        shell_sort_knuth!(dados_temp)
    end)
    
    tempo_fila_dinamica, _, _ = medir_tempo_memoria_precisao(() -> begin
        dados_temp = estrutura_encadeada_para_array(fila_encadeada)
        shell_sort_knuth!(dados_temp)
    end)
    
    tempo_pilha_dinamica, _, _ = medir_tempo_memoria_precisao(() -> begin
        dados_temp = estrutura_encadeada_para_array(pilha_encadeada)
        shell_sort_knuth!(dados_temp)
    end)
    
    # Exibindo resultados simples
    println("\nRESULTADOS:")
    println("Quantidade de dados: $num_dados")
    println("Estruturas Lineares:")
    println("Lista: $(formatar_tempo(tempo_lista_linear)) | Memória: $(formatar_memoria(memoria_lista_linear))")
    println("Fila: $(formatar_tempo(tempo_fila_linear)) | Memória: $(formatar_memoria(memoria_fila_linear))")
    println("Pilha: $(formatar_tempo(tempo_pilha_linear)) | Memória: $(formatar_memoria(memoria_pilha_linear))")
    println("Estruturas Dinâmicas:")
    println("Lista: $(formatar_tempo(tempo_lista_dinamica)) | Memória: $(formatar_memoria(memoria_lista_dinamica))")
    println("Fila: $(formatar_tempo(tempo_fila_dinamica)) | Memória: $(formatar_memoria(memoria_fila_dinamica))")
    println("Pilha: $(formatar_tempo(tempo_pilha_dinamica)) | Memória: $(formatar_memoria(memoria_pilha_dinamica))")
    
    # Salvando resultados em CSV
    open("resultados_comparacao_shellsort.csv", "w") do io
        write(io, "tipo_estrutura,estrutura,tempo_ms,memoria_bytes,memoria_formatada\n")
        write(io, "linear,lista,$(tempo_lista_linear),$(memoria_lista_linear),$(formatar_memoria(memoria_lista_linear))\n")
        write(io, "linear,fila,$(tempo_fila_linear),$(memoria_fila_linear),$(formatar_memoria(memoria_fila_linear))\n")
        write(io, "linear,pilha,$(tempo_pilha_linear),$(memoria_pilha_linear),$(formatar_memoria(memoria_pilha_linear))\n")
        write(io, "dinamica,lista,$(tempo_lista_dinamica),$(memoria_lista_dinamica),$(formatar_memoria(memoria_lista_dinamica))\n")
        write(io, "dinamica,fila,$(tempo_fila_dinamica),$(memoria_fila_dinamica),$(formatar_memoria(memoria_fila_dinamica))\n")
        write(io, "dinamica,pilha,$(tempo_pilha_dinamica),$(memoria_pilha_dinamica),$(formatar_memoria(memoria_pilha_dinamica))\n")
    end
    
    println("💾 Resultados salvos em: resultados_comparacao_shellsort.csv")
end

########### Execução ###########
executar_shellsort_em_estruturas("ratings.csv", 100)