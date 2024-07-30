# 실습 1 - 제공된 데이터 파일을 불러들여 x축은 나이, y축은 키를 나타내는 2차원 평면에 각 데이터의 위치를 점으로 표시

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# CSV 파일을 읽어 Pandas DataFrame으로 변환
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week7/lin_regression_data_03.csv", names=['age', 'height'])

# raw_data
age = raw_data['age'].to_numpy()
height = raw_data['height'].to_numpy()

# plot
plt.scatter(age, height, label="Infant's Age and Height Data")
plt.xlabel('Age [Months]')
plt.ylabel('Height [cm]')
plt.grid()
plt.legend() 

plt.show()
