# 실습 4 - 경사하강법 프로그램을 이용해 최적 매개변수 구하기

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 경사하강법 함수 정의
def numerical_gradient(f, W, X, y):
    h = 1e-4
    grad = np.zeros_like(W) # W와 동일한 형태의 0으로 채워진 배열 생성

    for idx in range(W.size):   # W의 모든 원소에 대해 반복
        tmp_val = W[idx]     # 원래의 값 저장

        # f(W+h) 계산
        W[idx] = tmp_val+h
        fxh1 = f(W, X, y)

        # f(W-h) 계산
        W[idx] = tmp_val-h
        fxh2 = f(W, X, y)

        # 기울기 계산
        grad[idx] = (fxh1-fxh2) / (2*h)

        W[idx] = tmp_val    # 값 복원

    return grad

# MSE 함수 정의
def function_MSE(W,X,y):
    mse = np.zeros(len(X))  # MSE를 저장할 배열을 초기화

    # 각 데이터 포인트에 대해 MSE를 계산
    for idx in range(len(X)):
        mse[idx] = (np.dot(W.T, X[idx]) - y[idx]) ** 2  # 예측값과 실제값의 차이의 제곱을 계산
    
    mse = np.sum(mse) / len(X)   # 모든 데이터 포인트에 대한 MSE를 합하여 평균을 계산

    return mse

# CSV 파일을 읽어 Pandas DataFrame으로 변환 
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week5/multiple_linear_regression_data.csv", names = ['height', 'weight', 'age'])

# raw_data
height = raw_data['height'].to_numpy()
weight = raw_data['weight'].to_numpy()
age = raw_data['age'].to_numpy()

# convert data
X = raw_data[['height', 'weight']].to_numpy()
X = np.c_[X, np.ones(len(X))]

y = raw_data['age'].to_numpy()
y = y.reshape((len(y), 1))

# X의 역행렬을 이용하여 해를 계산 
analytic_W = np.linalg.pinv(X.T @ X) @ X.T @ y
print(f"해석해 : \n {analytic_W}")

mse = function_MSE(analytic_W, X, y)
print(f'mse : {mse}')

num_epoch = 100_000 # 경사하강법을 수행할 epoch 수
eta = 1e-5   # Learning Rate
errors = [] # 각 에포크마다의 MSE를 저장할 리스트 초기화

# GD
GD_W = np.ones((3, 1))  # 경사하강법으로 찾을 가중치 초기값 설정
GD_W[0] = np.random.uniform(low=-1.0, high=1.0)   # 경사하강법으로 찾을 GD_W[0] 가중치를 무작위하게 설정
GD_W[1] = np.random.uniform(low=-1.0, high=1.0)   # 경사하강법으로 찾을 GD_W[1] 가중치를 무작위하게 설정
GD_W[2] = np.random.uniform(low=-15.0, high=-10.0)   # 경사하강법으로 찾을 GD_W[2] 가중치를 무작위하게 설정
print(f"랜덤하게 초기화한 가중치 값 : \n {GD_W}")

GD_W0_history = []  # W0의 변화를 저장할 리스트 초기화
GD_W1_history = []  # W1의 변화를 저장할 리스트 초기화
GD_W2_history = []  # W2의 변화를 저장할 리스트 초기화

for epoch in range (num_epoch):
    mse = function_MSE(GD_W, X, y) # 현재 가중치로의 MSE 계산
    gradient = numerical_gradient(function_MSE, GD_W, X, y)    # 현재 위치에서의 기울기 계산
    GD_W = GD_W - eta * gradient    # 경사하강법으로 가중치 업데이트

    if mse < 1.7:
        print("GD를 종료합니다.")
        break

    errors.append(mse)  # 현재 에포크의 MSE를 저장
    GD_W0_history.append(GD_W[0])   # 현재 W0를 저장
    GD_W1_history.append(GD_W[1])   # 현재 W1를 저장
    GD_W2_history.append(GD_W[2])   # 현재 W2를 저장
    if epoch % 1000 == 0:
        print(f"epoch : {epoch} ===============> W : {GD_W.flatten()}, gradient : {gradient.flatten()}, mse : {mse}")

print(f"결과 GD_W : \n {GD_W}")

# plot

height_data = np.linspace(55, 190, 1000)
weight_data = np.linspace(10, 100, 1000)
Height, Weight = np.meshgrid(height_data, weight_data)
analytic_y = analytic_W[0]*Height + analytic_W[1]*Weight + analytic_W[2]

fig = plt.figure()
ax1 = fig.add_subplot(121, projection='3d')  # Analytic Solution
ax2 = fig.add_subplot(122, projection='3d')  # Gradient Descent Method

ax1.scatter(height, weight, age)
ax1.plot_surface(Height, Weight, analytic_y, cmap='plasma')
ax1.set_xlabel('height')
ax1.set_ylabel('weight')
ax1.set_zlabel('age')
ax1.set_title('Analytic Solution')

GD_y =GD_W[0]*Height +GD_W[1]*Weight + GD_W[2]

ax2.scatter(height, weight, age)
ax2.plot_surface(Height, Weight, GD_y, cmap='plasma')
ax2.set_xlabel('height')
ax2.set_ylabel('weight')
ax2.set_zlabel('age')
ax2.set_title('Gradient Decent Method')

plt.show()