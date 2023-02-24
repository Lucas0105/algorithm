for test_case in range(int(input())):
    P, Q, R, S, W = map(int, input().split())

    A_charge = P * W
    B_charge = Q

    if R < W :
        B_charge += (W - R) * S

    print(f'#{test_case+1} {min(A_charge, B_charge)}')
