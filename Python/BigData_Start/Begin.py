listV = list()  # 1차원 배열 생성
sumV = 0
hSumV = 0

for i in range(4): # 2차원 배열 생성 + 사용자로부토 값 입력 받기
    a = list(map(int, input("정수 입력 : ").split()))
    listV.append(a)
    #listV.append(list(map(int, input("정수 입력 : ").split())))

    for j in range(len(a)):
        sumV += a[j]

# 2차원 리스트
# len(리스트 변수) --> 행의 갯수
# len(리스트 변수 [0]) --> 열의 갯수
        
rows = len(listV)   # 행의 갯수
cols = len(listV[0])    # 열의 갯수

# 가로 합계
for i in range(len(listV)):          # --> 4행
    colCnt = len(listV[i])
    for j in range(len(listV[0])):      # --> 2열
        hSumV += listV[i][j]
    
    print(round(hSumV / colCnt, 0), end = " ")
    hSumV = 0
print(" ")

# 세로 합계
for i in range(cols): 
    rowCnt = len(listV)  
    for j in range(rows):  
        hSumV += listV[j][i]
    
    print(round(hSumV / rowCnt, 0), end=" ")
    hSumV = 0
print(" ")

print(listV)
print(sumV)


# 초기 코드
""" rows = 4
cols = 2
List = []

for i in range(4):
    line = list(map(int, input("Enter number : ").split()))
    List += [line]

for i in range(4):
        a = int(List[i][0]) + int(List[i][1])
        b = int(List[0][i]) + int(List[0][i]) + int(List[0][i]) + int(List[0][i])
        print("%d" % int(a / 2), end = " ")
print("")

print(List)

# 1차원 리스트 생성
listV = list()

# 2차원 리스트 생성
[[ ]] 

a = list(map(int, input("정수 입력 : ").split()))
print(a) """

# numpy 모듈 사용

""" import numpy as np

listV = list()  # 1차원 배열 생성
sumV = 0
hSumV = 0

for i in range(4):  # 2차원 배열 생성 + 사용자로부터 값 입력 받기
    a = list(map(int, input("정수 입력 : ").split()))
    listV.append(a)

    for j in range(len(a)):
        sumV += a[j]

# 2차원 리스트
# len(리스트 변수) --> 행의 갯수
# len(리스트 변수 [0]) --> 열의 갯수

matrix = np.array(listV, dtype=int)
rows, cols = matrix.shape

# 가로 합계
for i in range(rows):
    colCnt = len(matrix[i])
    hSumV = np.sum(matrix[i])
    print(round(hSumV / colCnt, 0), end=" ")
print(" ")

# 세로 합계
for i in range(cols):
    rowCnt = len(matrix)
    hSumV = np.sum(matrix[:, i])
    print(round(hSumV / rowCnt, 0), end=" ")
print(" ")

print(matrix)
print(sumV) """
