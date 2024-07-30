import os
import sys

from konlpy.tag import Okt
from collections import Counter

import matplotlib
import matplotlib.pyplot as plt
from matplotlib import font_manager, rc

import re
import json

def showGraph(wordInfo, typeV) :

    font_location = "C:/Windows/Fonts/malgun.ttf"
    font_name = font_manager.FontProperties(fname=font_location).get_name()

    # 그래프에서 한글 폰트 적용
    matplotlib.rc('font', family=font_name)

    if (typeV == "api"):
        plt.xlabel('연도')
        plt.ylabel('출입국')

    sorted_dict_values = wordInfo.values()
    sorted_dict_keys = wordInfo.keys()
                       
    plt.bar(range(len(wordInfo)), sorted_dict_values, align='center')
    plt.xticks(range(len(wordInfo)), list(sorted_dict_keys), rotation=70)

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

def getNaverNouns(jsonData):

    wordInfo = dict()

    message = ""
    for i in jsonData :
        if ( "description" in i.keys() ) :
            message += re.sub(r'[^\w]', ' ', i["description"]) + " "
                    
    nlp = Okt()
    nouns = nlp.nouns(message)
    Counters = Counter(nouns)

    print("nouns : " + str(nouns) )
    print("Counters : " + str(Counters) )

    for tag, count in Counters.most_common(150) :
        if ( len(str(tag)) > 2 ) :
            wordInfo[tag] = count

    return wordInfo


def getOpenAPI(jsonData) :
    wordInfo = dict()

    for item in jsonData:
        if 'visitCnt' in item.keys():
            wordInfo[item['yymm']] = item['visitCnt']

    return wordInfo

def visualChoiceMenu():
    wordInfo = dict()
        
    print("그래프로 출력하고자 하는 메뉴를 선택")
    print("++++++++++++++++++++++++++++++++++")
    print("""
    1. 네이버 크롤링
    2. API 크롤링
    """)
    print("++++++++++++++++++++++++++++++++++")

    numV = int(input("메뉴 선택 : "))

    fileURL = input("파일의 경로 입력 : ")

    try :

        rFile = open(fileURL, "r", encoding="utf-8").read()
        jsonData = json.loads(rFile)

        if (numV == 1):
            typeV = "naver"
            wordInfo = getNaverNouns(jsonData)

        elif (numV == 2):
            typeV = "api"
            wordInfo = getOpenAPI(jsonData)

        showGraph(wordInfo, typeV)

    except Exception as e:
        print(e)

def visualCloud():
    fileURL = input("파일의 경로 입력 : ")

    try:
        rFile = open(fileURL, "r", encoding="utf-8").read()
        jsonData = json.loads(rFile)

        wordInfo = getNaverNouns(jsonData)

        showWordCloud("aaa", wordInfo)

    except Exception as e:
        print(e)
    
    


    

