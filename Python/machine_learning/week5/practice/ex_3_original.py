# 실습 3 - 해석해로 구한 선형모델의 평균제곱오차 구하기

import pandas as pd
import numpy as np

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

mse = function_MSE(analytic_W, X, y)
print(f'mse : {mse}')