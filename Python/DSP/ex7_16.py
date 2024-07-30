import numpy as np
import matplotlib.pyplot as plt

def convolution(x, h):
    # x와 h의 길이
    M = len(x)
    N = len(h)
    
    # 결과를 저장할 배열 초기화
    y = np.ones(M + N - 1)
    
    # 컨볼루션 연산
    for n in range(M + N - 1):
        y[n] = 0
        for k in range(M):
            if n - k >= 0 and n - k < N:
                y[n] += x[k] * h[n - k]
    
    return y

# x[n] = e^-an * u[n], a > 0
def x_n(a, n):
    return np.exp(-a * n) * (n >= 0)

# h[n] = u[n]
def h_n(n):
    return n >= 0

# n의 범위
n_values = np.arange(-10, 11)

# a와 n의 값을 설정
a = 0.5

# x[n]과 h[n]을 계산
x_values = x_n(a, n_values)
h_values = h_n(n_values)

# 컨볼루션 계산
convolved = convolution(x_values, h_values)

# 그래프 그리기
plt.figure(figsize=(12, 6))

plt.subplot(3, 1, 1)
plt.stem(n_values, x_values, use_line_collection=True)
plt.title('$x[n] = e^{-an} \cdot u[n]$, a > 0')
plt.xlabel('n')
plt.ylabel('x[n]')
plt.grid()

plt.subplot(3, 1, 2)
plt.stem(n_values, h_values, use_line_collection=True)
plt.title('$h[n] = u[n]$')
plt.xlabel('n')
plt.ylabel('h[n]')
plt.grid()

plt.subplot(3, 1, 3)
plt.stem(np.arange(-20, 21), convolved, use_line_collection=True)
plt.title('$x[n] * h[n]$')
plt.xlabel('n')
plt.ylabel('y[n]')
plt.grid()

plt.tight_layout()
plt.show()