'''
    8-Queens problem object class
    This object will generate a 8-queens problem object in this format:
        [q1,q2,q3,q4,q5,q6,q7,q8]
    This array represent the positions of 8 queens.Array index represents the X-axis and the
    array value means the Y-axis.
'''
from _8_queens_by_HC import *
from _8_queens_by_GA import *
class _8_queens:

    def __init__(self):
        self.queens_location = [0,0,0,0,0,0,0,0] #8 positions of queens.
        self.conflicts = [0,0,0,0,0,0,0,0]       #個別的conflicts數量
        pass
    
    def generate_8_queens_random(self,seed):
        #Set the random seed
        random.seed(seed)
        #Randomly get 8 integers to determine the position of queens.
        p = np.arange(8)
        random.shuffle(p)
        #Set the positions of queens
        for i in range(8):
            self.queens_location[i] = p[i]

    def generate_8_queens_assign(self,assign):
        #Directly assign value to problem
        for i in range(8):
            self.queens_location[i]=assign[i]
    
    def number_of_conflicts(self):
        #Count the number of independent queens
        count = total_count = 0
        for i in range(7):
            count = 0
            for j in range(i+1,8):
                if(self.queens_location[i]==self.queens_location[j]):
                    #In the same row
                    count += 1
                    continue
                delta_y = abs(i-j)
                delta_x = abs(self.queens_location[i]-self.queens_location[j]) #Calculate the slope
                if(delta_x==delta_y):
                    #對角線上
                    count += 1
                    continue
            total_count += count
            self.conflicts[i] = count
        self.conflicts[7] = count
        return total_count            

    def print_8_queens(self):
        for i in range(8):
            for j in range(8):
                if(7-self.queens_location[j]==i):
                    print('* ',end='')
                else:
                    print('O ',end='') 
            print()

    def solve_by_HC(self,restart_bound):
        solved = hill_climbing(self,restart_bound)
        return solved

    def solve_by_GA(self,restart_bound):
        solved = genetic_algorithm(self,restart_bound)
        return solved