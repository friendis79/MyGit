# 실습 2 - 해석해로 구한 선형모델과 데이터를 한 그래프에 표시

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# CSV 파일을 읽어 Pandas DataFrame으로 변환 
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week5/multiple_linear_regression_data.csv", names = ['height', 'weight', 'age'])

# raw_data
height = raw_data['height'].to_numpy()
weight = raw_data['weight'].to_numpy()
age = raw_data['age'].to_numpy()

# convert data
X = raw_data[['height', 'weight']].to_numpy()
X = np.c_[X, np.ones(len(X))]

y = raw_data['age'].to_numpy()
y = y.reshape((len(y), 1))

# X의 역행렬을 이용하여 해를 계산 
analytic_W = np.linalg.pinv(X.T @ X) @ X.T @ y
print(f"해석해 : \n {analytic_W}")

# plot
height_data = np.linspace(55, 190, 1000)
weight_data = np.linspace(10, 100, 1000)
Height, Weight = np.meshgrid(height_data, weight_data)
analytic_y = analytic_W[0]*Height + analytic_W[1]*Weight + analytic_W[2]

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.scatter(height, weight, age)
ax.plot_surface(Height, Weight, analytic_y, cmap='plasma')
ax.set_xlabel('height')
ax.set_ylabel('weight')
ax.set_zlabel('age')
ax.set_title('Analytic Solution')

plt.show()