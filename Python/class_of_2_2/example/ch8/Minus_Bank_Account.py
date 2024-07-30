import BankAccount as ba

#클래스 상속
class OverDraftAccount (ba.BankAccount):
    def __init__(self, name, number, balance, secNum, overdraft_limit = 0):
        super().__init__(name, number, balance, secNum)
        self.overdraft_limit = overdraft_limit #대월한도
    
    def withdraw(self, amount):
        if (self.balance - amount) < -(self.overdraft_limit) :
            print("대월 한도를 초과 했습니다.")
            print("%d원 출금이 취소되었습니다." %amount)
        else :
            self.balance -= amount
            print("통장에서 %d원이 출금 되었습니다." %amount)
        return self.balance
        

    
#통장 발행 예
Kim = OverDraftAccount("정만욱", 123456, 5000, 1238, overdraft_limit = 10000)



while True :
    print("입출금 서비스")
    print("1. 입금, 2. 출금, 3. 잔액조회, 4. 종료")
    service = int(input("원하는 서비스를 선택하세요 : "))
    if service == 4:
        break
    
    password = int(input("비밀번호를 입력하세요 : "))
    
    while password != Kim.getPassword():
        password = int(input("비밀번호를 다시 입력 하세요 : "))
            
    if service == 1:
        amount = int(input("금액을 입력하세요 : "))
        Kim.deposit(amount)
        
    if service == 2:
        amount = int(input("금액을 입력하세요 : "))
        Kim.withdraw(amount)
        Kim.checkBalance()
        
    if service == 3:
        Kim.checkBalance()
        
    print("==================================================================")