# 실습 1_1 - Logistic Regression에 사용되는 Sigmoid 함수 plot

import numpy as np
import matplotlib.pyplot as plt

# sigmoid 함수 정의
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

x = np.linspace(-10, 10, 100)  # -10부터 10까지 100등분한 값
y = sigmoid(x)

plt.plot(x, y)
plt.title('Sigmoid Function')
plt.xlabel('x')
plt.ylabel('y')
plt.grid()

plt.show()