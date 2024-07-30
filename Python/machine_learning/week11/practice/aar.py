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

# 클래스별 데이터 수
num_samples_per_class = 300

# 클래스 1 데이터 생성 (중심: (2, 4, 6), 노이즈 추가)
class1_center = [2, 4, 6]
class1_data = np.random.normal(loc=class1_center, scale=1.2, size=(num_samples_per_class, 3))
class1_df = pd.DataFrame(class1_data, columns=['x0', 'x1', 'x2'])
class1_df['target'] = 1  # 타겟 레이블 추가

# 클래스 2 데이터 생성 (중심: (4, 6, 2), 노이즈 추가)
class2_center = [4, 6, 2]
class2_data = np.random.normal(loc=class2_center, scale=1.2, size=(num_samples_per_class, 3))
class2_df = pd.DataFrame(class2_data, columns=['x0', 'x1', 'x2'])
class2_df['target'] = 2  # 타겟 레이블 추가

# 클래스 3 데이터 생성 (중심: (6, 2, 4), 노이즈 추가)
class3_center = [6, 2, 4]
class3_data = np.random.normal(loc=class3_center, scale=1.2, size=(num_samples_per_class, 3))
class3_df = pd.DataFrame(class3_data, columns=['x0', 'x1', 'x2'])
class3_df['target'] = 3  # 타겟 레이블 추가

# 데이터 합치기
data = pd.concat([class1_df, class2_df, class3_df], ignore_index=True)

# 데이터 저장
data.to_csv("NN_data.csv", index=False)

# 데이터 불러오기
data = pd.read_csv("NN_data.csv")

# 데이터 분할
Class1_x0, Class1_x1, Class1_x2 = [], [], []
Class2_x0, Class2_x1, Class2_x2 = [], [], []
Class3_x0, Class3_x1, Class3_x2 = [], [], []

for i in range(len(data)):
    if data['target'][i] == 1:
        Class1_x0.append(data['x0'][i])
        Class1_x1.append(data['x1'][i])
        Class1_x2.append(data['x2'][i])
    elif data['target'][i] == 2:
        Class2_x0.append(data['x0'][i])
        Class2_x1.append(data['x1'][i])
        Class2_x2.append(data['x2'][i])
    else:
        Class3_x0.append(data['x0'][i])
        Class3_x1.append(data['x1'][i])
        Class3_x2.append(data['x2'][i])

# 3D 그래프 생성
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(Class1_x1, Class1_x0, Class1_x2, alpha=0.5, label='class 1', marker='o')
ax.scatter(Class2_x1, Class2_x0, Class2_x2, alpha=0.5, label='class 2', marker='^')
ax.scatter(Class3_x1, Class3_x0, Class3_x2, alpha=0.5, label='class 3', marker='s')
plt.title('NN_data.csv(real_data_values)')
plt.legend()
plt.show()

# 입력 속성 수 계산 (타겟 열 제외)
input_size = data.shape[1] - 1

# 출력 클래스 수 계산
output_size = data['target'].nunique()

# 히든 레이어 노드 수 설정
hidden_size = int(input("The number of Hidden Nodes: "))

# 가중치 행렬 초기화 (랜덤 초기화)
np.random.seed(42)  # 재현성을 위해 시드 설정
W1 = np.random.randn(input_size, hidden_size) * 0.01  # 입력층 -> 은닉층 가중치
W2 = np.random.randn(hidden_size, output_size) * 0.01 # 은닉층 -> 출력층 가중치

print("W1 shape:", W1.shape)
print("W2 shape:", W2.shape)

# 입력 데이터 준비 (타겟 열 제외)
X = data.drop('target', axis=1).values

# 타겟 레이블 One-Hot Encoding
Y = pd.get_dummies(data['target']).values

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
print(f'hidden_layer : sigmoid function, output_layer : softmax function =====> y(predict) = {predicted_y}')

# 예측된 클래스 레이블
predicted_class = np.argmax(predicted_y) + 1  # 클래스 레이블은 1, 2, 3으로 되어있으므로 +1

# 실제 클래스 레이블
actual_class = data['target'][random_index]

print(f'Predicted class: {predicted_class}')
print(f'Actual class: {actual_class}')

# 전체 데이터에 대한 예측 값 도출
Y_pred = forward_propagation(X, W1, W2)
Y_pred_classes = np.argmax(Y_pred, axis=1) + 1

# 정확도 계산
accuracy = np.mean(Y_pred_classes == data['target'])
print(f'Accuracy: {accuracy * 100:.2f}%')