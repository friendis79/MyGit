import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense, Dropout
import matplotlib.pyplot as plt
import seaborn as sns

# 저장된 데이터 로드
file_path = 'C:/Coding/Python/hanium_project/risk_test/rssi_sample.csv'
df = pd.read_csv(file_path)

# RSSI 값을 거리로 변환하는 함수
def rssi_to_distance(rssi, rssi0=-40, n=2):
    return 10 ** ((rssi0 - rssi) / (10 * n))

# 다음 디바이스 ID 설정
df['NextDeviceID'] = df['DeviceID'].shift(-200)
df['NextDeviceID'].fillna(df['DeviceID'].iloc[0], inplace=True)
df['RSSI_NextDevice'] = df['RSSI'].shift(-200)
df['RSSI_NextDevice'].fillna(df['RSSI'].iloc[0], inplace=True)

# 다음 디바이스와의 거리 데이터 계산
df['DistanceToNextDevice'] = df['RSSI_NextDevice'].apply(rssi_to_distance)

# LSTM 모델에 입력할 데이터 준비
scaler = MinMaxScaler(feature_range=(0, 1))
df['ScaledDistanceToNextDevice'] = scaler.fit_transform(df['DistanceToNextDevice'].values.reshape(-1, 1))

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
X, y = create_sequences(df['ScaledDistanceToNextDevice'].values, seq_length)

# LSTM 모델 정의
model = Sequential([
    LSTM(50, return_sequences=True, input_shape=(seq_length, 1)),
    Dropout(0.2),
    LSTM(50, return_sequences=False),
    Dropout(0.2),
    Dense(1)
])
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

# 결과 출력 및 저장
df['PredictedDistanceToNextDevice'] = np.nan
df.loc[seq_length:, 'PredictedDistanceToNextDevice'] = predictions.flatten()
df['RiskLevel'] = np.nan
df.loc[seq_length:, 'RiskLevel'] = risk_levels

# CSV 파일로 저장
output_file_path = 'C:/Coding/Python/hanium_project/risk_test/rssi_distance_risk_predictions.csv'
df.to_csv(output_file_path, index=False)

print(f"예측된 거리 데이터와 위험도가 {output_file_path}에 저장되었습니다.")

# 위험도 수치 요약
print("\n위험도 수치 요약:")
risk_summary = df['RiskLevel'].value_counts().sort_index()
print(risk_summary)

# 일부 데이터 출력 (디바이스 1번부터 5번까지)
print("\n디바이스 1번부터 5번까지의 데이터:")
print(df[df['DeviceID'].isin([1, 2, 3, 4, 5])])