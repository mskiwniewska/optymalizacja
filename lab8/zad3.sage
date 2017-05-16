#Gra Blotto - gra dla dwóch osób z sumą zerową, w której gracze mają równocześnie rozdzielać ograniczone zasoby na pola bitwy.
#Poświęcając najwięcej zasobów na pole bitwy gracz wygrywa tę bitwę, a zysk jest równy łącznej liczbie zwycięskich pól bitewnych.
import numpy 
# S = 6
# (1, 1, 4) przeciwko (1, 2, 3) remis
# (1, 2, 3) przeciwko (2, 2, 2) remis
# (2, 2, 2) zbija (1, 1, 4)

macierz = numpy.array([[0, 0, 1], [0, 0, 0], [-1, 0, 0]])
x = macierz.shape[0]
y = macierz.shape[1]

c = [0]*x
c.append(1)
b = [0]*y
b.append(1)

kolumna = [[-1]]*y
wiersz = numpy.append([[1]*x], [[0]], axis=1)
A = macierz.transpose()
A = numpy.append(A, kolumna, axis=1)
A = numpy.append(A, wiersz, axis=0)

# program liniowy
con = [">="]*y
con.append("==")
var = [">="]*x
var.append("")

ILLP = InteractiveLPProblem(A, b, c, constraint_type = con, variable_type = var)
show(ILLP)

# wynik
show(ILLP.standard_form().run_simplex_method())
