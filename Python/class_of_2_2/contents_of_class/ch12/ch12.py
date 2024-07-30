#타이타닉호 상관관계 분석하기 - 히트맵(Hearmap)
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

titanic = pd.read_csv("D:/Coding/Python/class_of_2_2/contents_of_class/ch12/titanic.csv")

numeric_columns = titanic.select_dtypes(include=['float64', 'int64'])
titanic_corr = numeric_columns.corr(method="pearson")
print(titanic_corr)

sns.heatmap(titanic_corr,
            annot=True,
            vmin=-1, vmax=1,
            cmap="RdBu")

plt.show()