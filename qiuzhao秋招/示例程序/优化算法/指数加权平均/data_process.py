# -*- coding: utf-8 -*-
"""
Created on Wed Apr 19 17:25:08 2023

@author: Sora
"""


import re

reader = open(file = r".\data\每日天气.csv", mode = 'r', encoding='utf8')
li = []
regex = re.compile(pattern= r'\d{1,2}-\d{1,2}℃', flags=0)
for index,line in enumerate(reader):
    try:
        result = regex.search(line)
        if result:
            num1,num2 = list(map(int,result.group().strip("℃").split("-")))
        else:
            continue
        num = num1 + num2
        num //= 2
        li.append(num)
    except:
        print(line)
reader.close()
li.remove(min(li))