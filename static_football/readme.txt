Sezciuc Radu Cristian
grupa 331CB

Tema 1 EGC

Pentru a-mi usura munca, am construit functia "desenaredreptunghi" care primeste coordonatele unui dreptunghi, 
si intoarce obiectul adaugat pe axa de coordonate. Apoi, folosindu-ma de aceasta, am desenat terenul cu tusele
si portile sale. Tot cu ajutorul acestei functii am adaugat si celelalte dreptunghiuri ale jocului: scorul celor
doua echipe. Am alcatuit cercul din 12 triunghiuri, fiecare triunghi avand cate 3 puncte,toate stocate in 
vectorul de puncte. Apoi, folosindu-ma de aceleasi coordonate ale cercului am creat obiectul minge si jucatorii 
celor doua echipe pe care i-am stocat in cate un vector de pointeri la obiecte. Pentru animatie, m-am folosit de doua
variabile ce retin valorile cu care se face translatia mingii: tractx, traiectoria pe ox si tracty, traiectoria 
pe oy. In functie de aceste doua valori, mingea isi schimba traiectoria sau se opreste. In functia onIdle, am
pus conditiile pentru coliziunile cu mantele, si desigur pentru marcarea golurilor. Atunci cand o echipa marcheaza
un gol, se elimina si se adauga dreptunghiuri pe axa de coordonate astfel incat sa fie indicat scorul corect.
Tot in onIdle am tratat si coliziunea mingii cu jucatorii, ea oprindu-se in momentul in care distanta dintre
centrele mingii si jucatorului apropiat ei este aproximativ egala cu suma razelor celor doua cercuri. Functia
onKey am folosit-o pentru a controla jucatorii ce detin mingea. Vectorii posesie imi arata daca un jucator are 
mingea, astfel incat, in cazul in care o are sa o poate translatata inainte pe directia calculata in functie
de centrele celor doua cercuri: jucatorul si mingea. Tot aici am folosit functia de rotire relativa in jurul unui
punct atunci cand rotesc mingea in jurul jucatorului.
