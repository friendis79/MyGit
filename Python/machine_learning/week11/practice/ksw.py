import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# 데이터 로드
raw_data = pd.read_csv('NN_data.csv', encoding='utf-8', engine='python')

# 데이터프레임의 첫 몇 행과 컬럼명 확인
print("컬럼명: ", raw_data.columns)
print(raw_data.head())

# 입력 데이터와 목표 변수 분리
X = raw_data[['x0', 'x1', 'x2']].to_numpy()  # 입력 데이터 (특성)
Y = raw_data['correct_column_name'].to_numpy()  # 목표 변수 (레이블) - 'correct_column_name'을 실제 컬럼명으로 변경

# One-Hot Encoding 함수 정의
def one_hot_encoding(array, size):
    one_hot = np.zeros((array.size, size))  # size x size 크기의 영행렬 생성
    one_hot[np.arange(array.size), array - 1] = 1  # 인덱스를 맞춰서 1로 설정 (1-indexed to 0-indexed)
    return one_hot

# One-Hot Encoding 적용
Y_one_hot = one_hot_encoding(Y, 3)  # 3 클래스를 가정하여 One-Hot Encoding

# 2계층 신경망 클래스 정의
class NeuralNetwork:
    def __init__(self, input_size, output_size, hidden_size):
        self.input_size = input_size  # 입력 크기
        self.output_size = output_size  # 출력 크기
        self.hidden_size = hidden_size  # 은닉층 노드 수
        
        # He 초기화 적용하여 가중치 초기화
        self.weights_input_hidden = np.random.randn(input_size, hidden_size) * np.sqrt(2. / input_size)
        self.weights_hidden_output = np.random.randn(hidden_size, output_size) * np.sqrt(2. / hidden_size)
    
    # 시그모이드 함수 정의
    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))
    
    # 소프트맥스 함수 정의
    def softmax(self, x):
        exp_x = np.exp(x - np.max(x, axis=1, keepdims=True))  # 안정적인 소프트맥스를 위해 최대값을 빼줌
        return exp_x / np.sum(exp_x, axis=1, keepdims=True)
    
    # Feedforward 계산
    def feedforward(self, X):
        hidden = self.sigmoid(np.dot(X, self.weights_input_hidden))  # 은닉층 활성화
        output = self.softmax(np.dot(hidden, self.weights_hidden_output))  # 출력층 활성화
        return output
    
    # 예측 함수
    def predict(self, X):
        return self.feedforward(X)

# 신경망 모델 설정
input_size = X.shape[1]  # 입력 속성 수 (특성 수)
output_size = 3  # 출력 클래스 수
hidden_size = int(input("Hidden layer의 Node 수를 입력하세요: "))  # 은닉층 노드 수를 입력받음

# 신경망 인스턴스 생성
model = NeuralNetwork(input_size, output_size, hidden_size)

# 모델을 사용한 예측
predictions = model.predict(X)

# 예측 결과 출력
print("\n예측 결과 (확률):")
for i, pred in enumerate(predictions):
    print(f"Input {i + 1}에 대한 예측: {pred}")

# 예측된 클래스 라벨로 변환 (가장 높은 확률을 가진 클래스 선택)
predicted_labels = np.argmax(predictions, axis=1) + 1  # 0-indexed to 1-indexed

# 정확도 계산
accuracy = np.mean(predicted_labels == Y)
print(f"\n모델의 정확도: {accuracy * 100:.2f}%")
# 원본 데이터의 3D 플롯 생성
x0 = raw_data['x0'].to_numpy()
x1 = raw_data['x1'].to_numpy()
x2 = raw_data['x2'].to_numpy()
y = raw_data['y'].to_numpy()

# 3D 플롯 설정
fig = plt.figure(figsize=(6, 6))
ax = fig.add_subplot(projection='3d')

# 축 범위 설정
ax.set_xlim(-5, 10)
ax.set_ylim(-1, 10)
ax.set_zlim(-5, 10)

# 축 눈금 설정
ax.set_xticks([-5, 0, 5, 10])
ax.set_yticks([0, 5, 10])
ax.set_zticks([-5, 0, 5, 10])

# 3차원 그래프 생성, 점 찍기
ax.scatter(x0[y == 1], x1[y == 1], x2[y == 1], c='none', edgecolor='b', label='1', marker='o', s=30)
ax.scatter(x0[y == 2], x1[y == 2], x2[y == 2], c='none', edgecolor='r', label='2', marker='o', s=30)
ax.scatter(x0[y == 3], x1[y == 3], x2[y == 3], c='none', edgecolor='y', label='3', marker='o', s=30)

plt.legend()
plt.grid()
ax.view_init(25, 45)
plt.show()