for test_case in range(int(input())):
    N = int(input())

    num = 1
    snail = [[0 for x in range(N)] for y in range(N)]
    
    c_num = 0

    while num <= N*N:
        for row in range(c_num, N-c_num):
            snail[c_num][row] = num
            num += 1

        for col in range(c_num+1, N-c_num):
            snail[col][N-c_num-1] = num
            num += 1

        for row_reverse in range(N-c_num-2, c_num-1, -1):
            snail[N-c_num-1][row_reverse] = num
            num += 1

        for col_reverse in range(N-c_num-2, c_num, -1):
            snail[col_reverse][c_num] = num
            num += 1

        c_num += 1
        

    print(f'#{test_case+1}')
    for i in range(N):
        for j in range(N):
            print(snail[i][j], end=" ")
        print()

