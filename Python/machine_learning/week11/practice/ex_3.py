# 실습 3 - "NN_data.csv" 데이터를 활용한 실습 (데이터를 3차원 평면에 표시, One-Hot Encoding 구현, 2계층 신경망 구현)

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 활성화 함수 (Sigmoid)
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

# Softmax Function
def softmax(x):
    y = np.exp(x)
    sum = np.sum(y)
    return y / sum

# Forward Propagation
def forward_propagation(X, W1, W2):
    Z1 = np.dot(X, W1)  # 입력층 -> 은닉층
    A1 = sigmoid(Z1)    # 은닉층 활성화 함수 적용
    Z2 = np.dot(A1, W2) # 은닉층 -> 출력층
    A2 = softmax(Z2)    # 출력층 활성화 함수 적용
    return A2

# 데이터 불러오기
data = pd.read_csv("C:/Coding/Python/machine_learning/week11/NN_data.csv")

# 열 이름 확인
print("Columns in the dataset:", data.columns)

# 3D 그래프 생성
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# 데이터 포인트 플롯
colors = {1: 'blue', 2: 'orange', 3: 'yellow'}
for target in data['y'].unique():
    subset = data[data['y'] == target]
    ax.scatter(subset['x0'], subset['x1'], subset['x2'], label=f'Class {target}', marker='o', edgecolors=colors[target], facecolors='none', s=100)

# 축 레이블 설정
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# 범례 추가
ax.legend()

# 타이틀 설정
ax.set_title("Noisy Data Plot")

# 그래프 표시
plt.show()

# 클래스 중심과 크기 정의
class_size = 300
Class1_center = [2, 4, 6]
Class2_center = [4, 6, 2]
Class3_center = [6, 2, 4]

# 노이즈 추가된 데이터 생성
Class1 = np.random.normal(Class1_center, 1.2, size=(class_size, 3))
Class2 = np.random.normal(Class2_center, 1.2, size=(class_size, 3))
Class3 = np.random.normal(Class3_center, 1.2, size=(class_size, 3))

# 노이즈가 추가된 데이터를 하나의 데이터프레임으로 결합
noise_data = np.vstack([Class1, Class2, Class3])
noise_labels = np.array([1]*class_size + [2]*class_size + [3]*class_size)
noise_df = pd.DataFrame(noise_data, columns=['x0', 'x1', 'x2'])
noise_df['y'] = noise_labels

# 입력 속성 수 계산 (타겟 열 제외)
input_size = noise_df.shape[1] - 1

# 출력 클래스 수 계산
output_size = noise_df['y'].nunique()

# 히든 레이어 노드 수 설정
hidden_size = int(input("The number of Hidden Nodes: "))

# 가중치 행렬 초기화 (랜덤 초기화)
np.random.seed(42)  # 재현성을 위해 시드 설정
W1 = np.random.randn(input_size, hidden_size) * 0.01  # 입력층 -> 은닉층 가중치
W2 = np.random.randn(hidden_size, output_size) * 0.01 # 은닉층 -> 출력층 가중치

print("W1 shape:", W1.shape)
print("W2 shape:", W2.shape)

# 입력 데이터 준비 (타겟 열 제외)
X = noise_df.drop('y', axis=1).values

# 타겟 레이블 One-Hot Encoding
Y = pd.get_dummies(noise_df['y']).values

# 예측 값 도출
random_index = np.random.randint(0, len(X))
input_features = X[random_index]

hidden_layer_input = np.dot(input_features, W1)  # 은닉층 입력
hidden_layer_output = sigmoid(hidden_layer_input)  # 은닉층 출력 (활성화 함수 적용)
output_layer_input = np.dot(hidden_layer_output, W2)  # 출력층 입력
predicted_y = softmax(output_layer_input)  # 출력층 출력 (활성화 함수 적용)

print(f'Weight Matrix1: \n{W1}')
print(f'Weight Matrix2: \n{W2}')
print(f"NN_data_csv) index = {random_index}")
print(f'Derive predictions from randomly initialized weight matrices =====> {predicted_y}')

# 예측된 클래스 레이블
predicted_class = np.argmax(predicted_y) + 1  # 클래스 레이블은 1, 2, 3으로 되어있으므로 +1

# 실제 클래스 레이블
actual_class = noise_df['y'][random_index]

print(f'Predicted class: {predicted_class}')
print(f'Actual class: {actual_class}')

# 전체 데이터에 대한 예측 값 도출
Y_pred = []
for i in range(len(X)):
    input_features = X[i]
    hidden_layer_input = np.dot(input_features, W1)
    hidden_layer_output = sigmoid(hidden_layer_input)
    output_layer_input = np.dot(hidden_layer_output, W2)
    predicted_y = softmax(output_layer_input)
    Y_pred.append(predicted_y)

Y_pred_classes = np.argmax(Y_pred, axis=1) + 1

# 정확도 계산
accuracy = np.mean(Y_pred_classes == noise_df['y'])
print(f'Accuracy: {accuracy * 100:.2f}%')