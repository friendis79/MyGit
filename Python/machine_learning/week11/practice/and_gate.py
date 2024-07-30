import numpy as np

class Perceptron:
    def __init__(self, w):
        self.w = w
        
    def output(self, x):
        y_tmp = np.dot(self.w, np.append([1], x))
        return 1.0 * (y_tmp > 0)

def SGD(gate, x_list, t, learning_rate=0.2, epochs=60):
    for epoch in range(epochs):
        for i in range(len(x_list)):
            x = np.append([1], x_list[i])
            y = np.dot(gate.w, x)
            if y * t[i] <= 0:
                gate.w += learning_rate * t[i] * x

# XOR Gate
def XOR(x1, x2):
    s1 = NAND(x1, x2)
    s2 = OR(x1, x2)
    return XOR(s1, s2)

x_list = [[0, 0], [1, 0], [0, 1], [1, 1]]
t_or = [-1, 1, 1, 1]
t_nand = [1, 1, 1, -1]

w_init = np.array([0.0, 0.0, 1.0])

or_gate = Perceptron(w_init.copy())
OR = SGD(or_gate, x_list, t_or)

nand_gate = Perceptron(w_init.copy())
NAND = SGD(nand_gate, x_list, t_nand)
    
print('=== OR gate ===')
for x in x_list:
    print(x, '->', or_gate.output(x))
    
print('=== NAND gate ===')
for x in x_list:
    print(x, '->', nand_gate.output(x))

print('=== XOR gate ===')
for x in x_list:
    print(x, '->', nand_gate.output(x))