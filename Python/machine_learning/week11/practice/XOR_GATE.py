# AND GATE
def AND_percepytron(x1, x2 ):
    w1, w2, w0 = 1.0, 1.0, -1.2
    sum = w1*x1 + w2*x2 + w0
    if sum >= 0 :
        return 1
    else : 
        return 0

# OR GATE
def OR_percepytron(x1, x2 ):
    w1, w2, w0 = 1.0, 1.0, -0.8
    sum = w1*x1 + w2*x2 + w0
    if sum >= 0 :
        return 1
    else : 
        return 0

# NAND GATE
def NAND_percepytron(x1, x2 ):
    w1, w2, w0 = 1.0, 1.0, -1.2
    sum = w1*x1 + w2*x2 + w0
    if sum <= 0 :
        return 1
    else : 
        return 0
    
# XOR GATE 
def XOR_percepytron(x1, x2) :
    s1 = NAND_percepytron(x1, x2 )
    s2 = OR_percepytron(x1, x2 )
    return AND_percepytron(s1, s2 )

# XOR 게이트의 진리표 출력
print("XOR Gate Truth Table:")
print("x1 | x2 | XOR(x1, x2)")
print("---------------------")
for x1 in [0, 1]:
    for x2 in [0, 1]:
        print(f"{x1}  | {x2}  |  {XOR_percepytron(x1, x2)}")