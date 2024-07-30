# 실습 2 - 전체 데이터 중20(1번~20번)를 훈련 집합(S)으로 후반 5개(21번~~25번)를 테스트 집합(T)으로 나누고 각 집합의 데이터를 그래프로 표시

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# CSV 파일을 읽어 Pandas DataFrame으로 변환
raw_data = pd.read_csv("C:/Coding/Python/machine_learning/week7/lin_regression_data_03.csv", names=['age', 'height'])

# 총 데이터 크기를 구하고 교육 및 테스트 데이터 크기 계산
data_size = raw_data.shape[0]
train_size = int(0.8 * data_size)  # training data -> 80%
test_size = data_size - train_size # test data -> 20%

# training, test data 구분
train_data = raw_data[:train_size]
test_data = raw_data[train_size:]

# 나이 및 키 데이터 추출
train_age = train_data['age'].to_numpy()
train_height = train_data['height'].to_numpy()

test_age = test_data['age'].to_numpy()
test_height = test_data['height'].to_numpy()

# plot

plt.scatter(train_age, train_height, color='blue', label='Training Data')  # Training data
plt.scatter(test_age, test_height, color='orange', label='Test Data') # Test data plot

plt.xlabel('Age [months]')
plt.ylabel('Height [cm]')
plt.legend()
plt.grid()

plt.show()