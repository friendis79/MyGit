# 다음 4가지 경우에 대한 2계층 신경망을 설계하고 결과값 찾기

import numpy as np

# 활성화 함수 (Sigmoid)
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

# 활성화 함수 (ReLU)
def ReLU(x):
    return np.maximum(0, x)

# Softmax Function
def softmax(x):
    y = np.exp(x)
    sum = np.sum(y)
    return y / sum

# Identify Function
def identity(x):
    return x

# Weights Matrix
W1 = np.array([[0.1, 0.2, 0.3],
               [0.1, 0.3, 0.5],
               [0.2, 0.4, 0.6]])

W2 = np.array([[0.1, 0.2],
               [0.1, 0.4],
               [0.2, 0.5],
               [0.3, 0.6]])

# 입력
x = np.array([1.0, 0.5])

# 바이어스를 포함한 입력 벡터
x_with_bias = np.append(x, 1)

# 은닉층 계산
z1 = np.dot(x_with_bias, W1)
h_sigmoid = sigmoid(z1)
h_relu = ReLU(z1)

# 은닉층 결과에 바이어스(1)를 추가
h_sigmoid_with_bias = np.append(h_sigmoid, 1)
h_relu_with_bias = np.append(h_relu, 1)

# Case 1: 은닉층 - Sigmoid, 출력층 - 항등 함수
z2_case1 = np.dot(h_sigmoid_with_bias, W2)    # Case 1 출력층
y_case1 = identity(z2_case1)

# Case 2: 은닉층 - Sigmoid, 출력층 - 소프트맥스 함수
z2_case2 = np.dot(h_sigmoid_with_bias, W2)    # Case 2 출력층
y_case2 = softmax(z2_case2)

# Case 3: 은닉층 - ReLU, 출력층 - 항등 함수
z2_case3 = np.dot(h_relu_with_bias, W2)   # Case 3 출력층
y_case3 = identity(z2_case3)

# Case 4: 은닉층 - ReLU, 출력층 - 소프트맥스 함수
z2_case4 = np.dot(h_relu_with_bias, W2)   # Case 4 출력층
y_case4 = softmax(z2_case4)

# 결과 출력
print(f"Case 1 Output: {y_case1}")
print(f"Case 2 Output: {y_case2}")
print(f"Case 3 Output: {y_case3}")
print(f"Case 4 Output: {y_case4}")