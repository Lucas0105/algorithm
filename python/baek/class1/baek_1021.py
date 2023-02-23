from collections import deque

N, M = map(int, input().split())
q = deque([i for i in range(1, N+1)])
num_lst = list(map(int, input().split()))
result = 0

for num in num_lst:
    cnt = 0

    # 없는 경우 회전
    while q[0] != num:
        q.rotate(1)
        cnt += 1
    
    result += min(len(q) - cnt, cnt)
    q.popleft()

print(result)