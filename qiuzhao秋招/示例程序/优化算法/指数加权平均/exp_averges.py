# -*- coding: utf-8 -*-
"""
Created on Tue Apr 18 22:59:01 2023

@author: Sora
"""
from data_process import  li as li
import re
import matplotlib.pyplot as plt

plt.scatter(range(len(li)), li)
# plt.plot(li)
plt.show()


def exp_ave(li, beta = 0.9):
    temp = 0
    res = []
    fun = lambda x,y: beta*x + (1-beta) * y
    for t,v in enumerate(li) :
        temp = fun(temp,v)
        if t == 0:
            temp = temp/(1 - beta**(t+1))
        res.append(temp)
    return res

ans1 = exp_ave(li)
ans2 = exp_ave(li[::-1])[::-1]
ans = list(map( lambda x : (x[0]+x[1])//2 , zip(ans1, ans2)))

plt.plot(exp_ave(li),color = 'r')








