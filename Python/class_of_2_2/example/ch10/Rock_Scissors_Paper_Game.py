import random
from tkinter import *
window = Tk()

window.title("가위, 바위, 보 게임")
Label(window, text = "선택하세요", font = ("Malgun Gothic", "16")).pack()
frame = Frame(window)

rock_image = PhotoImage(file = "C:/Coding/Python/class_of_2_2/image/rock.png")
paper_image = PhotoImage(file = "C:/Coding/Python/class_of_2_2/image/paper.png")
scissors_image = PhotoImage(file = "C:/Coding/Python/class_of_2_2/image/scissors.png")

def pass_s():
    decide("가위")
def pass_r():
    decide("바위")
def pass_p():
    decide("보")
    
rock = Button(frame, image_ = rock_image, command = pass_r)
rock.pack(side = "left")
paper = Button(frame, image =paper_image, command = pass_p)
paper.pack(side = "left")
scissors = Button(frame, image =scissors_image, command = pass_p)
scissors.pack(side = "left")

frame.pack()
Label(window, text = "컴퓨터는 다음을 선택하였습니다.", font = ("Malgun Gothic", "16")).pack()

computer_image = Label(window, image = rock_image)
computer_image.pack()

output = Label(window, text = "", font = ("Malgun Gothic", "16"))
output.pack()

def decide(human) :
    computer = random.choice(["가위", "바위", "보"])
    if computer == "바위":
        computer_image["image"] = rock_image
    elif computer == "보":
        computer_image["image"] = paper_image
    else:
        computer_image["image"] = scissors_image
        
    if ((computer == "바위" and human == "보")
        or (computer == "보" and human == "가위")
        or (computer == "가위" and human == "바위")):
        result = "인간 승리!"
        
    elif computer == human:
        result = "비겼습니다!"
    
    else :
        result = "컴퓨터 승리!"
    output.config(text = "인간 : " + human + "   컴퓨터 : " + computer + "    " + result)

window.mainloop()