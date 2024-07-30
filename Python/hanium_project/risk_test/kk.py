import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense, Dropout

# Seed for reproducibility
np.random.seed(42)

# Parameters
num_devices = 5  # Number of BLE devices
num_samples_per_device = 200  # Number of RSSI values per device

# Generate sample RSSI data
device_ids = [f'Device_{i+1}' for i in range(num_devices)]
df = pd.DataFrame(columns=["DeviceID", "RSSI"])

for device_id in device_ids:
    rssi_data = np.random.randint(-100, 0, size=(num_samples_per_device, 1))
    device_data = pd.DataFrame(rssi_data, columns=["RSSI"])
    device_data["DeviceID"] = device_id
    df = pd.concat([df, device_data], ignore_index=True)

# Save the generated data to CSV
file_path = 'C:/Coding/Python/hanium_project/risk_test/rssi_sample.csv'
df.to_csv(file_path, index=False)
print(f"RSSI data has been saved to {file_path}.")

# RSSI to distance conversion function
def rssi_to_distance(rssi, rssi0=-40, n=2):
    return 10 ** ((rssi0 - rssi) / (10 * n))

# Calculate distance to the next device
df['Timestamp'] = np.tile(np.arange(num_samples_per_device), num_devices)
df.sort_values(by=['Timestamp', 'DeviceID'], inplace=True)

df['NextDeviceID'] = df.groupby('Timestamp')['DeviceID'].shift(-1).fillna(method='ffill')
df['RSSI_NextDevice'] = df.groupby('Timestamp')['RSSI'].shift(-1).fillna(method='ffill')

df['DistanceToNextDevice'] = df['RSSI_NextDevice'].apply(rssi_to_distance)

# Prepare data for LSTM
scaler = MinMaxScaler(feature_range=(0, 1))
df['ScaledDistanceToNextDevice'] = scaler.fit_transform(df['DistanceToNextDevice'].values.reshape(-1, 1))

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

# Define the LSTM model
model = Sequential([
    LSTM(50, return_sequences=True, input_shape=(seq_length, 1)),
    Dropout(0.2),
    LSTM(50, return_sequences=False),
    Dropout(0.2),
    Dense(1)
])
model.compile(optimizer='adam', loss='mean_squared_error')

# Reshape data for the LSTM model
X = X.reshape((X.shape[0], X.shape[1], 1))

# Train the model
model.fit(X, y, epochs=50, batch_size=32, validation_split=0.2)

# Predict distances
predictions = model.predict(X)

# Convert predictions back to original scale
predictions = scaler.inverse_transform(predictions)

# Calculate risk levels
def calculate_risk(distance):
    if distance <= 1:
        return 3  # High risk
    elif distance <= 2:
        return 2  # Medium risk
    elif distance <= 3:
        return 1  # Low risk
    else:
        return 0  # Very low risk

# Append predictions and risk levels to the dataframe
df['PredictedDistanceToNextDevice'] = np.nan
df.loc[seq_length:, 'PredictedDistanceToNextDevice'] = predictions.flatten()
df['RiskLevel'] = np.nan
df.loc[seq_length:, 'RiskLevel'] = [calculate_risk(dist) for dist in predictions.flatten()]

# Save the results to a CSV file
output_file_path = 'C:/Coding/Python/hanium_project/risk_test/rssi_distance_risk_predictions.csv'
df.to_csv(output_file_path, index=False)

print(f"Predicted distance data and risk levels have been saved to {output_file_path}.")

# Risk level summary
print("\nRisk level summary:")
risk_summary = df['RiskLevel'].value_counts().sort_index()
print(risk_summary)

# Print data for devices 1 to 5
print("\nData for devices 1 to 5:")
print(df[df['DeviceID'].isin(['Device_1', 'Device_2', 'Device_3', 'Device_4', 'Device_5'])])
