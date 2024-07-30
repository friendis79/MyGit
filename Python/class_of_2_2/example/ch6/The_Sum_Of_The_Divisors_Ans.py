while True:
    N = int(input("자연수를 입력 :"))
    if N == -1:
        break
    measure = []
    for i in range(1, int(N/2)+1):
        if N % i == 0:
            measure.append(i)
            
    if sum(measure) != N:
        print("%d is NOT perfect." %N)
        
    else :
        length = len(measure)
        print("%d = " %N, end = "")
        for k in range(length):
            if k < length -1:
                print("%d + " %measure[k], end="")
            else :
                print("%d" %measure[k])