k= 0
count = 0

num = int(input("정수를 입력 하시오 : "))

while num >= (1 << k) :
    if num & (1 << k) != 0:
        count += 1
    k+=1

binary = bin(num)
print("%d는 2진수로" %num, binary, "이고")
print("1로 설정된 비트개수는 %d개이다." %count)