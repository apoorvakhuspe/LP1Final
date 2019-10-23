import random
import string

ip="Hello Apoorva" #abcde
def generate_random_solution(length=len(ip)):
    return [random.choice(string.printable) for _ in range(length)] #256 char #list of all printable char

def evaluate(solution):	#heuristic 
    target = list(ip)
    diff = 0
    for i in range(len(target)):
        s = solution[i]
        t = target[i]
        diff += abs(ord(s) - ord(t)) #h-a, e-b
    return diff

def mutate_solution(solution):
    index = random.randint(0, len(solution) - 1)	#randomly choose index
    solution[index] = random.choice(string.printable) #randomly change value of that index

best = generate_random_solution()
best_score = evaluate(best)

count=0
while True:
    print('Best score so far', best_score, 'Solution', "".join(best))

    if best_score == 0:
        print('Found after {} attempts'.format(count))
        break

    new_solution = list(best)	#new
    mutate_solution(new_solution)
    print("Current solution ","".join(new_solution))
    score = evaluate(new_solution)	#cal score
    if evaluate(new_solution) < best_score:
        best = new_solution
        best_score = score
    count+=1
    
    
    
    
