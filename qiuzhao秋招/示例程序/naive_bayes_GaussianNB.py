# -*- coding: utf-8 -*-
"""
Created on Mon Apr 17 15:57:42 2023

@author: Sora
"""

import pandas as pd
from io import StringIO

data = '编号,色泽,根蒂,敲声,纹理,脐部,触感,密度,含糖率,好瓜\n\
1,青绿,蜷缩,浊响,清晰,凹陷,硬滑,0.697,0.46,是\n\
2,乌黑,蜷缩,沉闷,清晰,凹陷,硬滑,0.774,0.376,是\n\
3,乌黑,蜷缩,浊响,清晰,凹陷,硬滑,0.634,0.264,是\n\
4,青绿,蜷缩,沉闷,清晰,凹陷,硬滑,0.608,0.318,是\n\
5,浅白,蜷缩,浊响,清晰,凹陷,硬滑,0.556,0.215,是\n\
6,青绿,稍蜷,浊响,清晰,稍凹,软粘,0.403,0.237,是\n\
7,乌黑,稍蜷,浊响,稍糊,稍凹,软粘,0.481,0.149,是\n\
8,乌黑,稍蜷,浊响,清晰,稍凹,硬滑,0.437,0.211,是\n\
9,乌黑,稍蜷,沉闷,稍糊,稍凹,硬滑,0.666,0.091,否\n\
10,青绿,硬挺,清脆,清晰,平坦,软粘,0.243,0.267,否\n\
11,浅白,硬挺,清脆,模糊,平坦,硬滑,0.245,0.057,否\n\
12,浅白,蜷缩,浊响,模糊,平坦,软粘,0.343,0.099,否\n\
13,青绿,稍蜷,浊响,稍糊,凹陷,硬滑,0.639,0.161,否\n\
14,浅白,稍蜷,沉闷,稍糊,凹陷,硬滑,0.657,0.198,否\n\
15,乌黑,稍蜷,浊响,清晰,稍凹,软粘,0.36,0.37,否\n\
16,浅白,蜷缩,浊响,模糊,平坦,硬滑,0.593,0.042,否\n\
17,青绿,蜷缩,沉闷,稍糊,稍凹,硬滑,0.719,0.103,否'

df = pd.read_csv(StringIO(data), index_col=0)

from sklearn import preprocessing

le = preprocessing.LabelEncoder()
df['色泽'] = le.fit_transform(df['色泽'].values)
df['根蒂'] = le.fit_transform(df['根蒂'].values)
df['敲声'] = le.fit_transform(df['敲声'].values)
df['纹理'] = le.fit_transform(df['纹理'].values)
df['脐部'] = le.fit_transform(df['脐部'].values)
df['触感'] = le.fit_transform(df['触感'].values)
df['好瓜'] = le.fit_transform(df['好瓜'].values)

# 划分训练集和测试集
train_x, train_y = df[['色泽', '根蒂', '敲声', '纹理', '脐部', '触感', '密度', '含糖率']], df[['好瓜']]
test_x, test_y = df[:1][['色泽', '根蒂', '敲声', '纹理', '脐部', '触感', '密度', '含糖率']], df[:1][['好瓜']]

from sklearn.naive_bayes import GaussianNB

gnb = GaussianNB()
# training
gnb.fit(train_x, train_y.values.ravel())
# predicting
pred_y = gnb.predict(test_x)
print(pred_y)