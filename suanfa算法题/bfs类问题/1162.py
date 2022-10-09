'''
最简单的想法就是对每个海域找最近的小岛，但是会超时。
好一点儿的想法就是将每个岛屿看作波源，同时发射信号（上下左右），哪一片海域最后获得信号，那个海域获得信号的时间就是最远距离。
'''
# 第一版
def maxDistance( grid: list[list[int]]) -> int:
    ans = -1
    def bfs(i,j,grid):
        next_step = [(0,1),(0,-1),(1,0),(-1,0)]
        start = (i,j)
        stack = [(i,j)]
        temp = []
        out = set()
        flag = True
        while flag:
            for i,j in stack:
                if grid[i][j] == 1:
                    flag = False
                    ans = abs(start[0]-i) + abs(start[1]-j)
                    break
                for i0,j0 in next_step:
                    if 0 <= i+i0 <= len(grid)-1 and 0<= j+j0<len(grid[0]) and (i+i0,j+j0) not in out :
                        temp.append((i+i0,j+j0))
                out.add((i,j))
            # print(out)
            if temp == []:
                break
            stack = temp
            temp = []
        return ans
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == 0:
                ans = max(bfs(i,j,grid),ans)
                print(ans)
    return ans

# 第二版

def MaxDistance(grid: list[list[int]]) -> int:
    m, n = len(grid), len(grid[0])

    stack = []
    for i in range(m):
        for j in range(n):
            if grid[i][j]:
                stack.append([i, j])

    if len(stack) == m*n or not stack:
        return -1

    step = 1
    while stack:
        nex = []
        for i, j in stack:
            for x, y in [[i+1, j], [i-1, j], [i, j+1], [i, j-1]]:
                if 0<=x<m and 0<=y<n and not grid[x][y]:
                    nex.append([x, y])
                    grid[x][y] = 3
        for _ in grid:
            print(_)
        print('\n')
        
        stack = nex
        step += 1
    return step-2

grid = [[1 for _ in range(40)]]
for _ in range(38):
    grid.append([1] + [0 for _ in range(38)] + [1])
grid.append([1 for _ in range(40)])
# print(grid)
print(MaxDistance(grid))