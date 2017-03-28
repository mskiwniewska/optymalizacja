import numpy
import itertools

print ('Algorytm stosowany do problemów w postaci normalnej (Ax<=b i x>=0)')

#kilka podstawowych funkcji
#sprawdzamy ze wspolrzedne sa >=0
def wspnieujemne(z):
    wspnieujemne = True
    for i in z:
        if i <= 0:
            wsp = False
    return wspnieujemne

# operacje na macierzach 
# wybieramy kolumne z macierzy
def wybierzkolumne(tablica, kolumnaX):
    return tablica[:, [kolumnaX]]

# dodajemy kolumne na koniec 
def dodajkolumne(tablica, kolumna):
    if tablica is None:
        return kolumna
    else:
        return numpy.append(tablica,kolumna, 1)

# wybieramy mozliwe kolumny z ktorych stworzymy kwadratowa macierz
def wybormozliwychkolumn(k, l):
    for kolumny in itertools.permutations(range(k + l), k):
        if kolumny == tuple(sorted(kolumny)):
            yield kolumny

print('Wprowadzmy wzor na f')
ilosc = int(input('Podaj liczbe zmiennych: '))

c= []
# nasza funckja f

for i in range(ilosc):
    c.append(float(input('Wspolczynnik przy x' + str(i + 1) + ': ')))

print('Wprowadzmy ograniczenia')
iloscograniczen = int(input('Liczba ograniczen: '))

A = []
b = []

# nasze ograniczenia (oraz A,b,c)
for i in range(iloscograniczen):
    print ('Ograniczenie ' + str(i+1)), i + 1
    a = []
    for j in range (ilosc):
        a.append(float(input('Wspolczynnik przy x' + str(j + 1) + ': ')))
    b.append(float(input('Liczba po prawej stronie nierownosci: ')))
    for j in range(iloscograniczen):
        if i == j:
            a.append(1.0)
        else:
            a.append(0.0)
    A.append(a)
    c.append(0.0)

A = numpy.array(A)
b = numpy.array(b)
c = numpy.array(c)

maxZ = float('-inf')
maxX = []
for kolumny in wybormozliwychkolumn(ilosc,iloscograniczen):
    a = None
    for i in kolumny:
        a = dodajkolumne(a, wybierzkolumne(A, i))
    if numpy.linalg.det(a) != 0.0:
        z = numpy.linalg.inv(a).dot(b)
        if wspnieujemne(z):
            Z = [0] * (ilosc + iloscograniczen)
            j = 0
            for i in kolumny:
                Z[i] = z[j]
                j += 1
            if c.dot(Z) >= maxZ:
                maxZ = c.dot(Z)
                maxX = Z[:ilosc]

if maxX == []:
    print ('Brak rozwiazan.')
else:
    print ('Argmax f= ' + str(maxX))
    print ('Max f= ' + str(maxZ))
