import numpy as np
import pandas as pd

# 데이터 불러오기
data = pd.read_csv("NN_data_generated.csv")

# 입력 속성 수 자동 체크 (Input features count)
input_size = data.shape[1] - 1  # 'target' 열을 제외한 나머지 열의 수

# 출력 클래스 수 자동 체크 (Output class count)
output_size = data['target'].nunique()

print(f"Input size: {input_size}")
print(f"Output size: {output_size}")

# Hidden layer의 노드 수 설정
hidden_size = 10  # 원하는 값으로 설정 가능

# Weight Matrix 생성 및 초기화 (랜덤 초기화)
np.random.seed(42)  # 재현성을 위해 시드 설정

# 입력층과 히든층 사이의 가중치 행렬
W1 = np.random.randn(input_size, hidden_size) * 0.01

# 히든층과 출력층 사이의 가중치 행렬
W2 = np.random.randn(hidden_size, output_size) * 0.01

print("W1 shape:", W1.shape)
print("W2 shape:", W2.shape)

# 활성화 함수 (Sigmoid)
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

# 소프트맥스 함수
def softmax(z):
    exp_z = np.exp(z - np.max(z, axis=1, keepdims=True))
    return exp_z / np.sum(exp_z, axis=1, keepdims=True)

# Forward Propagation
def forward_propagation(X, W1, W2):
    # 입력층 -> 히든층
    Z1 = np.dot(X, W1)
    A1 = sigmoid(Z1)
    
    # 히든층 -> 출력층
    Z2 = np.dot(A1, W2)
    A2 = softmax(Z2)
    
    return A2

# 입력 데이터 준비
X = data.drop('target', axis=1).values

# 예측 값 도출
Y_pred = forward_propagation(X, W1, W2)

# 예측 값 확인
print("Predicted Y shape:", Y_pred.shape)
print("Predicted Y (first 5 samples):")
print(Y_pred[:5])