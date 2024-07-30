n = int(input("n을 입력하시오 : ")) #n의 값을 입력 받음
nlist = [] #nlist라는 공백 리스트 생성

for i in range(1,n+1) : #1부터 n까지의 숫자에 대해 반복
    column = [] #각 행에 대한 공백 리스트 생성
    if (i % 2 == 0) : #만약 i가 짝수라면
        for j in range(n,0,-1) : #n부터 1까지 역순으로 반복
            column.append(j+n*(i-1)) #append()함수를 사용하여 계산된 값을 column 리스트에 추가
            print("%d " %(j+n*(i-1)), end = "") #결과를 출력하고 줄 바꿈을 하지 않음
        nlist.append(column) #append()함수를 사용하여 nlist에 현재 행의 column을 추가
        print() #다음 줄로 넘어감
        
    if (i % 2 == 1) : #만약 i가 홀수라면
        for j in range(1, n+1) : #1부터 n까지 반복
            column.append(j+n*(i-1)) #append()함수를 사용하여 계산된 값을 column 리스트에 추가
            print("%d " %(j+n*(i-1)), end = "") #결과를 출력하고 줄 바꿈을 하지 않음
        nlist.append(column) #append()함수를 사용하여 nlist에 현재 행의 column을 추가
        print() #다음 줄로 넘어감