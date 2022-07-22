for test_case in range(int(input())):
    N = int(input())
    result = set()
    n = 1
    tmp = 0
    while len(result) != 10:
        tmp = N * n
        result = result | set(str(tmp))

        n += 1

    print(f'#{test_case+1} {tmp}')