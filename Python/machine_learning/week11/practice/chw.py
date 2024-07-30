import numpy as np

#step_function
def step_func(t):
    if t>0 : return 1
    else: return 0

#training_set
X = np.array([
    [0, 0, 1],
    [0, 1, 1],
    [1, 0, 1],
    [1, 1, 1]
])

print(len(X))
print(range(len(X)))

y_and = np.array([0, 0, 0, 1])
y_nand = np.array([1, 1, 1, 0])
y_or = np.array([0, 1, 1, 1])

#perceptron_fit_function
def perceptron_fit(X, Y, epochs):
    W = np.zeros(len(X[0]))
    eta = 0.2
    for t in range(epochs):
        print('epoch = ', t)
        for i in range(len(X)):
            predict = step_func(np.dot(X[i], W))
            error = Y[i] - predict
            W += eta * error * X[i]
            print("현재 처리 입력 = ", X[i], "정답 = ", Y[i], "출력 = ", predict, "변경된 가중치 = ", W)
    return W

#perception_predict_function
def perceptron_predict(X, W):
    predict = []
    for x in X:
        print(x[0], x[1], "=>", step_func(np.dot(x, W)))
        predict.append(step_func(np.dot(x, W)))
    return predict

#AND GATE
W_and = perceptron_fit(X, y_and, 6)
and_predict = perceptron_predict(X, W_and)
print(W_and)

#OR GATE
W_or = perceptron_fit(X, y_or, 6)
or_predict = perceptron_predict(X, W_or)
print(W_or)

#NAND GATE
W_nand = perceptron_fit(X, y_nand, 6)
nand_predict = perceptron_predict(X, W_nand)
print(W_nand)

#XOR GATE process
xor_middle_output = np.array([or_predict, nand_predict]).T
add_colmn = np.ones((xor_middle_output.shape[0], 1))
xor_middle_input = np.hstack((xor_middle_output, add_colmn))

#XOR GATE (used AND, OR and NAND)
xor_predict = perceptron_predict(xor_middle_input, W_and)