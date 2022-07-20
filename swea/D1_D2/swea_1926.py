N = int(input())

for i in range(1, N+1):
    temp = str(i)
    num = 0
    for j in temp:

        if j == '3' or j == '6' or j == '9':
            num += 1
    
    if num == 0:
        print(temp, end=' ')
    elif num == 1:
        print('-', end=' ')
    elif num == 2:
        print('--', end=' ')
