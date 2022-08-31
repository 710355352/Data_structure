import random

def insert(line:list)->list:
    '''
    插入排序
    '''
    for i in range(len(line)):
        pre = i - 1
        cur = line[i]
        while pre >= 0 and line[pre] > cur:
            line[pre+1] = line[pre]
            pre-=1
        line[pre+1] = cur
    return line

if __name__ == '__main__':
    line = [random.randint(20,30) for i in range(20)]
    print(line)
    print(insert(line))