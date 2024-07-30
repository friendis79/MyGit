#객체의 멤버에 접근
""" class Counter:
    def __init__(self):
        self.count = 0
    def increment(self):
        self.count += 1
        
a = Counter()
a.increment()
print("Counter's value : ", a.count) """

#매개변수가 있는 생성자
""" class Counter:
    def __init__(self, initValue = 0):
        self.count = initValue
    def increment(self):
        self.count += 1
        
a = Counter(100) #카운터의 초깃값이 100이 된다.
b = Counter() #카운터의 초기값은 0이 된다.

a.increment()
print("PC : ", a.count)

b.increment()
print("PC : ", b.count) """

#Circle 클래스 만들기
""" import math

#Create Circle Class
class Circle:
    def __init__(self, radius = 0):
        self.radius = radius
    def getArea(self):
        area = math.pi * self.radius**2
        return area
    def getPerimeter(self):
        circum = 2 * math.pi * self.radius
        return circum
    
#원의 반지름을 입력한 후 Circle객체를 생성한다.
r = int(input("원의 반지름 입력 : "))
c = Circle(r)

print("원의 면적 : ", round(c.getArea(), 2))
print("원의 둘레 : ", round(c.getPerimeter(), 2)) """

#파이썬의 접근 제한자
""" class AccessModifier :
    def __init__(self):
        self.public = "PUBLIC"
        self.__private = "PRIVATE"
        self._protected = "PROTECTED"
        
    def print_test(self):
        print(self.public)
        print(self.__private)
        print(self._protected)
        
#AccessModifier 객체를 생성한다.
obj = AccessModifier()
obj.print_test() """

#접근자와 설정자
""" class Student:
    def __init__(self, name = None, age = 0):
        self.__name = name
        self.__age = age
    def getAge(self):
        return self.__age
    def getName(self):
        return self.__name
    def setAge (self, age):
        self.__age = age
    def setName(self, name):
        self.__name = name
        
obj = Student ("Jeong", 20)
name = obj.getName(); age = obj.getAge()
print(name, age) """

#객체를 함수로 전달 (import Bank_Account)
""" import Bank_Account

#Mobile로 입금
def MobileBank(M, amount):
    M.deposit(amount)
    
#MobileBank()를 호출하여 변경된 내용을 확인한다. 
Kim = Bank_Account.BankAccount(4000, 123456)
Kim.ViewAccount()
MobileBank(Kim, 9000)
# Kim.ViewAccount() # 잔고 출력 1번만 """

#매개변수가 있는 생성자
""" class Counter :
    def __init__(self):
        self.count = 0
    def increment (self):
        self.count += 1

a = Counter()
a.increment()
print("PC : ", a.count) """

#부모 클래스 정의
""" class Person:
    def __init__(self, name, age, gender):
        self.name = name
        self.age = age
        self.gender = gender
    def aboutMe(self):
        print("My name is ", self.name, ".")
        print("Age is", self.age, "old.")
        
#자식 클래스 정의
class Employee(Person):
    def __init__(self, name, age, gender, hiredate, salary):
        Person.__init__(self, name, age, gender)
        self.Hiredate = hiredate
        self.Salary = salary
        
    def dowork(self):
        print("열심히 일을 합니다.")
        
    def aboutMe(self):
        Person.aboutMe(self)
        print("제 입사일은", self.Hiredate, "입니다.")
        print("제 급여는", self.Salary, "입니다.")
        
Kim = Employee("김철수", 27, "남", "2020.01.01", "5,000,000") 
Kim.dowork()
Kim.aboutMe() """   

#특수 Method
""" class Word:
    def __init__(self, txt):
        self.txt = txt
    # 특수 메서드 __repr__() -> instence => print()
    def __repr__(self):
        return str(self.txt)
    
# 메인 출력
word1 = Word('Apple')
word2 = Word('Orange')
word3 = Word(100)
print(word1, word2, word3, sep = " ")

class Sum :
    def __init__(self, num):
        self.num = num
    
    #특수 메서드 add_() -> instence 사이를 덧셈 작업 해줌 
    def __add__(self, other):
        return self.num + other.num
     
#메인출력
num1 = Sum(20)
num2 = Sum(40)
print(num1 + num2) """

# 멀티 쓰레드

""" ## 쓰레드 미적용 시 ##
import time

class RacingCar:
    carName = ""
    def __init__(self, name):
        self.CarName = name
    def runCar(self):
        for i in range(0, 3):
            CarStr = self.CarName + "~~run. \n"
            print(CarStr, end = '')
            time.sleep(0.1)     # 0.1s stop
            
#main code
car1= RacingCar("@Car1")        
car2= RacingCar("#Car2")
car3= RacingCar("$Car3")

car1.runCar()
car2.runCar()
car3.runCar() """

""" ## 쓰레드 적용 시 ##
import threading
import time

class RacingCar:
    carName = ""
    def __init__(self, name):
        self.CarName = name
    def runCar(self):
        for i in range(0, 3):
            CarStr = self.CarName + "~~run. \n"
            print(CarStr, end = '')
            time.sleep(0.1)     # 0.1s stop
            
#main code
car1= RacingCar("@Car1")        
car2= RacingCar("#Car2")
car3= RacingCar("$Car3")

th1 = threading.Thread(target= car1.runCar)
th2 = threading.Thread(target= car2.runCar)
th3 = threading.Thread(target= car3.runCar)

th1.start()
th2.start()
th3.start() """

#멀티 프로세싱
import multiprocessing
import time

class RunningHorse :
    horseName = ''
    def __init__(self, name) :
        self.horseName = name
    
    def runHorse(self) :
        for _ in range(0, 3):
            horseStr = self.horseName + '~~ Running. \n'
            print(horseStr, end  = '')
            time.sleep(0.1)
            
if __name__ == "__main__":
    horse1 = RunningHorse('@얼룩말')
    horse2 = RunningHorse('$조랑말')
    
    mp1 = multiprocessing.Process(target=horse1.runHorse)
    mp2 = multiprocessing.Process(target=horse2.runHorse)
    
    mp1.start()
    mp2.start()
    
    mp1.join()
    mp2.join()

