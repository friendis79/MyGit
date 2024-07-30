a, b, c = map(int, input("Enter a, b, c value : ").split())
    
print("%d^2 + %dx + %d 방정식의 근은" % (a, b, c))

D = b**2 - 4*a*c

if D > 0:
    print("서로 다근 두 실근입니다.")
    
elif D == 0:
    print("중근입니다.")
    
else:
    print("서로 다른 두 허근입니다.")
    