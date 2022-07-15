T = int(input())

for TC in range(1, T+1):
    N = int(input())
    dp = []
    dp.append([1])
    dp.append([1, 1])

    for i in range(2, N): # N = 3
        dpTemp = []
        dpTemp.append(1)
        for j in range(1, i):
            dpTemp.append(dp[i-1][j-1] + dp[i-1][j])
        dpTemp.append(1)
        dp.append(dpTemp)

    print(f'#{TC}')
    
    if TC == 1:
        print(1)
    else:
        for i in dp:
            for j in i:
                print(j, end=' ')
            print()