import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

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
data = pd.read_csv("C:/Coding/Python/machine_learning/week8, 9/Iris.csv", names=['sepal_length', 'petal_length', 'variety'])

# 데이터에서 꽃받침 길이(cm), 꽃잎 길이(cm), iris (0, 1) 추출
iris_data = data[data['variety'].isin(['Setosa', 'Versicolor'])]

# Setosa를 0, Versicolor를 1로 변환
iris_data['variety'] = iris_data['variety'].map({'Setosa': 0, 'Versicolor': 1})

# 입력값(X)과 목표값(y) 분리
X1 = iris_data[['sepal_length']].values.reshape(-1, 1)
X2 = iris_data[['petal_length']].values.reshape(-1, 1)
ones_column = np.ones((len(X1), 1))
X = np.hstack((X1, X2, ones_column))

y = iris_data['variety'].values

# 3차원 공간에 데이터 표시
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# Setosa 종류의 데이터 0으로 구분
setosa = data[data['variety'] == 'Setosa']
ax.scatter(setosa['sepal_length'], setosa['petal_length'], [0] * len(setosa), c='r', label='Setosa')

# Versicolor 종류의 데이터 1으로 구분
versicolor = data[data['variety'] == 'Versicolor']
ax.scatter(versicolor['sepal_length'], versicolor['petal_length'], [1] * len(versicolor), c='b', label='Versicolor')

# 축 레이블과 범례 추가
ax.set_xlabel('Sepal (cm)')
ax.set_ylabel('Petal (cm)')
ax.set_zlabel('Variety')
ax.legend()

plt.title('Emperical Solution')

# Decision boundary 표시

# 학습률과 에포크 설정
learning_rate = 0.001
epochs = 20_000

# Gradient Descent 알고리즘 적용
weights, loss_history, weights_history = gradient_descent(X, y, learning_rate, epochs)

# 결정 경계 표시
x_values = np.linspace(np.min(X[:, 0]), np.max(X[:, 0]), 100)
y_values = np.linspace(np.min(X[:, 1]), np.max(X[:, 1]), 100)
x_values, y_values = np.meshgrid(x_values, y_values)
z_values = (weights[0] )* x_values + (weights[1]) * y_values + (weights[2]) 
ax.plot_surface(x_values, y_values, z_values, alpha=0.5)
plt.show()

# 정확도 출력
Accuracy = accuracy(X, y, weights)
print(f'훈련결과, 정확도 : {Accuracy:.2f}%')

# 임의의 값으로 성별 예측
random_weight = np.array([1, 1, 1])  # 임의의 값
prediction = predict(weights, random_weight)
print(f'Predicted gender for weight 20g: {prediction}')

print('최종 가중치 (w0, w1, w2):', weights[0], weights[1], weights[2])