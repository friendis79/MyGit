import os
import sys
import json
import pandas as pd

def jsonFileWrite(jsonResult, typeV):

    if(typeV == "naver"):
        fileN = "saveNaverCrawler"

    elif (typeV == "api"):
        fileN = "saveApiCrawler"

    with open("./"+ fileN + ".json", "w", encoding="utf-8") as outfile :

        jsonFile = json.dumps(jsonResult, indent=4, sort_keys=True, ensure_ascii=False)

        outfile.write(jsonFile)
    
    print("jsonFile이 생성되었습니다.")
    
# 공공데이터

"""
def jsonFileWrite(jsonResult):

    print(jsonResult)
    
    with open ("./saveDA.json", "w", encoding="utf-8") as outfile :

        jsonFile = json.dumps(jsonResult, indent=4, sort_keys=True, ensure_ascii=False)

        outfile.write(jsonFile)

    print("jsonFile이 생성되었습니다.")
"""

def csvFileWrite(csvResult):

    cols = ["출입국", "방문객수", "연월"]

    result_df = pd.DataFrame(csvResult, columns = cols)
    result_df.to_csv("./saveDA.csv", index=True, encoding="cp949")

    print("csvFile이 생성되었습니다.")
