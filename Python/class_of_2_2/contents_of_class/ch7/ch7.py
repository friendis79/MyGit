#함수 호출과 값 반환
""" import math

##함수 선언 부분##
def get_area(radius):
    area = math.pi * radius**2
    return area

##Main Code Part##
r = int(input("Enter radius of circle : "))
result = get_area(r)
print("Area of Circle with radius is %d : " %r, result) """

#return문을 이용한 반환
def get_sum(a, b) :     #두 수의 합을 반환하는 함수
    result = a + b
    return result

def print_sum():
    a = 10
    b = 20
    result = a + b
    print("%3d과 %3d의 합 = %d" % (a, b, result))
    
n1 = get_sum(100, 200)
print("100과 200의 합 = ", n1)
print_sum()

#반지름을 입력하여 원의 둘레 길이와 면적 구하기
""" def get_circle(r) :
    circle = 2 * math.pi * r
    area = math.pi * r**2
    return circle, area

radius = int(input("원의 반지름을 입력 하시오 : "))
ret_c, ret_a = get_circle(radius)

print("원 둘레의 길이는 : %.2f" % ret_c)
print("원의 면적은 : %.2f" %ret_a) """

# 2진수 변환
""" def convert(num) :
    binary = []
    while num > 0: 
        remainder = num % 2
        binary.insert(0, remainder)
        num //= 2
    return binary

a = int(input("Enter integer number : "))

result = convert(a)
print("%d의 2진수 ---> %s" %(a, result)) """

#함수의 매개변수 전달
#입력된 두 정수 범위까지의 합을 계산하기#
""" def get_sum(start, end):
    sum = 0
    for i in range(start, end+1):
        sum += i
    
    return sum

a, b = map(int, input("정수 두 개 값을 입력 : ").split())
value = get_sum(a, b)
print("%d부터 %d까지의 합 = %d" %(a, b, value))
print(value) """

#디폴트 인수
""" #함수 선언 부분
def get_sum(v1, v2, v3 = 10) :
    sum = 0
    sum = v1 + v2 + v3
    return sum

hap = 0
hap = get_sum(10, 20)
print("매개변수가 2개인 함수를 호출한 결과 ==> %d" %hap)
hap = get_sum(10, 20, 30)
print("매개변수가 3개인 함수를 호출한 결과 ==> %d" %hap) """

#키워드 인수
#함수 선언 부분
""" def get_sum(v1, v2, v3) :
    print("v1 = %d, v2 =%d, v3 =%d" %(v1, v2, v3))
    sum = 0
    sum = v1 + v2 + v3
    return sum

hap = 0
hap = get_sum(v2 = 200, v3 = 300, v1 = 100)
print("키워드 인수로 함수를 호출한 결과 => %d" %hap) """

#가변 인수
""" #함수 선언 부분
def get_sum(*args) :
    sum = 0
    for num in args :
        sum = sum + num
    return sum
    
hap = 0
hap = get_sum(10, 30)
print("매개변수가 2개인 함수를 호출한 결과 => %d" %hap)
hap = get_sum(10, 30, 60)
print("매개변수가 3개인 함수를 호출한 결과 => %d" %hap)

def dic_func(**kwargs) :
    for k in kwargs.keys() :
        print("%s --> %d명입니다." %(k, kwargs[k]))
        
dic_func(트와이스 =9, 소녀시대 = 7, 걸스데이 = 4, 블랙핑크 = 4) """

#패킹 (Packing)
""" def sum_all(*numbers) :
    result = 0
    for n in numbers :
        result += n
    return result
    
hap = sum_all(10, 20, 30)
print("전체 합 : %d" %hap)
hap = sum_all(10, 20, 30, 40, 50, 60)
print("전체 합 : %d" %hap) """

#언패킹 (unpacking)
""" def sum(a, b, c):
    return a+ b+ c

numbers = [10, 20, 30]
hap = sum(*numbers)
print("Total :  %d" %hap)

numbers = [10, 20, 30, 40]
hap = sum(*numbers)
print("Total = %d" %hap) """

#1~45 난수 출력
""" import random

def getNumbers() :
    num = random.randint(1, 45)
    for i in range(6) :
        while num in lotto:
            num = random.randint(1, 45)
        lotto.append(num)
        
lotto = []
num = 0
getNumbers()
lotto.sort()

print("Selected lotto numbers ==> ", end = '')
for i in range(6):
    print("%d" %lotto[i], end = '') """

#재귀 함수
#zCount Down
""" def countdown(n) :
    if n <= 0:
        print("Launch!!")
    else :
        print(n, "\t", end = '')
        countdown(n-1)
        
n = int(input("Enter countdown value : "))
countdown(n) """

#피보나치 수열 함수의 재귀적 구현
""" def fibonacci(n) :
    if n<=1:
        return n
    else :
        # F_n = F_(n-1) + F_(n-2)
        return(fibonacci(n-1) + fibonacci(n-2))
    
nterms = int(input("Enter value of Fibonacco : "))

#음수일 경우 피노차ㅣ 수를 구할 수 없음
if nterms <= 0:
    print("Error : Plz enter positive number.")
else :
    print("Fibonacci sequence : ", end = '')
    for i in range(nterms):
        print(fibonacci(i), "\t", end = '') """

#람다 함수
""" f =lambda x, y : x + y

print("정수의 합 : ", f(10, 20))

print("정수의 합 : ", f(20, 30)) """

#2차 함수 그래프 그리기
""" import turtle
t = turtle.Turtle()

#좌표 그리기
def drawaxis(size):
    for i in range(4):
        t.setheading(90*i)
        t.forward(size)
        t.home()
        
#2차함수 그리기
drawaxis(300)
t.pencolor('red')
t.pensize(3)
t.up()
x = -10
y = x**2 -8*x-8
t.goto(x*10, y)
t.down()
for x in range(-10, 21):
    y = (x**2 - 8*x-8)
    t.goto(x*10, y)
    
turtle.done()
turtle.bye() """

#global 키워드를 사용한 전역변수와 참조 방법
""" def print_sum():
    global a, b
    a = 100; b = 200
    result = a + b
    print("print_sum() 내부 : %d 과 %d의 값은 %d 입니다."
              %(a, b, result))
        
        
a = 10
b = 20
print_sum()
result = a+ b
print("print_sum() 외부 : %d 과 %d의 값은 %d 입니다."
      %a, b, result) """