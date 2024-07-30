import numpy as np
import pandas as pd
import tensorflow as tf
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense, Dropout

# 샘플 RSSI 데이터 생성
np.random.seed(42)
num_devices = 10  # BLE 디바이스 수
num_samples_per_device = 200  # 각 디바이스당 RSSI 값 수
device_ids = [f'Device_{i+1}' for i in range(num_devices)]  # 디바이스 ID 목록

# 빈 데이터프레임 생성
df = pd.DataFrame(columns=["DeviceID", "RSSI"])

# 각 디바이스에 대해 RSSI 데이터 생성 및 데이터프레임에 추가
for device_id in device_ids:
    rssi_data = np.random.randint(-100, 0, size=(num_samples_per_device, 1))  # -100에서 0 사이의 RSSI 값 생성
    device_data = pd.DataFrame(rssi_data, columns=["RSSI"])
    device_data["DeviceID"] = device_id
    df = pd.concat([df, device_data], ignore_index=True)

# RSSI 값을 거리로 변환하는 함수
def rssi_to_distance(rssi, rssi0=-40, n=2):
    return 10 ** ((rssi0 - rssi) / (10 * n))

# 거리 데이터 계산
df['Distance'] = df['RSSI'].apply(rssi_to_distance)

# LSTM 모델에 입력할 데이터 준비
scaler = MinMaxScaler(feature_range=(0, 1))
df['ScaledDistance'] = scaler.fit_transform(df['Distance'].values.reshape(-1, 1))

# 시계열 데이터 생성
def create_sequences(data, seq_length):
    xs, ys = [], []
    for i in range(len(data) - seq_length):
        x = data[i:i + seq_length]
        y = data[i + seq_length]
        xs.append(x)
        ys.append(y)
    return np.array(xs), np.array(ys)

seq_length = 10
X, y = create_sequences(df['ScaledDistance'].values, seq_length)

# LSTM 모델 정의
model = Sequential()
model.add(LSTM(50, return_sequences=True, input_shape=(seq_length, 1)))
model.add(Dropout(0.2))
model.add(LSTM(50, return_sequences=False))
model.add(Dropout(0.2))
model.add(Dense(1))

model.compile(optimizer='adam', loss='mean_squared_error')

# 데이터 형태 변경
X = X.reshape((X.shape[0], X.shape[1], 1))

# 모델 학습
model.fit(X, y, epochs=50, batch_size=32, validation_split=0.2)

# 예측
predictions = model.predict(X)

# 예측값을 실제 거리로 변환
predictions = scaler.inverse_transform(predictions)

# 위험도 계산 함수
def calculate_risk(distance):
    if distance <= 1:
        return 3  # 높은 위험도
    elif distance <= 2:
        return 2  # 중간 위험도
    elif distance <= 3:
        return 1  # 낮은 위험도
    else:
        return 0  # 매우 낮은 위험도

# 위험도 계산
risk_levels = [calculate_risk(dist) for dist in predictions.flatten()]

# 결과 출력
df['PredictedDistance'] = np.nan
df.loc[seq_length:, 'PredictedDistance'] = predictions.flatten()
df['RiskLevel'] = np.nan
df.loc[seq_length:, 'RiskLevel'] = risk_levels

# CSV 파일로 저장
file_path = 'C:/Coding/Python/hanium_project/didimdol/rssi_distance_risk_predictions.csv'
df.to_csv(file_path, index=False)

print(f"예측된 거리 데이터와 위험도가 {file_path}에 저장되었습니다.")