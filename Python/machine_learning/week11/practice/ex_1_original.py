# 실습 1 - AND, OR, NAND 퍼셉트론을 활용하여 XOR 게이트를 구현

import numpy as np

# AND Gate
def AND(x1, x2, w1 = 1.0, w2 = 1.0, b = -1.2):  # x1w1 + x2w2 + b > 0 일 때 y = 1, 그렇지 않으면 y = 0이어야 하므로 가중치(w1, w2)는 양수, b는 음수가 되어야 한다.
    x = np.array([x1, x2])
    w = np.array([w1, w2])
    return 1 if np.sum(x*w) + b >=0 else 0

# OR Gate
def OR(x1, x2, w1 = 1.0, w2 = 1.0, b = -0.5):   # # x1w1 + x2w2 + b > 0 일 때 y = 1, 그렇지 않으면 y = 0이어야 하므로 가중치(w1, w2)는 양수, b는 음수가 되어야 한다.
    x = np.array([x1, x2])
    x = np.array([x1, x2])
    w = np.array([w1, w2])
    return 1 if np.sum(x*w) + b >=0 else 0

# NAND Gate
def NAND(x1, x2, w1 = -1.0, w2 = -1.0, b = 1.2):    # # x1w1 + x2w2 + b > 0 일 때 y = 0, 그렇지 않으면 y = 1이어야 하므로 가중치(w1, w2)는 음수, b는 양수가 되어야 한다.
    x = np.array([x1, x2])
    w = np.array([w1, w2])
    return 1 if np.sum(x*w) + b >=0 else 0

# XOR Gate
def XOR(x1, x2):
    s1 = NAND(x1, x2)
    s2 = OR(x1, x2)
    return AND(s1, s2)

print("OR Gate")
for x1 in [0, 1]:
    for x2 in [0, 1]:
        print(f"[{x1}, {x2}] => {OR(x1, x2)}")

print("\n")

print("NAND Gate")
for x1 in [0, 1]:
    for x2 in [0, 1]:
        print(f"[{x1}, {x2}] => {NAND(x1, x2)}")

print("\n")        

print("XOR Gate")
for x1 in [0, 1]:
    for x2 in [0, 1]:
        print(f"[{x1}, {x2}] => {XOR(x1, x2)}")