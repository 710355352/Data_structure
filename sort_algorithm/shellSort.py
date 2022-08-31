import random
def shell(line:list )->list:
    '''
    希尔排序，实际上就是将插入排序中的1变成gap，让gap从最大变到1
    zhe'yang'jiu
    '''
    gap = 1
    while gap < len(line)/3:
        gap = 3*gap + 1
        print(gap)
    while gap > 0:
        for i in range(len(line)-gap):
            cur = line[i+gap]
            pre = i
            while pre >= 0 and line[pre] > cur:
                line[pre+gap] = line[pre]
                pre-=gap
            line[pre+gap] = cur
        gap = int(gap/3)
        print(gap)
    return line


if __name__ == '__main__':
    line = [random.randint(20,30) for i in range(20)]
    print(line)
    print(shell(line))