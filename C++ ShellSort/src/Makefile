CC = g++
CFLAGS = -Wall -O2 -std=c++11

# Diretórios exatos da sua estrutura
STRUCT_DIRS = FilaDinamica FilaEstatica ListaDinamica ListaEstatica PilhaDinamica PilhaEstatica

# Lista explícita dos executáveis esperados
EXECUTAVEIS = shellsort_FilaDinamica shellsort_FilaEstatica shellsort_ListaDinamica shellsort_ListaEstatica shellsort_PilhaDinamica shellsort_PilhaEstatica

all: $(EXECUTAVEIS)

# Regra genérica para todos os shellsort_*
shellsort_%: %/shellsort_%.cpp
	@echo "🔨 Compilando $@..."
	@if [ -f "$<" ]; then \
		$(CC) $(CFLAGS) -I$* -o $@ $< && echo "✅ $@ compilado com sucesso!" || echo "❌ Erro ao compilar $@"; \
	else \
		echo "❌ Arquivo $< não encontrado!"; \
		exit 1; \
	fi

# Regras específicas como backup (caso a genérica não funcione)
shellsort_FilaEstatica: FilaEstatica/shellsort_FilaEstatica.cpp
	@echo "🔨 Compilando $@..."
	$(CC) $(CFLAGS) -IFilaEstatica -o $@ $<

shellsort_FilaDinamica: FilaDinamica/shellsort_FilaDinamica.cpp
	@echo "🔨 Compilando $@..."
	$(CC) $(CFLAGS) -IFilaDinamica -o $@ $<

shellsort_ListaEstatica: ListaEstatica/shellsort_ListaEstatica.cpp
	@echo "🔨 Compilando $@..."
	$(CC) $(CFLAGS) -IListaEstatica -o $@ $<

shellsort_ListaDinamica: ListaDinamica/shellsort_ListaDinamica.cpp
	@echo "🔨 Compilando $@..."
	$(CC) $(CFLAGS) -IListaDinamica -o $@ $<

shellsort_PilhaEstatica: PilhaEstatica/shellsort_PilhaEstatica.cpp
	@echo "🔨 Compilando $@..."
	$(CC) $(CFLAGS) -IPilhaEstatica -o $@ $<

shellsort_PilhaDinamica: PilhaDinamica/shellsort_PilhaDinamica.cpp
	@echo "🔨 Compilando $@..."
	$(CC) $(CFLAGS) -IPilhaDinamica -o $@ $<

run: all
	@echo ""
	@echo "📊 Resultados de tempo de execução:"
	@for exe in $(EXECUTAVEIS); do \
		if [ -f "./$$exe" ]; then \
			echo ""; \
			echo "🏃 Executando $$exe..."; \
			START=$$(date +%s.%N); \
			./$$exe 2>&1; \
			END=$$(date +%s.%N); \
			if command -v bc >/dev/null 2>&1; then \
				TIME=$$(echo "scale=10; $$END - $$START" | bc 2>/dev/null); \
				if [ ! -z "$$TIME" ]; then \
					printf "⏱ Tempo total (real): %.6f segundos\n" "$$TIME"; \
				fi; \
			fi; \
		else \
			echo "❌ $$exe não foi compilado"; \
		fi; \
	done

clean:
	@echo "🧹 Limpando executáveis..."
	@rm -f $(EXECUTAVEIS)
	@echo "✅ Limpeza concluída!"

# Compilar apenas um específico
compile-one:
	@echo "Digite o nome (ex: FilaEstatica):"
	@read nome; \
	if [ -f "$$nome/shellsort_$$nome.cpp" ]; then \
		echo "🔨 Compilando shellsort_$$nome..."; \
		$(CC) $(CFLAGS) -I$$nome -o shellsort_$$nome $$nome/shellsort_$$nome.cpp && \
		echo "✅ Compilado com sucesso!" || echo "❌ Erro na compilação"; \
	else \
		echo "❌ Arquivo $$nome/shellsort_$$nome.cpp não encontrado"; \
	fi

test-all:
	@echo "🧪 Testando compilação individual:"
	@for dir in $(STRUCT_DIRS); do \
		echo ""; \
		echo "📁 Testando $$dir..."; \
		if [ -f "$$dir/shellsort_$$dir.cpp" ]; then \
			$(CC) $(CFLAGS) -I$$dir -o test_$$dir $$dir/shellsort_$$dir.cpp 2>&1 && \
			echo "✅ $$dir: OK" || echo "❌ $$dir: ERRO"; \
			rm -f test_$$dir; \
		else \
			echo "❌ $$dir: Arquivo não encontrado"; \
		fi; \
	done

debug:
	@echo "🔍 Informações de Debug:"
	@echo "EXECUTAVEIS: $(EXECUTAVEIS)"
	@echo ""
	@for dir in $(STRUCT_DIRS); do \
		echo "📁 $$dir:"; \
		if [ -f "$$dir/shellsort_$$dir.cpp" ]; then \
			echo "  ✅ shellsort_$$dir.cpp"; \
		else \
			echo "  ❌ shellsort_$$dir.cpp não encontrado"; \
		fi; \
		if [ -f "$$dir/shellsort_$$dir.hpp" ]; then \
			echo "  ✅ shellsort_$$dir.hpp"; \
		else \
			echo "  ❌ shellsort_$$dir.hpp não encontrado"; \
		fi; \
	done

.PHONY: all run clean compile-one test-all debug
