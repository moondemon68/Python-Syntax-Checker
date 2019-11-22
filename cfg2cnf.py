import sys, itertools

# List initialization
Terminals = []
Variables = []
Productions = []

# Helper function to make new variables that haven't yet exist
def requestVariable(var):
    i = 1
    if (var[-1] >= '0' and var[-1] <= '9'):
        var = var[:-1]
    newVar = var.upper() + str(i)
    while (newVar in Variables):
        i = i + 1
        newVar = var.upper() + str(i)
    return newVar

cfgFile = 'cfg.txt'

file = open(cfgFile, 'r')
# Format file: 
# Terminal (all lowercase)
# Variable (all must start in uppercase letter)
# Production 1 (RHS -> LHS1 LHS2 | LHS3 LHS4 | LHS5)
# Production 2

# Read file, and transform it into lists
Terminals = file.readline().replace('\n', '').split(' ')
Variables = file.readline().replace('\n', '').split(' ')
ReadProductions = file.readlines()
for i in range(len(ReadProductions)):
    ReadProductions[i] = ReadProductions[i].replace('\n', '')
Productions = []
for i in range(len(ReadProductions)):
    LHS = ReadProductions[i].split(' -> ')[0]
    RHS = ReadProductions[i].split(' -> ')[1].split(' | ')
    for j in range(len(RHS)):
        Terms = RHS[j].split(' ')
        Productions.append((LHS, Terms))

# START: Eliminate the start symbol from right-hand sides
if (not 'S0' in Variables):
    Variables.append('S0')
    Productions = [('S0', [Variables[0]])] + Productions

# TERM: Eliminate rules with nonsolitary terminals (A -> B c becomes A -> B Z and Z -> c)

# Create a dictionary of terminals:variables
Dictionary = {}

# Check if there is any A -> a already
for Production in Productions:
    if ((Production[0] in Variables) and (Production[1][0] in Terminals) and (len(Production[1]) == 1)):
        Dictionary[Production[1][0]] = Production[0]

# Create a temporary list to hold modified productions
Productions2 = []
for Production in Productions:
    if ((Production[0] in Variables) and (Production[1][0] in Terminals) and (len(Production[1]) == 1)):
        Productions2.append(Production)
    else:
        for Terminal in Terminals:
            i = 0
            for Term in Production[1]:
                if ((Terminal == Term) and (not Terminal in Dictionary)):
                    Dictionary[Terminal] = requestVariable(Terminal)
                    Variables.append(Dictionary[Terminal])
                    Productions2.append((Dictionary[Terminal], [Terminal]))
                    Production[1][i] = Dictionary[Terminal]
                elif (Terminal == Term):
                    Production[1][i] = Dictionary[Terminal]
                i = i + 1
        Productions2.append((Production[0], Production[1]))
Productions = Productions2

# BIN: Eliminate right-hand sides with more than 2 nonterminals
Productions2 = []
for Production in Productions:
    if (len(Production[1]) <= 2):   # No problem
        Productions2.append(Production)
    else:
        NewVariable = requestVariable(Terminal)
        Variables.append(NewVariable)
        Productions2.append((Production[0],[Production[1][0]] + [NewVariable]))
        
        for i in range(1, len(Production[1]) - 2):
            Variables.append(requestVariable(NewVariable))
            Productions2.append((NewVariable, [Production[1][i], NewVariable(i+1)])) 
        Productions2.append((NewVariable, Production[1][len(Production[1])-2:len(Production[1])]))
Productions = Productions2

# DEL: Eliminate ε-rules (if there is an epsilon rule in productions)
# Skipped. Simply make a CFG that doesn't contain any epsilon rule :)

# UNIT: Eliminate unit rules
for i in range(500):    # Better safe than sorry
    Productions2 = []
    UnitRules = []
    for Production in Productions:
        if ((Production[0] in Variables) and (Production[1][0] in Variables) and (len(Production[1]) == 1)):    # (A -> B form)
            UnitRules.append((Production[0], Production[1][0]))
        else:
            Productions2.append(Production)
    for Unit in UnitRules:
        for Production in Productions:
            if ((Unit[1] == Production[0]) and (Unit[0] != Production[0])):
                Productions2.append((Unit[0], Production[1]))
    Productions = Productions2


file = open('cnf.txt', 'w')
Productions = sorted(Productions)   # For easier new lines
Done = []

# Printing the productions list in a good format (S0 must be in the first line)
for Production in Productions:
    if (Production[0] == 'S0'):
        if (Production[0] in Done):
            if (len(Production[1]) == 1):
                file.write(' | ' + Production[1][0])
            else:
                file.write(' | ' + Production[1][0] + ' ' + Production[1][1])
        else:
            if (Production == 'S0'):
                file.write('\n')
            Done.append(Production[0])
            file.write(Production[0] + ' -> ')
            if (len(Production[1]) == 1):
                file.write(Production[1][0])
            else:
                file.write(Production[1][0] + ' ' + Production[1][1])
for Production in Productions:
    if (Production[0] != 'S0'):
        if (Production[0] in Done):
            if (len(Production[1]) == 1):
                file.write(' | ' + Production[1][0])
            else:
                file.write(' | ' + Production[1][0] + ' ' + Production[1][1])
        else:
            if (Production != 'S0'):
                file.write('\n')
            Done.append(Production[0])
            file.write(Production[0] + ' -> ')
            if (len(Production[1]) == 1):
                file.write(Production[1][0])
            else:
                file.write(Production[1][0] + ' ' + Production[1][1])