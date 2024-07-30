# 실습 4 - 실습 3에서 구한 선형 기저함수 모델의 평균제곱오차(MSE)를 훈련 집합과 테스트 집합에 대해 각각 구하고 그래프로 표시

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Gaussian Basis Function
def gaussian_basis(x, mu, sigma):
    return np.exp(-0.5 * ((x - mu) / sigma) ** 2)

# Gaussian Weights Calculation
def gaussian_weights(k, x, y):
    rho = ((max(x) - min(x)) / (k - 1))  # rho 계산
    centers = np.linspace(min(x), max(x), k)  # 중심 계산
    basis_functions = gaussian_basis(x[:, np.newaxis], centers, rho)  # 가우시안 함수 계산
    matrix = np.column_stack((basis_functions, np.ones(len(x))))  # 바이어스 항 추가
    weights = np.linalg.pinv(matrix.T @ matrix) @ matrix.T @ y  # 최적 가중치 계산
    y_predict = matrix @ weights
    mse = np.mean((y_predict - y) ** 2)  # MSE 계산
    return weights, mse

# CSV 파일을 읽어 Pandas DataFrame으로 변환
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week7/lin_regression_data_03.csv", names=['age', 'height'])

# 총 데이터 크기를 구하고 교육 및 테스트 데이터 크기 계산
data_size = raw_data.shape[0]
train_size = int(0.8 * data_size)  # training data -> 80%
test_size = data_size - train_size # test data -> 20%

# training, test data 구분
train_data = raw_data[:train_size]
test_data = raw_data[train_size:]

# 나이 및 키 데이터 추출
train_age = train_data['age'].to_numpy()
train_height = train_data['height'].to_numpy()

test_age = test_data['age'].to_numpy()
test_height = test_data['height'].to_numpy()

k_values = range(6, 14)
train_mse_values = []
test_mse_values = []

# # k 값을 기준으로 MSE 계산 및 그래프 표시
for k in k_values:
    # 훈련 데이터 MSE 계산
    train_weights, train_mse = gaussian_weights(k, train_age, train_height)
    train_mse_values.append(train_mse)
    
    # 훈련 데이터에서 훈련된 가중치를 사용하여 MSE 계산
    test_basis_functions = gaussian_basis(test_age[:, np.newaxis], np.linspace(min(train_age), max(train_age), k),
                                          (max(train_age) - min(train_age)) / (k - 1))
    test_matrix = np.column_stack((test_basis_functions, np.ones(len(test_age))))
    y_predict_test = test_matrix @ train_weights
    test_mse = np.mean((y_predict_test - test_height) ** 2)
    test_mse_values.append(test_mse)

# plot
plt.plot(k_values, train_mse_values, label='training MSE', color='blue')
plt.plot(k_values, test_mse_values, label='test MSE', color='orange')

plt.xlabel('k')
plt.ylabel('MSE')
plt.title('Comparison of training and testing MSEs according to k values')
plt.grid()
plt.legend()

plt.show()