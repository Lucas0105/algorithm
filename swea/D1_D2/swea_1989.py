T = int(input())

for test_case in range(T):
    input_str = input()

    if input_str == input_str[::-1]:
        print(f'#{test_case+1} 1')
    else :
        print(f'#{test_case+1} 0')