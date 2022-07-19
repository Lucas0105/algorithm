T = int(input())
rank = ['A+', 'A0', 'A-', 'B+', 'B0', 'B-', 'C+', 'C0', 'C-', 'D0']

for test_case in range(T):
    N, K = map(int, input().split())
    score = []

    for i in range(N):
        tmp = 0
        mid, final, hw = map(int, input().split())
        tmp += mid * 0.35
        tmp += final * 0.45
        tmp += hw * 0.2
        score += [tmp]

    k_score = score[K-1]
    k_rank = 0

    score.sort(reverse=True)
    
    for i in score:
        if i < k_score:
            break
        k_rank +=1

    rate = N // 10


    print(f'#{test_case+1} {rank[(k_rank-1)//rate]}')
    
