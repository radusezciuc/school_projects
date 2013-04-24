Sezciuc Radu
321CB

Enunt: http://cursuri.cs.pub.ro/~poo/wiki/index.php/Tema4

Am implementat interfata MyHashMap in clasa MyHashMapImpl. Pentru calcularea indicelui bucketului unde vor fi distribuite entryurile, am folosit o metoda numita
bucketcode ce translateaza cheia intr-o valoare potrivita indexului ArrayListului de bucketuri. Apoi, dupa ce am implementat clasele EntryImpl si BucketsImpl, am
definit principalele functii pentru lucrul cu MyHashMap : get(care intoarce valoarea entryului in functie de cheia data ca parametru), put(care actualizeaza un entry
existent sau creeaza unul nou), remove(care scoate din MyHashMap entryul corespunzator cheii date), si size(returneaza numarul de bucketuri create).

Apoi, in a doua faza am creat clasele Student ( folosind hashCodeul prezentat in tema) si LazyStudent(caruia i-am dat un hashCode constant ). Cel mai eficient mod
de implementare a unui HashMap este atunci cand numarul de bucketuri este egal cu numarul de entryuri, pentru ca in acest fel numarul de entryuri va fi egal distribuit
pe cate un bucket, si atunci accesarea se face in timp constant.Insa, cu cat scade HashCodeul/ numar de bucketuri cu atat scade si eficienta. Cea mai slaba eficienta
este atunci cand distribuim toate entryurile pe un singur bucket, sau pentru un HashCode constant. Astfel, pentru a cauta un entry intr-un singur bucket, obtinem un 
timp mai mare.

