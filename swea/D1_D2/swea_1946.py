T = int(input())

for test_case in range(1, T+1):
    N = int(input())

    result = ""
    for i in range(N):
        c, num = input().split()
        for j in range(int(num)):
            result = result+c

    num = 0
    print(f'#{test_case}')
    for c in result:
        print(c,end='')
        num += 1
        if num%10 == 0:
            print()
    print()