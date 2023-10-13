import os
from tqdm import tqdm 
import time

print(os.get_terminal_size().columns)
# def get_filelists(file_dir='.'):
#     list_directory = os.listdir(file_dir)
#     filelists = []
#     for directory in list_directory:
#         # os.path 模块稍后会讲到
#         if(os.path.isfile(directory)):
#             filelists.append(directory)
#     return filelists

# print(get_filelists(r'D:\个人资料'))

#　最基本操作直接使用tqdm包裹可迭代对象

def exsample1():
    for i in tqdm(range(100)):
        time.sleep(0.1)
# exsample1()

# 生成一个tqdm对象，再调用
def exsample2():
    pbar = tqdm(range(100))
    for c in pbar:
        time.sleep(0.1)
# exsample2()    

# 生成描述头
def exsample3():
    pbar = tqdm(range(100))
    for c in pbar:
        time.sleep(0.1)
        pbar.set_description(desc=f"已运行{c}个")
    pbar.close()
# exsample3()

# 自定义tqdm条有多少个，如果update超过了会乱码
def exsample4():
    iter = 100
    pbar = tqdm(total=iter)
    for c in range(iter):
        time.sleep(0.1)
        pbar.update(1)
    pbar.close()
# exsample4()

#　设置右边描述
def exsample5():
    from random import random,randint
    iter = 100
    pbar = tqdm(total=iter)
    for c in range(iter):
        time.sleep(0.1)
        pbar.update(1)
        pbar.set_description(desc=f"第{c}迭代")
        pbar.set_postfix(loss=random(),gen=randint(1,999),str="h",lst=[1,2])
    pbar.close()
# exsample5()


from time import sleep
from tqdm import trange, tqdm
from multiprocessing import Pool, freeze_support, RLock

L = list(range(9))

def progresser(n):
  interval = 0.001 / (n + 2)
  total = 5000
  text = "#{}, est. {:<04.2}s".format(n, interval * total)
  for i in trange(total, desc=text, position=n,ascii=True):
    sleep(interval)

if __name__ == '__main__':
  freeze_support() # for Windows support
  p = Pool(len(L),
       # again, for Windows support
       initializer=tqdm.set_lock, initargs=(RLock(),))
  p.map(progresser, L)
  print("\n" * (len(L) - 2))


