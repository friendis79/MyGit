import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 가우시안 함수 정의
def gaussian_basis(x, mu, sigma):
    return np.exp(-0.5 * ((x - mu) / sigma) ** 2)

# 가우시안 최적의 매개변수 계산
def gaussian_weights(k, x, y):
    rho = ((max(x) - min(x)) / (k - 1)) # rho 계산
    matrix = [] # 가우시안 기저 함수의 매트릭스 초기화
    
    # 각 가우시안 함수에 대한 매개변수 계산
    for center in range(k):
        centers = min(x) + (rho * center) # 중심 계산
        basis = gaussian_basis(x, centers, rho) # 가우시안 함수 계산
        matrix.append(basis) # 매트릭스에 가우시안 함수 추가
    matrix.append(np.ones(len(x))) # 바이어스 항 추가
    matrix = np.array(matrix).T # 매트릭스 변환
    weights = np.linalg.pinv(matrix.T @ matrix) @ matrix.T @ y # 최적 가중치 계산
    return weights

# MSE 계산 함수
def calculate_mse(k, age, height):
    weights = gaussian_weights(k, age, height)
    basis_functions = np.array([gaussian_basis(age, min(age) + ((max(age) - min(age)) / (k - 1)) * center, (max(age) - min(age)) / (k - 1)) for center in range(k)]).T
    basis_functions = np.column_stack((basis_functions, np.ones(len(age))))
    y_predict = basis_functions @ weights
    mse = np.mean((y_predict - height) ** 2)
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
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week5/multiple_linear_regression_data.csv", names=['height', 'weight', 'age'])

# raw_data
height = raw_data['height'].to_numpy() # 키 데이터 추출
age = raw_data['age'].to_numpy() # 나이 데이터 추출

# 가우시안 기저 함수의 가중치 계산
k_values = [3, 5, 8, 10]  # 다양한 기저 함수 개수에 대해 실험
mse_values = []

# MSE 계산
for k in k_values:
    mse_values.append(calculate_mse(k, age, height))

# 그래프 그리기 함수 호출
plot_mse_vs_k(k_values, mse_values)