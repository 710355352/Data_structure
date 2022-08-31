import random
def selection(line:list )->list:
    for i in range(len(line)):
        minu = i
        for j in range(i,len(line)):
            if line[minu] > line[j]:
                minu = j
        line[minu],line[i] = line[i],line[minu]
    return line


if __name__ == '__main__':
    line = [random.randint(20,30) for i in range(20)]
    print(line)
    print(selection(line))