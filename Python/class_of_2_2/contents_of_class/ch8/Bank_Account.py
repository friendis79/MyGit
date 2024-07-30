#통장 만들기
class BankAccount:
    def __init__(self, balance, number) :
        self.__balance = balance
        self.__acctNum = number

    def withdraw (self, amount):
        if self.__balance < amount :
            print("잔액이 부족하여 출금이 취소 되었습니다.")
            return self.__balance
        self.__balance -= amount
        print("통장에", amount, "원이 출금 되었음.")
        BankAccount.ViewAccount(self)
        return self.__balance
    
    def deposit(self, amount):
        self.__balance += amount
        print("통장에", amount, "원이 입금 되었음.")
        BankAccount.ViewAccount(self)
        return self.__balance
    
    def ViewAccount(self):
        balance = self.__balance
        acctNum =  self.__acctNum
        print(acctNum, "통장 잔액은", balance, "원 입니다.")
        
""" Kim = BankAccount(4000, 123456)
Kim.ViewAccount()
Kim.deposit(2000)
Kim.withdraw(3000)
Kim.withdraw(5000) """