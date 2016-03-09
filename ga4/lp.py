import math
from pulp import *

fi = open("Data.txt", "r")

x0 = LpVariable("x0", 0)
x1 = LpVariable("x1", 0)
x2 = LpVariable("x2", 0)
x3 = LpVariable("x3", 0)
x4 = LpVariable("x4", 0)
x5 = LpVariable("x5", 0)
z = LpVariable("z")

prob = LpProblem("min abs dev", LpMinimize)

prob += z

for columns in (row.strip().split("\t") for row in fi):
    prob += (x0)+(x1*int(columns[1]))+(x2*math.cos((2*math.pi*int(columns[1]))/(365.25)))+(x3*math.sin((2*math.pi*int(columns[1]))/(365.25)))+(x4*math.cos((2*math.pi*int(columns[1]))/(365.25*10.7)))+(x5*math.cos((2*math.pi*int(columns[1]))/(365.25*10.7)))-float(columns[0])<=z
    prob += (x0)+(x1*int(columns[1]))+(x2*math.cos((2*math.pi*int(columns[1]))/(365.25)))+(x3*math.sin((2*math.pi*int(columns[1]))/(365.25)))+(x4*math.cos((2*math.pi*int(columns[1]))/(365.25*10.7)))+(x5*math.cos((2*math.pi*int(columns[1]))/(365.25*10.7)))-float(columns[0])>=-z

status = prob.solve(GLPK(msg=0))
LpStatus[status]

print value(x0)
print value(x1)
print value(x2)
print value(x3)
print value(x4)
print value(x5)
