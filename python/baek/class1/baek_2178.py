def search_miro(cnt, position):
    global min_cnt, N, M, mirror_map, visited
    if position[0] == N and position[1] == M:
        if min_cnt > cnt:
            min_cnt = cnt
        return

    if visited[position[0]][position[1]] == 0:
        visited[position[0]][position[1]] = 1
    else :
        return
    # 오른쪽으로 이동
    if position[1]+1 != M+1 and mirror_map[position[0]][position[1]+1] == 1:
        mirror_map[position[0]][position[1]+1] = 0
        search_miro(cnt+1, [position[0], position[1]+1])
        mirror_map[position[0]][position[1]+1] = 1

    # 아래로 이동
    if position[0]+1 != N+1 and mirror_map[position[0]+1][position[1]] == 1:
        mirror_map[position[0]+1][position[1]] = 0
        search_miro(cnt+1, [position[0]+1, position[1]])
        mirror_map[position[0]+1][position[1]] = 1


    # 위로 이동
    if position[0]-1 != -1 and mirror_map[position[0]-1][position[1]] == 1:
        mirror_map[position[0]-1][position[1]] = 0
        search_miro(cnt+1, [position[0]-1, position[1]])
        mirror_map[position[0]-1][position[1]] = 1


    # 왼쪽으로 이동
    if position[1]-1 != -1 and mirror_map[position[0]][position[1]-1] == 1:
        mirror_map[position[0]][position[1]-1] = 0
        search_miro(cnt+1, [position[0], position[1]-1])
        mirror_map[position[0]][position[1]-1] = 1

N, M = map(int, input().split())
N -= 1
M -= 1
cnt = 0
mirror_map = []
visited = []

for i in range(N+1):
    visited += [[False] * (M+1)]

for i in range(N+1):
    mirror_map += [list(map(int, input()))]

queue = [[0, 0, 1]]
visited[0][0] = True

while queue:
    position = queue.pop(0)

    if position[0] == N and position[1] == M:
        cnt = position[2]
        break


    # 오른쪽으로 이동
    if position[1]+1 != M+1 and mirror_map[position[0]][position[1]+1] == 1 and not visited[position[0]][position[1]+1] :
        queue += [[position[0], position[1]+1, position[2] + 1]]
        visited[position[0]][position[1]+1] = True

    # 아래로 이동
    if position[0]+1 != N+1 and mirror_map[position[0]+1][position[1]] == 1 and not visited[position[0]+1][position[1]]:
        queue += [[position[0]+1, position[1], position[2] + 1]]
        visited[position[0]+1][position[1]] = True

    # 위로 이동
    if position[0]-1 != -1 and mirror_map[position[0]-1][position[1]] == 1 and not visited[position[0]-1][position[1]]:
        queue += [[position[0]-1, position[1], position[2] + 1]]
        visited[position[0]-1][position[1]] = True

    # 왼쪽으로 이동
    if position[1]-1 != -1 and mirror_map[position[0]][position[1]-1] == 1 and not visited[position[0]][position[1]-1]:
        queue += [[position[0], position[1]-1, position[2] + 1]]
        visited[position[0]][position[1]-1] = True


print(cnt)



# 모범 답안
# from collections import deque
# N, M = map(int, input().split())
# adj_list = [[]*M for _ in range(N)]
# visited_list = [[False]*M for _ in range(N)]
# q = deque([0,0])
# visited_list[0][0] = True
# # 입력
# for i in range(N):
#     temp = input()
#     for j in range(M):
#         adj_list[i].append(int(temp[j]))

# dx = [-1, 1, 0, 0]
# dy = [0, 0, -1, 1]
        
# while q:
#     x = q.popleft()
#     y = q.popleft()
#     for i in range(4):
#         temp_x = x + dx[i]
#         temp_y = y + dy[i]
#         if 0 <= temp_x < N and 0 <= temp_y < M and not visited_list[temp_x][temp_y] and adj_list[temp_x][temp_y] == 1:
#             q.append(temp_x)
#             q.append(temp_y)
#             visited_list[temp_x][temp_y] = True
#             adj_list[temp_x][temp_y] = adj_list[x][y] + 1

# print(adj_list[N-1][M-1])