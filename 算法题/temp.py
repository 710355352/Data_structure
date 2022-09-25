f = open(file = '1.csv', mode = 'r', encoding='utf8')
lines = f.readlines()
f.close()
# print(lines)
map = []
for line in lines:
    line = line.strip('\n')
    thisline = line.split(',')
    thisline = [int(_) for _ in thisline]
    summ = sum(thisline)
    ave = summ/len(thisline)
    map.append((summ,ave,len(thisline)))
    # print(thisline)
print(map)
sum_all = 0
size = 0

for i in map:
    # print(type(i[0]))
    sum_all += i[0]
    size+=i[-1]
    print(i[1])
print(f'All numbers ave is {sum_all/size}')

    

    








