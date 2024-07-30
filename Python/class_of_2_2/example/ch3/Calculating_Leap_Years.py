year = int(input("년도를 입력하시오 : "))

isLeafYear = (year % 4 ==0 and year % 100 != 0) or (year % 400 == 0)

if isLeafYear :
    print("%d년은 윤년입니다." % year)

else:
    print("%d년은 평년입니다." % year)