
for test_case in range(int(input())):
    N = int(input())

    result = [0] * 8

    if N>=50000:
        result[0] = N//50000
        N %= 50000

    if N>=10000:
        result[1] = N//10000
        N %= 10000

    if N>=5000:
        result[2] = N//5000
        N %= 5000

    if N>=1000:
        result[3] = N//1000
        N %= 1000

    if N>=500:
        result[4] = N//500
        N %= 500

    if N>=100:
        result[5] = N//100
        N %= 100

    if N>=50:
        result[6] = N//50
        N %= 50

    if N>=10:
        result[7] = N//10
        N %= 10
    
    print('#'+str(test_case+1))
    for i in result:
        print(i, end=" ")
    print()