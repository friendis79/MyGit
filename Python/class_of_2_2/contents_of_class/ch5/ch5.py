#리스트 개념
""" aa = [0, 0, 0, 0]
hap = 0

aa[0] = int(input("1st number : "))
aa[1] = int(input("2nd number : "))
aa[2] = int(input("3rd number : "))
aa[3] = int(input("4th number : "))

hap = aa[0] + aa[1] + aa[2] +aa[3]

print("TOTAL ==> %d" % hap) """

#두 번째 aa[1]에서 네 번째인 aa[]3]까지 삭제
""" aa = [10, 20, 30, 40, 50]
aa[1:4] = []
print(aa) """

#리스트 자체를 삭제하는 방법
""" aa = [10, 20, 30]; aa = []; print(aa)
aa = [10, 20, 30]; aa = None; print(aa)
# aa = [10, 20, 30]; del(aa); print(aa) """

#두 번째 aa[1]에서 네 번째인 aa[]3]까지 삭제
""" aa = [10, 20, 30, 40, 50]
aa[1:4] = []
print(aa) """

# 리스트 선언과 초기화
""" aa = []
bb = []
value = 0

for i in range(0, 100) :
    aa.append(value)
    value += 2
    
print("aa[0]에는 %d, aa[99]에는 %d이 입력됩니다." % (aa[0], aa[99]))

for j in range(0, 100) :
    bb.append(aa[99-j])
    
print("bb[0]에는 %d, bb[99]에는 %d이 입력됩니다." % (bb[0], bb[99])) """

# 리스트 요소에 접근
""" aa = [28, 31, 33, 35, 27, 26, 25]

for i in range(len(aa)) : # 
    print(aa[i], end = ',')

print("\n")

for element in aa :
    print(element, end = ',') """

# 리스트 입력 하번에 받기 - 1
""" hap = 0

aa = list(map(int, input("Enter number : ").split()))

print(aa)

hap = aa[0] + aa[1] + aa[2] +aa[3]

print("TOTAL ==> %d" % hap) """

# 리스트로 터틀 그래픽 그리기
""" import turtle
import random
## 전역 변수 선언 부분 ##

myTurtle , tX, tY, tColor, tSize, tShape= [None] * 6
shapeList = []
playerTurtles = [] # 거북 2차원 리스트
swidth, sheight=500, 500

turtle.title('거북 리스트 활용')
turtle.setup(width = swidth + 50, height = sheight + 50)
turtle.screensize(swidth, sheight)

shapeList = turtle.getshapes()

for i in range(0, 100) :
    random.shuffle(shapeList)
    myTurtle = turtle.Turtle(shapeList[0])
    tX = random.randrange(-swidth / 2, swidth / 2)
    tY = random.randrange(-sheight / 2, sheight / 2)
    r = random.random(); g = random.random(); b = random.random()
    tSize = random.randrange(1, 3)
    playerTurtles.append([myTurtle, tX, tY, tSize, r, g, b])
    
for tList in playerTurtles :
    myTurtle = tList[0]
    myTurtle.color((tList[4], tList[5], tList[6]))
    myTurtle.pencolor((tList[4], tList[5], tList[6]))
    myTurtle.turtlesize(tList[3])
    myTurtle.goto(tList[1], tList[2])
    
turtle.done()
turtle.bye() """

# 슬라이싱 문법 및 개념
""" aa = [2, 5, 8, 7, 9, 10, 13, ['Let''s', 'go', 'Python']]

print(aa[0:4])

print(aa[2:5])

print(aa[ : 5])

print(aa[3 : ])

print(aa[7][0:2])


#step
numbers = [10, 20, 30, 40, 50, 60, 70, 80, 90]

sublist = numbers[2:7:2]

print(sublist) """

#역순 뒤집기
""" A = [10, 20, 30, 40, 50, 60, 70, 80, 90]
B = A[ : : -1]
print(A)
print(B)
print("A[3]의 항목값", A[3], "의 고유 주소 값 : ", id(A[3]))
print("B[-4]의 항목값", B[-4], "의 고유 주소 값 : ", id(B[-4]))
A.reverse()
print(A)

#두 리스트를 합치는 연산자
a = [1, 2, 3]
b = [4, 5, 6]
c = a+ b
print(c)

heroes1 = ["Iron man", "Torr"]
heroes2 = ["Hulk", "Captin America"]
avengers = heroes1 + heroes2
print(avengers) """


#두 번쨰에 위치한 값을 1로 변경하는 방법
""" aa = [10, 20, 30]
aa[1] = 1
print(aa)
 """
#두 번째에 값인 20을 200과 201값 2개로 변경하는 방법
""" aa = [10, 20, 30]
aa[1:2] = [200, 201]
print(aa) """


