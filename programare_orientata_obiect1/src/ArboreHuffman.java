/**
 * 
 * @author Sezciuc Radu
 *
 */
public class ArboreHuffman {
	Queue q;
	Nod rad;
	
/** Constructor al arborelui Huffman ce il construieste pe acesta cu ajutorul vectorului de frecventa al caracterelor citite,arbore folosit ulterior la codificare
 * 
 *  
 * @param f:vectorul de frecventa al caracterelor cu ajutorul carora construim arborele Huffman folosit pentru codificare
 */
	public ArboreHuffman(Vectorfrecventa f)
	{
		q=new Queue(f.nr);      						//initializarea cozii auxiliare pentru construirea arborelui
		int i=0;
	    Nod aux;
		
	    for(i=0;i<f.nr;i++)					//crearea cozii prin adaugare repetata de noduri cu ajutorul metodei push
		{                                   
			aux=new Nod(f.cif[i],(int)f.lit[i],null,null,null);
			q.push(aux);
		}
		
		Nod aux1;
		Nod aux2;
		
		while (q.size()>1)          //construirea propriu-zisa a arborelui prin scoaterea a cate doua noduri din coada, si plasarea lor la locul potrivit in arbore
		{
			aux1=q.pop();
			aux2=q.pop();
			aux=new Nod(aux1.frec+aux2.frec,-1,null,aux1,aux2);
			q.push(aux);
		}								//ultimul element ramas in coada reprezinta radacina arborelui nou creat
 
	}	
	/**Constructor al arborelui Huffman cu ajutorul vectorului de codificare,arbore folosit ulterior la decodificare
	 * 
	 * @param v:vectorul de codificare al caracterelor cu ajutorul carora construim arborele Huffman folosit pentru decodificare
	 */
	public ArboreHuffman(Vectorcodificare v)
	{int i=0,j=0;
	 char[] vcar;									//initalizari
	 Nod aux;
	 Nod aux2=new Nod(0,-1,null,null,null);        //aux2 va avea in el mereu radacina arborelui creata la inceput
	 
	 while (i<v.n)       //parcurgerea fiecarui caracter din vectorul de codificari citit in Main
					{
		 				vcar=new char[v.l[i].length()];
		 				v.l[i].getChars(0, v.l[i].length(),vcar,0);  //spargerea codificarii corespunzatoare fiecarui caracter intr-un vector de caractere 
			         	j=0;
			         	rad=aux2;
			         	while(j<vcar.length)        //parcurgerea arborelui conform fiecarui caracter din codificare. Pentru '0',indicele va merge pe latura stanga, pentru '1' pe latura dreapta
			         					{			//in caz ca nodul nu exista, este creat
			         						if (vcar[j]=='0') {if (rad.stanga!=null) {
			         																	rad=rad.stanga;
										   										   		if (j==vcar.length-1) rad.c=v.c[i]; 
										   										  	 }
			         															else {																 //parcurgerea pe latura stanga
			         																 	if (j==vcar.length-1) aux=new Nod(0,v.c[i],null,null,null);
			         																					 else aux=new Nod(0,-1,null,null,null); 
			         															         rad.stanga=aux;
			         															         rad=rad.stanga;
			         															   		}
			         										  }
			         								     else {if (rad.dreapta!=null) {
			         									  							 	rad=rad.dreapta;
			         															     	if (j==vcar.length-1) rad.c=v.c[i];
			         															   	  }
			         															 else {
			         																	if (j==vcar.length-1) aux=new Nod(0,v.c[i],null,null,null);	 //parcurgerea pe latura dreapta
			         																	  				 else aux=new Nod(0,-1,null,null,null);
			         																	rad.dreapta=aux;
			         																	rad=rad.dreapta;
			         																}
			         									  }
			         						j++;    //trecerea la urmatorul caracter din codificare
			         					 }
			         	i++;  //trecerea la urmatorul caracter din vectorul de codificari
			         }
	rad=aux2;						//la final, indicele ce a parcurs arborele primeste adresa radacinii initiale
			         				
	}
	
			         					
	/** Metoda de codificare prin parcurgerea arborelui Huffman
	 * 		         					
	 * @param n:numarul de elemente alocate vectorului de codificare
	 * @param rad:radacina arborelui Huffman folosit pentru alcatuirea codificarii
	 * @return v:vectorul de codificare rezultat
	 */
			         					
			         					
	public Vectorcodificare codificare(int n,Nod rad)
	{int i=0,j=0;
	 Vectorcodificare v=new Vectorcodificare(n);         //initializari
	 Stack st=new Stack(n);
	 st.push(rad);
	 String cod="";
	 rad.codif=cod; 
	 
	 while (st.size()>0)                              //parcurgerea arborelui Huffman:cat timp stiva nu ramane fara elemente(stiva ce contine noduri din componenta arborelui)
	 					{if ((rad.stanga!=null) && (rad.stanga.ver==0))
		 										{
		 											st.push(rad.stanga);
		 											rad.stanga.ver=1;           //completarea codificarii:se adauga '0' daca in drumul spre caracter se ia pe latura stanga
		 											cod=cod+"0";
		 											rad.stanga.codif=cod;
		 											rad=rad.stanga;
		 										}
		 								else {if ((rad.dreapta!=null) && (rad.dreapta.ver==0))
		 										{
		 											st.push(rad.dreapta);
		 											rad.dreapta.ver=1;        //completarea codificarii:se adauga '1' daca in drumul spre caracter se ia pe latura dreapta
		 											cod=cod+"1";
		 											rad.dreapta.codif=cod;
		 											rad=rad.dreapta;
		 										}
		 												else {
		 														rad=st.pop();			//in caz ca acest nod exista si a fost si verificat(parcurs),se scoate din stiva 
		 														if (rad.c!=-1) {
		 																		 v.l[v.n]=rad.codif;
		 														                 v.c[v.n]=(int) rad.c;  //definitivarea codificarii:se completeaza vectorul de codificare cu codul obtinut in urma parcurgerii arborelui
		 														                 v.n=v.n+1;
		 																		}
		 														if (st.size()!=0) rad=st.list.get(st.list.size()-1);
		 														cod=rad.codif;
		 													 }
		 								     }
		 				}
	 int aux;
	 String aux2;
	 
	 for(i=0;i<v.n;i++) 
			for(j=i;j<v.n;j++) 
				if (v.c[i]>v.c[j])      //la final, se sorteaza vectorul de codificari obtinut in ordine crescatoare dupa codul ASCII al caracterelor aparute in sir
				{
					aux=v.c[i];
					aux2=v.l[i];
					v.c[i]=v.c[j];
					v.l[i]=v.l[j];
					v.c[j]=aux;
					v.l[j]=aux2;
				}
	
	 return v;
}
	/**Metoda de decodificare a codurilor primite in Main prin parcurgerea arborelui Huffman
	 * 
	 * @param rad:radacina arborelui Huffman folosit pentru alcatuirea decodificarii
	 * @param sirc:sirul de decodificat citit de la tastatura
	 * @return sir:situl rezultat in urma decodificarii
	 */
	public String decodificare(Nod rad,String sirc)
	{
	 String sir="";
	 int i=0;
	 Nod aux=rad;									//initializari
	 char[] scod=new char[sirc.length()];
	 sirc.getChars(0,sirc.length(),scod,0);			//spargerea sirului de codificari intr-un vector de caractere
	 
	 for(i=0;i<scod.length;i++) {					//pentru toate caracterele din sirul de codificari
		 							if ( (rad.stanga==null) && (rad.dreapta==null) ) {
		  																				sir=sir+(char)rad.c; //pentru fiecare frunza(caracter gasit) adaugam la sirul rezultat caracterul obtinut
		  																				rad=aux;
		 																	  	 	 }
		 							if (scod[i]=='0') rad=rad.stanga;      //0 pentru a merge pe subarborele stang
	                                             else rad=rad.dreapta;	   //1 pentru a merge pe subarborele drept
	 						    }
	 
	 if ( (rad.stanga==null) && (rad.dreapta==null) ) {
														sir=sir+(char)rad.c; //repetarea verificarii,deorece for-ul precedent se incheie fara a sti daca ultimul nod a fost verificat ca fiind frunza sau nu
														rad=aux;
		  										  	  }
	 
	 
	 return sir;
	}
}

