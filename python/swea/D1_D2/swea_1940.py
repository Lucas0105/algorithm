for test_case in range(int(input())):
    N = int(input())    
    distance = 0
    speed = 0
    for i in range(N):
        tmp = tuple(map(int, input().split()))

        if tmp[0] != 0:
            command, v = tmp

            if command == 1:
                speed += v
            else :
                speed -= v
        
        
        if speed < 0 : 
            speed = 0

        distance += speed

    print(f'#{test_case+1} {distance}')
