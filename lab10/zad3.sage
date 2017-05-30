# program zaklada, ze wszystkie krawedzie maja wage 1
# problem istnienia skojarzenia maksymalnego w grafie z zad 1 jako problem liniowy 
# wariant całkowitoliczbowy i zrelaksowany tego zadania liniowego.
macierz=[[1,0,1,0,0,1,0],[1,0,0,1,0,0,0],[0,1,1,0,1,0,0],[1,0,0,1,0,0,1],[0,1,0,0,0,0,1],[0,1,0,0,1,1,0],[0,0,1,0,0,0,1]]
show(macierz)
# to nasza macierz polaczen w grafie
# PL dla x
MILP=MixedIntegerLinearProgram(maximization=True)
x=MILP.new_variable(integer=True,nonnegative=True)
# range() & len()
k=0  # funkcja celu
for i in range(len(macierz)):
    for j in range(len(macierz)):
        if macierz[i][j]==1:
            k+=x[i,j]
MILP.set_objective(j)
# ograniczenia
# range() & len()
for i in range(len(macierz)):
    c=0 # funkcja celu
    for j in range(len(macierz)):
        if macierz[i][j]==1:
            c+=x[i,j]
    MILP.add_constraint(c<=1)
for j in range(len(macierz)):
    c = 0
    for i in range(len(macierz)):
        if macierz[i][j]==1:
            c+=x[i,j]
    MILP.add_constraint(c<=1)
# wyniki 
print "PROBLEM BAZOWY: \n"
show(MILP.solve())
wartosc_x=MILP.get_values(x)
show(wartosc_x)
# program dualny
# PL dla y
MILPP=MixedIntegerLinearProgram(maximization=False)
y=MILPP.new_variable(integer=True,nonnegative=True)
# range() & len()
k = 0 # funkcja celu
for i in range(2):
    for j in range(len(macierz)):
        k+=y[i,j]
MILPP.set_objective(k)
# ograniczenia
for i in range(len(macierz)):
    for j in range(len(macierz)):
        if macierz[i][j]==1:
            MILPP.add_constraint(y[0,i]+y[1,j]>=1)
# wyniki
print 'PROBLEM DUALNY: \n'
show(MILPP.solve())
wartosc_y=MILPP.get_values(y)
show(wartosc_y)
