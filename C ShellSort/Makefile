CC = gcc
CFLAGS = -Wall -O2

STRUCT_DIRS = FilaDinamica FilaEstatica ListaDinamica ListaEstatica PilhaDinamica PilhaEstatica

# Procura todos os arquivos shellsort_*.c dentro das pastas
MAIN_SRCS = $(foreach dir, $(STRUCT_DIRS), $(wildcard $(dir)/shellsort_*.c))
EXECUTAVEIS = $(patsubst %.c,%,$(notdir $(MAIN_SRCS)))

# Junta todos os arquivos .c de suporte (excluindo os shellsort_*.c)
SUPPORT_SRCS = $(filter-out $(MAIN_SRCS), $(foreach dir, $(STRUCT_DIRS), $(wildcard $(dir)/*.c)))

all: $(EXECUTAVEIS)

# Compila cada executável
$(EXECUTAVEIS):
	@src_path=$$(find $(STRUCT_DIRS) -name $@.c); \
	$(CC) $(CFLAGS) -o $@ $$src_path $(SUPPORT_SRCS)

run: all
	@echo ""
	@echo "📊 Resultados de tempo de execução:"
	@for exe in $(EXECUTAVEIS); do \
		echo ""; \
		echo "🏃 Executando $$exe..."; \
		START=$$(date +%s.%N); \
		./$$exe; \
		END=$$(date +%s.%N); \
		TIME=$$(echo "$$END - $$START" | bc); \
		printf "⏱ Tempo total (real): %.6f segundos\n" "$$TIME"; \
	done

clean:
	rm -f $(EXECUTAVEIS)
