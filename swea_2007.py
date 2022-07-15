T = int(input())

for TC in range(1, T+1):
    madi = input()

    num = 1
    for i in range(len(madi)):
        if madi[0:num] == madi[num:num+num]:
            break
        num += 1

    print(f'#{TC} {num}')