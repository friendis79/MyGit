import random
tries = 0
guess = 0
answer = random.randint(1, 100)

print("Match the numbers from 1 to 100 given by the computer: ")

while True :
    guess = int(input("Enter number : "))
       
    tries += 1
    
    if guess > answer:
         print("Lower than the number suggested by the computer!")
         
    elif guess < answer:
        print("Hihger than the number suggested by the computer!")
        
    else:
            print("Congraurations!")
            print("Tries : %d" % tries)
            print("Answer : %d" % answer)
            break