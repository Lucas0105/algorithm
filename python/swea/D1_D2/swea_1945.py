check = [2, 3, 5, 7, 11]

for test_case in range(int(input())):
    N = int(input())
    result = [0] * 5 
    while N != 1:
        for idx, value in enumerate(check):
            if N % value == 0 :
                result[idx] += 1
                N = N//value
                break


    print(f'#{test_case+1}', end=' ')
    for i in result:
        print(i, end=' ')
    print()