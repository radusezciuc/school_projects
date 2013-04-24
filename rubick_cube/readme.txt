SEZCIUC Radu Cristian 
grupa 331CB

Tema 2 - EGC

In aceasta tema am implementat cubul Rubik in limbajul C++.

1.Compilare/Rulare

Tema poate fi compilata si rulata cu ajutorul lui Visual Studio 2008.

2.Descrierea implementarii / Solutii alese.

Pornind de la frameworkul oferit la laborator, am ales implementarea cubului Rubik astfel incat acesta sa fie format din 27 de cuburi mai mici. Cum cu acest framework nu putem crea cuburi care sa aiba culorile fetelor diferite, am lucrat cu fetele cuburilor, si nu cu cuburile intregi. Astfel incat, dupa ce am creat 6 vectori de puncte ( specifice celor 6 fete ale cubului mic), le-am folosit pe acestea pentru a crea 27 de cuburi (intr-un cub Rubik fiind necesare 3*3*3 cuburi) si a le adauga la sistemul principal de coordonate.

Odata cu crearea fetelor am setat si culoarea acestora in functie de coordonatele lor, si le-am adaugat pe toate la vectorul "fata", ce va avea la final 27*6 elemente (27 de cuburi * 6 fete). Pentru a putea roti anumite straturi ale cubului m-am folosit de 6 vectori(top,bottom,left,right,front,back,mdex, medy si medz) in care am pastrat cuburile specifice straturilor. Un astfel de vector va avea 9 cuburi*6 fete. 

Pentru a putea roti cubul am alcatuit functia "rotirecuburi", care roteste un anumit vector de fete dat, in functie de axele OX,OY si OZ. Cum eu rotesc un strat in functie de centrul axelor de coordonate si axele OX, OY si OZ, atunci cand cubul intreg isi schimba unghiul, straturile nu se vor mai misca adecvat fata de restul cubului. De aceea, inainte de a roti un strat, am readus cubul in pozitie initiala, am rotit stratul, dupa care am dus cubul intreg in pozitia la care se afla inainte de rotire. Pentru a memora toate rotirile cubului intreg m-am folosit de vectorul rotiri.

Partea cea mai grea a acestei teme mi s-a parut a fi rotirea straturilor. Desigur, m-am folosit de aceeasi functie "rotirecuburi" pentru a face asta, dar odata cu rotirea straturilor, acestea se vor rearanja si vor lua nastere straturi noi. De aceea, pentru a actualiza straturile cubului Rubick, am folosit functia "actlayere". Aceasta aranjeaza cubul in pozitie initiala, si afla ce fete apartin noilor straturi comparand toate punctele fetelor cu axele OX,OY si OZ. De exemplu, toate cuburile care au coordonata y mai mare decat 3.9 vor apartine stratlui top. Cele cu coordonata mai mica decat 3.9 pe axa OY vor apartine sratului bottom s.a.m.d. Dupa actualizarea straturilor, am readus cubul in pozitia initiala.

Functia onKey am folosit-o pentru a roti cubul intreg sau un anumit layer la apasarea unei taste.

In functia onIdle, testez cubul permanent pentru a observa daca are toate fetele de aceeasi culoare. Daca se intampla asta, atunci jocul este resetat. Testarea se face verificand pe rand daca fetele extreme straturilor au aceeasi culoare. Daca jocul este terminat cu succes, atunci ecranul se intuneca pentru cateva secunde si apare scorul obtinut in numarul de cuburi afisat pe ecran. La apasarea tastei 'q', jocul actual se termina si reincepe unul nou.

3.Taste folosite:

1-Roteste cubul dupa axa OX
2-Roteste cubul dupa axa OY
3-Roteste cubul dupa axa OZ
t-Roteste stratul 'top' al cubului
d-Roteste stratul 'bottom' al cubului
l-Roteste stratul 'left' al cubului
r-Roteste stratul 'right' al cubului
b-Roteste stratul 'back' al cubului
f-Roteste stratul 'front' al cubului
x-Roteste stratul 'medx' al cubului
y-Roteste stratul 'medy' al cubului
z-Roteste stratul 'medz'  al cubului
s-Pornirea jocului in modul 'Rezolvare'
q-Reinceperea jocului

Jocul se poate reincepe apasand tasta q, doar dupa terminarea unuia vechi! Tasta q functioneaza doar atunci cand apare ecranul cu scorul al jocului cel vechi.