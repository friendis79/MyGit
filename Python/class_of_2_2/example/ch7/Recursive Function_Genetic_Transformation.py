# 재귀 호출

def base2(n):
    if n < 2:
        print(numberChar[n], end = '')
    else :
        base2(n // 2) # // -> 정수 나눗셈 연산자
        print(numberChar[n % 2], end = '')

def base8(n):
    if n < 8:
        print(numberChar[n], end = '')
    else :
        base2(n // 8)
        print(numberChar[n % 8], end = '')
        
def base16(n):
    if n < 16:
        print(numberChar[n], end = '')
    else :
        base2(n // 16)
        print(numberChar[n % 16], end = '')
        
numberChar = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
numberChar += ['A', 'B', 'C', 'D', 'E', 'F']

number = int(input("Enter decimal number : "))

print("\n Binary : ", end = '')
base2(number)

print("\n Octal : ", end = '')
base8(number)

print("\n Hexadecimal : ", end = '')
base16(number)