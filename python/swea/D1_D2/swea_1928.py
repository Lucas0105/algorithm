table = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'

for test_case in range(int(input())):
    input_str = input()
    decode_val = ''
    result = ''
    for char in input_str:
        val = bin(table.index(char))[2:]        # 0b10 => 0b 바이너리 표시, 뒤에 부분이 값 10

        for i in range(6-len(val)):
            val = '0'+val
        decode_val += val    # 6bit씩 저장


    # 8bit 씩 읽어와 아스키 코드 디코딩
    for i in range(0, len(decode_val), 8):
        result += chr(int('0b'+decode_val[i:i+8], 2))

    print(f'#{test_case+1} {result}')
    