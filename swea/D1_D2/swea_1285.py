for test_case in range(int(input())):
    result = 0
    count = 0

    N = int(input())
    dol = list(map(int, input().split()))
    dol = list(map(abs, dol))

    result = min(dol)
    count = dol.count(result)

    print(f'#{test_case+1} {result} {count}')