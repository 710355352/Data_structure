from typing import List, overload
import random




@overload
def bubble_sort(line:List)->List: ...
@overload
def bubble_sort(line:List,flag:bool)->List: ...

def bubble_sort(line:List,arg = None) -> List:
    n = len(line)
    if arg:
        for i in range(1,n):
            flag = arg
            for j in range(n-i):
                if line[j] <= line[j+1]:
                    continue
                else:
                    line[j],line[j+1] = line[j+1], line[j]
                    flag = False

            if flag == True:
                break
    else:
        for i in range(1,n):
            flag = arg
            for j in range(n-i):
                if line[j] <= line[j+1]:
                    continue
                else:
                    line[j],line[j+1] = line[j+1], line[j]
    return line 

if __name__ == '__main__':
    line = [random.randint(0,20) for i in range(20000)]
    print(line)
    print(bubble_sort(line))
