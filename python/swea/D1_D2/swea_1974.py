T = int(input())

for test_case in range(T):
    sudoku = []
    check = True
    for i in range(9):
        sudoku.append(list(map(int, input().split())))

    for i in range(9):
        check = True if len(set(sudoku[i])) == 9 else False
        if not check:
            break
        
        tmp = []
        for j in range(9):
            tmp += [sudoku[j][i]]
        check = True if len(set(tmp)) == 9 else False
        if not check:
            break

    
    for i in range(0, 9, 3):
        for j in range(0, 9, 3):
            if not check:
                break
            tmp = []
            for k in range(3):
                for m in range(3):
                    tmp += [sudoku[k+i][m+j]]
            check = True if len(set(tmp)) == 9 else False

    print(f'#{test_case+1} {int(check)}')