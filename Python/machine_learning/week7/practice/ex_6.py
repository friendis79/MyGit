# 실습 6 - 실습 5에서 만든 다섯 개의 데이터 집합을 이용해 5겹 교차검증을 구현 
# 모델은 K=9일 때의 가우스함수를 이용한 선형 기저함수 모델을 사용
# 이를 위해 5개의 홀드아웃 검증을 설계하고 각 홀드아웃의 결과물 (매개변수, 일반화, 오차)를 구하기)

import numpy as np
import pandas as pd

# Gaussian Basis Function
def gaussian_basis(x, mu, sigma):
    return np.exp(-0.5 * ((x - mu) / sigma) ** 2)

# Gaussian Weights Calculation
def gaussian_weights(k, x, y):
    rho = ((max(x) - min(x)) / (k - 1))
    centers = np.linspace(min(x), max(x), k)
    basis_functions = gaussian_basis(x[:, np.newaxis], centers, rho)
    matrix = np.column_stack((basis_functions, np.ones(len(x))))
    weights = np.linalg.pinv(matrix.T @ matrix) @ matrix.T @ y
    return weights

# CSV 파일 읽기
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week7/lin_regression_data_03.csv", names=['age', 'height'])

# 5개의 부분집합으로 분할
data_size = raw_data.shape[0]
subset_size = data_size // 5  # 전체 데이터 크기를 5등분
subsets = [raw_data[i * subset_size: (i + 1) * subset_size] for i in range(5)]

# 5겹 교차검증 수행
k = 9  # 가우시안 기저 함수의 수

results = []

for i in range(5):
    # 검증 데이터와 훈련 데이터 분리
    validation_data = subsets[i]  # 1개의 부분집합을 검증 데이터로 사용
    train_data = pd.concat([s for j, s in enumerate(subsets) if j != i])  # 나머지 4개 부분집합을 훈련 데이터로 사용

    train_age = train_data['age'].to_numpy()
    train_height = train_data['height'].to_numpy()

    validation_age = validation_data['age'].to_numpy()
    validation_height = validation_data['height'].to_numpy()

    # 모델 학습
    weights = gaussian_weights(k, train_age, train_height)

    # 검증 데이터 예측
    validation_basis_functions = gaussian_basis(
        validation_age[:, np.newaxis], 
        np.linspace(min(train_age), max(train_age), k), 
        (max(train_age) - min(train_age)) / (k - 1)
    )
    
    validation_matrix = np.column_stack((validation_basis_functions, np.ones(len(validation_age))))
    y_predict_validation = validation_matrix @ weights  # 예측값

    # 검증 데이터의 MSE 계산
    validation_mse = np.mean((y_predict_validation - validation_height) ** 2) ** 0.5

    # 결과 저장
    results.append({
        "holdout": i + 1,
        "weights": weights,
        "validation_mse": validation_mse,
    })

# 결과 출력
for result in results:
    print(f"Holdout {result['holdout']}:")
    print(f"Parameters (Weights): {result['weights']}")
    print(f"Validation MSE: {result['validation_mse']:.5f}")
    print("-" * 50)