maze = [
    [0,1,1,0,1],
    [0,0,1,0,1],
    [1,0,0,1,0],
    [0,0,0,0,0],
    [0,0,1,0,0]
]
n,m = len(maze), len(maze[0])
ans = []
li = []
move = [(0,1),(0,-1),(1,0),(-1,0)]
def dfs(i,j):
    if i == n-1 and j == m-1:
        temp = [ _ for _ in li ]
        ans.append(temp)
        # print(ans)
        return
    if i < 0 or j<0 or i>=n or j >= m:
        return
    else:
        if maze[i][j] == 1:
            return 
        maze[i][j] = 1
        li.append((i,j))
        # print(li)
        # for _ in maze:
        #     print(_)
        # print('\n')
        for x_,y_ in move:
            new_i,new_j = i+x_,j+y_
            dfs(new_i,new_j)
        maze[i][j] = 0
        li.pop()
        # print(li)
        # for _ in maze:
        #     print(_)
        # print('\n')
dfs(0,0)
print(ans)