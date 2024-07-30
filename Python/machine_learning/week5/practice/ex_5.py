# 주어진 데이터에 대해 K개의 가우스 함수를 이용한 선형 기저함수회귀모델의 최적 매개변수(해석해)를 자동 계산하는 프로그램

import numpy as np
import pandas as pd

# 가우시안 함수 정의
def gaussian_basis(x, mu, sigma):
    return np.exp(-0.5 * ((x - mu) / sigma) ** 2)

# 가우시안 최적의 가중치 계산
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
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week5/linear_regression_data01.csv", names=['age', 'height'])

# raw_data
age = raw_data['age'].to_numpy()
height = raw_data['height'].to_numpy()

# 가우시안 기저 함수의 가중치 계산
k_values = [3, 5, 8]  # 다양한 기저 함수 개수에 대해 설정

# 각 K 값에 대해 최적의 가중치 계산
gaussian_weights_history = [gaussian_weights(k, age, height) for k in k_values]

# 결과 출력
for k, (weights, mse) in zip(k_values, gaussian_weights_history):
    print(f'\nk={k}, \ngaussian_weights = {weights}, \nMSE = {mse:.4f}')