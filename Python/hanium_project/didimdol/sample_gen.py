import numpy as np
import pandas as pd

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

# CSV 파일로 저장
file_path = 'C:/Coding/Python/hanium_project/didimdol/rssi_sample1.csv'
df.to_csv(file_path, index=False)

print(f"샘플 RSSI 데이터가 {file_path}에 저장되었습니다.")