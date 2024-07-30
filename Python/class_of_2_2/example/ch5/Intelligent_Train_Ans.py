getin = []
getoff = []
remain = []

r= 0

for i in range(5):
    print("%d station : " % (i+1), end = '')
    a, b = map(int, input("getin  getoff : ").split())
    getin.append(a)
    getoff.append(b)
    c = b - a
    r = r + c
    remain.append(r)
    
print("max : %d" %max(remain))