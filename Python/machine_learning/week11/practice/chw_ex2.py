import numpy as np

#sigmoid_function
def sigmoid_func(z):
    return 1 / (1 + np.exp(-z))

#rectified linear unit_function
def relu_func(x):
    if x>0 : return x
    else: return 0

#softmax_function
def softmax(x):
    y = np.exp(x)
    sum = np.sum(y)
    return y/sum

#Weight Matrix_W1
W_1 = np.array([
    [0.1, 0.2, 0.3],
    [0.1, 0.3, 0.5],
    [0.2, 0.4, 0.6]
])

#Weight Matrix_W2
W_2 = np.array([
    [0.1, 0.2],
    [0.1, 0.4],
    [0.2, 0.5],
    [0.3, 0.6]
])

#hidden_layer_input
X = [1.0, 0.5]
X += [1.0]

##################### case1) hidden_layer : sigmoid function, output_layer : identity function #########################
C1_a = np.zeros(len(X))      #hidden_layer_output
C1_b = np.zeros(len(X)+1)    #output_layer_input
C1_c = np.zeros(2)           #output_layer_output

for i in range(len(C1_a)):
    C1_a[i] = np.dot(X, W_1[:, i])
    C1_b[i]  = sigmoid_func(C1_a[i])
C1_b[len(X)] = 1 
C1_b = C1_b.reshape(1, -1)

for j in range(len(C1_c)):
    C1_c[j] = np.dot(C1_b, W_2[:, j])
Y1 = C1_c #final_output
print(f'case1) hidden_layer : sigmoid function, output_layer : identity function =====> y = {Y1}')


##################### case2) hidden_layer : sigmoid function, output_layer : softmax function #########################
C2_a = np.zeros(len(X))      #hidden_layer_output
C2_b = np.zeros(len(X)+1)    #output_layer_input
C2_c = np.zeros(2)           #output_layer_output

for i in range(len(C2_a)):
    C2_a[i] = np.dot(X, W_1[:, i])
    C2_b[i]  = sigmoid_func(C2_a[i])
C2_b[len(X)] = 1 
C2_b = C2_b.reshape(1, -1)

for j in range(len(C2_c)):
    C2_c[j] = np.dot(C2_b, W_2[:, j])
Y2 = softmax(C2_c) #final_output
print(f'case2) hidden_layer : sigmoid function, output_layer : softmax function  =====> y = {Y2}')


##################### case3) hidden_layer : relu_function, output_layer : identity function #########################
C3_a = np.zeros(len(X))      #hidden_layer_output
C3_b = np.zeros(len(X)+1)    #output_layer_input
C3_c = np.zeros(2)           #output_layer_output

for i in range(len(C3_a)):
    C3_a[i] = np.dot(X, W_1[:, i])
    C3_b[i]  = relu_func(C3_a[i])
C3_b[len(X)] = 1 
C3_b = C3_b.reshape(1, -1)

for j in range(len(C3_c)):
    C3_c[j] = np.dot(C3_b, W_2[:, j])
Y3 = C3_c #final_output
print(f'case3) hidden_layer : relu_function   , output_layer : identity function =====> y = {Y3}')


##################### case4) hidden_layer : relu_function, output_layer : softmax function #########################
C4_a = np.zeros(len(X))      #hidden_layer_output
C4_b = np.zeros(len(X)+1)    #output_layer_input
C4_c = np.zeros(2)           #output_layer_output

for i in range(len(C4_a)):
    C4_a[i] = np.dot(X, W_1[:, i])
    C4_b[i]  = relu_func(C4_a[i])
C4_b[len(X)] = 1 
C4_b = C4_b.reshape(1, -1)

for j in range(len(C4_c)):
    C4_c[j] = np.dot(C4_b, W_2[:, j])
Y4 = softmax(C4_c) #final_output
print(f'case4) hidden_layer : relu_function   , output_layer : softmax function  =====> y = {Y4}')