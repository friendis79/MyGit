# 네이버 검색 API
import os   # 운영체제 관련 정보
import sys  # 시스템 관련 정보
import urllib.request   # 웹페이지에 요청하기 위한 라이브러리 파일
import json

from konlpy.tag import Okt
from collections import Counter
import re

import matplotlib
import matplotlib.pyplot as plt
from matplotlib import font_manager, rc

import pytagcloud
import webbrowser

stack_for_Naver = ''
searchT = ['blog', 'news', 'cafearticle']
urlT = []
resultN = dict()

# 사용자 관련 정보
client_id = "KmgehGFFgV0AMGo0JpuP"
client_secret = "wTlyhX01ls"


# Modules

# Get Naver URL
def getURL(strV, searchT) :
    encText = urllib.parse.quote(strV)
    url = "https://openapi.naver.com/v1/search/" + searchT + "?query=" + encText + "&start=1&display10"     # JSON 결과
    
    return url

# 네이버에 요청하기
def main(url) : 
    request = urllib.request.Request(url)
    request.add_header("X-Naver-Client-Id",client_id)
    request.add_header("X-Naver-Client-Secret",client_secret) 
    response = urllib.request.urlopen(request)
    rescode = response.getcode()

    if(rescode==200):
        response_body = response.read()
        retData = response_body.decode('utf-8') 
        # json file -> dictionary object
        resultT = json.loads(retData)
        print("검색된 개수 : " + str(resultT["total"])) # 검색된 총량을 제시 -> dict으로 변환에 문제 없음.
        
        resultD = [] # descri"description":i["description"]})
        print(resultD)

        global stack_for_Naver
        
        for i in resultD :
            if ("description" in i.keys()) :
                stack_for_Naver += re.sub(r'[^\w]', ' ', i["description"]) + " "

def countNouns(message) :
    nlp = Okt()
    nouns = nlp.nouns(message)
    Counters = Counter(nouns)    
    
    print("nouns : " + str(nouns))
    print("Counters : " + str(Counters)) 
    
    wordInfo = dict()
    for tag, count in Counters.most_common(150):
        if (len(str(tag)) >= 2 ) : 
            wordInfo[tag] = count
    sorted_dict = dict()
    sorted_dict = dict(sorted(wordInfo.items(),
                              key = lambda x: x[1],
                              reverse = True))
    
    return sorted_dict

def plotBar(sorted_dict) :
    font_location = "C:/Windows/Fonts/malgun.ttf"
    font_name = font_manager.FontProperties(fname=font_location).get_name()
    
    # 그래프에서 한글 폰트 적용하기 위함
    matplotlib.rc('font', family = font_name)
    
    plt.xlabel('주요 단어')
    plt.ylabel('빈도수')
    
    plt.bar(range(len(sorted_dict)), sorted_dict.values(), align = 'center')
    plt.xticks(range(len(sorted_dict)), list(sorted_dict.keys()), rotation=70)

    plt.show()

def savebyimg(sorted_dict) :
    file_pos = "C:/Users/jmw31/Desktop" +strV + "_cloud_img.jpg"
    taglist = pytagcloud.make_tags(sorted_dict.items(), maxsize = 90)
    pytagcloud.create_tag_image( taglist, file_pos, size=(640,480), fontname ="korean", rectangular = "False")

    webbrowser.open(file_pos)

# main
strV = input("검색할 단어 입력 : ")
for i in searchT :
    temp = getURL(strV, i)
    urlT.append(temp)
    print(urlT)
for i in urlT :
    main(i)
resultN = countNouns(stack_for_Naver)

plotBar(resultN)
savebyimg(resultN)
