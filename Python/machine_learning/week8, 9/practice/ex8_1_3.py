# 실습 1_3 - 사슴벌레 분류 문제를 Logistic Regression으로 판별 후 Cross Entropy Loss & Gradient Descent 알고리즘을 적용하여 가중치 w_0, w_1을 구하고 그 변화과정을 plot

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# sigmoid
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

# Cross Entropy Loss
def cross_entropy_loss(y_true, y_pred):
    epsilon = 1e-15  # 로그의 값이 무한대로 발산하는 것을 방지하기 위한 아주 작은 값
    y_pred = np.clip(y_pred, epsilon, 1 - epsilon)  # 0 또는 1에 수렴하지 않도록 값 제한
    return -np.mean(y_true * np.log(y_pred) + (1 - y_true) * np.log(1 - y_pred))

# Gradient Descent
def gradient_descent(X, y, learning_rate, epochs):
    n = X.shape[0]  # data sample
    m = X.shape[1]  # bias & weights
    w = np.ones(m)
    loss_history = []
    weights_history = []

    for epoch in range(epochs):
        z = np.dot(X, w)
        y_pred = sigmoid(z)
        loss = cross_entropy_loss(y, y_pred)
        gradient = np.dot(X.T, (y_pred - y)) / n
        w -= learning_rate * gradient
        loss_history.append(loss)
        weights_history.append(w.copy())

        if (epoch + 1) % 10000 == 0:
            print(f'Epoch {epoch + 1}, Loss: {loss}')
    
    return w, loss_history, weights_history


# CSV 파일을 읽어 Pandas DataFrame으로 변환
data = pd.read_csv("C:/Coding/Python/machine_learning/week8, 9/binary_data_insect.csv", names=['weights', 'genders'])

# 데이터에서 사슴벌레의 무게(g)와 성별 추출
X = data['weights'].to_numpy()
y = data['genders'].to_numpy()

# bias을 위한 Intercept 항 추가
X = np.vstack([ X , np.ones(len(X))]).T # 주어진 배열들을 수직으로 쌓아서(위아래로) 하나의 배열로 결합

# 학습률과 에포크 설정
learning_rate = 0.001
epochs = 250_000

# Gradient Descent 알고리즘 적용
weights, loss_history, weights_history = gradient_descent(X, y, learning_rate, epochs)

# 에포크와 Cross Entropy Loss에 대한 그래프
plt.figure(figsize=(10, 6))
plt.plot(loss_history, 'g')
plt.title('Cross Entropy Loss')
plt.xlabel('Epochs')
plt.ylabel('Cross Entropy Loss')
plt.grid()
plt.show()

# 에포크와 가중치 대한 그래프
weights_history = np.array(weights_history)
plt.figure(figsize=(10, 6))
plt.plot(weights_history[:, 0], 'b', label='w0')
plt.plot(weights_history[:, 1], 'r', label='w1')
plt.title('Weight')
plt.xlabel('Epochs')
plt.ylabel('Weights')
plt.legend()
plt.grid()
plt.show()

print('최종 가중치 (w0, w1):', weights)