from itertools import combinations as comb
from itertools import product


def paint(black_cells):
    wall = [[False] * C for _ in range(R)]
    for r, c in black_cells:
        wall[r][c] = True
    return wall


def count_contrasts(black_cells):
    wall = paint(black_cells)
    count = 0
    for r, c in black_cells:
        if r > 0:
            count += (wall[r-1][c] != wall[r][c])
        if r < R-1:
            count += (wall[r+1][c] != wall[r][c])
        if c > 0:
            count += (wall[r][c-1] != wall[r][c])
        if c < C-1:
            count += (wall[r][c+1] != wall[r][c])
    return count


R, C, N = map(int, input().split())
grid = product(range(R), range(C))
max_contrasts = -1
for cells in comb(grid, N):
    count = count_contrasts(cells)
    if count > max_contrasts:
        max_contrasts = count
        best_wall = paint(cells)
for row in best_wall:
    for j in row:
        print(int(j), end='')
    print()
