T = int(input())

for test_case in range(T):
    N = list(map(int, input().split()))

    N.sort()

    N.pop()     # N.pop(index) 가능 default 는 -1

    del N[0]  

    result = sum(N)/len(N)

    print(f'#{test_case+1} {round(result)}')