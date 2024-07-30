result =0
data = input("숫자를 입력 하세요 : ")
n = len(data)

for i in range(n) :
    num = int(data[i])
    if(num <= 1 or result <=1) :
        result += num
    else :
        result *= num

print("입력된 숫자로 만들 수 있는 가장 큰 수는 : ", result)