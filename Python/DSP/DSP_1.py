import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import cheby2, freqz, lfilter

# 필터 매개변수 설정
order = 4  # 필터 차수
ripple = 20  # 차단 대역 리플 (dB)
cutoff = 0.2  # 차단 주파수 (비정규화, Nyquist 주파수 기준)

# 체비셰프 2형 필터 설계
b, a = cheby2(order, ripple, cutoff, btype='low', analog=False)

# 주파수 응답 계산
w, h = freqz(b, a, worN=2000)

# 주파수 응답 그래프
plt.plot(w / np.pi, 20 * np.log10(abs(h)))
plt.title('Chebyshev Type II frequency response')
plt.xlabel('Normalized Frequency (xπ rad/sample)')
plt.ylabel('Amplitude [dB]')
plt.grid()
plt.show()

# 샘플 신호 생성 및 필터 적용
t = np.linspace(0, 1.0, 500)
x = 0.5 * np.sin(2 * np.pi * 5 * t) + np.sin(2 * np.pi * 50 * t)
y = lfilter(b, a, x)

# 원 신호 및 필터된 신호 그래프
plt.plot(t, x, label='Original signal')
plt.plot(t, y, label='Filtered signal', linestyle='--')
plt.title('Original and Filtered Signal')
plt.xlabel('Time [s]')
plt.ylabel('Amplitude')
plt.legend()
plt.grid()
plt.show()