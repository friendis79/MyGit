w = float(input("몸무게를 kg 단위로 입력하시오 : "))
h = float(input("키를 cm단위로 입력하시오 : "))

hm = h/100
bmi = w/(hm**2)

print("Ur BMI is %.2f" % bmi)