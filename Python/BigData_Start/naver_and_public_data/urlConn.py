import os
import sys
import urllib.request

# 사용자 관련 정보
client_id = "KmgehGFFgV0AMGo0JpuP"
client_secret = "wTlyhX01ls"

serviceKey = "hziu8VQkdiZwXlj%2Bpa6MPaDPYBSg6yVy5pvpIlqlkekaG6EEurDJIvgA23WkRnq9jaLZVexrg9%2B%2B%2FynQLxRqNg%3D%3D"

def getURL(url, typeV) :
    request = urllib.request.Request(url)

    if (typeV == "naver"):
        request.add_header("X-Naver-Client-Id",client_id)
        request.add_header("X-Naver-Client-Secret",client_secret)
        
    response = urllib.request.urlopen(request)

    if(response.getcode() == 200):
        
        return response.read().decode('utf-8')
        
    else :
        return None

def getNaverURLSetting(typeV, strV) :
    
    encText = urllib.parse.quote(strV)
    url = "https://openapi.naver.com/v1/search/" + typeV + "?query=" + encText + "&start=1&display=10"
    # url = "https://openapi.naver.com/v1/search/blog.xml?query=" + encText # XML 결과

    return url

def getAPIURLSetting(yymm, nat_cd, ed_cd) :

    url = 'http://openapi.tour.go.kr/openapi/service/EdrcntTourismStatsService/getEdrcntTourismStatsList'
    param = "?_type=json"+"&serviceKey="+serviceKey+"&YM="+str(yymm)+"&NAT_CD="+str(nat_cd)+"&ED_CD="+str(ed_cd)

    print("getURLSetting Method ==========================================")
    print(url + param)
    print("getURLSetting Method ==========================================")
    
    return url + param
