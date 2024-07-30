#한 행씩 읽어 들이기 (한 행 읽어 오기)
""" infile = open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/test.txt", "r", encoding = "UTF-8")
line = infile.readline() #한 행만 읽어옴
print(line)
infile.close() """

#한 행씩 읽어 들이기 (모든 행 읽어 오기)
""" infile = open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/test.txt", "r", encoding = "UTF-8")

while True:                 # while True: 사용해서 공백이 나오기 전까지 readline()을 실행
    line = infile.readline()
    if line == "":
        break
    print(line, end = '')
    
infile.close() """

#한 번에 모두 읽기 readlines() 함수
""" infile = open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/test.txt", "r", encoding = "UTF-8")

lines = infile.readlines() #한 번에 모두 읽는 역할을 하는 readlines() --> 출력하면 문자열?로 나옴
print(lines)
print('-'*20)

for line in lines: #문자열? 식으로 나오는것을 없앰
    line = line.strip() # strip()을 사용함으로써 공백(개행 문자 포함)을 제거
    print(line)
    
infile.close() """

#파일 전체 읽기
""" infile = open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/test.txt", "r", encoding = "UTF-8")

#read() -> 파일의 내용 전체를 문자열로 돌려준다.
data = infile.read()
print(data)
infile.close() """

#파일명을 입력하여 파일 전체 읽기
""" infile = None
fName, inList, inStr = "", [], ""

fName = input("파일명을 입력 하세요 : ") # D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/test.txt
infile = open(fName, 'r', encoding = 'UTF-8')

inList = infile.readlines()
for inStr in inList:
    print(inStr, end = "")
    
infile.close() """

#파일명이 없을 때 오류 처리
""" import os

infile = None
fName, inList, inStr = "", [], ""

fName = input("파일명을 입력 하세요 : ")

if os.path.exists(fName):
    infile = open(fName, 'r', encoding = 'UTF-8')
    
    inList = infile.readlines()
    
    for inStr in inList:
        print(inStr, end = "")
        infile.close()
else :
    print("%s 파일이 없습니다." % fName) """

#텍스트 파일 저장하기 writelines() - List에 있는 문자열 파일에 저장하기
""" outFile = open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/data.txt", "w")
memo = ["1번 째 줄입니다. \n", "2번 째 줄입니다. 냐하 \n"]
outFile.writelines(memo)
outFile.close() """

#텍스트 파일 저장하기 writelines() - 키보드에서 입력한 내용을 한 행씩 파일에 쓰는 코드
""" ouFile = None
outStr = ""

outFile = open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/data.txt", "w")

while True:
    outStr = input("내용 입력 :")
    if outStr != "":
        outFile.write(outStr + "\n")
        
    else :
        break
    
outFile.close()
print("---정상적으로 파일에 씀---") """

#파일을 읽어 다른 파일로 저장하기
""" inStr = ""
inFile = open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/data.txt", "r")
outFile = open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/data4.txt", "w")

inList = inFile.readlines()
for inStr in inList:
    outFile.write(inStr)
    
inFile.close()
outFile.close()
print("---파일이 정상적으로 복사되었음 ---") """

#write()함수 - 문자열을 파일에 저장하기
""" outFile = open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/data.txt", "w")
data = ""

for i in range(1, 6):
    data += "%s번 째 줄입니다. \n" %i
    
outFile.write(data)
outFile.close() """

#기존 파일에 새로운 내용 추가하기
""" outFile = open("D:/Spyder_PyThon/contents_of_class/ch9/data.txt", "a")
data = ""

for i in range(6, 10):
    data += "%s번 째 줄입니다. \n" %i
    
outFile.writelines(data)
outFile.close() """

#텍스트 파일 with문 사용 -> f.write("")
""" with open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/data.txt", "w") as f:
    f.write("처음에는 우리가 습관을 만들지만 \n")
    f.write("그 다음에는 습관이 우리를 만든다 \n")"""

#이진 파일 읽고 쓰기
""" data = [1, 2, 3, 4, 5]
with open ("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/bData.bn", "wb") as outFile:
    outFile.write(bytes(data)) """

#이진 파일 복사하기 - 하나의 이미지 파일을 다른 이미지 파일로 복사하기
""" filename1 = "한국산업기술대학교.png"
filename2 = "한국공학대학교.png"

infile = open("D:/coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/한국산업기술대학교.png", "rb")
outfile = open("D:/coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/한국공학대학교.png", "wb")

#입력 파일에서 1024 바이트씩 읽어서 출력 파일에 쓴다.
while True:
    copy_buffer = infile.read(1024)
    if not copy_buffer:
        break
    outfile.write(copy_buffer)
    
infile.close()
outfile.close()
print(filename1 + "를" + filename2 + "로 복사하였습니다.") """


#파이썬 GUI를 이용하여 PNG 이미지 파일 출력
""" import tkinter

window = tkinter.Tk()
window.title("한국공학대학교 보기")

img = tkinter.PhotoImage(file = "D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/한국공학대학교.png", master = window)

TU_Korea = tkinter.Label(window, image = img)
TU_Korea.pack()
window.mainloop() """

#파이썬 GUI를 이용하여 JPG 이미지 파일 출력
""" import tkinter
from PIL import Image, ImageTk

window = tkinter.Tk()
window.title("한국공학대학교 보기")

load = Image.open("D:/coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/한국공학대학교.jpg")
render = ImageTk.PhotoImage(load)

TU_Korea = tkinter.Label(window, image=render)
TU_Korea.pack()
window.mainloop() """

#Try, except 문 - 예외 발생
""" myStr = "파이썬은 재미 있어요!!"
strPoList = []
index = 0

while True:
    try :
        index = myStr.index("파이썬", index)
        strPoList.append(index)
        index = index + 1 #다음 위치부터 찾음
    except :
    break
    
print("파이썬 글자 위치 -->", strPoList) """

#Try, except 문 - 예외 처리
""" myStr = "재미 있어요 파이썬"
strPoList = []
index = 0

while True:
    try :
        index = myStr.index("파이썬", index)
        strPoList.append(index)
        index = index + 1 #다음 위치부터 찾음
    except:
        break
    
print("파이썬 글자 위치 -->", strPoList) """

#Try, except 문 - 숫자 입력
""" while True:
    try :
        n = input("숫자를 입력하세요 : ")
        n = int(n)
        break
    except ValueError:
        print("정수가 아닙니다. 다시 입력하세요.")
        
print("정수 입력이 성공 하였습니다.") """

#Try, except문 = 파일 이름 입력
""" try :
    fname = input("파일 이름을 입력 하세요 :")
    infile = open(fname, "r")

except IOError:
    print("파일" + fname + "을 발견할 수 없습니다.") """

#다중 예외 처리 - 여러개의 오류 처리
""" try :   # 먼저 발생한 에러를 표시 -> IndexError
    a = [1, 2]
    print(a[3])
    4/0
    
except ZeroDivisionError:
    print("0으로 나눌 수 없습니다.")
except IndexError:
    print("인덱싱 할 수 없습니다.") """
    
""" try :   # 먼저 발생한 에러를 표시 -> ZeroDivisionError
    a = [1, 2]
    4 / 0
    print(a[3])
    
except ZeroDivisionError:
    print("0으로 나눌 수 없습니다.")
except IndexError:
    print("인덱싱 할 수 없습니다.") """

#다중 예외 처리 - try문에 else절 사용
""" try :
    fh = open("D:/Spyder_PyThon/contents_of_class/ch9/testfile.txt", "w")
    fh.write("테스트 데이터를 파일에 씁니다!!")
    
except IOError:
    print("Error : 파일을 찾을 수 없거나 데이터를 쓸 수 없습니당.")

else:
    print("파일에 성공적으로 기록하였습니다.")
    fh.close() """

#오류와 예외처리 - try...finally
""" def division (a, b):
    x = a / b
    print(x)
    
try :
    division(4, 0)
except ZeroDivisionError as e:
    print("0으로 나누지 마세요. {0} 에러가 발생합니다.".format(e))
else:
    print("나눗셈이 정상적으로 실행 되었습니다.")
finally:
    print("프로그램을 종료 합니다.") """
    
#예외 발생하기
""" def three_multiple():
    x = int(input("3의 배수를 입력하세요 : "))
    #x가 3의 배수가 아니면
    if x % 3 != 0:
        #예외를 발생시킴
        raise Exception("3의 배수가 아닙니다.")
    print(x)
    
try :
    three_multiple()
except Exception as e:
    print("예외가 발생했습니다.", e) """

#CSV 파일    
""" import csv

f = open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/weather.csv")
data = csv.reader(f)
header = next(data)
print(header)
temp = 100.0

for row in data:
    if temp > float(row[3]):
        temp = float(row[3])
    
print("가장 추웠던 날은", temp, "입니다.")
f.close() """