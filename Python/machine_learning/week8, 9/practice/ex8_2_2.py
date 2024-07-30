# 실습 2_2 - Cross Entropy Loss를 비용함수로 사용하는 경사하강법 구현 및 경사하강법의 반복 횟수에 따른 Cross Entropy Loss의 변화 및 매개변수의 변화를 그래프로 그리기

import pandas as pd
import numpy as np
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
    w = np.zeros(m)
    loss_history = []
    weights_history = []

    for i in range(m) : # 주어진 범위에 맞게  임의의 값 설정
        w[i] = np.random.uniform(low = -3.0, high=3.0) 

    for epoch in range(epochs):
        z = np.dot(X, w) 
        y_pred = sigmoid(z)
        loss = cross_entropy_loss(y, y_pred)
        gradient = np.dot(X.T, (y_pred - y)) 
        w -= learning_rate * gradient
        
        loss_history.append(loss)
        weights_history.append(w.copy())

        if (epoch + 1) % 1000 == 0:
            print(f'Epoch {epoch + 1}, Loss: {loss}')
    
    return w, loss_history, weights_history

# CSV 파일을 읽어 Pandas DataFrame으로 변환
data = pd.read_csv("C:/Coding/Python/machine_learning/week8, 9/Iris.csv", names=['sepal_length', 'petal_length', 'variety'])

data = data[data['variety'].isin(['Setosa', 'Versicolor'])]
# 데이터에서 꽃받침 길이(cm), 꽃잎 길이(cm), iris (0, 1) 추출

# Setosa를 0, Versicolor를 1로 변환
data['variety'] = data['variety'].map({'Setosa': 0, 'Versicolor': 1})

# 입력값(X)과 목표값(y) 분리
X1 = data[['sepal_length']].values.reshape(-1, 1)
X2 = data[['petal_length']].values.reshape(-1, 1)
ones_column = np.ones((len(X1), 1))
X = np.hstack((X1, X2, ones_column))

y = data['variety'].values

# 학습률과 에포크 설정
learning_rate = 0.001
epochs = 20_000

# Gradient Descent 알고리즘 적용
weights, loss_history, weights_history = gradient_descent(X, y, learning_rate, epochs)

epochs_ = range(0, epochs)

# 에포크 수에 따른 Cross Entropy Loss의 변화
plt.figure(figsize=(10, 6))
plt.plot(epochs_, loss_history, 'green')
plt.title('Cross Entropy Loss')
plt.xlabel('Epochs')
plt.ylabel('Cross Entropy Loss')
plt.xlim(0, epochs)
plt.grid()
plt.show()

# 에포크 수에 따른 가중치의 변화
weights_history = np.array(weights_history)
plt.figure(figsize=(10, 6))
plt.plot(epochs_, weights_history[:, 0],'black',  label='w0')
plt.plot(epochs_, weights_history[:, 1],'red', label='w1')
plt.plot(epochs_, weights_history[:, 2],'blue',  label='w2')
plt.title('Weights')
plt.xlabel('Epochs')
plt.ylabel('Weights')   
plt.xlim(0, epochs)
plt.legend()
plt.grid()
plt.show()

print('최종 가중치 (w0, w1, w2):', weights[0], weights[1], weights[2])