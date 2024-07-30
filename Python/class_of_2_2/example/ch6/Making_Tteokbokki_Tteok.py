#떡의 갯수 (N)와 요청한 떡의 길이(M)를 입력 받기
n, m = map(int, input("떡의 갯수와 길이 입력 :").split())

#각 떡의 개별 입력
length = []

for i in range(n) :
  print("%d 번째 떡의 길이 : " %(i+1), end = "")
  a= int(input())
  length.append(a)

 #탐색을 위한 시작점과 끝점 설정
  start = 0
  end = max(length)

 #탐색 수량(반복)
result = 0
while (start <= end) :
  total = 0
  mid = (start + end) // 2
  for x in length :
    if x > mid :
      total += x - mid
  if total < m :
    end = mid -1
  else :
    result = mid
    start = mid +1

print("절단기의 최대 높이 : ", result)



