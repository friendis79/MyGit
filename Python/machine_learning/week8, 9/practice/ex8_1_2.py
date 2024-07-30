# 실습 1_2 - 제공된 데이터 파일을 불러들여 X축은 사슴벌레의 무게(g), y축은 성별을 나타내는 2차원 평면에 각 데이터의 위치를 표시

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# CSV 파일을 읽어 Pandas DataFrame으로 변환
data = pd.read_csv("C:/Coding/Python/machine_learning/week8, 9/binary_data_insect.csv", names=['weights', 'genders'])

# 데이터에서 사슴벌레의 무게(g)와 성별 추출
weights = data['weights'].to_numpy()
genders = data['genders'].to_numpy()

# 성별에 따라 색상과 마커 지정
colors = {0: 'red', 1: 'blue'}
markers = {0: 'o', 1: 's'}

# 성별에 따라 데이터 플롯
for weight, gender in zip(weights, genders):    # 사슴벌레 무게와 성별 데이터를 하나의 차트에 표시
    plt.scatter(weight, gender, color=colors[gender], marker=markers[gender])

plt.xlabel("weight (g)")
plt.ylabel("gender")
plt.title("Weight vs Gender")
plt.grid()

plt.show()