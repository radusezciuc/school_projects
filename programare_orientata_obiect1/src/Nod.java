/**
 * 
 * @author Sezciuc Radu
 *
 */
public class Nod {
	int frec;
	int c;
	Nod parinte;
	Nod stanga;
	Nod dreapta;
	int ver;
	String codif;
	
/** Constructor al nodului ce initializeaza toate campurile acestuia cu valorile date ca parametri
 * 
 * @param frec:frecventa de aparitie corespunzatoare fiecarui nod din arbore
 * @param c:codul ASCII corespunzator caracterului reprezentat de nodul din arbore
 * @param parinte:parintele nodului
 * @param stanga:fiul stang al nodului
 * @param dreapta:fiul drept al nodului
 */
	public Nod(int frec,int c,Nod parinte,Nod stanga,Nod dreapta)       /*Constructor al nodului din arbore care
																		initializeaza pe acesta cu anumite valori*/
	{																		
		this.frec=frec;
		this.c=c;
		this.parinte=parinte;
		this.stanga=stanga;
		this.dreapta=dreapta;
		ver=0;
	}
}
