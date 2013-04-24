SEZCIUC Radu Cristian 
grupa 331CB

Tema 4 - EGC

In aceasta tema am implementat jocul "Imperiul Contraataca" in limbajul C++.

1.Compilare/Rulare

Tema poate fi compilata si rulata cu ajutorul lui Visual Studio 2008.

2.Descrierea implementarii / Solutii alese.

Primul pas in efectuarea temei a fost desenarea asteroizilor. M-am folosit de o clasa externa pentru a instantia asteroizii, creati cu functia glutSolidDodecahedron().
La crearea acestora, i-am adaugat imediat intr-un vector pentru a-i putea sterge atunci cand sunt distrusi sau se lovesc de nava. Acestia sunt creati la coordonate aleatoare (cu ajutorul functiei rand()) cu culori aleatoare. 

Nava am desenat-o folosindu-ma de functia ReadOffReader. Apeland aceasta functie in InitScene, am salvat in variabila Mesh nava, inacadrand-o apoi intr-o sfera. Odata cu nava, simultan se vor deplasa si camera asociata acesteia si scutul ei protector. Pentru a face asta m-am folosit de un un Vector3D ce pastreaza coordonatele navei(sferei, si camerei). La apasarea tastelor, aceste coordonate se modifica creand efectul de miscare. La distrugerea asteroizilor m-am folosit de functia mouse ce apeleaza la randul ei functia pick si processhits. La un click, variabila "obiect" retine indicele asteroidului selectat din vector, acesta fiind distrus ulterior. Efectul laserului a fost creat prin a desena o linie de la nava la obiectul distrus.

Atunci cand este nava se loveste de unul dintre asteroizi, atunci scutul acesteia isi pierde din vizibilitate. Asta se intampla de 2 ori, la a treia lovitura jocul luand sfarsit.

3. Taste folosite

1 - camera dinamica
2 - camera nava
3 - camera asteroid
w - deplasarea navei in sus
a - deplasarea navei la stanga
s - deplasarea navei in jos
d - deplasarea navei in dreapta
z - departarea navei
x - apropierea navei
i - deplasarea camerei in sus
j - deplasarea camerei la stanga
k - deplasarea camerei in jos
l - deplasarea camerei in dreapta 
o - departarea camerei
p - apropierea camerei
mouse- selectare/distrugere asteroid