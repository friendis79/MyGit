itemPrice = int(input("물건값을 입력하세요 : "))
note = int(input("1,000원 지폐 개수 : "))
coin500 = int(input("500원 동전 개수 : "))
coin100 = int(input("100원 동전 개수 : "))

change = note*1000 + coin500*500 + coin100*100 - itemPrice

nCoin500 = change // coin500
change %= 500

nCoin100 = change // coin100
change %= 100

nCoin10 = change // 10
change %= 10

print("===거스름돈===")

print("500won = ", nCoin500)
print("100won = ", nCoin100)
print("10won = ", nCoin10)