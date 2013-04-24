/**
 * 
 * @author Sezciuc Radu
 *
 */
public class Vectorfrecventa {
	int[] cif;	//Vector ce contine frecventa caracterelor corespunzatoare din vectorul lit.
	char[] lit;  //Vector de caractere
	int nr;     //Numarul de elemente al celor doi vectori egali
/**Initializarea vectorului de frecvente 
 * 
 * @param n:numarul de elemente alocate pentru vectorul de frecventa
 */
	public Vectorfrecventa(int n)
	{
		cif=new int[n];
		lit=new char[n];
		nr=0;
	}
}
