def shell_sort(data):
    n = len(data)
    h = 1
    while h < n // 3:
        h = 3 * h + 1  # Geração da sequência de Knuth

    while h > 0:
        for i in range(h, n):
            temp = data[i]
            j = i
            while j >= h and data[j - h] > temp:
                data[j] = data[j - h]
                j -= h
            data[j] = temp
        h = h // 3  # Redução segundo Knuth
    return data