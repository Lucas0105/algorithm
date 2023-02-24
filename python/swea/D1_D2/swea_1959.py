T = int(input())

for test_case in range(T):
    N, M = map(int, input().split())
    

    A = list(map(int, input().split()))
    B = list(map(int, input().split()))

    result = 0

    if N > M:
        N, M = M, N
        A, B = B, A

    for i in range(M-N+1):
        tmp = 0
        for j in range(N):
            tmp += A[j] * B[j+i]

        if tmp > result:
            result = tmp

    print(f'#{test_case+1} {result}')
