# 배열 간의 연산
""" import numpy as np

A = np.array([1, 2, 3, 4])
B = np.array([5, 6, 7])

result = A + B
print(result) # 배열의 크기가 일치하지 않으면 계산할 수 없음 - ValueError: operands could not be broadcast together with shapes
 """
# 배열을 만든 후 연산 수행
""" import numpy as np

a = np.array(range(1, 11))
b = np.array(range(10, 101, 10))

print(a+b); print(a-b); print(a*b); print(a/b) """

# 2차원 배열의 생성
""" import numpy as np

b = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
print(b)
print(b[0][2]) """

# numpy 배열의 속성
""" import numpy as np

array_a = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
print("array a = ", array_a)

print("array a's shape = ", array_a.shape)
print("array a's ndim = ", array_a.ndim)
print("array a's dtype = ", array_a.dtype)
print("array a's size = ", array_a.size)
print("array a's itemsize = ", array_a.itemsize) """

# numpt 배열 계산 - 행, 열 단위 계산
""" import numpy as np
score = np.array([[99, 93, 60], [98, 82, 93], [93, 65, 81], [78, 82, 81]])

print("배열의 전체 합 : ", score.sum())
print("배열의 최소 값 : ", score.min())
print("배열의 최대 값 : ", score.max())
print("배열의 평균 값 : ", score.mean())
print("배열의 표준편차 값 : ", score.std())
print("배열의 분산 값 : ", score.var())
print("배열축의 평균 값 : ", score.mean(axis=0)) """

# 인덱싱과 슬라이싱
""" import numpy as np

score = np.array([88, 72, 93, 94, 89, 78, 99])

print("score[2] => ", score[2])
print("score[-1] => ", score[-1])
print("score[1:4] => ", score[1:4])
print("score[3:] => ", score[3:])
print("score[4:-1] => ", score[4:-1]) """

# 논리적 인덱싱을 이용한 추출
""" import numpy as np

ages = np.array([10, 19, 25, 30, 28])
y = ages > 20
print(y)
print(ages[ages > 20]) """

# 2차원 배열의 인덱싱
""" import numpy as np
y = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
print(y)

array = np.array(y)
print(array) """

# 2차원 배열의 인덱싱 - 2
""" import numpy as np

array = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])

print(array[0][2])
print(array[0, 2])
print(array[0, 0])
print(array[2, -1]) """

# 2차원 배열의 인덱싱 - 3
""" import numpy as np
array  = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
array[0, 0] = 12
print(array)

array[2, 2] = 1.234
print(array) """

# 2차원 배열 슬라이싱 - 큰 행렬에서 작은 행렬의 일부 추출
""" import numpy as np

array = np.array([[1, 2, 3, 4],
                  [5, 6, 7, 8],
                  [9, 10, 11, 12],
                  [13, 14, 15, 16]])
print(array[0:2, 2:4])
print(array[0])
print(array[1, 1:3]) """

# 2차원 배열의 논리적 인덱싱 - 조건에 맞는 값 추출
""" import numpy as np

array = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])

print(array > 5)
print(array[array > 5])
print(array[: , 2])
print(array[: , 2] > 5)


# 필터링
print(array [ : ] % 2 == 0)
print(array [array %2 == 0]) """

# 전치행렬 계산하기
""" import numpy as np

a = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
x = a.transpose()
print(x)

a= x.T
print(a) """

# 벡터의 내적 외적
""" import numpy as np

v1 = np.array([1, 2, 3])
v2 = np.array([4, 5, 6])
print(np.dot(v1, v2))
print(np.cross(v1, v2)) """

# 역행렬
""" import numpy as np

x = np.array([[2, 5], [1, 3]])
y = np.linalg.inv(x)
print(y) """

# 선형 방정식
""" import numpy as np

a = np.array([[3, 1], [1, 2]])
b = np.array([9, 8])
r = np.linalg.solve(a, b)
print(r) """

# numpy 데이터 생성 함수 - arange()
""" import numpy as np

x = np.arange(1, 10, 2)
print(x) """

# numpy 데이터 생성 함수 - linspace()
""" import numpy as np

x = np.linspace(0, 10, 100)
print(x) """

# numpy 데이터 생성 함수 - logspace()
""" import numpy as np

x = np.logspace(0, 5, 10)
print(x) """

# 난수 생성 - 균일 분포 난수 생성 : random.rand()
""" import numpy as np

#시드가 설정되면 난수는 0.0에서 1.0값으로 생성된다.
np.random.seed(100)

print(np.random.rand(5))
print(np.random.rand(5, 3)) """

# 난수 생성 - 정규 분포 난수 생성 : random.randn()
""" import numpy as np

print(np.random.randn(5, 4))

# 평균값과 표준편차를 다르게 하려면 다음과 같이 하면 된다.
m, sigma = 10, 2

print(sigma*np.random.randn(5)) """

# 난수 생성 - 정규 분포의 난수 생성 : random.normal(평균, 표준편차, 배열차원)
""" import numpy as np

mu, sigma = 0, 0.1 #평균과 표준편차
print(np.random.normal(mu, sigma, 5)) """

# matplotlib 사용하기
""" import matplotlib.pyplot as plt
plt.plot([15.6, 14.2, 16.3, 18.2, 17.1, 20.2, 22.4])
plt.show() """

# 직선 그래프 그리기
""" from matplotlib import pyplot as plt
x = [1, 2, 3, 4, 5, 6, 7]
y = [15.6, 14.2, 16.3, 18.2, 17.1, 20.2, 22.4]
plt.plot(x, y)
plt.show() """

# 직선 그래프 그리기 - 2
""" from matplotlib import pyplot as plt

x = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
y = [15.6, 14.2, 16.3, 18.2, 17.1, 20.2, 22.4]

plt.plot(x, y)
plt.xlabel("day")
plt.ylabel("temperature")
plt.show() """

# 직선 그래프 그리기 - 3
""" from matplotlib import pyplot as plt

x = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
y1 = [15.6, 14.2, 16.3, 18.2, 17.1, 20.2, 22.4]
y2 = [20.1, 23.1, 23.8, 25.9, 23.4, 25.1, 26.3]

plt.plot(x, y1, x, y2)
plt.xlabel("day")
plt.ylabel("temperature")
plt.show() """

# 직선 그래프 그리기 - 4
""" from matplotlib import pyplot as plt

x = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
y1 = [15.6, 14.2, 16.3, 18.2, 17.1, 20.2, 22.4]
y2 = [20.1, 23.1, 23.8, 25.9, 23.4, 25.1, 26.3]

plt.plot(x, y1, label="Seoul")
plt.plot(x, y2, label="Busan")
plt.xlabel("day")
plt.ylabel("temperature")
plt.legend(loc="upper left")
plt.title("Temperature of Cities")
plt.show() """

# 막대 그래프 그리기
""" import matplotlib.pyplot as plt
x = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
y = [15.6, 14.2, 16.3, 18.2, 17.1, 20.2, 22.4]
plt.bar(x, y, width=0.7, color = "blue")
plt.show() """

# 3차원 그래프
""" import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 3차원 축(axis)을 얻는다.
axis = plt.axes(projection = '3d')

# 3차원 데이터를 numpy 배열로 생성한다.
z = np.linspace(0, 1, 100)
x = z*np.sin(30*z)
y = z*np.cos(30*z)

# 3차원 그래프를 그린다.
axis.plot3D(x, y, z, color = "red")
plt.show() """

# 이변 함수 3차원 그래프 그리기
""" import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 차원 축의 값을 얻는다.
ax = plt.axes(projection='3d')

# f(x, y) 함수를 정의한다.
def f(x, y):
    r = 2 * x**2 + y**2
    ans = r * np.exp(-r)
    return ans

# x, y 계산 범위를 설정하고 구간을 -2, 2로 설정하고 9등분한다.
xn = 9
x = np.linspace(-2, 2, xn)
y = np.linspace(-2, 2, xn)

# x, y의 각 값들을 함수에 대입했을 때 결과값을 저장하기 위해 2차원 배열 temp를 선언한다.
temp = np.zeros((len(x), len(y)))
for i in range(xn):
    for j in range(xn):
        temp[j, i] = f(x[i], y[j])

# 좌표점 x, y를 격자 좌표 xx, yy로 만든다.
xx, yy = np.meshgrid(x, y)

# 3차원 그래프에 함수의 표면을 출력한다.
ax.plot_surface(xx, yy, temp, cmap='viridis')

# 그래프를 표시한다.
plt.show()

ax.plot_surface(xx, yy, temp, rstride=1, cstride=1, alpha=0.3, color='blue', edgecolor='block')
plt.show() """

# 이미지 출력
""" import matplotlib.pyplot as plt
import matplotlib.image as img
import matplotlib.font_manager as fm

# 한글 폰트를 사용하기 위한 세팅
font_path = 'C:/Windows/Fonts/malgun.ttf'
font_prop = fm.FontProperties (fname=font_path)
font_name = font_prop.get_name()
plt.rc('font', family=font_name)

# 이미지 출력
plt.suptitle("한국공학대학교")
image = img.imread("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/한국공학대학교.jpg")
plt.imshow(image)
plt.show() """

# 히스토그램과 정규분포 그래프
""" import matplotlib.pyplot as plt
import numpy as np

numbers = np.random.normal(0, 1, 1000)
m = numbers.mean() #평균
s = numbers.std()  #표준편차

x = np.linspace(m - 3*s, m + 3*s, 100)
y = (lambda x: 1 / (s * np.sqrt(2 * np.pi)) * np.exp(-(x - m)**2 / (2 * s**2)))(x)

fig, ax1 = plt.subplots()
ax1.hist (numbers, rwidth=0.7) # 히스토그램 그래프
ax2 = ax1.twinx()
ax2.plot(x, y, 'r') # 정규분포 그래프 그리기
plt.grid()
plt.show() """

# sin(), cos() 함수 그리기
""" import matplotlib.pyplot as plt
import numpy as np

# -2pi에서 2pi까지 100개의 데이터를 균일하게 생성한다.
x = np.linspace(-2 * np.pi, 2* np.pi, 100)

# numpy 배열에 sin() 함수를 적용한다.
y1 = 2*np.sin(x)
y2 = np.cos(x)

plt.plot(x, y1, x, y2)
plt.grid()
plt.show() """

# 잡음이 들어간 sin() 함수 그리기
""" import matplotlib.pyplot as plt
import numpy as np

# -2pi에서 2pi까지 100개의 데이터를 균일하게 생성한다.
x = np.linspace(-2 * np.pi, 2* np.pi, 100)

# 평균이 0이고 표준편차가 1인 100개의 난수
noise = np.random.normal(0, 1, 100)

# numpy 배열에 sin() 함수를 적용한다.
y1 = np.sin(x)
y2 = np.sin(x) + noise

plt.plot(x, y1, x, y2, 'r')
plt.grid()
plt.show() """

# 연속시간 신호와 이산 신호 그리기
""" import numpy as np
import matplotlib.pyplot as plt

t = np.linspace(0, 2*np.pi, 300)
xt = (2/5)*t*np.cos(2*np.pi*t)

plt.subplot(2, 1, 1)
plt.plot(t, xt, "b")
plt.title("Continuous time signal / Discrete time signal")
plt.grid()

nt = np.linspace(0, 2*np.pi, 50)
dt = (2/5)*nt*np.cos(2*np.pi*nt)
plt.subplot(2,1, 2)
plt.stem(nt, dt, "r")
plt.grid()

plt.show() """


