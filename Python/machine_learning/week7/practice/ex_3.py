# 실습 3 - 실습 2에서 만든 훈련 집합을 적용해 k = 6,7,8,9,10,11,12,13일 때의 가우스 함수를 이용한 선형 기저함수 모델의 최적해 구하기

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

# 각 k 값에 대한 최적 가중치 및 MSE 계산
for k in range(6, 14):
    weights, mse = gaussian_weights(k, train_age, train_height)

    print(f"k = {k}의 최적해 : {weights}")
    print("-" * 50)
