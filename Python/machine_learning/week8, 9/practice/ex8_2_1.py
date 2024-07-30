# 실습 2_1 - 제공된 데이터 파일을 불러들여 3차원 공간에 표시

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# CSV 파일을 읽어 Pandas DataFrame으로 변환
data = pd.read_csv("C:/Coding/Python/machine_learning/week8, 9/Iris.csv", names=['sepal_length', 'petal_length', 'variety'])

setosa = data[data['variety'] == 'Setosa']
versicolor = data[data['variety'] == 'Versicolor']

# 3차원 공간에 데이터 표시
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# Setosa 종류의 데이터 0으로 구분
ax.scatter(setosa['sepal_length'], setosa['petal_length'], [0] * len(setosa), c='r', label='Setosa')

# Versicolor 종류의 데이터 1으로 구분
ax.scatter(versicolor['sepal_length'], versicolor['petal_length'], [1] * len(versicolor), c='b', label='Versicolor')

# 축 레이블과 범례 추가
ax.set_xlabel('Sepal Length (cm)')
ax.set_ylabel('Petal Length (cm)')
ax.set_zlabel('Species')
ax.legend()

plt.title('Iris Data')
plt.show()