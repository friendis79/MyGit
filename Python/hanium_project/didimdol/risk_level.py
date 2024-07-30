import pandas as pd

# 데이터 읽기
data = pd.read_csv("C:/Coding/Python/hanium_project/didimdol/rssi_distance_risk_predictions.csv")

# 데이터프레임의 구조 확인
print(data.head())

# 위험 수준 할당 함수 정의
def assign_risk_level(predicted_distance):
    if predicted_distance <= 10:
        return 'High'
    elif predicted_distance <= 50:
        return 'Medium'
    elif predicted_distance <= 100:
        return 'Low'
    else:
        return 'Very Low'

# RiskLevel 열에 위험 수준 할당
data['RiskLevel'] = data['PredictedDistance'].apply(assign_risk_level)

# 각 디바이스별로 처리된 결과 확인
devices = data['DeviceID'].unique()
for device in devices:
    device_data = data[data['DeviceID'] == device]
    print(f"Device {device}:")
    print(device_data.head())

# 변환된 데이터프레임을 저장
data.to_csv('C:/Coding/Python/hanium_project/didimdol/updated_data_with_risk_levels_1.csv', index=False)