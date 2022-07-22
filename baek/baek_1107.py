N = int(input())

err_btn_cnt = int(input())

err_btn = list(map(int, input().split()))

current_num = 100

result = 0

N_list = list(N)

for char in N_list:
    min = 20
    for i in range(10):
        if i not in err_btn : 



print(result)