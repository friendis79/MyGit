import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense
import matplotlib.pyplot as plt

# 샘플 파일 로드
def load_data(file_path):
    data = pd.read_csv(file_path)
    return data

# 데이터 전처리 및 시퀀스 생성 함수
def preprocess_data(data, seq_length):
    scaler = MinMaxScaler(feature_range=(0, 1))
    scaled_data = scaler.fit_transform(data)

    sequences = []
    labels = []
    for i in range(len(scaled_data) - seq_length):
        sequences.append(scaled_data[i:i + seq_length])
        labels.append(scaled_data[i + seq_length])
    return np.array(sequences), np.array(labels), scaler

# 모델 훈련 및 평가
def train_lstm_model(X_train, y_train, X_val, y_val, seq_length):
    model = Sequential()
    model.add(LSTM(units=50, return_sequences=True, input_shape=(seq_length, 1)))
    model.add(LSTM(units=50))
    model.add(Dense(1))

    model.compile(optimizer='adam', loss='mean_absolute_error')

    history = model.fit(X_train, y_train, epochs=20, batch_size=32, validation_data=(X_val, y_val))
    
    return model, history

# RSSI 데이터 시각화
def plot_rssi_data(data):
    plt.figure(figsize=(12, 6))
    plt.plot(data, label='RSSI')
    plt.title('RSSI Data')
    plt.xlabel('Time')
    plt.ylabel('RSSI')
    plt.legend()
    plt.show()

# 예측 결과 시각화
def plot_predictions(data, predictions, scaler, seq_length):
    data = scaler.inverse_transform(data)
    plt.figure(figsize=(12, 6))
    
    # 원본 데이터
    plt.plot(data, label='Original RSSI')
    
    # 예측 데이터
    predictions_plot = np.empty_like(data)
    predictions_plot[:, :] = np.nan
    predictions_plot[seq_length:len(predictions) + seq_length, :] = predictions
    plt.plot(predictions_plot, label='Predicted RSSI')
    
    plt.title('RSSI Prediction')
    plt.xlabel('Time')
    plt.ylabel('RSSI')
    plt.legend()
    plt.show()

# 위험도 계산
def calculate_risk(data, threshold):
    risk = np.where(data < threshold, 1, 0)
    return risk

# 위험도 백분율 계산
def calculate_risk_percentage(risk):
    total_points = len(risk)
    high_risk_points = np.sum(risk)  # 위험한 포인트 수
    risk_percentage = (high_risk_points / total_points) * 100
    return risk_percentage

# 전체 프로세스 함수
def main(file_path, seq_length, risk_threshold):
    data = load_data(file_path)
    plot_rssi_data(data.values)
    
    X, y, scaler = preprocess_data(data, seq_length)

    train_size = int(len(X) * 0.8)
    X_train, X_val = X[:train_size], X[train_size:]
    y_train, y_val = y[:train_size], y[train_size:]

    model, history = train_lstm_model(X_train, y_train, X_val, y_val, seq_length)

    loss = model.evaluate(X_val, y_val)
    print(f"Validation Loss: {loss}")

    predictions = model.predict(X_val)
    predictions = scaler.inverse_transform(predictions)
    
    plot_predictions(data.values, predictions, scaler, seq_length)
    
    risk = calculate_risk(data.values, risk_threshold)
    plot_risk(data.values, risk)
    
    risk_percentage = calculate_risk_percentage(risk)
    
    return predictions, risk, risk_percentage

# 위험도 시각화
def plot_risk(data, risk):
    plt.figure(figsize=(12, 6))
    plt.plot(data, label='RSSI')
    plt.fill_between(range(len(data)), data.flatten(), where=risk.flatten() == 1, color='red', alpha=0.3, label='High Risk')
    plt.title('Risk Analysis Based on RSSI')
    plt.xlabel('Time')
    plt.ylabel('RSSI')
    plt.legend()
    plt.show()

# 샘플 파일 경로와 시퀀스 길이, 위험도 기준 값 지정
file_path = 'C:/Coding/Python/hanium_project/didimdol/rssi_sample1.csv'
seq_length = 10
risk_threshold = -150  # 예: RSSI 값이 -150 이하인 경우 높은 위험도로 간주

# 전체 프로세스 실행
predictions, risk, risk_percentage = main(file_path, seq_length, risk_threshold)

# 예측 결과 출력
print("Predictions:")
print(predictions)

# 위험도 백분율 출력
print("Risk Percentage:")
print(f"{risk_percentage:.2f}%")