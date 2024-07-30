import naverCrawler as nc
import apiCrawler as ac
import visualShow as vsh

num = 0

while (True):
    print("하고자하는 아래의 내용을 선택")
    print("==========================================")
    print("메뉴 목록")
    print("""
    1. 네이버 크롤링  (카페, 뉴스, 블로그)
    2. 공공 Data 크롤링 (출입국)
    3. 그래프 출력
    4. 워드클라우드
    5. 종료""")
    print("==========================================")

    num = int(input("번호 입력 : "))

    if (num == 1) :
        nc.naverCrawler()

    elif (num == 2) :
        ac.apiCrawler()

    elif (num == 3) :
        vsh.visualChoiceMenu()

    elif (num == 4):
        vsh.visualCloud()
        
    elif (num == 5):
        print("종료합니다.")
        break

    else :
        print("잘못입력 하였습니다.")
