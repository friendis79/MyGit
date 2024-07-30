mixlist = ['apple', 5, 'banana', 'grape', 3, 8, 6, 'melon']  #mixlist는 리스트에 요소를 대입

for x in mixlist:  #mixlist의 각 요소에 대해 반복
    if type(x) == str:  #만약 x의 타입이 문자열이면
        print("%s --> type is string" % x)  #해당 문자열과 타입 정보를 출력
    elif type(x) == int:  #만약 x의 타입이 정수이면
        print("%d --> type is integer" % x)  #해당 정수와 타입 정보를 출력