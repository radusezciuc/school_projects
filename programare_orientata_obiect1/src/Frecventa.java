/**
 * 
 * @author Sezciuc Radu
 *
 */
public class Frecventa {
	/**Metoda calculeaza frecventa de aparitie a caracterelor din sir
	 * 
	 * @param s:sirul citit de la tastatura in main,ale carui caractere trebuie calculata frecventa de aparitie 
	 * @return f:vectorul de frecventa al caracterelor componente ale sirului
	 */

	public static Vectorfrecventa frecv(String s)
	{
		int i=0,j=0,m=0;
		char[] v=new char[s.length()];
		
		s.getChars(0,s.length(),v,0);
		Vectorfrecventa f=new Vectorfrecventa(s.length());   //spargerea sirului intr-un vector de caractere pentru analizarea pe rand a fiecarui element
		
		boolean k=false;
		for (i=0;i<v.length;i++)  //parcurgerea sirului de caractere
		{
			k=false;
			j=0;
			
			while ((j<i) && (k==false))      //gasirea de duplicate a caracterului curent in urma acestuia
				if (v[i]==v[j]) k=true;
				else j=j+1;
			
			if (k==false)       //daca e prima oara cand intalnim acest caracter, il adaugam in vectorul de frecventa de aparitie
			{
				f.lit[f.nr]=v[i];
				for(m=0;m<v.length;m++) if (v[i]==v[m]) f.cif[f.nr]=f.cif[f.nr]+1;     	//construirea efectiva a vectorului de frecvente de aparitie		    										
				f.nr=f.nr+1;
     		}
		}
		
		int aux;
		char aux2;
		for(i=0;i<f.nr;i++) 
			for(j=i;j<f.nr;j++) 
				if (f.cif[i]>f.cif[j])
				{							//sortarea crescatoare la final al vectorului de frecvente de aparitie obtinut 
					aux=f.cif[i];
					aux2=f.lit[i];
					f.cif[i]=f.cif[j];
					f.lit[i]=f.lit[j];
					f.cif[j]=aux;
					f.lit[j]=aux2;
				}

		return f;	
	}
}



