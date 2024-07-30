# 실습 7  - 실습 6에서 각 K개에 대한 평균제곱오차를 구하고 x축은 K값, y축은 평균제곱오차를 나타내는 2차원 그래프

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

# MSE 계산 함수
def calculate_mse(k, age, height):
    weights, mse = gaussian_weights(k, age, height)
    return mse

# plot
def plot_mse_vs_k(k_values, mse_values):
    plt.stem(k_values, mse_values, linefmt='b-', markerfmt='bo', basefmt='r-')
    plt.xlabel('Number of Basis Functions (K)')
    plt.ylabel('Mean Squared Error (MSE)')
    plt.title('MSE vs. Number of Basis Functions')
    plt.grid(True)
    plt.show()

# CSV 파일을 읽어 Pandas DataFrame으로 변환 
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week5/linear_regression_data01.csv", names=['age', 'height'])

# raw_data
height = raw_data['height'].to_numpy() # 키 데이터 추출
age = raw_data['age'].to_numpy() # 나이 데이터 추출

# 가우시안 기저 함수의 가중치
k_values = [3, 5, 8, 10]  # 다양한 기저 함수 개수에 대해 설정

# MSE
mse_values = [calculate_mse(k, age, height) for k in k_values]

# 그래프 그리기 함수 호출
plot_mse_vs_k(k_values, mse_values)