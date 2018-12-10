'''
    Solve the 8-queens problem by Hill Climbing with Random Restart.
'''
import numpy as np
import random
import time
import copy
def hill_climbing(eq,restart_bound=20):

    from _8_queens import _8_queens
    changed = 1         #Check the conflict is changed
    solved = False      #Check the problem is solved
    random_restart = 0  #Randomly restart flag
    count = 1           #Count the run times of loop
    directions = np.arange(8) #The group of queen's next step
    
    #Get the copy of eq
    eq_clone = copy.deepcopy(eq)

    while(solved==False and count<=restart_bound):
        changed = 0
        if (random_restart==1):
            #Random restart 
            eq_clone.generate_8_queens_random(time.time()+count)
            random_restart = 0

        conflicts = eq_clone.number_of_conflicts()              #Calculate the number of conflicts
        new_conflicts = conflicts                               #If we found new lower conflict value ,the value of new_confilcts will be different from conflicts.
        max_conflict_queen = np.argmax(eq_clone.conflicts)      #Find the queen that have the max value of conflicts. 
        for next_p in directions: #走上下
            if(next_p!=max_conflict_queen):
                #Move the queen.
                org = eq_clone.queens_location[max_conflict_queen]
                move_to(eq_clone,max_conflict_queen,next_p)

                #Calculate the conflicts.
                new_conflicts = eq_clone.number_of_conflicts()
                
                if(new_conflicts<conflicts):
                    #Get less conflicts.將此做為新的基準點
                    real_next_p = next_p
                    conflicts = new_conflicts
                    changed = 1
                #Move back
                move_to(eq_clone,max_conflict_queen,org)
                    
        if(changed==1):
            #Found the new local maxima.Move queen to the position
            move_to(eq_clone,max_conflict_queen,real_next_p)
            random_restart = 0
        else:
            #New local maxima is not found.Use the random restart.
            random_restart = 1
        
        solved = True if(conflicts==0) else False       #Check if the problem is solved.
        count += 1
    return {
                "solved":solved,
                "result_eq":eq_clone
            }

def move_to(eqs,current,next_step):
    #Move queen to the next position.
    eqs.queens_location[current] = next_step

def can_move_to(eqs,current,next_step):
    #確保下一個位置沒有其他queen在同一個row
    for i in range(8):
        if (next_step==eqs.queens_location[i]):
            #Repeated
            return False
    return True

