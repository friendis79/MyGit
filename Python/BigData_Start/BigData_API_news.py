# 네이버 검색 API 예제 - 블로그 검색
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

# 사용자 관련 정보
client_id = "KmgehGFFgV0AMGo0JpuP"
client_secret = "wTlyhX01ls"

# 검색할 단어 입력
strV = input("검색할 단어 입력 : ")
encText = urllib.parse.quote(strV) # encText -> Encoding Text
url = "https://openapi.naver.com/v1/search/news?query=" + encText + "&start=1&display=10" # JSON 결과

print("url : " + str(url))

# url = "https://openapi.naver.com/v1/search/blog.xml?query=" + encText # XML 결과

# 네이버에 요청하기 위함
request = urllib.request.Request(url)
request.add_header("X-Naver-Client-Id",client_id)
request.add_header("X-Naver-Client-Secret",client_secret)
response = urllib.request.urlopen(request)
rescode = response.getcode()
if(rescode==200):
    response_body = response.read()
    retData = response_body.decode('utf-8')

    resultT = json.loads(retData)

    print("검색된 개수 : " + str(resultT["total"]))

    resultD = []
    for i in resultT["items"] :
        resultD.append( {"description" : i["description"]})
    

    message = ""
    for i in resultD :
        if ("description" in i.keys()) :
            message += re.sub(r'[^\w]', ' ', i["description"]) + " "

    nlp = Okt()
    nouns = nlp.nouns(message)
    Counters = Counter(nouns)

    print("nouns : " + str(nouns))
    print("Counters : " + str(Counters))

    wordinfo = dict(())
    for tag, count in Counters.most_common(150) :
        if (len(str(tag)) > 2):
            wordinfo[tag] = count

    print(wordinfo)

    font_location = "C:/Windows/Fonts/malgun.ttf"
    font_name = font_manager.FontProperties(fname=font_location).get_name()

    # 그래프에서 한글 폰트 적용
    matplotlib.rc('font', family=font_name)

    plt.xlabel('주요 단어')
    plt.ylabel('빈도 수')

    sorted_dict_value = sorted(wordinfo.values(), reverse=True)
    sorted_dict_key = sorted(wordinfo.keys(), reverse=True)

    sorted_dict = dict()
    sorted_dict = dict(sorted(wordinfo.items(), key=lambda x:x[1], reverse=True))

    plt.bar(range(len(sorted_dict)), sorted_dict_value, align='center')
    plt.xticks(range(len(sorted_dict)), list(sorted_dict_key), rotation=70)

    plt.show()

    file_pos = "C:/Users/jmw31/Desktop" +strV + "_cloud_img.jpg"

    taglist = pytagcloud.make_tags(sorted_dict.items(), maxsize=90)
    pytagcloud.create_tag_image(taglist, file_pos, size=(640, 480), fontname="korean", rectangular="False")

    webbrowser.open(file_pos)

else:
    print("Error Code:" + rescode)