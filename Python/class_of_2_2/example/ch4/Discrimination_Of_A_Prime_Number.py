n = int(input("Enter a positive integer greater than 1: "))

for i in range(2, n+1) :
     answer = True
     for a in range(2,i) :
        if i % a == 0 :
            answer = False
            break
     if answer == True:
         print(i, end = ' ')