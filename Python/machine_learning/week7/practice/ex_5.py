# 실습 5 - 전체 데이터를 차례로 5등분하여 5개의 부분집합으로 나누고,
# 각 집합의 데이터를 x축은 나이, y축은 키를 나타내는 2차원 평면에 서로 다른 모양의 마커로 표시

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# CSV 파일을 읽어 Pandas DataFrame으로 변환
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week7/lin_regression_data_03.csv", names=['age', 'height'])

# 데이터 분할
data_size = raw_data.shape[0]
subset_size = data_size // 5  # 전체 데이터 크기를 5등분

# 데이터를 5개의 부분 집합으로 나누기
subsets = [raw_data[i * subset_size: (i + 1) * subset_size] for i in range(5)]

# 부분 집합 시각화 및 표시
plt.figure()
markers = ['o', 's', '+', '*', 'x']  # 각 부분집합을 구분하기 위한 다른 마커

for i, subset in enumerate(subsets):
    plt.scatter(subset['age'], subset['height'], marker=markers[i], label=f'Subset {i+1}')

plt.xlabel('Age')
plt.ylabel('Height')
plt.title('Visualization of Data Subsets')
plt.legend()
plt.grid()
plt.show()