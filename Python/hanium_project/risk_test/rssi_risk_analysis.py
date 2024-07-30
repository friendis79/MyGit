import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# 데이터프레임 로드
df = pd.read_csv('C:/Coding/Python/hanium_project/risk_test/rssi_distance_risk_predictions.csv')

# 산점도를 통한 군집도 예측 시각화
plt.figure(figsize=(10, 6))
sns.scatterplot(x=df.index, y='PredictedDistanceToNextDevice', data=df, hue='RiskLevel', palette='viridis', size='RiskLevel', sizes=(20, 200))
plt.title('Predicted Distance and Risk Level Scatter Plot')
plt.xlabel('Index')
plt.ylabel('Predicted Distance to Next Device')
plt.legend(title='Risk Level')
plt.show()

# 위험도 수치 시각화
risk_count = df['RiskLevel'].value_counts()
plt.figure(figsize=(8, 6))
sns.barplot(x=risk_count.index, y=risk_count.values, palette='rocket')
plt.title('Distribution of Risk Levels')
plt.xlabel('Risk Level')
plt.ylabel('Frequency')
plt.show()