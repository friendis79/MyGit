# 실습 7 - 실습 #6에서 각 홀드아웃의 결과로 생성된 선형 기저함수 모델을 각각의 훈련데이터, 검증데이터와 함께 그래프에 표시

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

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

# 데이터 분할
data_size = raw_data.shape[0]
subset_size = data_size // 5  # 5등분
subsets = [raw_data[i * subset_size: (i + 1) * subset_size] for i in range(5)]

# 5겹 교차검증 수행
k = 9  # 가우시안 기저 함수의 수

results = []

# 3x2 서브플롯 생성
fig, axs = plt.subplots(3, 2, figsize=(15, 12), sharey=True)  # 3행 2열 서브플롯
axs = axs.flatten()  # 3x2 서브플롯을 평면으로 만듦

# 각 홀드아웃에 대해
for i in range(5):
    ax = axs[i]  # 서브플롯 순서
    validation_data = subsets[i]  # 검증 데이터
    train_data = pd.concat([s for j, s in enumerate(subsets) if j != i])  # 훈련 데이터

    train_age = train_data['age'].to_numpy()
    train_height = train_data['height'].to_numpy()

    validation_age = validation_data['age'].to_numpy()
    validation_height = validation_data['height'].to_numpy()

    # 모델 학습
    weights = gaussian_weights(k, train_age, train_height)

    # 전체 데이터에 대해 모델 예측
    full_age_range = np.linspace(min(train_age), max(train_age), 100)
    full_basis_functions = gaussian_basis(
        full_age_range[:, np.newaxis], 
        np.linspace(min(train_age), max(train_age), k), 
        (max(train_age) - min(train_age)) / (k - 1)
    )
    full_matrix = np.column_stack((full_basis_functions, np.ones(len(full_age_range))))
    full_predictions = full_matrix @ weights  # 모델 예측

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

    # 서브플롯에 그래프 그리기
    ax.plot(full_age_range, full_predictions, label=f"prediction (k={i + 1}-fold, MSE={validation_mse:.3f})", color='b')  # 모델 예측
    ax.scatter(train_age, train_height, label="training set", color='b')
    ax.scatter(validation_age, validation_height, label="validation set", color='orange')

    ax.set_title("Regression with Gaussian Basis Functions")
    ax.set_xlabel("age [months]")
    ax.set_ylabel("height [cm]")
    ax.grid(True)
    ax.legend()  # 범례 추가

# 여분 서브플롯 비움
axs[-1].axis("off")

plt.show()