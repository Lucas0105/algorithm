import math

N, M = map(int, input().split())

line_set = []
line = []

for _ in range(M):
    s, l = map(int, input().split())

    line_set.append(s)
    line.append(l)

# 최저가
line_set.sort()
line.sort()

min_line_set = line_set[0]
min_line = line[0]

# 낱게 줄로만 사는 경우
result1 = min_line * N

# 세트로만 사는 경우
result2 = math.ceil(N / 6) * min_line_set

# 세트랑 낱게 섞어서 사는 경우
result3 = (N // 6) * min_line_set + (N % 6) * min_line

print(min(result1, result2, result3))