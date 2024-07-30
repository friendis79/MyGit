print("세 개의 양의 정수를 입력하시오.")  # "세 개의 양의 정수를 입력하시오."를 출력하는 문구

num = []  # num이라는 빈 리스트를 생성

for i in range(0, 3):  # 0부터 2까지 세 번 반복
    num.append(int(input(str(i+1) + "번째 양의 정수 : ")))  #양의 정수를 입력 받아 num 리스트에 추가

summ = sum(num)  #sum() 함수를 사용하여 num 리스트의 합을 계산하고 summ 변수에 저장

if summ % 2 == 0:  #리스트의 합이 짝수이면
    #max() 함수를 사용하여 num 리스트에서 최댓값을 구하고 해당 값을 출력
    print("세 수의 합은 짝수이고, 가장 큰 수는", max(num), "이다.")
else:  #짝수가 아닌 홀수이면 f-string을 사용하여 합을 출력
    print(f"세 수의 합은 홀수이고, 그 합은 {summ}이다.")