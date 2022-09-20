import random


def partation(line,left,right):
    att = line[left]
    while left < right:
        while left < right and line[right] >= att:
            right-=1
        line[left] = line[right]
        while left < right and line[left] <= att:
            left+=1
        line[right] = line[left]
    line[left] = att
    return left


def Quick_Sort(line:list, left = 0, right = None)->list:
    '''
    快排
    快排的思想是让每一个元素都归位，
    归位就是让每个元素处在自己应该在的位置
    例如，第一步我们让第一个元素调整到其应该处于的位置，
    递归的让这个元素的剩下的左右序列重复上一步，直到每一个元素都归位，
    那么整体自然就归位了

    所以说，这个函数存在两部分，第一部分是让给定的序列的第一个元素归位
    第二步是递归调用该元素剩下的左右序列
    '''
    # print(left,right)
    if line == []:
        return line
    if left < right:
        mid = partation(line,left,right)
        # print(line)
        Quick_Sort(line,left,mid-1)
        Quick_Sort(line,mid+1,right)


if __name__ == '__main__':
    line = [random.randint(0,30) for i in range(20)]
    print(line)
    Quick_Sort(line,0,len(line)-1)
    print(line)