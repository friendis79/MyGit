p = int(input("cash : "))
r = float(input("interest : "))
n = int(input("time : "))

r /= 100
m_r = (1+r/12)
cash = p*m_r*(m_r**(n*12)-1)/(r/12)

print("매월 %d를 예금하면 %d년 후 원리금은 %d입니다." % (p, n, cash))