# 공공데이터 API
import requests

serviceKey = "hziu8VQkdiZwXlj+pa6MPaDPYBSg6yVy5pvpIlqlkekaG6EEurDJIvgA23WkRnq9jaLZVexrg9++/ynQLxRqNg=="

url = 'http://openapi.tour.go.kr/openapi/service/EdrcntTourismStatsService/getEdrcntTourismStatsList'
params ={'serviceKey' : serviceKey, 'YM' : '201201', 'NAT_CD' : '112', 'ED_CD' : 'E' }

response = requests.get(url, params=params)
print(response.content)


