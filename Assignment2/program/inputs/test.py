import numpy as np

filename='input.txt'
fileread=[]
with open(filename,'r') as file:
    for line in file:
        line = line.strip().split()
        for a in line:
            fileread.append(a)

readarray = np.array(fileread)
print (list(map(float,readarray)))
file.close()