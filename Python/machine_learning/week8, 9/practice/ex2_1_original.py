import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# CSV 파일을 읽어 Pandas DataFrame으로 변환
data = pd.read_csv("C:/Coding/Python/machine_learning/week8/Iris.csv", names=['sepal_length', 'petal_length', 'variety'])

# 카테고리 변수를 이진 변수로 변환
data['variety'] = data['variety'].map({'Setosa': 0, 'Versicolor': 1})

# 데이터에서 꽃받침 길이(cm), 꽃잎 길이(cm), iris (0, 1) 추출
x = data['sepal_length'].to_numpy()
y = data['petal_length'].to_numpy()
z = data['variety'].to_numpy()

# plot
fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.scatter(x, y, z)
ax.set_xlabel('sepal_length')
ax.set_ylabel('petal_length')
ax.set_zlabel('variety')

plt.show()