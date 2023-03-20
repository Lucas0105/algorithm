bars = input()
is_bar = "()"
answer = 0
bar_num = 0

i = 0
while i < len(bars) - 1:
    cur_bar = bars[i] + bars[i+1]
# 레이져가 아니면서 왼쪽 괄호이면 쇠막대기 하나 추가
    if cur_bar != is_bar and bars[i] == '(':
        bar_num += 1
        answer += 1
# 레이져이면 쇠막대기만큼 추가
    elif cur_bar == is_bar:
        i += 1
        answer += bar_num
# 오른쪽 괄호이면 쇠막대기 감소
    elif bars[i] == ')':
        bar_num -= 1

    i += 1
print(answer)
