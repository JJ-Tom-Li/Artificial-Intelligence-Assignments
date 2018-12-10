'''
    Assignment_#3-_8-Queens_Problem
    系級:資工四
    學號:4104056004
    姓名:李家駿

    Generate 100 8-queens instances and solve them (where possible) by Hill Climbing 
    with Random Restart and Genetic Algorithm. Measure the search cost and percentage 
    of solved problems.
'''
from _8_queens import _8_queens
#from _8_queens_by_HC import *
import time

solve_number_of_HC = 0      #Counting the solve number of Hill Climbing
solve_number_of_GA = 0      #Counting the solve number of Genetic Algorithm 
NUMBER_OF_PROBLEMS = 100    #The number of problems needing to be solved.
search_time_hc = 0.0        #Recording the search time of hill climbing
search_time_ga = 0.0        #Recording the search time of genetic algorithm

#Generate problems
for i in range(NUMBER_OF_PROBLEMS):
    print("Problem ",i+1,":")
    #Generate 8-queens problem object
    eq = _8_queens()
    #eq.generate_8_queens_random(i+int(time.time()))
    eq.generate_8_queens_random(i)
    
    print(eq.queens_location)
    eq.print_8_queens()
    print("The number of confilcts:",eq.number_of_conflicts())
    
    print("\nSolved by HC:\n")
    
    #Solve the problem by hill climbing
    t1 = time.time()
    hc_result = eq.solve_by_HC(1000)
    search_time_hc += time.time()-t1

    if(hc_result['solved']):
        solve_number_of_HC += 1

    #if(hc_result['solved']):
    print(hc_result['result_eq'].queens_location)
    hc_result['result_eq'].print_8_queens()
    print("The number of confilcts:",hc_result['result_eq'].number_of_conflicts())
    print("The problem is solved:",hc_result['solved'])
    
    print("\nSolved by GA:\n")

    #Solve the problem by genetic algorithm
    t1 = time.time()
    ga_result = eq.solve_by_GA(50)
    search_time_ga += time.time()-t1

    if(ga_result['solved']):
        solve_number_of_GA += 1
    #if(ga_result['solved']):
    print(ga_result['result_eq'].queens_location)
    ga_result['result_eq'].print_8_queens()
    print("The number of confilcts:",ga_result['result_eq'].number_of_conflicts())
    print("The problem is solved:",ga_result['solved'])
    print("---------------------------------------------------------")

#Print the search cost and percentage of solved problems.
print("The percentage of solved problems of HC is:",float(solve_number_of_HC/NUMBER_OF_PROBLEMS))
print("The search cost:",search_time_hc," sec")
print("The percentage of solved problems of GA is:",float(solve_number_of_GA/NUMBER_OF_PROBLEMS))
print("The search cost:",search_time_ga," sec")
