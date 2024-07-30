while True :
    N, M, K = map(int, input("세 개의 수를 공백으로 구분하여 입력 : ").split())
    #M번더하기, K번초과X, 배열크기N
    
    if 2 <= N <= 1000 and 1 <= M <= 10000 and 1 <= K <= 10000:
        break
    else  :
        print("입력 범위를 벗어납니다.")

data = list(map(int, input("N개의 수를 공백으로 구분하여 입력 : ").split()))
data.sort()

res=0
max_value = data[N-1]
sec_max = data[N-2]

a = int(M/K)
b = M%K
for i in range(0,a):
    for i in range(0, K):
        res += max_value

for i in range(0,b):
    res += sec_max
    
print("출력 결과 : %d" %res)