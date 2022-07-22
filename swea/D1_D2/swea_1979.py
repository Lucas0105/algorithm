T = int(input())

for test_case in range(T):
    N, K = map(int, input().split())
    puzzle = []
    result = 0

    for i in range(N):
        puzzle.append( list(map(int, input().split())))
    
    for m in range(N):
        for i in range(N-K + 1):
            if i != 0 and puzzle[m][i-1] == 1:
                continue
            count = 0
            
            for k in range(i, N):
                if puzzle[m][k] == 1:
                    count += 1
                else:
                    break
            
            if count == K:
                result +=1

        for i in range(N-K + 1):
            if i != 0 and puzzle[i-1][m] == 1:
                continue
            count = 0
            
            for k in range(i, N):
                if puzzle[k][m] == 1:
                    count += 1
                else:
                    break
            
            if count == K:
                result +=1
     
    print(f'#{test_case+1} {result}')