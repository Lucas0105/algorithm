## Why 왜 알고리즘을 공부하는가?
알고리즘 문제를 해결하는 것이 재밌어서 시작하였습니다.

## 목표
1일 1알고리즘을 수행하자

## 배운 내용
### 모듈러 연산
- 성질 1
```
(a + b) mode m = ((a mod m) + (b mod m)) mod m
```

- 성질 2
```
(a * b) mode m = ((a mod m) * (b mod m)) mod m
```

- 증명 1
```
a mod m = T       
b mod m = S       

a = T + i*m (i는 임의의 정수)          
b = S + j*m (j는 임의의 정수)   

(a + b) mode m = ((a mod m) + (b mod m)) mod m

(T + i*m + S + j*m) mod m = (T + S + (i + j)m) mod m = (T + S) mod m

(T + S) mod m = ((a mod m) + (b mod m)) mod m
```
(i + j)m 을 m으로 나눈 나머지 값은 0이기 때문에 제거해주었습니다.

- 증명 2         
위의 증명 1과 동일한 방식으로 수행하면 성립합니다.

```
(a * b) mode m = ((a mod m) * (b mod m)) mod m
```

### 관련 문제
- https://www.acmicpc.net/problem/11051

## 시작 기간
2023-02-20 ~ 

## 다른 스터디 모임과 병행
https://github.com/yangDM9378/emp_Study

## 결과
