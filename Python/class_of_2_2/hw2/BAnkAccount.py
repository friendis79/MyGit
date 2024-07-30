#기반 클래스
class BankAccount:
    def __init__(self, name, number, balance, secNum):
        self.balance = balance
        self.__acctNum = number
        self.__name = name
        self.__secNum = secNum
        
    def withdraw(self, amount):
        if self.balance < amount:
            print("잔액이 부족합니다.")
            print("%d원 출금이 취소되었습니다." %amount)
            
        else :
            self.balance -=amount
            print("통장에서 %d원이 출금 되었습니다." %amount)
            print("%d원 출금이 취소 됐습니다." %amount)            
        return self.balance
        
    def deposit(self, amount):
        self.balance += amount
        print("통장에 %d원이 입금 되었습니다." %amount)
        BankAccount.checkBalance(self)
        return self.balance
        
    def checkBalance(self):
        balance = self.balance
        name = self.__name
        print("%s님의 통장 잔액은 %d원 입니다." %(name, balance))
        
    def getPassword(self):
        return self.__secNum