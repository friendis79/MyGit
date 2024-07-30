import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

#sigmoid_function
def sigmoid_func(z):
    return 1 / (1 + np.exp(-z))

#softmax_function
def softmax(x):
    y = np.exp(x)
    sum = np.sum(y)
    return y/sum

#read_data
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week11/NN_data.csv", header=0, names=['', 'x0', 'x1', 'x2', 'y'])
num = raw_data[''].to_numpy()
x0 = raw_data['x0'].to_numpy()
x1 = raw_data['x1'].to_numpy()
x2 = raw_data['x2'].to_numpy()
y = raw_data['y'].to_numpy()

###############  "NN_dat5a_csv"     #############################################
##############  class1~3_data ==> real_data_values plot   ######################
C1_x0, C1_x1, C1_x2 = [], [], []
C2_x0, C2_x1, C2_x2 = [], [], []
C3_x0, C3_x1, C3_x2 = [], [], []

for i in range(len(num)):
    if y[i] == 1:
        C1_x0.append(x0[i])
        C1_x1.append(x1[i])
        C1_x2.append(x2[i])
    elif y[i] == 2:
        C2_x0.append(x0[i])
        C2_x1.append(x1[i])
        C2_x2.append(x2[i])
    else:
        C3_x0.append(x0[i])
        C3_x1.append(x1[i])
        C3_x2.append(x2[i])

#plot ==> NN_data.csv(real_data_values)
fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(C1_x1, C1_x0, C1_x2, alpha=0.5, label='class 1')
ax.scatter(C2_x1, C2_x0, C2_x2, alpha=0.5, label='class 2')
ax.scatter(C3_x1, C3_x0, C3_x2, alpha=0.5, label='class 3')
plt.xlim(-3, 10)
plt.ylim(10, -5)
plt.title('NN_data.csv(real_data_values)')
plt.legend()
plt.show()

################   Class 1, 2, 3   ###################################################
###### Noise : A normal distribution with mean(center) and variance(1.2)   ###########

class_size = 300
Class1_center = [2, 4, 6]
Class2_center = [4, 6, 2]
Class3_center = [6, 2, 4]

Class1 = np.random.normal(Class1_center, 1.2, size=(class_size, 3))
Class2 = np.random.normal(Class2_center, 1.2, size=(class_size, 3))
Class3 = np.random.normal(Class3_center, 1.2, size=(class_size, 3))

class1_x = Class1[:, 0]
class1_y = Class1[:, 1]
class1_z = Class1[:, 2]

class2_x = Class2[:, 0]
class2_y = Class2[:, 1]
class2_z = Class2[:, 2]

class3_x = Class3[:, 0]
class3_y = Class3[:, 1]
class3_z = Class3[:, 2]

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(class1_x, class1_y, class1_z, alpha=0.5, label='class 1')
ax.scatter(class2_x, class2_y, class2_z, alpha=0.5, label='class 2')
ax.scatter(class3_x, class3_y, class3_z, alpha=0.5, label='class 3')
plt.xlim(-3, 10)
plt.ylim(10, -5)
plt.title('Data samples with noise added to the center values')
plt.legend()
plt.show()

#One-Hot Encoding
y_oh = []
for i in range(len(num)):
    if y[i] == 1:
        y_oh.append([1, 0, 0])
    elif y[i] == 2:
        y_oh.append([0, 1, 0])
    else:
        y_oh.append([0, 0, 1])

##########    <Two-layer artificial neural network>     ###########################################################
##########    m-input k-class classification system     ###########################################################
##########    activation function) hidden_layer : sigmoid function, output_layer : softmax function    ############

#The number of input attributes = m (check)
m = raw_data.shape[1] - 2

#The numner of Output Classes = k (check)
k = len(set(y))

#The number of Hidden Node
node_num = int(input("The number of Hidden Nodes: "))

#Weight Matrix_W1 ==> (m)x(n)
W_1 = np.random.rand(m, node_num)

#Weight Matrix_W2 ==> (n)x(k)
W_2 = np.random.rand(node_num, k)

#"NN_data_csv" ==> Weight Matrix ==> predict_y
random_index = np.random.randint(0, len(x0))
X = [x0[random_index], x1[random_index], x2[random_index]]

a = np.zeros(m)           #hidden_layer_output
b = np.zeros(node_num)    #output_layer_input
c = np.zeros(k)           #output_layer_output

a = np.dot(X, W_1)
b = sigmoid_func(a)
c = np.dot(b, W_2)
predict_y = softmax(c)

print(f'Weight Matrix1: \n{W_1}')
print(f'Weight Matrix2: \n{W_2}')
print(f"NN_data_csv) index = {random_index}")
print(f'hidden_layer: sigmoid function, output_layer: softmax function =====> y(predict) = {predict_y}')

# 예측된 클래스 레이블
predicted_class = np.argmax(predict_y) + 1  # 클래스 레이블은 1, 2, 3으로 되어있으므로 +1

# 실제 클래스 레이블
actual_class = y[random_index]

print(f'Predicted class: {predicted_class}')
print(f'Actual class: {actual_class}')

# 전체 데이터에 대한 예측 값 도출
Y_pred = []
for i in range(len(x0)):
    X = [x0[i], x1[i], x2[i]]
    a = np.dot(X, W_1)
    b = sigmoid_func(a)
    c = np.dot(b, W_2)
    Y_pred.append(softmax(c))

Y_pred_classes = np.argmax(Y_pred, axis=1) + 1

# 정확도 계산
accuracy = np.mean(Y_pred_classes == y)
print(f'Accuracy: {accuracy * 100:.2f}%')
