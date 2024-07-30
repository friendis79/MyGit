import numpy as np

class perceptron:   # self -> perceptron : 클래스의 인스턴스를 의미
    def __init__(self, w):  # 객체를 초기화하는 메소드/생성자
        self.w = w  # w를 인자로 받아 self.w 초기화

    def output(self, x):    # 메소드 정의
        tmp = np.dot(self.w, np.append(1, x))
        result = 1.0*(tmp>0)
        return result

w = np.array([-1.2, 1, 1])
and_gate = perceptron(w)
x_list = [[0, 0], [1, 0], [0, 1], [1, 1]]
for x in x_list:
    print(f"x = {x} ====> {and_gate.output}")