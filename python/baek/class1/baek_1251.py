word = input()

N = len(word)

result = []

for i in range(1, N-1):
    for j in range(i+1, N):
        tmp = word[:i][::-1]
        tmp += word[i:j][::-1]
        tmp += word[j:][::-1]

        result.append(tmp)

result.sort()
print(result[0])