T = int(input())

for test_case in range(T):
    N = int(input())

    sum = 0
    for i in range(1, N+1, 2):
        sum+=i

    for i in range(2, N+1, 2):
        sum-=i

    print(f'#{test_case+1} {sum}')