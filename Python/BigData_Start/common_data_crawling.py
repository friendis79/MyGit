import os
import sys
import urllib.request
import json

import matplotlib
import matplotlib.pyplot as plt
from matplotlib import font_manager, rc

import pandas as pd

# URL을 얻어옴

def getURLSetting(yymm, nat_cd, ed_cd) :

    serviceKey = "hziu8VQkdiZwXlj%2Bpa6MPaDPYBSg6yVy5pvpIlqlkekaG6EEurDJIvgA23WkRnq9jaLZVexrg9%2B%2B%2FynQLxRqNg%3D%3D"

    url = 'http://openapi.tour.go.kr/openapi/service/EdrcntTourismStatsService/getEdrcntTourismStatsList'

    param = "?_type=json"+"&serviceKey="+serviceKey+"&YM="+str(yymm)+"&NAT_CD="+str(nat_cd)+"&ED_CD="+str(ed_cd)

    print(url + param)
    
    return url + param

# 해당되는 URL에서 정보를 뽑아냄

def getURL(url) :
    request = urllib.request.Request(url)
    response = urllib.request.urlopen(request)

    if(response.getcode()==200):
        return response.read().decode('utf-8')
        
    else :
        return None

#해당되는 정보로 그래프를 나타냄

def showGraph(wordInfo) :

    font_location = "C:/Windows/Fonts/malgun.ttf"
    font_name = font_manager.FontProperties(fname=font_location).get_name()

    # 그래프에서 한글 폰트 적용
    matplotlib.rc('font', family=font_name)

    plt.xlabel('연도')
    plt.ylabel('출입국')

    sorted_dict_values = wordInfo.values()
    sorted_dict_keys = wordInfo.keys()
                       
    plt.bar(range(len(wordInfo)), sorted_dict_values, align='center')
    plt.xticks(range(len(wordInfo)), list(sorted_dict_keys), rotation=70)

    plt.show()

def jsonFileWrite(jsonResult):

    print(jsonResult)
    
    with open ("./saveDA.json", "w", encoding="utf-8") as outfile :

        jsonFile = json.dumps(jsonResult, indent=4, sort_keys=True, ensure_ascii=False)

        outfile.write(jsonFile)

    print("jsonFile이 생성되었습니다.")

def csvFileWrite(csvResult):

    cols = ["출입국", "방문객수", "연월"]

    result_df = pd.DataFrame(csvResult, columns = cols)
    # result_df.to_csv("./saveDA.csv", index=True, encoding="utf-8") 
    result_df.to_csv("./saveDA.csv", index=True, encoding="cp949")

    print("csvFile이 생성되었습니다.")


def main():

    yymm_s= input("시작할 년도를 입력(yyyy) : ")
    yymm_e= input("종료할 년도를 입력(yyyy) : ")
    
    print("출/입국 구분 코드 ===================================================================")
    print("321 : 프랑스 \t 170 : 태국 \t 113 : 대만 \t 374 : 스위스")
    print("출/입국 구분 코드 ===================================================================")
    nat_cd = input("검색하고자 하는 나라의 코드 입력 : ")

    print("출/입국 구분 코드 ===================================================================")
    print("D = 국민 해외 관광객 \t E = 방한 해외 관광객")
    print("출/입국 구분 코드 ===================================================================")
    ed_cd = input("출/입국 코드 입력 : ")

    ed_cd = ed_cd.upper()

    if (ed_cd != "E" or ed_cd != "D"):
        print("잘못 입력")

    jsonResult = []
    csvResult = []

    for year in range(int(yymm_s), int(yymm_e) + 1):
    
        for month in range(1, 13):
            yyyymm= "{0}{1:0>2}".format(str(year), str(month))  # 0-> 뒤에 있는 format에 넣겠다 {1:0>2} 1자리 숫자를 두 자리 숫자로 바꾸는데 앞 자리에는 0을 추가


            urlV = getURLSetting(yyyymm, nat_cd, ed_cd)
            rtnV = getURL(urlV)

            if (rtnV != None):
                reData = json.loads(rtnV)

            print("===================================================================")
            print("reData : "+ str(reData) )
            print("===================================================================")
            if(reData['response']['header']['resultMsg'] == "OK"):
                print("a" + str(reData['response']['body']['items']) + "b" )
                
                if(reData['response']['body']['items'] == ""):

                    print(str(yyyymm) + "월의 값이 없어 종료합니다.")
                    break
            # 국가 코드
            natKorNm = reData['response']['body']['items']['item']['natKorNm']
            natKorNm = natKorNm.replace(' ','')     # 공백을 붙임

            # 방문자 수
            visitCnt = natKorNm = reData['response']['body']['items']['item']['num']

            # 해당 월
            visitMonth = natKorNm = reData['response']['body']['items']['item']['ym']

            jsonResult.append({"natKorNm" : natKorNm, "visitCnt" : visitCnt, "yymm" : yyyymm})

            csvResult.append([natKorNm, visitCnt, yyyymm])
        

        # resultCode = reData['response']['header']['resultCode']

        # print("reData : ", reData)
        
    print("결과 출력 ===================================================================")
    print("jsonResult : " + str(jsonResult))
    print("csvnResult : " + str(csvResult))
    print("결과 출력 ===================================================================")

    wordInfo = dict()

    for item in jsonResult:
        if 'visitCnt' in item.keys():
            wordInfo[item['yymm']] = item['visitCnt']

    showGraph(wordInfo)

    jsonFileWrite(jsonResult)     # json 파일로 저장
                                  # dict 형태로 저장되어진 내용 (데이터 타입)을 통해서 파일을 저장하는 것이 편함
                        
    csvFileWrite(csvResult)       # csv 파일로 저장
                                  # list 형태로 저장되어진 내용 (데이터 타입)을 기반으로 csv 파일 생성
    


if (__name__ == "__main__"):
    main()
