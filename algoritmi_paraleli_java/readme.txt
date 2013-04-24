SEZCIUC Radu Cristian 
grupa 331CB

Tema 2 - APD

(ReadMe-ul se citeste de preferat cu NotePad++ sau Gedit)
Aceasta tema a fost scrisa in limbajul Java, sub sistemul de operare Windows.

1.Compilare/Rulare

Tema poate fi compilata si rulata cu ajutorul lui Eclipse.

2.Descrierea implementarii / Solutii alese.

Pentru efectuarea acestei teme am ales desigur modelul Replicated Workers. Intrucat rezolvarea ei presupunea rezolvarea mai multor taskuri: de Map, Reduce 1 si
Reduce2, am ales formarea a trei WorkPooluri, trei stive de solutii partiale si prin urmare am folosit 3*NT thread-uri pentru rezolvarea fiecarei stive de taskuri.
Am folosit o singura clasa de solutii partiale aceasta continand campuri si variabile necesare pentru toate cele 3 taskuri, dar constructori diferiti. Programul 
primeste ca parametrii numarul de threaduri, fisierul de input si de output. Functioneaza bine pentru orice fisier de intrare si orice numar de threaduri ales.

a.Taskul Map

Pentru rezolvarea taskului Map, procesarea unei solutii partiale presupune obtinerea unei structuri de date ce retine numarul de cuvinte si numarul acestora 
de aparitii pentru fiecare secventa a fiecarui document scris in fisierul de intrare(fiecare executata de cate un thread). Astfel, aceasta va fi de forma 
ArrayList<HashMap<String,HashMap<String,Integer>>>, adica un vector de perechi (document,pereche(cuvant,nraparitii)). Fiecare solutie partiala este creata cu 
ajutorul unui cosntructor ce primeste exact parametrii functiei Map: nume document, octet inceput si octet de sfarsit pentru secventa citita, apoi este adaugata 
la WorkPool pentru a fi procesata. 
Se creeaza numarul de threaduri pentru rezolvarea taskurilor, rezolvarea unui task de tip Map facandu-se in felul urmator: se sare la secventa de octeti 
specificata cu ajutorul lui skipBytes, se sare peste caracterele nealfabetice sau literelor care fac parte dintr-un cuvant incomplet, se citesc restul cuvintelor
intregi, si se adauga la o structura de date auxiliara(care mai tarziu va fi adaugata la ArrayListul final) impreuna cu frecventa lor de aparitie.

b.Taskul Reduce1

Pentru rezolvarea taskului Reduce1, o solutie partiala reprezinta concatenarea tuturor structurilor de date ce apartin unui anumit document, si calcularea 
frecventelor lor de aparitie in functie de documentul in care ele apar. Pentru a paraleliza si acest task, am creat iarasi un workpool ce contine la randul
lui un alt vector de solutii partiale ce asteapta sa fie rezolvat de acelasi numar de threaduri. Pentru concatenarea acestor structuri de date am folosit
un HashMap<String,Float> (cate unul pentru fiecare document in parte), care retine cuvantul si numarul lui de aparitii(de data aceasta de tip float, pentru ca 
tot aici vom calcula si frecventa de aparitie a lui). Am parcurs structura, si am creat acest HashMap adunand aparitiile cuvintelor pentru toate secventele in
care apar, dupa care am salvat toate aparitiile intr-un vector. Am ales aceasta implementare, pentru ca sortand descrescator acest vector vom obtine primele
n valori ca ale lui ca fiind valorile cuvintelor cele mai relevante. Afland al n-lea element al acestui vector este echivalent cu a afla numarul de aparitii
a ultimului cuvant relevant. Astfel, dupa acest criteriu am facut selectia cuvintelor relevante intre o noua structura de date pe care am adaugat-o in 
workpool, structura ce va folosi pentru rezolvarea ultimului task.

c.Taskul Reduce2

Pentru paralelizarea taskului Reduce2, am ales aceeasi abordare ca mai sus: un nou workpool, o noua stiva de solutii partiale. Procesarea lor a constat in faptul
ca a trebuit sa selectez doar documentele care contin toate cuvintele cautate. Variabila boolean ok am folosit-o pentru a determina daca un astfel de document
este relevant, daca el contine toate cuvintele cautate. Daca da, atunci il adaug in structura finala de date: un HashMap<String,HashMap<String,Float>> - adica
o pereche (document,pereche(cuvant, frecventa de aparitie)). La final, in Main, cu ajutorul Threadului Master am afisat frecventele de aparitie ale cuvintelor
cautate ce fac parte din maxim X documente cu formatul cerut.