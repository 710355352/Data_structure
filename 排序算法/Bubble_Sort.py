from typing import List


import random
def bubble_sort(line:List) -> List:
    n = len(line)
    for i in range(n):
        for j in range(n-i):
            if line[j] <= line[j+1]:
                continue
            else:
                line[j],line[j+1] = line[j+1], line[j]
    return line 



if __name__ == '__main__':
    line = [random.randint(0,20) for i in range(20)]
    print(line)
    print(bubble_sort(line))
