# 실습 6 - K = 3, 5, 8, 10일 때, 훈련 데이터와 선형 기저함수 회귀 모델을 그래프에 표시

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 가우시안 함수 정의
def gaussian_basis(x, mu, sigma):
    return np.exp(-0.5 * ((x - mu) / sigma) ** 2)

# 가우시안 최적의 가중치 계산
def gaussian_weights(k, x, y):
    rho = ((max(x) - min(x)) / (k - 1))  # 간격 계산
    centers = np.linspace(min(x), max(x), k)  # 중심 계산
    basis_functions = gaussian_basis(x[:, np.newaxis], centers, rho)  # 가우시안 함수 계산
    matrix = np.column_stack((basis_functions, np.ones(len(x))))  # 바이어스 항 추가
    weights = np.linalg.pinv(matrix.T @ matrix) @ matrix.T @ y  # 최적 가중치 계산
    y_predict = matrix @ weights
    mse = np.mean((y_predict - y) ** 2)  # MSE 계산
    return weights, mse

# plot
def plot_gaussian_regression(ax, age, height, k, weights, mse):
    age_ = np.linspace(np.min(age), np.max(age), len(age))
    data_range = (max(age) - min(age)) / (k - 1) # sigma
    centers = np.linspace(min(age), max(age), k)
    basis_functions = np.array([gaussian_basis(age_, center, data_range ) for center in centers]).T
    basis_functions = np.column_stack((basis_functions, np.ones(len(age_))))
    print(basis_functions)
    y_predict = basis_functions @ weights
    ax.scatter(age, height, label='Original')
    ax.plot(age_, y_predict, 'r', label=f'Predict, k={k}, MSE = {mse:.3f}')
    ax.set_ylabel('Height')
    ax.set_xlabel('Age')
    ax.set_title(f'Regression with gaussian basis function (k={k})')
    ax.legend()
    ax.grid()

# CSV 파일을 읽어 Pandas DataFrame으로 변환 
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week5/linear_regression_data01.csv", names=['age', 'height'])

# raw_data
age = raw_data['age'].to_numpy()
height = raw_data['height'].to_numpy()

# 가우시안 기저 함수의 가중치 계산
k_values = [3, 5, 8, 10]  # 다양한 기저 함수 개수에 대해 설정

# 2x2 subplot
fig, axs = plt.subplots(2, 2, figsize=(10, 8))

# subplot plot
for i in range(2):
    for j in range(2):
        k = k_values[i*2 + j]  # 각각의 서브플롯에 대해 같은 k 값을 사용

        weights, mse = gaussian_weights(k, age, height) # 가중치 계산

        # plot 호출
        plot_gaussian_regression(axs[i, j], age, height, k, weights, mse)

plt.tight_layout()
plt.show()