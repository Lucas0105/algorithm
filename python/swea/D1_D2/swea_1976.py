T = int(input())

for test_case in range(T):
    a_h, a_m, b_h, b_m = map(int, input().split())

    result_h = a_h + b_h
    result_m = a_m + b_m

    carry_h = result_m // 60
    result_m %= 60

    result_h += carry_h

    if result_h % 12 == 0:
        result_h = 12
    else :
        result_h %= 12

    print(f'#{test_case+1} {result_h} {result_m}')

    