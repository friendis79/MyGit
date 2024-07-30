# 리스트 생성하기
""" s1 = {1, 2, 3, 3, 3, 4}

print(s1)

print(type(s1))

s2 = set([1, 2, 3, 3, 3, 4])

print(s2)

s3 = set('Python')

print(s3)
 """
 
# 튜플의 인덱싱 및 슬라이싱
""" tuple = (1, 2, 3, 'a', 'b', 'c')

tuple[0]

tuple[4]

tuple[2:5]

tuple[2:]

print(tuple) """

#  튜플의 연산
""" tuple1 = (10, 20, 30)

tuple2 = tuple1 + tuple1
print(tuple2)

tuple3 = tuple1*2
print(tuple3)

#tuple4 = tuple1 + 40

tuple4 = tuple1 + (40,)
print(tuple4)

fruits = ("apple", "banana", "grape")
fruits = ("pear", "kiwi")
print(fruits)

numbers = [10, 20, 30]
numbers += (40, 50)
print(numbers)

numbers = (10, 20, 30, 40, 50)
sum = numbers[0] + numbers[2] + numbers[3]
print(sum) """

# 튜플의 삭제
""" fruits = ("apple", "banana", "grape")
print(fruits)

del(fruits[0])

del(fruits)
#print(fruits) """

# 튜플과 리스트의 상호 변경
""" myList = [10, 20, 30, 40]

myTuple = type(myList)

print(myTuple)

myTule = ['a', 'b', 'c', 'd']

myList = list(myTule)

print(myList) """

# 딕셔너리 생성
""" dict1 = {1:'a', 2:'b', 3:'c'}

print(dict1)

dict2 = {'a':1, 'b':2, 'c':3}
print(dict2)

dic = {'e':1, 'a':3, 'b':5, 'c':1, 'd':2} """

# 딕셔너리 사용
""" student = {'학번':2020144030, '이름':'정민욱', '학과':'전자공학과'}

print(list(student.keys()))

print(student.values())

print(student.items())

print('이름' in student)

singer = {}

singer['이름'] = "트와이스"
singer['구성원 수'] = 9
singer['데뷔'] = "서바이벌 식스틴"
singer['대표곡'] = "Signal"

for k in singer.keys():
    print("%s --> %s" %(k, singer[k])) """


# key를 오름차순하여 리스트로 변환
""" dic_a = sorted(dic)
print(dic_a)
 """
#key를 오름차순 정렬
""" dic_b = sorted(dic.items())
print(dic_b)
print(dict(dic_b)) """

# key를 내림차순 정렬
""" dic_c = sorted(dic.items(), reverse = True)
print(dic_c)
print(dict(dic_c)) """

# value를 오름차순 정렬
""" dic_d = sorted(dic.items(), key = lambda x : x[1])
print(dic_d)
print(dict(dic_d)) """

# value를 내림차순 정렬
""" dic_e = sorted(dic.items(), key = lambda x : x[1], reverse = True)
print(dic_e)
print(dict(dic_e)) """

# 딕셔너리 항목 추가하고 삭제하기
""" student1 = {'학번':2020144030, '이름':'정민욱', '학과':'전자공학과'}

print(student1.get('이름'))
print(student1.keys())

'''print(student1)

student1['연락처'] = '010-7176-5119'

print(student1)

del(student1['학과'])

print(student1)'''

student1["연락처"] = "010-7176-5119"

print(student1)
#print(student1.pop("연락처"))
if "연락처" in student1:
    print(student1.pop("연락처"))
print(student1) """

# 리스트와 세트
""" List1 = [1, 2, 3, 4, 5, 1, 2]

print(len(set(List1)))

List1 = [1, 2, 3, 4, 5]
List2 = [3, 4, 5, 6, 7]

print(set(List1) & set(List2)) """


# 세트 연산 및 요소 추가 및 삭제하기
""" fruits = {"apple", "banana", "grape", "peach"}
size = len(fruits)
print(size)

if "apple" in fruits :
    print("집합안에 apple이 있습니다.")
    
for x in fruits :
    print(x, end = ",")
    
print()
for x in sorted(fruits) :
    print(x, end = ",")
    
fruits.add("kiwi")
fruits.remove("grape")
print(fruits) """

# 세트 함축 연산
""" aList = [1, 2, 3, 4, 5, 1, 2]

result = {x for x in aList if x %2 == 0}

print(result) """

# 집합 연산
""" A = {1, 2, 3}
B = {3, 4, 5}

print(A | B)

print(A & B)

print(A.intersection(B))

print(A - B)

print(A.difference(B)) """

# 튜플의 수정
""" fruits = ("apple", "banana", "grape") #[] => List, () => Tuple
fruits[1] = "pear"

print(fruits)
['apple', 'pear', 'grape']

fruits = ("apple", "banana", "grape")

fruits[1] = "pear" """

# 튜플 패킹과 언패킹
""" t = ('apple', 'banana', 'grape')

print(t[0], t[1])

(s1, s2, s3) = t
print(s2, s3)

print(type(s1)) """

