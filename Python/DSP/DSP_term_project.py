import numpy as np
import matplotlib.pyplot as plt

def chebyshev_poly(n, x):
    """체비셰프 다항식 T_n(x) 계산"""
    if n == 0:
        return np.ones_like(x)
    elif n == 1:
        return x
    else:
        Tn_1 = x
        Tn_2 = np.ones_like(x)
        for i in range(2, n + 1):
            Tn = 2 * x * Tn_1 - Tn_2
            Tn_2 = Tn_1
            Tn_1 = Tn
        return Tn_1

def chebyshev_filter_response(N, epsilon, w):
    """체비셰프 필터의 주파수 응답 계산"""
    cos_w = np.cos(w)
    Tn_w = chebyshev_poly(N, cos_w)
    H_w = 1 / np.sqrt(1 + epsilon**2 * Tn_w**2)
    return H_w

# 필터 매개변수 설정
epsilon = 0.5  # 리플 파라미터
w = np.linspace(-2 * np.pi, 2 * np.pi, 1000)

# 그래프 설정
fig, axs = plt.subplots(2, 2, figsize=(12, 8))
orders = [1, 2, 3, 4]
colors = ['blue', 'green', 'orange', 'red']

for i, order in enumerate(orders):
    H_w = chebyshev_filter_response(order, epsilon, w)
    ax = axs[i // 2, i % 2]
    ax.plot(w, H_w, color=colors[i])
    ax.set_title(f'Chebyshev Filter Order {order}')
    ax.set_xlabel('Frequency (rad/sample)')
    ax.set_ylabel('Amplitude')
    ax.grid()

plt.tight_layout()
plt.show()