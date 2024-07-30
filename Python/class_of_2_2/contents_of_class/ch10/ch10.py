#tkinter 모듈 사용법
""" import tkinter
window = tkinter.Tk()
window.mainloop() """

#윈도우 창 크기 조절하기
""" from tkinter import *

window = Tk()
window.title("윈도우창 연습")
window.geometry("400x100")
window.resizable(width = FALSE, height = FALSE)

window.mainloop() """

#기본 위젯
""" from tkinter import *
window = Tk()

label1 = Label(window, text = "Python을")
label2 = Label(window, text = "열심히", font =  ("궁서체", 30), fg = "blue", anchor = SE)
textBox = Entry(window)
btn = Button(window, text = "ok")

label1.pack();
label2.pack();
textBox.pack();
btn.pack()

window.mainloop() """

#레이블에 이미지 넣기 (고양이)
""" from tkinter import *
window = Tk()

photo = PhotoImage(file = "D:/Coding/Python/class_of_2_2/image/cat.gif",
                   master = window)
label1 = Label(window, image = photo)

label1.pack()

window.mainloop() """

#버튼
""" from tkinter import *
window = Tk()

def exit_window() :
    print("프로그램이 종료 됩니다.")
    window.destroy()
    window.quit()
    
button = Button(window, text = "프로그램 종료", fg = "red", command = exit_window)

button.pack()

window.mainloop() """

#체크 버튼
""" from tkinter import *
from tkinter import messagebox

window = Tk()

def myFunc():
    if chk.get() == 0:
        messagebox.showinfo("", "체크 버튼이 선택되지 않았어요.")
    else :
        messagebox.showinfo("", "체크 버튼이 선택되었어요")
        
chk = IntVar()
cb1 = Checkbutton(window, text = "선택하세요", variable = chk, command = myFunc)

cb1.pack()

window.mainloop() """

#라디오 버튼
""" from tkinter import *
window = Tk()

##함수 선언 부분##
def myFunc() :
    if var.get() == 1:
        label1.configure(text = "파이썬")
    elif var.get() == 2:
        label1.configure(text = "C++")
    else :
        label1.configure(text = "Java")
        
##메인 코드 부분##
var = IntVar()
rb1 = Radiobutton(window, text = "파이썬", variable = var, value = 1, command = myFunc)
rb2 = Radiobutton(window, text = "C++", variable = var, value = 2, command = myFunc)
rb3 = Radiobutton(window, text = "java", variable = var, value = 3, command = myFunc)

label1 = Label(window, text = "선택한 언어 : ",font = ("맑은 고딕", 10), fg = "red")

rb1.pack()
rb2.pack()
rb3.pack()
label1.pack()
window.mainloop() """

#세로 배치
""" from tkinter import *

window = Tk()

Button1 = Button(window, text = "버튼 1")
button2 = Button(window, bg = "yellow", text = "버튼 2")
button3 = Button(window, bg = "red", text = "버튼 3")

Button1.pack()
button2.pack()
button3.pack()

window.mainloop() """

#가로배치
""" from tkinter import *

window = Tk()

Button1 = Button(window, text = "버튼 1")
button2 = Button(window, bg = "yellow", text = "버튼 2")
button3 = Button(window, bg = "red", text = "버튼 3")

Button1.pack(side = LEFT)
button2.pack(side = LEFT)
button3.pack(side = LEFT)

window.mainloop() """

#for문을 이용한 배치
""" from tkinter import *
window = Tk()

btnList = [None] * 3

for i in range(0, 3):
    btnList[i] = Button(window, text = "버튼" + str(i+1))

for btn in btnList :
    btn.pack(side = RIGHT)
    
window,mainloop() """

#수직 정렬
""" from tkinter import *
window = Tk()

btnList = [None] * 3

for i in range(0, 3):
    btnList[i] = Button(window, text = "버튼" + str(i+1))

for btn in btnList :
    btn.pack(side = TOP)
    
window,mainloop() """

#폭 조정
""" from tkinter import *
window = Tk()

btnList = [None] * 3

for i in range(0, 3):
    btnList[i] = Button(window, text = "버튼" + str(i+1))

for btn in btnList :
    btn.pack(side = TOP, fill = X)
    
window,mainloop() """

#위젯 사이의 여백 조절
""" from tkinter import *
window = Tk()

btnList = [None] * 3

for i in range(0, 3):
    btnList[i] = Button(window, text = "버튼" + str(i+1))

for btn in btnList :
    btn.pack(side = TOP, fill = X, padx = 10, pady = 10)
                                  #-> 픽셀값  -> 픽셀값
window,mainloop()
 """

#위젯 내부의 여백 조절
""" from tkinter import *
window = Tk()

btnList = [None] * 3

for i in range(0, 3):
    btnList[i] = Button(window, text = "버튼" + str(i+1))

for btn in btnList :
    btn.pack(side = TOP, fill = X, ipadx = 10, ipady = 10)
                                 #-> 픽셀값  -> 픽셀값  
window,mainloop() """

#위젯을 테이블 형태로 배치
""" from tkinter import *

##변수 선언 부분##
btnList = [""] * 9
fnameList = ["honeycomb.gif","gingerbread.gif","jellybean.gif",
             "kitkat.gif", "lollipop.gif","marshmallow.gif",
             "nougat.gif", "oreo.gif", "pie.gif"]
photoList=[None] * 9
num = 0

##메인 코드 부분##
window= Tk()
window.geometry("210x210")

for i in range(0,9):
    photoList[i] = PhotoImage(file="D:/Coding/Python/class_of_2_2/image/"+fnameList[i], master = window)
    btnList[i] = Button(window, image = photoList[i])

for i in range(0,3):
    for k in range(0,3):
        btnList[num].grid(row = i, column = k)
        num += 1

window.mainloop() """

#위젯을 고정 위치에 배치
""" from tkinter import *
from time import *
##변수 선언 부분##
btnList = [""] * 9
fnameList = ["honeycomb.gif","gingerbread.gif","jellybean.gif",
             "kitkat.gif", "lollipop.gif","marshmallow.gif",
             "nougat.gif", "oreo.gif", "pie.gif"]
photoList = [None] * 9
i, k = 0, 0
xPos, yPos = 0, 0
num = 0

##메인 코드 부분##
window = Tk()
window.geometry("210x210")

for i in range(0,9):
    photoList[i] = PhotoImage(file= fnameList[i], master = window)
    btnList[i] = Button(window, image = photoList[i])
    
for i in range(0, 3):
    for k in range(0, 3):
        btnList[num].place (x = xPos, y = yPos)
        num += 1
        xPos += 70
    xPos = 0
    yPos += 70
    
window.mainloop() """
    
#버튼 이벤트 처리
""" from tkinter import *
from tkinter import messagebox

def process() :
    messagebox.showinfo("버튼", "버튼이 클릭됨")
    
window = Tk()

button = Button(window, text = "클릭하세여", command = process)
button.pack()
window.mainloop() """

#버튼 이벤트 처리 - 레이블과 버튼을 사용하여 간단한 카운터 코드 작성
""" from tkinter import *
window = Tk()

counter = 0
def clicked() :
    global counter
    counter += 1
    label['text'] = "버튼 클릭 횟수 : " + str(counter)
    
label = Label(window, text = "아직 눌려지지 않음")
label.pack()
button = Button(window, text = "증가", command = clicked).pack()
window.mainloop() """

#마우스 이벤트 처리
""" from tkinter import *
window = Tk()

def callback(event) :
    print(event.x, event.y, "에서 마우스 이벤트 발생")

frame = Frame(window, width = 600, height = 200)
frame.bind("<Button - 1>", callback)
frame.pack()
window.mainloop() """

#event 매개변수를 활용한 마우스 이벤트 처리 - 마우스를 클릭할 때마다 어떤 마우스가 클릭되었는지 보여주고 클릭한 좌표를 출력
""" from tkinter import *

##함수 선언 부분##
def clikMouse(event):
    txt = ""
    if event.num == 1:
        txt += "마우스 왼쪽 버튼이 ("
        
    elif event.num == 3:
        txt += "마우스 오른쪽 버튼이 ("
        
    txt += str(event.y) + "," + str(event.x) + ")에서 클릭됨"
    label1.configure(text = txt)
    
##메인 코드 부분##
window = Tk()
window.geometry("400x400")
    
label1 = Label(window, text = "이곳이 바뀜")
window.bind("<Button>", clikMouse)
label1.pack(expand =1, anchor = CENTER)
window.mainloop() """

#키보드 이벤트 처리
""" from tkinter import *

##함수 선언 부분##
def keyEvent(event) :
    txt = "키보드 이벤트 눌린 키 : " + chr(event.keycode)
    label1.configure(text = txt)
    print("키보드 이벤트 눌린 키 : " + chr(event.keycode))
    
##메인 코드 부분##
window = Tk()
window.geometry("200x200")

label1 = Label(window, text = "키보드 이벤트")
window.bind("<Key>", keyEvent)
label1.pack(expand = 1, anchor = CENTER)
window.mainloop() """

#메뉴 만들기
""" from tkinter import *

window = Tk()

mainMenu = Menu(window)
window.config(menu = mainMenu)

fileMenu = Menu(mainMenu)
mainMenu.add_cascade(label = "파일", menu = fileMenu)
fileMenu.add_command(label = "열기")
fileMenu.add_separator()
fileMenu.add_command(label = "종료")

window.mainloop() """

#메뉴 만들기 - 메뉴를 선택하면 동작하게 만들기
""" from tkinter import *
from tkinter import messagebox

##함수 선언 부분##
def func_open() :
    messagebox.showinfo("메뉴 선택", "열기 메뉴를 선택함")
    
def func_exit():
    window.quit()
    window.destory()
    
##메인 코드 부분##
window = Tk()
mainMenu = Menu(window)
window.config(menu = mainMenu)

fileMenu = Menu(mainMenu)
mainMenu.add_cascade(label = "파일", menu = fileMenu)
fileMenu.add_command(label = "열기", command = func_open)

fileMenu.add_separator()
fileMenu.add_command(label = "종료", command = func_exit)

window.mainloop() """

#대화 상자의 생성과 사용
""" from tkinter import *
from tkinter.simpledialog import *

## 함수 선언 부분##
window =Tk()
window.geometry("200x200")

label1 = Label(window, text= "입력된 값 : ")
label1.pack()

value = askinteger("확대 배수", "주사위 숫지 (1~6)을 입력하세요", minvalue=1, maxvalue=6)

label1.config(text = "입력된 값 : " + str(value))
window.mainloop() """

#캔버스 생성
""" from tkinter import *
window = Tk()                                  #화면 출력
w = Canvas(window, width = 300, height = 200)  #캔버스 생성
w.pack()                                       #그래픽 출력 준비

window.mainloop() """

#직선과 사각형 그리기
""" from tkinter import *

window = Tk()
w = Canvas(window, width = 300, height = 200)
w.pack()
w.create_rectangle(50, 25, 200, 100, fill = "blue")
w.create_line(0, 0, 300, 200)
w.create_line(0, 0, 300, 100, fill = "red")

window.mainloop() """

#도형 관리
""" from tkinter import *

window = Tk()
w = Canvas(window, width = 300, height = 200)
w.pack()
w.create_rectangle(50, 25, 200, 100, fill = "blue")

i = w.create_line(0, 0, 300, 100, fill = "red")
w.coords(i, 0, 0, 300, 100)        #좌표 변경
w.itemconfig(i, fill = "blue")     #색상 변경
w.delete(i)                        #객체 i 삭제(전체 삭제는 w.delete(ALL))
window.mainloop() """

#색상 설정
""" from tkinter import *
window = Tk()

w = Canvas(window, width = 300, height = 200)
w.pack()
w.create_rectangle(50, 25, 200, 100, fill = "#FF24B5")
w.create_rectangle(5, 5, 25, 25, outline = "red")   

window.mainloop() """

#대화 상자를 이용한 색상 지정
""" from tkinter import *
from tkinter.colorchooser import *
window = Tk()

w = Canvas(window, width = 300, height = 200)
w.pack()
color = askcolor()
w.create_rectangle(50, 25, 200, 100, fill = color[1])

window.mainloop() """

#폰트 지정
""" from tkinter import *
window = Tk()

canvas = Canvas(window, width = 400, height = 200, bg = "#afeeee")
canvas.create_text(200, 100, fill = "darkblue", font = "Times 30 italic bold", text = "This is a text example.")
canvas.pack()
window.mainloop() """

#도형 그리기
""" from tkinter import *
window = Tk()

w = Canvas(window, width = 300, height = 200)
w.pack()

w.create_line(50, 15, 250, 15)
w.create_rectangle(50, 35, 250, 85, fill = "blue")
w.create_arc(50, 100, 250, 250, extent = 90)

window.mainloop() """


