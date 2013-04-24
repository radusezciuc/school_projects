Sezciuc Radu Cristian
331CB

Tema3APD

In rezolvarea acestei teme am folosit limbajul C.

1.Compilare si Rulare

Pentru compilarea temei este de ajuns rularea comenzii make. 
Exemplu de rulare:"mpirun -np 2 sursa mandelbrot1.in man.pgm"

2.Solutia aleasa in rezolvarea temei

Am ales procesul master, cel de rang 0, ca fiind procesul care citeste pentru inceput toate datele de intrare din fisierul text. Acesta apoi trimite aceste date (transpuse sub forma unui vector) catre celelalte procese folosindu-se de MPI_Send. Am alocat cate o matrice pentru fiecare proces in parte(o matrice liniarizata sub forma de vector), fiecare dintre acestea calculand doar o anumita portiune, o portiune ce va fi egala cu inaltimea matricii de pixeli impartita la numarul total de procese. Altfel spus, fiecarui proces ii revine un numar de linii din matrice de calculat. Toate procesele vor avea astfel de calculat acelasi numar de linii, exceptand pe ultimul, in cazul in care inaltimea matricii nu se imparte exact la numarul de procese. Pentru a decide ce portiune ii revine fiecarui proces, m-am folosit de variabilele div(diviziune),indi(indice inceput) si indf(indice final): diviziunea retine cate linii ii revine fiecarui proces, in timp ce indice inceput si indice final sunt indicii care retin limitele intre care procesul trebuie sa-si desfasoare lucrul. Dupa ce fiecare proces si-a terminat lucrul dupa algoritmii corespunzatori, fiecare va trimite procesului master fasiile de vectori calculate. Procesul master le va concatena pe toate acestea si le va afisa in fisierul de iesire specificat. 

3.Teste efectuate

Am testat programul pe toate imaginile, si acesta se comporta bine pe orice numar de procese introdus. Insa, acesta nu scaleaza timpii foarte bine.
Exemple de teste:

Mandelbrot1
1 proces:
real	0m8.713s
2 procese:
real	0m8.278s
4 procese:
real	0m7.566s
8 procese:
real	0m9.284s

Mandelbrot2
1 proces:
real	0m0.340s
2 procese:
real	0m1.323s
4 procese:
real	0m1.315s
8 procese:
real	0m1.252s

Julia5
1 proces:
real	0m19.779s
2 procese:
real	0m10.916s
4 procese:
real	0m10.904s
8 procese:
real	0m18.204s

Julia6
1 proces:
real	0m0.652s
2 procese:
real	0m1.422s
4 procese:
real	0m1.369s
8 procese:
real	0m1.364s





