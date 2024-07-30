# Fibonacci Sequence Module

def fib(n): #피보나치 수열을 차례대로 출력
    a, b = 0, 1
    while b < n:
        print(b, end = '')
        c = a+ b
        a = b
        b= c
    print(fib)
    
def fib2(n) : #피보나치 수열을 리스트로 반환
    result = []
    a, b = 0, 1
    while b < n:
        result.append(b)
        a, b = b, a + b
    return result