# 네이버 API 통
import os
import sys
import urllib.request
import json

from konlpy.tag import Okt
from collections import Counter
import re

import matplotlib
import matplotlib.pyplot as pltpip
from matplotlib import font_manager, rc

import pytagcloud
import webbrowser

# 사용자 관련 정보
client_id = "KmgehGFFgV0AMGo0JpuP"
client_secret = "wTlyhX01ls"

def getURL(url) :
    request = urllib.request.Request(url)
    
    request.add_header("X-Naver-Client-Id",client_id)
    request.add_header("X-Naver-Client-Secret",client_secret)
    response = urllib.request.urlopen(request)
    rescode = response.getcode()

    if(rescode==200):
        response_body = response.read()
        retData = response_body.decode('utf-8')

        resultT = json.loads(retData)
        
    else :
        resultT = None

    return resultT

def showGraph(sorted_dict) :

    font_location = "C:\\Windows\\Fonts\\malgun.ttf"
    font_location = "C:/Windows/Fonts/malgun.ttf"

    font_name = font_manager.FontProperties(fname=font_location).get_name()

    # 그래프에서 한글 폰트 적용
    matplotlib.rc('font', family=font_name)

    plt.xlabel('주요 단어')
    plt.ylabel('빈도수')

    """
    sorted_dict = dict(sorted(wordInfo.items(), reverse=True))
    sort_dict_val = sorted(wordInfo.values(), reverse=True)
    sort_dict_key = sorted(wordInfo.keys(), reverse=True)
    """
    plt.bar(range(len(sorted_dict)), sorted_dict.values(), align='center')
    plt.xticks(range(len(sorted_dict)), list(sorted_dict.keys()), rotation=70)

    plt.show()

def showWordCloud(strV, sorted_dict) :
    file_pos = "C:/Users/jmw31/Desktop" +strV + "_cloud_img.jpg"
    taglist = pytagcloud.make_tags( sorted_dict.items(),
                                                maxsize=90 )
    pytagcloud.create_tag_image( taglist,
                                                 file_pos,
                                                 size=(640, 480),
                                                 fontname="korean",
                                                 rectangular="False" )

    webbrowser.open(file_pos)
    


# 네이버에 요청하기

def getURLSetting(typeV, strV) :
    
    encText = urllib.parse.quote(strV)
    url = "https://openapi.naver.com/v1/search/" + typeV + "?query=" + encText + "&start=1&display=10"
    # url = "https://openapi.naver.com/v1/search/blog.xml?query=" + encText # XML 결과

    return url

def jsonFileWrite(jsonResult):

    with open("./saveNaverCraw.json", "w", encoding="utf-8") as outfile :

        jsonFile = json.dumps(jsonResult, indent=4, sort_keys=True, ensure_ascii=False)

        outfile.write(jsonFile)
    
    print("jsonFile이 생성되었습니다.")

def main() :

    print("네이버 API를 활용한 Crawler를 진행합니다.")
    print("Crawlering은 뉴스, 카페, 블로그의 데이터를 10건씩 수집합니다.")

    resultD = []
    message = ""
    searchT = [ "news", "blog", "cafearticle" ]
    strV = input("검색어 입력 : ")

    for i in searchT :
        urlV = getURLSetting(i, strV)     # URL Setting
        retData = getURL(urlV)      # URL 접속 후 Data 획득

        # Data 누적
        if ( retData is not None ) :
            print("검색된 개수 : " + str(retData["total"]))

            for i in retData["items"] :
                resultD.append( { "description" : i["description"] })

            message = ""
            for i in resultD :
                if ( "description" in i.keys() ) :
                    message += re.sub(r'[^\w]', ' ', i["description"]) + " "

        print("============================")
        print("resultD : " + str(resultD) )
        print("message : " + str(message))
        print("============================")
        
    nlp = Okt()
    nouns = nlp.nouns(message)
    Counters = Counter(nouns)

    print("nouns : " + str(nouns) )
    print("Counters : " + str(Counters) )

    wordInfo = dict()
    for tag, count in Counters.most_common(150) :
        if ( len(str(tag)) > 2 ) :
            wordInfo[tag] = count

    print(wordInfo)

    sorted_dict = dict()
    sorted_dict = dict(sorted(wordInfo.items(),
                                 key = lambda x: x[1],
                                 reverse = True ))


    print(sorted_dict)

    showGraph(sorted_dict)
    showWordCloud(strV, sorted_dict)

    jsonFileWrite(resultD)
    jsonFileWrite(sorted_dict)


if ( __name__ == "__main__") :
    main()