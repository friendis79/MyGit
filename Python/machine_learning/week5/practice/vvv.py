# 실습 6 - K = 3, 5, 8, 10일 때, 훈련 데이터와 선형 기저함수 회귀 모델을 그래프에 표시

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# X를 다항 기저 함수로 변환
def polynomial_basis(X, K):
    n_samples, n_features = X.shape
    X_poly = np.ones((n_samples, 1))
    for d in range(1, K + 1):
        X_poly = np.concatenate((X_poly, X ** d), axis=1)
    return X_poly

def calculate_MSE(W,X,y):
    mse = np.zeros(len(X))  # MSE를 저장할 배열을 초기화

    # 각 데이터 포인트에 대해 MSE를 계산
    for idx in range(len(X)):
        mse[idx] = (np.dot(W.T, X[idx]) - y[idx]) ** 2  # 예측값과 실제값의 차이의 제곱을 계산
    
    mse = np.sum(mse) / len(X)   # 모든 데이터 포인트에 대한 MSE를 합하여 평균을 계산

    return mse

# CSV 파일을 읽어 Pandas DataFrame으로 변환 
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week5/linear_regression_data01.csv", names=['age', 'height'])

# raw_data
age = raw_data['age'].to_numpy()
height = raw_data['height'].to_numpy()

# convert data
X = raw_data['age'].to_numpy().reshape(-1, 1)  # Reshape to make it a column vector
y = raw_data['height'].to_numpy().reshape(-1, 1)

# Fit polynomial regression
K = int(input("K : "))
X_poly = polynomial_basis(X, K)
coefficients = np.linalg.inv(X_poly.T @ X_poly) @ X_poly.T @ y

# Predict using the model
age_range = np.linspace(np.min(age), np.max(age), 100).reshape(-1, 1)
X_poly_range = polynomial_basis(age_range, K)
predicted_height = X_poly_range @ coefficients

# 선형 회귀 모델의 평균제곱오차(MSE)를 계산 
mse = calculate_MSE(coefficients, X_poly, y)

print(mse)
