/**
 * 
 * @author Sezciuc Radu
 *
 */
public class Vectorcodificare {
	int[] c;     //vector al codurilor ASCII ale caracterelor
	String[] l;   //vector de siruri ce reprezinta codificarile caracterelor
	int n;       //numarul de elemente al vectorilor egali
/** Constructor ce initializeaza vectorul de codificare
 * 
 * @param n:numarul de elemente alocate pentru vectorul de codificare
 */
	public Vectorcodificare(int n)
	{
		c=new int[n];
		l=new String[n];
		n=0;
	}
}
