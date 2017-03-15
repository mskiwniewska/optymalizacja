#include <stdio.h>
#include <stdlib.h>

//Problem N hetmanow - polega na ustawieniu na szachownicy wymiaru NxN tychze figur tak aby zadna z nich nie mogla zabic innej
//Hetman ustawiony na szachownicy atakuje wszystkie pola w poziomie,pionie i po skosie

int iloscRozw= 0; //liczy ilosc rozwiazan

void HetDwa(int i, int k[], int w[], int p1[], int p2[], int liczbaHetmanow);

void Het(int liczbaHetmanow) //funckja wprowadzajaca
{
    int k[liczbaHetmanow]; // k[i] to numer wiersza hetmana w kolumnie o numerze i
    int w[liczbaHetmanow]; // w[i] = 1 jesli wiersz i-ty zajety, wpp w[i] = 0
    int iloscPrzekatnych = 2*liczbaHetmanow -1; //ilosc przekatnych dla szachownicy wymiaru NxN
    int p1[iloscPrzekatnych]; // dla hetmana o wspolrzednych (i,j)
    // p1[i+j] = 1 jesli przekatna typu i+j jest zajeta, wpp p1[i+j] = 0
    int p2[iloscPrzekatnych]; // niech a=liczbaHetmanów - 1 (bo biore 'i' oraz 'j' od 0 do liczbaHetmanów - 1)
    // p2[i-j+a] = 1 jesli przekatna typu i-j+a jest zajeta, wpp jest wolna

    int l;
    for (l = 0; l < liczbaHetmanow; l++)
        w[l] = 0; //na poczatku wszystkie wiersze wolne

    for (l = 0; l < iloscPrzekatnych; l++)
        p1[l] = p2[l] = 0; //na poczatku wszystkie przekatne wolne

    HetDwa(0,k,w,p1,p2, liczbaHetmanow); //wywoluje funckje Hetdwa dla kolumny o numerze 0
}

void HetDwa(int i, int k[], int w[], int p1[], int p2[], int liczbaHetmanow) //funkcja glowna, ustawia hetmanow i liczy rozw
{
    int j, l; // j to numer wiersza, l jest pomocnicze w drugiej petli
    int a = liczbaHetmanow -1;
    for (j = 0; j < liczbaHetmanow; j++) //przelatuje po kolejnych wierszach
        if (!w[j] && !p1[i+j] && !p2[i-j+a]) { //jezeli wiersz j-ty i odpowiednie przekatne wolne
                //to ustawiam hetmana na pozycji (i,j)
            k[i] = j; //ustawiam
            w[j] = p1[i+j] = p2[i-j+a] = 1; //czyli juz zajelam wiersz j-ty i odpowiednie przekatne

            if (i == a) { //gdy juz przelecialam po wszystkich kolumnach
                for (l = 0; l < liczbaHetmanow; l++)
                    printf("%d ", k[l]); //wypisuje ciag N liczbowy ktory przedstawia polozenie hetmanow
                printf("\n");
                iloscRozw++; //zwiekszam nasz licznik rozwiazan
            }
            else
                HetDwa(i+1,k,w,p1,p2, liczbaHetmanow); //dla kolejnej kolumny

            w[j] = p1[i+j] = p2[i-j+a] = 0; //zeby otrzymywac kolejne nowe rozwiazania inne od poprzednich
        }
}

int main()
{
    printf("Przyjmuje ze numery kolumn i wierszy naleza do zbioru {0,...,N-1}\n");
    printf("Polozenie hetmanow na szachownicy:\n");
    printf("Kazdy ciag cyfr to rozwiazanie zawierajace numery wierszy w kolejnych kolumnach\n");
    //np. jedyne rozwiazanie symetryczne dla n=8 bedzie mialo postac 42061753

    int liczbaHetmanow;
    printf("Podaj N=");
    scanf ("%d", &liczbaHetmanow);
    Het(liczbaHetmanow);

    printf("Jest %d rozwiazan.\n", iloscRozw);

    return 0;
}
