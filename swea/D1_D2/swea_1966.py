
for test_case in range(int(input())):
    N = int(input())

    N_list = list(map(int, input().split()))

    print(f'#{test_case+1}', end=" ")

    N_list.sort()

    for i in N_list:
        print(i, end=" ")
    print()