def gap_score(score_list):  #리스트의 가장 큰 값과 가장 작은 값의 차를 구하는 함수 정의
    score_list.sort()  #리스트를 sort() 함수를 사용하여 오름차순으로 정렬
    gap = score_list[-1] - score_list[0]  #리스트의 가장 큰 값에서 가장 작은 값의 차를 gap 변수에 대입
    return gap  #gap 값을 반환

score_list = [45, 66, 70, 83, 50, 77, 87, 92, 73, 89]  #score_list에 주어진 리스트 요소를 대입
result = gap_score(score_list)  #gap_score() 함수를 사용하여 결과값을 result 변수에 대입
print(result)  #결과 출력