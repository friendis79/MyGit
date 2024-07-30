import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense

# 데이터 로드
data = pd.read_csv('C:/Coding/Python/hanium_project/rssi_exam/rssi_data.csv')

# 장치 1번과 나머지 장치들의 RSSI 값만 사용
data = data[['Time', 'Device_1', 'Device_2', 'Device_3', 'Device_4', 'Device_5']]

# 시간 컬럼 제거 및 값 스케일링
scaler = MinMaxScaler()
data_scaled = scaler.fit_transform(data.drop('Time', axis=1))

# 데이터 준비
def create_dataset(dataset, look_back=1):
    X, Y = [], []
    for i in range(len(dataset) - look_back):
        a = dataset[i:(i + look_back), :]
        X.append(a)
        Y.append(dataset[i + look_back, 0])  # 장치 1번의 값
    return np.array(X), np.array(Y)

look_back = 10
X, y = create_dataset(data_scaled, look_back)

# LSTM 모델 생성
model = Sequential()
model.add(LSTM(50, return_sequences=True, input_shape=(look_back, 5)))
model.add(LSTM(50))
model.add(Dense(1))
model.compile(optimizer='adam', loss='mean_squared_error')

# 모델 학습
model.fit(X, y, epochs=10, batch_size=1, verbose=2)

# 예측
predictions = model.predict(X)

# 실제 값으로 변환
predictions_rescaled = scaler.inverse_transform(np.concatenate((predictions, np.zeros((predictions.shape[0], 4))), axis=1))[:, 0]

# 밀집도 및 위험도 계산
distance_threshold = -70  # 예시 RSSI 기준
density = np.mean(data.iloc[:, 2:] > distance_threshold, axis=1)
risk = np.mean(density > 0.5)  # 임의의 기준값 0.5

# 데이터프레임에 추가
results = pd.DataFrame(data['Time'][look_back:].reset_index(drop=True))
results['Predicted_Device_1'] = predictions_rescaled
results['Density'] = density[look_back:]
results['Risk'] = (density[look_back:] > 0.5).astype(int)

# 결과 출력
print(results)

# 시각화
plt.figure(figsize=(12, 8))

plt.subplot(3, 1, 1)
plt.plot(data['Time'][look_back:], results['Predicted_Device_1'], label='Predicted Device 1 RSSI')
plt.xticks(rotation=45)
plt.legend()

plt.subplot(3, 1, 2)
plt.plot(data['Time'][look_back:], results['Density'], label='Density')
plt.xticks(rotation=45)
plt.legend()

plt.subplot(3, 1, 3)
plt.plot(data['Time'][look_back:], results['Risk'], label='Risk')
plt.xticks(rotation=45)
plt.legend()

plt.tight_layout()
plt.show()

# 밀집도와 위험도 출력문
avg_density = np.mean(results['Density'])
overall_risk = np.mean(results['Risk'])

print(f"Average Density: {avg_density:.2f}")
print(f"Overall Risk: {overall_risk:.2f}")