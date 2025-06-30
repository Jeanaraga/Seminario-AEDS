#!/bin/bash

set -e

# Arquivo CSV de saída
CSV="resultados_memoria.csv"

# Início do CSV (apenas se não existir)
if [ ! -f "$CSV" ]; then
    echo "Programa,MemoriaMaxBytes" > "$CSV"
fi

# Loop sobre todos os binários shellsort_*
for BIN in shellsort_*; do
    # Ignorar se não for executável
    if [[ ! -x "$BIN" ]]; then
        echo "⚠️ Pulando $BIN (não é executável)"
        continue
    fi

    echo "🚀 Testando memória de: $BIN"

    OUT="massif_${BIN}.out"
    TXT="massif_${BIN}.txt"

    # Executa com valgrind
    valgrind --tool=massif --quiet --massif-out-file="$OUT" ./"$BIN" > /dev/null 2>&1

    # Converte para formato legível (opcional)
    ms_print "$OUT" > "$TXT"

    # Pega pico de uso de heap
    PEAK=$(grep 'mem_heap_B=' "$OUT" | cut -d= -f2 | sort -nr | head -n1)

    # Garante que o PEAK não está vazio
    if [ -z "$PEAK" ]; then
        PEAK="0"
        echo "❌ Nenhuma alocação de heap detectada em $BIN"
    fi

    # Salva no CSV
    echo "$BIN,$PEAK" >> "$CSV"

    echo "✅ $BIN usou até $(numfmt --to=iec $PEAK) de heap"
done

echo -e "\n📊 Resultados salvos em: $CSV"
