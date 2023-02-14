def zero_matrix(mat):
    zeros = list()
    for i,row in enumerate(mat):
        for j,num in enumerate(row):
            if num == 0: zeros.append((i,j))
            
    for (x,y) in zeros:
        for i in range(len(mat)): mat[i][y] = 0
        for i in range(len(mat[x])): mat[x][i] = 0

    return mat

assert zero_matrix([[1,1,2], [1,2,4], [1,0,0]]) == [[1,0,0],[1,0,0],[0,0,0]]
assert zero_matrix([[1]]) == [[1]]

