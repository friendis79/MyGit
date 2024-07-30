# 실습 3 - 해석해로 구한 선형모델의 평균제곱오차 구하기

import pandas as pd
import numpy as np

# MSE 함수 정의
def function_MSE(W, X, y):
    predictions = X @ W  # 예측값 계산
    squared_errors = (predictions - y) ** 2  # 오차의 제곱 계산
    mse = np.mean(squared_errors)  # 평균 제곱 오차 계산
    return mse

# CSV 파일을 읽어 Pandas DataFrame으로 변환 
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week5/multiple_linear_regression_data.csv", names=['height', 'weight', 'age'])

# convert data
X = raw_data[['height', 'weight']].values
X = np.concatenate([X, np.ones((X.shape[0], 1))], axis=1)
y = raw_data['age'].values.reshape(-1, 1)

# X의 역행렬을 이용하여 해를 계산 
analytic_W = np.linalg.pinv(X.T @ X) @ X.T @ y

mse = function_MSE(analytic_W, X, y)
print(f'mse : {mse}')