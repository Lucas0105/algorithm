T = int(input())

for test_case in range(1, T+1):
    N = int(input())
    item = list(map(int, input().split()))
    score = 0

    max_value = item.pop()

    for i in range(N-2, -1, -1):
        if max_value < item[i]:
            max_value = item[i]
        else :
            score += max_value - item[i]


    print(f'#{test_case} {score}')