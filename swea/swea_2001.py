T = int(input())

for test_case in range(T):
    N, M = map(int, input().split())
    
    fly_map = []

    for i in range(N):
        fly_map.append(list(map(int, input().split())))
    
    max = 0

    for i in range(N-M+1):
        for j in range(N-M+1):
            tmp = 0
            for k in range(M):
                for z in range(M):
                    tmp += fly_map[k+i][z+j]

            if tmp > max:
                max = tmp


    print(f'#{test_case+1} {max}')