# 퍼셉트론을 활용하여 XOR 게이트 구현 (AND, OR, NAND 퍼셉트론 활용)

import numpy as np

# step function
def step_func(t):
    if t > 0 :  return 1
    else :      return 0

# perceptron_fit: 퍼셉트론 학습 함수
def perceptron_fit(X, Y, epochs, learning_rate=0.2):
    W = np.zeros(len(X[0]))
    for t in range(epochs):
        for i in range(len(X)):  # 각 입력 샘플에 대해 반복
            predict = step_func(np.dot(X[i], W))  # 현재 가중치를 사용하여 예측
            error = Y[i] - predict
            W += learning_rate * error * X[i]  # 가중치 업데이트
    return W

# perceptron_predict: 학습된 가중치를 사용하여 예측
def perceptron_predict(X, W):
    predict = []  # 예측 값을 저장할 리스트
    for x in X:  # 각 입력 샘플에 대해 반복
        result = step_func(np.dot(x, W))  # 현재 가중치를 사용하여 예측
        predict.append(result)
    return predict

# print_predictions: 예측 결과 출력
def print_predictions(X, predictions):
    for x, prediction in zip(X, predictions):  # 각 입력 샘플과 예측 값에 대해 반복
        print(f'x = [{x[0]}, {x[1]}] =====> {prediction}')  # 입력과 예측 결과 출력

# train_and_test_gate: 특정 논리 게이트에 대해 퍼셉트론 학습 및 테스트
def train_and_test_gate(X, Y, gate_name):
    print(gate_name)  # 논리 게이트 이름 출력
    W = perceptron_fit(X, Y, 6)
    predictions = perceptron_predict(X, W)  # 학습된 가중치를 사용하여 예측
    print_predictions(X, predictions)  # 예측 결과 출력
    print("최종 가중치:", W)
    print("\n")

# XOR 게이트는 다층 퍼셉트론이 필요하므로 별도로 처리
def xor_predict(X):
    # AND Gate
    print("AND Gate")
    W_and = perceptron_fit(X, AND_perceptron, 6)
    AND_predict = perceptron_predict(X, W_and)
    print_predictions(X, AND_predict)

    # OR Gate
    print("OR Gate")
    W_or = perceptron_fit(X, OR_perceptron, 6)
    OR_predict = perceptron_predict(X, W_or)
    print_predictions(X, OR_predict)

    # NAND Gate
    print("NAND Gate")
    W_NAND = perceptron_fit(X, NAND_perceptron, 6)
    NAND_predict = perceptron_predict(X, W_NAND)
    print_predictions(X, NAND_predict)
    
    # XOR Gate
    XOR_middle_output = np.array([OR_predict, NAND_predict]).T  # OR 및 NAND 결과를 XOR 중간 입력으로 변환
    add_column = np.ones((XOR_middle_output.shape[0], 1))  # 바이어스 열 추가
    xor_middle_input = np.hstack((XOR_middle_output, add_column))  # 중간 입력에 바이어스 추가

    print("XOR Gate")
    XOR_predict = perceptron_predict(xor_middle_input, W_and)
    print_predictions(X, XOR_predict)

# 입력 데이터
X = np.array([
    [0, 0, 1],
    [0, 1, 1],
    [1, 0, 1],
    [1, 1, 1]
])

# 각 논리 게이트에 대한 정답 출력
AND_perceptron = np.array([0, 0, 0, 1])
OR_perceptron = np.array([0, 1, 1, 1])
NAND_perceptron = np.array([1, 1, 1, 0])

# 각 논리 게이트 학습 및 테스트
train_and_test_gate(X, AND_perceptron, "AND")
train_and_test_gate(X, OR_perceptron, "OR")
train_and_test_gate(X, NAND_perceptron, "NAND")

# XOR 게이트 테스트
print("XOR")
xor_predict(X)