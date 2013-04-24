import java.util.Scanner;


public class Main {

	/**
	 * @param args c:pentru codificare,d:pentru decodificare
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		if (args[0].equals("c"))
		{	
			//Codificare
			Scanner sc=new Scanner(System.in);     //obiectul Scanner folosit pentru citire
			String s1="",s="";     					//initializari 
			int i=0,j=0;
	    	
			while(!s1.equals("."))
			{
				s1=sc.nextLine();						//alcatuieste sirul de caractere obtinut in urma citirii a mai multor randuri
				if(!s1.equals(".")) if (i!=0) s=s+"\r\n"+s1;
	    										else s=s+s1;		//prima oara, nu se coboara pe urmatorul rand
				i++;
			}
			
			Vectorfrecventa f=Frecventa.frecv(s);		//obiect ce foloseste la obtinerea vectorului de frecvente de aparitie a caracterelor citite
	    
			ArboreHuffman a=new ArboreHuffman(f);		//obiect ce foloseste la obtinerea arborelui Huffman
	    
			char[] ve=new char[s.length()];
			int[] u=new int[s.length()];
		
			s.getChars(0,s.length(),ve,0);			 //spargerea sirului citit intr-un vector de caractere
			for(i=0;i<s.length();i++) u[i]=(int)ve[i];
			String sir="";
			Vectorcodificare vec=a.codificare(f.nr,a.q.list.get(0)); //obtinerea vectorului de codificare pentru fiecare caracter in parte
			for(i=0;i<vec.n;i++) 
								System.out.println(vec.c[i]+" "+vec.l[i]);	//afisarea vectorului de codificare
			System.out.println(".");
			for(i=0;i<s.length();i++) 
					for(j=0;j<vec.n;j++) 
							if (u[i]==vec.c[j]) 
												{
													System.out.print(vec.l[j]); //afisarea codificarii totale obtinute
	                                                sir=sir+vec.l[j]; 
	    										}
		}
		
		else
		{
			//Decodificare
	    
	    	Scanner sc2=new Scanner(System.in);
	    	Vectorcodificare vcod=new Vectorcodificare(260);
	    	String sd="";
	    	String str;
	    	int number;
	    	int k=0;
	    	char[] vd=new char[20];			//initializari
	    	char[] vd1;
	    	char[] vd2;
	    	
	    	sd=sc2.nextLine();			
	    	while(!sd.matches("^.$"))		//cat timp nu intalnim randul punct in timpul citirii
	    								{
	    									k=0;
	    									sd.getChars(0,sd.length(),vd,0); //spargerea randului intr-un vector de caractere
	    									while (vd[k]!=' ') 
	    														k++;	//determinarea locului spatiului in rand pentru a separa codul ASCII al caracterului de codificarea acestuia
	    									vd1=new char[k];
	    									sd.getChars(0,k,vd1,0);   		//punerea codului ASCII al caracterului intr-un vector de caractere vd1
	    									vd2=new char[sd.length()-k-1];
	    									sd.getChars(k+1,sd.length(),vd2,0);		//punerea codificarii corespunzatoare intr-un vector de caractere vd2
	    									number = Integer.parseInt(new String(vd1)); 	//punerea codului ASCII al caracterului intr-un numar
	    					 				str=new String(vd2);					//punerea codificarii intr-un sir de caractere
	    					 				
	    					 				vcod.c[vcod.n]=number;
	    					 				vcod.l[vcod.n]=str;					//initializarea vectorului de codificare
	    					 				vcod.n=vcod.n+1;
	    					 				sd=sc2.nextLine();
	    								}
	    
	        str=sc2.nextLine(); //citirea codificarii totale
	
	        ArboreHuffman h=new ArboreHuffman(vcod);		//construirea arborelui Huffman corespunzator codificarii
	        
	        String sir2="";
	    
	        sir2=h.decodificare(h.rad,str);			//decodificarea pe baza arborelui Huffman obtinut
	        
	        System.out.println(sir2);			//afisarea decodificarii obtinute
	        System.out.print(".");
	    
		}
	    
	}
	}


