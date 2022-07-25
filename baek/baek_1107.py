
def remocorn(result, check_btn, N):
    global min_num

    for num in check_btn:
        result = result + str(num)

        result_num = abs(int(result)-N) + len(result)

        if min_num > result_num :
            min_num = result_num

        if len(result) < len(str(N)) + 1:
            remocorn(result, check_btn, N)

        result = result[:-1]

N = int(input())
check = list(range(10))
err_btn_cnt = int(input())

err_btn = set()

if err_btn_cnt:
    err_btn = list(map(int, input().split()))

check_btn = set(check) - set(err_btn)

min_num = abs(N-100)

if err_btn_cnt == 0 :
    min_num = min(min_num, len(str(N)))
else :
    remocorn('', check_btn, N)
    

print(min_num)
