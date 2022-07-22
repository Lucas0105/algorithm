import copy

test = int(input())

def degree90(store):
    temp = copy.deepcopy(store)
    for i in range(len):
        for j in range(len):
            store[i][j] = temp[len-1-j][i]


    
for test_case in range(1, test+1):
    N = int(input())

    global len

    len = N

    store = []
    result = []

    for i in range(N):
        store.append(list(map(int, input().split())))
        
    
    for i in range(3):
        degree90(store)
        result.append(copy.deepcopy(store))


    print(f'#{test_case}')

    for i in range(N):
        for j in range(3):
            for k in result[j][i]:
                print(k, end='')
            print(' ', end='')
        print()


