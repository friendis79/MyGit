infilename = input("입력 파일 이름: ") # D:/Coding/Python/class_of_2_2/example/ch9/sales.txt
outfilename = input("출력 파일 이름: ") # D:/Coding/Python/class_of_2_2/example/ch9/summary.txt

infile = open(infilename, "r")
outfile = open(outfilename, "w")

summ = 0
count = 0

line = infile.readline()
while line != "":
    s = int(line)
    summ += s
    count += 1
    line = infile.readline()

outfile.write("총매출 =" + str(summ) + "\n")
outfile.write("평균 일매출 =" + str(summ / count) + "\n")

print("총매출 = " + str(summ))
print("평균 일매출 = " + str(summ / count))

infile.close()
outfile.close()