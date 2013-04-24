Sezciuc Radu Cristian
Grupa 311,Seria CB

Tema2


Task 1
	Am incercat citirea nodurilor invecinate cu cel corespunzator liniei folosind functia fgets.Am considerat ca este mai usor sa citesc cate o linie, 
decat sa incerc citirea cu fscanf element cu element(evident,dupa efectuarea "formalitatilor" de citire dintr-un fisier text: deschidere,etc).
Astfel, am putut transforma direct intr-un vector de intregi sirul de caractere obtinut din fgets prin folosirea functiei str2num.Parcurgand fiecare vector, 
si notand lungimea lui cu kn(citit de asemenea din fisierul text), am construit matricea de adiacenta a grafului "A",tinand cont sa pastrez diagonala principala 0.
Am construit apoi matricea diagonala K, ce are pe diagonala ei numarul de noduri ce se invecineaza direct cu nodul respectiv (la pozitia (i,i) a matricei K,
se gaseste numarul de noduri cu care se invecineaza nodul i).Calculandu-l pe M ca fiind transpusa produsului dintre inversa lui K si A, si calculand matricea R, 
am implementat recurenta care duce la aflarea rezultatului final. Pe pagina de Wikipedia trimisa ca referinta, este data o formula de recurenta ce contine R(t) 
si R(t+1),si pentru a implementa, am preferat notarea lor cu R si RS, vectori ce se schimba la fiecare apelare a secventei repetitive while (while ce are ca si 
conditie max(abs(RS-R)) ).Am folosit functia max, pentru a determina diferenta maxima intre elementele celor doi vectori, si pentru a intra de cat mai multe ori 
in acest while, pentru precizia rezultatului.Vectorul final rezultat, RS, este rezultatul functiei Iterative.

Task 2
	Pentru citirea din fisier text, am pastrat aceeasi metoda ca la functia iterative.m .Metoda algebraica foloseste o singura formula, astfel ca nu mai folosim 
recurenta. Pentru a calcula inversa unei matrici(problema reala a acestui task) am folosit functia inversa.m, care se foloseste de algoritmul de factorizare Gram-Schmidt
si algoritmul de rezolvare a unui sistem de ecuatii triunghiular superior, SST.m.Ambele functii au fost date/explicate la curs si la laborator,astfel ca am explicat 
efectul lor prin unele comentarii.Dupa calcularea inversei matricii lui K, am calculat si inversa matricii (I-dM) de data aceasta nemaifolosind functia inversa.m, ci 
direct in algebraic.m.Am notat cu T inversa acestei matrici, dupa care am folosit-o simplu in aplicarea formulei gasita in documentatia din tema(Wikipedia).Dupa care,
evident, am inchis fisierul deschis initial spre citire. 


Task 3
	In acest task, am apelat cate o data cele doua functii construite anterior, pentru a forma cei doi vectori PR1 si PR2(vectorii rezultanti functiilor iterative
si algebraic).Dupa afisarea lor, intrucat functiile iterative si algebraiv efectuau o citire care nu returna cei doi parametrii val1 si val2, a trebuit sa ii citesc 
in aceasta functie. Astfel, am "Sarit" peste cele N randuri cu indicii si vecinii lor, folosindu-ma de un fgets care imi salva de fiecare data sirul intr-o variabila.
Scopul acestui fgets este de fapt sa parcurga fisierul pana la final, pana la val1 si val2, valoarea propriu zisa a sirului nefolosindu-mi.Dupa citirea celor doua 
valori,am calculat parametrii a si b specifici, din cele doua conditii de continuitate: a*val1+b=0 si a*val2+b=1. Am duplicat vectorul PR2, si l-am sortat apoi,
pentru a-l putea afisa in a treia sectiune a fisierului ".out". Vectorul ind( de la indici) are rolul de a salva indicii initiali ai vectorului PR2, intrucat acestia se
amesteca dupa sortare,aici folosindu-ma de duplicatul facut initial.Dupa construirea vectorului cu indici ind, am afisat simplu de n ori, printr-un for,cele 3 numere 
cerute de catre cerinta:locul fiecarei pagini in acest clasament, indicele ei initial, si "rankul" acestei pagini privitor la multimea paginilor mai importante.  

