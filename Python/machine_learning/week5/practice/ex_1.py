# 실습 1 - 제공된 데이터 파일을 불러들여 x축은 키, y축은 몸무게, z축은 나이를 나타내는 3차원 공간에 각 데이터의 위치를 점으로 표시

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

# plot
fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.scatter(height, weight, age)
ax.set_xlabel('height')
ax.set_ylabel('weight')
ax.set_zlabel('age')

plt.show()