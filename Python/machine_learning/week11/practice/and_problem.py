#실습1 NAND
import numpy as np

def step_func(t):
    if t > 0: return 1
    else: return 0

#훈련데이터 세트
X = np.array([
    [0,0,1],
    [0,1,1],
    [1,0,1],
    [1,1,1]
])

y_or = np.array([0,1,1,1])
y_Nand = np.array([1,1,1,0])
y_Xor = np.array([0,1,1,0])

W_or = np.zeros(len(X[0]))
W_Nand = np.zeros(len(X[0]))
W_and = np.zeros(len(X[0]))

def perceptron_fit(X, Y, epochs,W):
    
    eta = 0.2
    for t in range(epochs):
        print("epoch = ",t)
        for i in range(len(X)):
            predict = step_func(np.dot(X[i],W))
            error = Y[i] - predict #오차계산
            W += eta * error * X[i] #가중치 업데이트
            print("현재 처리 입력 = ",X[i],"정답 = ",Y[i],"출력 = ", predict,"변경된 가중치 = ", W)
    
    return W

def perceptron_predict(X,Y):
    global W
    for x in X:
        print(x[0], x[1], "=>", step_func(np.dot(x,W)))
        


W_Nand = perceptron_fit(X,y_Nand,6,W_Nand)
W_or = perceptron_fit(X,y_or,6,W_or)

def perceptron_fitXOR(X,Y,epochs,W_or,W_Nand,W_and):
    s = np.ones_like(X)
    for i in range(0,4,1):
        s[i][0] = step_func(np.dot(X[i],W_Nand))
        s[i][1] = step_func(np.dot(X[i],W_or))
        
    eta = 0.2
   
    for t in range(epochs):
        print("epoch = ",t)
        for i in range(len(s)):
            predict = step_func(np.dot(s[i],W_and))
            error = Y[i] - predict #오차계산
            W_and += eta * error * s[i] #가중치 업데이트
            print("현재 처리 입력 = ",s[i],"정답 = ",Y[i],"출력 = ", predict,"변경된 가중치 = ", W_and)
    
perceptron_fitXOR(X,y_Xor,6,W_or,W_Nand,W_and)