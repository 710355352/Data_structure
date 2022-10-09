maze = [
    [0,1,1,0,1],
    [0,0,1,0,1],
    [1,0,0,1,0],
    [0,1,0,0,0],
    [0,0,1,0,0]
]
n,m = len(maze), len(maze[0])
ans = []
li = []
move = [(0,1),(0,-1),(1,0),(-1,0)]
def bfs():
    Out = [(0,0)]
    In = [(1,0)]

    while In:
        temp = []
        for i,j in In:
            Out.append((i,j))
            for x_,y_ in move:
                new_i,new_j = i+x_,j+y_
                if new_i<0 or new_j<0 or new_i >= len(maze) or new_j >= len(maze[0]):
                    continue
                if maze[new_i][new_j] == 1:
                    continue
                if i == len(maze) and new_j == len(maze[0]):
                    break
                if (new_i,new_j) not in Out:
                    temp.append((new_i,new_j))
        In = temp
        temp = []
    return Out
print(sorted(bfs()))


