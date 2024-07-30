#10 -3
""" # Tkinter 라이브러리를 불러옵니다.
from tkinter import *

# Tkinter의 기본 창을 생성합니다.
window = Tk()

# 라디오 버튼이 변경될 때 호출되는 함수입니다.
def rd0_change():
    # var.get()을 사용하여 현재 선택된 라디오 버튼의 값을 확인합니다.
    if var.get() == 1:
        # 1일 경우 "Venz"로 레이블을 업데이트합니다.
        Label1.configure(text="Venz")
    else:
        # 1이 아닐 경우 "Porsche"로 레이블을 업데이트합니다.
        Label1.configure(text="Porsche")

# 정수형 변수 var를 생성합니다.
var = IntVar()

# "Venz"와 "Porsche" 레이블을 갖는 두 개의 라디오 버튼을 생성합니다.
# 라디오 버튼은 var 변수와 연결되어 있으며, 선택될 때 rd0_change 함수가 호출됩니다.
rdo1 = Radiobutton(window, text="Venz", variable=var, value=1, command=rd0_change)
rdo2 = Radiobutton(window, text="Porsche", variable=var, value=2, command=rd0_change)

# 초기에 "Selected Car"라고 표시되는 레이블을 생성합니다.
Label1 = Label(window, text="Selected Car", fg="red")

# 위젯들을 창에 배치합니다.
rdo1.pack()
rdo2.pack()
Label1.pack()

# GUI 이벤트 루프를 시작하여 창이 종료될 때까지 프로그램을 실행합니다.
window.mainloop() """

#10 - 4
""" from tkinter import *

window = Tk()

Button1 = Button(window, text = "버튼 1")
button2 = Button(window, text = "버튼 2")
button3 = Button(window, text = "버튼 3")

Button1.pack(side = BOTTOM)
button2.pack(side = BOTTOM)
button3.pack(side = BOTTOM)

window.mainloop() """

#10 - 7
""" from tkinter import *
window = Tk()

def clickMouse(event):
    txt = str(event.y) + str(event.x) + "에서 클릭됨"
    Label1.configure(text=txt)
    
window.geometry("400x400")
Label1 = Label(window, text = "this point cahnge")
window.bind("<Button>", clickMouse)
Label1.pack(expand =1, anchor = CENTER)
window.mainloop() """

#10 - 5
""" # Tkinter 및 Pillow 모듈 가져오기
from tkinter import *
from PIL import Image, ImageTk

# 이미지 슬라이더 클래스 정의
class ImageSlider:
    def __init__(self, master, image_folder, image_list):
        self.master = master
        self.image_folder = image_folder
        self.image_list = image_list
        self.current_index = 0

        # 이미지를 표시할 레이블 생성
        self.image_label = Label(master)
        self.image_label.pack()

        # 초기 이미지 업데이트
        self.update_image()

        # 이전 버튼
        self.prev_button = Button(master, text="이전", command=self.show_previous)
        self.prev_button.pack(side=LEFT)

        # 다음 버튼
        self.next_button = Button(master, text="다음", command=self.show_next)
        self.next_button.pack(side=RIGHT)

    # 이미지 업데이트 함수
    def update_image(self):
        # 현재 인덱스에 해당하는 이미지 경로 생성
        image_path = f"{self.image_folder}{self.image_list[self.current_index]}"
        # 이미지 열기
        image = Image.open(image_path)
        # 이미지를 Tkinter PhotoImage로 변환
        photo = ImageTk.PhotoImage(image)

        # 이미지 레이블 업데이트
        self.image_label.config(image=photo)
        # 이미지를 가비지 컬렉션에서 보호하기 위해 참조 유지
        self.image_label.image = photo

    # 이전 이미지 표시 함수
    def show_previous(self):
        # 이전 버튼 클릭 시 현재 인덱스 업데이트 및 이미지 업데이트
        self.current_index = (self.current_index - 1) % len(self.image_list)
        self.update_image()

    # 다음 이미지 표시 함수
    def show_next(self):
        # 다음 버튼 클릭 시 현재 인덱스 업데이트 및 이미지 업데이트
        self.current_index = (self.current_index + 1) % len(self.image_list)
        self.update_image()

# 메인 코드 시작
if __name__ == "__main__":
    # Tkinter 루트 창 생성
    root = Tk()
    root.title("이미지 슬라이더")

    # 이미지 폴더 경로 및 파일 리스트 지정
    image_folder = "D:/Coding/Python/class_of_2_2/image/"
    image_list = ["honeycomb.gif", "gingerbread.gif", "jellybean.gif",
                  "kitkat.gif", "lollipop.gif", "marshmallow.gif",
                  "nougat.gif", "oreo.gif", "pie.gif"]

    # ImageSlider 클래스를 사용하여 애플리케이션 생성
    app = ImageSlider(root, image_folder, image_list)

    # Tkinter 이벤트 루프 시작
    root.mainloop() """

""" from tkinter import *
from PIL import Image, ImageTk

# Function to update the displayed image
def update_image(index):
    image_path = f"D:/Coding/Python/class_of_2_2/image/{image_list[index]}"
    image = Image.open(image_path)

    photo = ImageTk.PhotoImage(image)

    image_label.config(image=photo)
    image_label.image = photo  # Keep a reference to the image to prevent it from being garbage collected
    
# Function to show the previous image
def show_previous():
    global current_index
    current_index = (current_index - 1) % len(image_list)
    update_image(current_index)

# Function to show the next image
def show_next():
    global current_index
    current_index = (current_index + 1) % len(image_list)
    update_image(current_index)

# Tkinter setup
root = Tk()
root.title("Image Slider")
root.geometry("400x400")

# List of image filenames
image_list = ["honeycomb.gif", "gingerbread.gif", "jellybean.gif",
              "kitkat.gif", "lollipop.gif", "marshmallow.gif",
              "nougat.gif", "oreo.gif", "pie.gif"]

# Initial index
current_index = 0

# Image label
image_label = Label(root)
image_label.pack()

# Previous button
prev_button = Button(root, text="Previous", command=show_previous)
prev_button.pack(side=LEFT)

# Next button
next_button = Button(root, text="Next", command=show_next)
next_button.pack(side=RIGHT)

# Initial image display
update_image(current_index)

# Run the Tkinter event loop
root.mainloop() """

#책 문제
from tkinter import *
from time import *

# 파일명 리스트
fnameList = ["jeju1", "jeju2", "jeju3", "jeju4", "jeju5", "jeju6", "jeju7", "jeju8", "jeju9"]

# 초기 인덱스
num = 0

# "다음" 버튼 클릭을 처리하는 함수
def clickNext():
    global num
    # 인덱스를 1 증가시키고, fnameList의 길이 내에서 래핑
    num = (num + 1) % len(fnameList)
    # 레이블을 업데이트하여 현재 파일명을 표시
    pLabel.config(text=fnameList[num])

# "이전" 버튼 클릭을 처리하는 함수
def clickPrev():
    global num
    # 인덱스를 1 감소시키고, fnameList의 길이 내에서 래핑
    num = (num - 1) % len(fnameList)
    # 레이블을 업데이트하여 현재 파일명을 표시
    pLabel.config(text=fnameList[num])

# 메인 윈도우 생성
window = Tk()
window.geometry("700x100")

# "이전" 버튼과 연결된 clickPrev 함수 생성
btnPrev = Button(window, text="<< 이전", command=clickPrev)
# "다음" 버튼과 연결된 clickNext 함수 생성
btnNext = Button(window, text=">> 다음", command=clickNext)
# 현재 파일명을 표시할 레이블 생성
pLabel = Label(window, text="파일명", font=("궁서체", 20), fg="blue")

# 버튼과 레이블을 윈도우에 배치
btnPrev.place(x=150, y=10)
btnNext.place(x=500, y=10)
pLabel.place(x=300, y=10)

# Tkinter 이벤트 루프 시작
window.mainloop()

# 10 - 9
""" from tkinter import *
window = Tk()

totalMenu = Menu(window)
window.config(menu = totalMenu)
upMenu = Menu(totalMenu)

# 상위 메뉴 추가
totalMenu.add_cascade(label="상위 메뉴", menu=upMenu)

# 하위 메뉴 1 추가
upMenu.add_command(label="하위 메뉴 1", command=lambda: print("하위 메뉴 1 선택"))

# 하위 메뉴 2 추가
upMenu.add_command(label="하위 메뉴 2", command=lambda: print("하위 메뉴 2 선택"))

window.mainloop() """

#11 -11
""" try :
    infile = open("D:/Coding/Python/class_of_2_2/contents_of_class/ch9/testfiles/data3.txt", "r")
    value = 100 /0
    
except IOError:
    print("파일 입출력 오류")

except ZeroDivisionError :
    print("0으로 나눔")

print("프로그램 종료") """

