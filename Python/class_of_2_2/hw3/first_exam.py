print("세 개의 양의 정수를 입력하시오") #"세 개의 양의 정수를 입력하시오"를 출력한다.
num = []

#input()함수를 사용하여 세 양의 정수를 입력받는다.
x = int(input("첫번째 양의 정수 : "))
y = int(input("두번째 양의 정수 : "))
z = int(input("세번째 양의 정수 : "))

if (x + y+ z) % 2 == 0: #(x + y + z)를 2로 나눈 나머지가 0일 때는 짝수임을 확인한다.
    if x > y and x > z: #x가 y와 z보다 크면 가장 큰 수는 x인 것을 확인한다.
        print("세 수의 합은 짝수이고, 가장 큰 수는 %d 이다." %x)
    elif y > z:
        print("세 수의 합은 짝수이고, 가장 큰 수는 %d 이다." %y)
    else:
        print("세 수의 합은 짝수이고, 가장 큰 수는 %d이다" %z)
        
else:
    print("세 수의 합은 홀수이고, 그 합은", x+y+z, "이다.")
    
""" print("세 개의 양의 정수를 입력하시오.")
num = []

for i in range(0, 3):
    num.append(int(input(str(i+1) + "번째 양의 정수 : ")))

summ = sum(num)

if summ % 2 == 0:
    print("세 수의 합은 짝수이고, 가장 큰 수는", max(num), "이다.")
else:
    print("세 수의 합은 홀수이고, 그 합은", snumm, "이다.") """
    
""" for i in range(len(nlist)) :
    for j in range(len(nlist[i])) :
        print("%3d" %nlist[i][j], end="")
    print("") """