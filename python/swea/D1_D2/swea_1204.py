for test_case in range(int(input())):
    input()
    score = [0] * 102
    datas = list(map(int, input().split()))
    
    for data in datas:
        score[data] += 1

    max = 0
    index = 0
    for idx, data in enumerate(score):
        if max <= data:
            max = data
            index = idx

    print(f'#{test_case+1} {index}')