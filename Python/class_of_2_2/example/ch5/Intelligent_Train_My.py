outt = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
inn = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

current_p = 0
max_p = 0

for i in range(0, 10) :
    outt[i], inn[i] = map(int, input(str(i+1) + "번역 내린 사람 탄 사람 : ").split())

for i in range(0, 10) :
    current_p = current_p - outt[i] + inn[i]
    if current_p >= max_p:
        max_p = current_p
        
print("최대 인원수는 %d" %max_p)