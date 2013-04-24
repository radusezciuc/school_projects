
public class Dictionar {
	
	public String cuvant;
	public int frecventa;
	public int dist;

	public Dictionar(String cuvant,int frecventa)
	{
		this.cuvant=cuvant;
		this.frecventa=frecventa;
		this.dist=-1;
	}
	
	public Dictionar(String cuvant,int frecventa,int dist)
	{
		this.cuvant=cuvant;
		this.frecventa=frecventa;
		this.dist=dist;
	}
	
	public Dictionar(Dictionar d)
	{
		this.cuvant=d.cuvant;
		this.frecventa=d.frecventa;
		this.dist=d.dist;
	}
	
	
}
