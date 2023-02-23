month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

for test_case in range(int(input())):
    a_month, a_day, b_month, b_day = map(int, input().split())
    day = b_day - a_day
    result = 0
    for i in range(a_month, b_month):
        result += month[i-1]
    result += day

    print(f'#{test_case+1} {result+1}')