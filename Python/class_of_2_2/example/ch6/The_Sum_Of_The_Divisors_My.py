n = int(input("자연수를 입력하세요 : "))
list1 = []

for i in range(1,n): # 반복횟수가 많아 속도가 느려질 수 有
    if n%i == 0:
        list1.append(i)

if sum(list1) == n:
    print("%d is Perfect" %n)
    print("%d = " %n, end='')
    for i in range(0, len(list1)) :
        print(list1[i], end=' ')
        if i != len(list1)-1 :
            print('+', end=' ')
        
else :
    print("%d is NOT perfect." % n)
    
    
    
    
    