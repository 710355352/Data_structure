# 详见https://www.bilibili.com/video/BV1uA411N7c5?p=23&spm_id_from=pageDriver&vd_source=ac0bbbffda6996e441315418279f131b
'''
预备知识：
满二叉树是指二叉树的最后一层是满叶子的，即第n层有2**（n-1）个叶子节点
完全二叉树则比满二叉树要求降低，是指倒数第二层必须满，最后一层的叶子节点集中在树的左侧，即每一层都是从左向右依次排列
    性质 ： 完全二叉树可以1-1对应于一个列表
            在列表中，父节点的index为i，那么其左孩子节点的index则为2*i+1，右孩子节点则为2*i+2
            显然，孩子节点 j 的父节点为 （j-1）//2 
这就是堆排序的基础。
堆则是完全二叉树的一种特殊情况，分为大根堆和小根堆，大根堆则是完全二叉树的父节点比其两个子节点值大，小根堆则相反。（算作是一般有序，不是完全有序）

堆排序的过程分为两个，
其一，构建初期的大根堆
    大根堆的建立是农村包围城市的思想，从最小的最后一个小堆进行向下调整，依次到大根堆的root节点，这样就保证了大根堆的形成
其二，将大根堆逐渐变小
    每次将大根堆的root节点与最后一个叶子节点互换，并减少大根堆的长度，在进行一次向下调整。

这两个过程都会用到一个大根堆的向下调整过程，即只有root节点不在该有的位置上，而root的两个子节点都是大根堆。
这个过程我们写成函数sift
'''
def sift(li, low, high):
    '''
    li : 待排序的序列
    low : 所注意的根节点位置
    high : 大根堆的结束位置（最后一个叶子节点）
    '''
    i = low # 起始将low保存为i
    j = 2 * i + 1 # j代表i的左孩子节点
    tmp = li[i] # tmp 代表根节点的值
    # 接下来就是调整的过程
    while j <= high: # 确保左孩子未越界
        if j + 1 <= high and li[j] < li[j+1]: #保证右孩子不越界并且右孩子比左孩子大
            j = j + 1 # 此时将j标记为两个孩子中最大的那个
        if li[j] > tmp: # 如果最大值比tmp大，那么就将孩子j 与 i的位置互换（实际上不需要，只需更换i的值即可）
            li[i] = li[j]
            i = j # 此时的i就变为j的位置，并继续循环
            j = 2 * i + 1 # j仍未i的左孩子
        else: # 如果tmp比两个孩子都大，那么tmp就应该在i这个位置上, 并且结束循环
            li[i] = tmp
            break
    else: # 若是因为越界导致的循环退出，则表示i已经是叶子节点，tmp就在此处即可
        li[i] = tmp


def head_sort(li):
    n = len(li)
    # 构建初始的大根堆
    high = n -1 # high是指向大根堆的最后一个叶子，由此来找到第一个需要向下调整的父节点，也就是最后一个父节点
    low = (high - 1) // 2 # 最后一个父节点
    for i in range(low, -1, -1): # 
        sift(li, i, high)
    low = 0
    # 排序过程
    while high > 0 : # 当high比0大，也就是待排序的堆长度为2时。继续循环
        li[high], li[low] = li[low], li[high] # 交换root节点(low)和最后一个叶子节点(high)
        high  -= 1 # 待排序序列长度减一
        sift(li,low,high) # 此时root节点为最后一个叶子节点，需要一次向下调整来使得堆仍为大根堆
    return li
if __name__ == '__main__':
    import random
    limit_and_num = 10000
    line = [random.randint(0,limit_and_num) for i in range(limit_and_num // 100)]
    nice_line = sorted(line)
    print(line)
    print(head_sort(line))
    print(head_sort(line) == nice_line)