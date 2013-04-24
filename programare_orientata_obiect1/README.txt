Sezciuc Radu, grupa 321CB



//Programul poate primi doi indici in mainul acestuia:pentru c, se va apela codificarea unui anumit text, iar pentru d, se va folosi decodificarea unui anumit
sir de caractere format din biti.



//Codificare

	Pentru codificare, dupa citirea sirului de caractere, am apelat la gasirea frecventei de aparitie a fiecarui caracter din sir, cu ajutorul metodei 
Vectorfrecventa din clasa Frecventa.Apoi, odata obtinut vectorul de frecvente al fiecarui caracter, am construit arborele Huffman corespunzator acestuia. Folosindu-ma
de o coada, am adaugat in aceasta toate nodurile ce contin caracaterul si frecventa acestuia.Vectorul de frecventa fiind ordonat dupa frecventa de aparitie,
coada se va forma deja ordonata.Apoi, in timp ce scoteam cate doua elemente din coada(pe cele cu frecventele de aparitie cele mai mici), cream un nou nod ce are 
frecventa egala cu suma celor doua frecvente de aparitie ale nodurilor recent eliminate din coada. Acest nod va avea drept fii elementele reprezentate de cele doua 
noduri inlaturate din coada. Dupa aceste operatii, acesta va fi introdus in coada de prioritati la locul corespunzator acestuia, astfel incat frecventele din coada 
sa fie in continuare ordonate. Dupa repetarea acestei operatii,ultimul nod ramas in coada este reprezentat de radacina arborelui Huffman.
	Dupa formarea arborelui, prin parcurgerea acestuia cu ajutorul metodei Codificare din clasa ArboreHuffman(folosind o stiva ce retine nodurile care au fost
parcurse in trecut) , obtinem vectorul de codificare final, ce contine atat caracterul cat si codificarea corespunzatoare acestuia. Parcurgand din nou sirul de 
caractere citit la inceput, alcatuim codificarea finala asociind fiecare caracter cu codificarea acestuia.



//Decodificare

	Pentru decodificare, am citit vectorul de codificari conform metodei explicate in comentarii. Apoi, conform acestui vector, am construit arborele Huffman
corespunzator cu ajutorul celui de-al doilea constructor al clasei ArboreHuffman. Am luat codificarea fiecarui caracter in parte, si am format arborele in felul
urmator: am creat un nod fiu stang pentru fiecare '0' din codificare, si un nod fiu drept pentru fiecare '1' din codificare daca acesta nu era deja creat.Atunci cand
epuizam toate caracterele din codificarea unui caracter,ultimului nod(care va fi frunza)atribuiam codul ASCII corespunzator codificarii recent folosite.Apoi treceam la 
urmatorul caracter, plecand de fiecare data de la radacina.Dupa crearea arborelui, am obtinut decodificarea finala cu ajutorul metodei decodificare: parcurgand 
arborele am alcatuit sirul final decodificat, si l-am afisat.