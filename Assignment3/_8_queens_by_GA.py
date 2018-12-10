'''
    Solve the 8-queens problem by Genetic Algorithm.
'''
import numpy as np
import random
import time
import copy
from _8_queens_by_HC import move_to,can_move_to
def genetic_algorithm(eq,restart_bound=50):

    from _8_queens import _8_queens

    population_number = 200                     #The number of population.
    number_of_states = population_number        #The number of initial states.
    number_of_successors = number_of_states * 2 #The number of successors.Number after star will affect the survival rate of successors.
    count = 1                                   #Count the iteration times.
    states_conflicts = np.zeros((number_of_states,), dtype=int)     #Use to store the number of conflicts of initial states.
    successors = [_8_queens() for i in range(number_of_successors)] #Store the successors.
    chance = 1                                                    #The probability of mutation.

    #Give the random seed
    random.seed(time.time())

    #Get the copy of eq
    eq_clone = []
    for i in range(number_of_states):
        eq_clone.append(copy.deepcopy(eq))

    #Randomly generate initial states
    directions = np.arange(8)       #8 directions
    for i in range(number_of_states):
        #Randomly choices a queen to move
        current_p = random.choice(directions)
        #Randomly choices a move
        next_p = random.choice(directions)
        #Generate the state
        move_to(eq_clone[i],current_p,next_p)
        #Get number of conflicts
        states_conflicts[i]=eq_clone[i].number_of_conflicts()

    while(count<=restart_bound):
        #print("The ",count," times.")
        successors_conflicts = np.zeros(number_of_successors) #Initialize the number of conflicts of successors.
        #Randomly cross over to get successors
        for i in range(int(number_of_successors/2)):
            s1,s2= get_s1s2(states_conflicts,number_of_states)  #Get parent.
            cross_over(successors[i*2],successors[i*2+1],eq_clone[s1],eq_clone[s2]) #Cross over to get two successors.
            successors_conflicts[i*2]=successors[i*2].number_of_conflicts()         #Get the number of conflicts of successors.
            successors_conflicts[i*2+1]=successors[i*2+1].number_of_conflicts()
        
        survival = np.argsort(successors_conflicts) #Sort the successors_conflicts to get less conflicts states.
        if successors_conflicts[survival[0]]==0:
            #The first value of list successors_conflicts is the least number of conflicts.
            #If we get 0 from successors_conflicts[survival[0]].There is a solution.
            return {
                        "solved":True,
                        "result_eq":successors[survival[0]]
            }
        
        #Eliminate the successors that have more conflicts.
        #The remaining successors will become the new states to crossover. 
        for i in range(number_of_states):
            eq_clone[i]=successors[survival[i]]
            states_conflicts[i]=successors_conflicts[survival[i]]
            
            #mutation
            if(random.random() <=chance):
                mutation(eq_clone[i])
        count +=1
    return {
                        "solved":False,
                        "result_eq":eq_clone[0]
        }
def get_s1s2(state_conflicts,number_of_states):
    #將conflicts的數量作為權重，選出兩個parent states.
    s1 = s2 = 0
    conflicts_lcm = np.lcm.reduce(state_conflicts)  #Get the lcm of conflicts.
    choice = np.arange(number_of_states)            #Choice from the all states.
    weight = np.full(number_of_states,conflicts_lcm)/state_conflicts    #Use the conflicts number as probability weight to choice the parents.
    while(s1==s2):#Find s1 and s2 which are different.
        s1,s2 = random.choices(choice,weights=weight,k=2)
    return s1,s2
def cross_over(successor1,successor2,eq1,eq2):
    #Cross over two parent states to get two successors
    n = random.randint(0,2)+2#Where to cut the gene
    gene1 = []
    gene2 = []
    gene1[:n]=eq1.queens_location[:n]+eq2.queens_location[n:]
    gene2[:n]=eq2.queens_location[:n]+eq1.queens_location[n:]
    successor1.generate_8_queens_assign(gene1)
    successor2.generate_8_queens_assign(gene2)

def mutation(successor):
    #Randomly mutation
    i = random.randint(0,7)
    successor.queens_location[i]=random.randint(0,7)

    