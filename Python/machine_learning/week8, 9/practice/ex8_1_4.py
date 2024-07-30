# 실습 1_4 - Logistic Regression의 정확도를 산출하고 Decision Boundary를 plot 
# ※ predict 함수를 만들어 임의의 값을 이용해 성별을 판별

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# sigmoid
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

# Cross Entropy Loss
def cross_entropy_loss(y_true, y_pred):
    epsilon = 1e-15 # 로그의 값이 무한대로 발산하는 것을 방지하기 위한 아주 작은 값
    y_pred = np.clip(y_pred, epsilon, 1 - epsilon)  # 0 또는 1에 수렴하지 않도록 값 제한
    return -np.mean(y_true * np.log(y_pred) + (1 - y_true) * np.log(1 - y_pred))

# Gradient Descent
def gradient_descent(X, y, learning_rate, epochs):
    n = X.shape[0]  # data sample
    m = X.shape[1]  # bias & weights
    w = np.ones(m)
    loss_history = []
    acc_history = []

    for epoch in range(epochs):
        z = np.dot(X, w)
        y_pred = sigmoid(z)
        loss = cross_entropy_loss(y, y_pred)
        gradient = np.dot(X.T, (y_pred - y)) / n
        w -= learning_rate * gradient
        loss_history.append(loss)

        # 정확도 계산
        acc = accuracy(X, y, w)
        acc_history.append(acc)

        if (epoch + 1) % 10000 == 0:
            print(f'Epoch {epoch + 1}, Loss: {loss}, Accuracy: {acc}%')
    
    return w, loss_history, acc_history

# accuracy
def accuracy(X, y, weights):
    y_pred = predict(X, weights)
    y_pred_class = np.where(y_pred >= 0.5, 1, 0)  # 확률을 0 또는 1로 변환
    acc = np.mean(y_pred_class == y) * 100
    return acc

# predict
def predict(weight, weights):
    z = weight @ weights
    prob_male = sigmoid(z)
    return np.where(prob_male >= 0.5, 1, 0)  # 0.5 이상이면 1(Male), 아니면 0(Female)으로 예측

# CSV 파일을 읽어 Pandas DataFrame으로 변환
data = pd.read_csv("C:/Coding/Python/machine_learning/week8, 9/binary_data_insect.csv", names=['weight', 'gender'])

# 데이터에서 사슴벌레의 무게(g)와 성별 추출
X = data['weight'].to_numpy()
y = data['gender'].to_numpy()

# 절편(bias)을 위한 Intercept 항 추가
X = np.vstack([ X , np.ones(len(X))]).T

# 성별에 따라 색상 설정
colors = ['blue' if g == 0 else 'red' for g in y]

# 데이터 포인트 및 예측값 시각화
plt.figure(figsize=(10, 6))
plt.scatter(data['weight'], data['gender'], c=colors)
plt.xlabel('Weights(g)')
plt.ylabel('Gender (0: Female, 1: Male)')
plt.title('Stagworm Weight and Gender Distribution')
plt.grid()

# Decision boundary 직선 그리기

# 하이퍼파라미터 설정
learning_rate = 0.001
epochs = 250_000

# Gradient Descent를 통한 모델 학습
weights, loss_history, acc_history = gradient_descent(X, y, learning_rate, epochs)

x_values = np.linspace(np.min(X), np.max(X), len(X))
y_values = weights[0] * x_values + weights[1]
plt.plot(x_values, y_values, label='Decision Boundary')
plt.xlim(20, 100)
plt.ylim(-0.2, 1.2)
plt.legend()
plt.show()

# 임의의 값을 사용하여 성별 예측
random_weight = np.array([1, 20])
predicted_gender = predict(random_weight, weights)

Accuracy = accuracy(X, y, weights)
prediction = predict(weights, random_weight)

print(f'훈련결과, 정확도 : {Accuracy:.2f}%')
print(f'Predicted gender for weight 20g: {prediction}')
print(f'w0 = {weights[0]}, w1 = {weights[1]}')