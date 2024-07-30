def convert(num):
    tmp = ''
    while num :
        tmp = str(num % 2) + tmp
        num //= 2
    return tmp
    
a = int(input("Enter ant integar : "))

result = convert(a)

count = 0;

for i in range(len(result)):
    if result[i] != '0':
        count += 1
        
print("Binary --> %s의 1의 개수는 %d" %(result, count))