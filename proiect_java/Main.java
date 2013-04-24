import java.util.*;
import java.io.*;


public class Main {
	
	public static int LevenshteinDistance(String cuvant1,String cuvant2 )
	{   int i,j,m=cuvant1.length(),n=cuvant2.length();
		int[][] distanta=new int[m+1][n+1];
		int min;
		for (i=0;i<=m;i++) distanta[i][0]=i;
		for (j=0;j<=n;j++) distanta[0][j]=j;
		
		for (j=1;j<=n;j++)
			for (i=1;i<=m;i++)
			 {
				if (cuvant1.charAt(i-1)==cuvant2.charAt(j-1)) distanta[i][j]=distanta[i-1][j-1];
											else {
												  min=distanta[i-1][j]+1;
											      if (distanta[i][j-1]+1<min) min=distanta[i][j-1]+1; 
											      if (distanta[i-1][j-1]+1<min) min=distanta[i-1][j-1]+1;
											      
											      distanta[i][j]=min;
											      											   
												  }
				
			 }
		
		
		
		return distanta[m][n];
	}
	
	
	public static Dictionar corectarecuvant(String sir,ArrayList<Dictionar> dictionary)
	{
		int dlmin=Integer.MAX_VALUE;
		int frecvmax=Integer.MIN_VALUE;
		int i,pos=Integer.MAX_VALUE;
		Dictionar result;
		
		int dist;
		for (i=0;i<dictionary.size();i++)
		{	dist=LevenshteinDistance(sir,dictionary.get(i).cuvant);
			
			if (dlmin>dist) {dlmin=dist; pos=i; frecvmax=dictionary.get(i).frecventa;}
							 else if (dlmin==dist) {if (dictionary.get(i).frecventa>frecvmax) {pos=i; frecvmax=dictionary.get(i).frecventa;}
							                        else if ((dictionary.get(i).frecventa==frecvmax) && (i<pos)) {pos=i; frecvmax=dictionary.get(i).frecventa;}
							 						}
		}
		
		dictionary.get(pos).dist=dlmin;
		result=new Dictionar(dictionary.get(pos).cuvant,dictionary.get(pos).frecventa,dictionary.get(pos).dist);
		
		return result; 
		
	}
	
	
	public static String corectaresir(String sir,ArrayList<Dictionar> dictionary)
	{   
		String sirfaraspatii="";
		StringTokenizer s=new StringTokenizer(sir);
		while (s.hasMoreTokens()) sirfaraspatii=sirfaraspatii+s.nextToken();
		
		int n=sirfaraspatii.length(),i,j,l,k;
		Dictionar[][] m=new Dictionar[n][n];
		Dictionar altern;
		
	
		for(i=0;i<n;i++) 
			for(j=i;j<n;j++) m[i][j]=corectarecuvant(sirfaraspatii.substring(i,j+1),dictionary);
								
							   
			
		
		
		for(l=1;l<=n;l++)
			for (i=0;i<n-l+1;i++)
			{j=i+l-1;
			for (k=i;k<j;k++){  StringTokenizer s1=new StringTokenizer(m[i][j].cuvant);
								
			             
								altern=new Dictionar(m[i][k].cuvant+" "+m[k+1][j].cuvant,m[i][k].frecventa+m[k+1][j].frecventa,m[i][k].dist+m[k+1][j].dist);
								StringTokenizer s2=new StringTokenizer(altern.cuvant);
								if (m[i][j].dist>altern.dist) m[i][j]=altern;
                                							  else if (m[i][j].dist==altern.dist) {if (s1.countTokens()>s2.countTokens()) m[i][j]=altern;
                                							  											   								  else if (s1.countTokens()==s2.countTokens())  {if (m[i][j].frecventa<altern.frecventa) m[i][j]=altern;
                                							  											   								  																						  else if (m[i][j].frecventa==altern.frecventa && m[i][j].cuvant.compareTo(altern.cuvant)>0) m[i][j]=altern;
                                							  											   								  												 }
                                							  									  }
								}
			}                                     
	
	return m[0][n-1].cuvant;
		
	}

	
	public static void main(String[] args) {
		
		
	
		String linie;
		ArrayList<Dictionar> dictionary=new ArrayList<Dictionar>();
		
		try
		{
		FileInputStream fisier=new FileInputStream("dict.txt");
		DataInputStream in=new DataInputStream(fisier);
		BufferedReader br=new BufferedReader(new InputStreamReader(in));
		
		linie=br.readLine();
		StringTokenizer st=new StringTokenizer(linie);
		
		while(linie!=null) {
							dictionary.add(new Dictionar(st.nextToken(),Integer.parseInt(st.nextToken())));
							linie=br.readLine(); 
							st=new StringTokenizer(linie);
							}
		
        in.close();
		}catch (Exception e) {}
		
		Scanner s=new Scanner(System.in);
		String sir=s.nextLine();
		System.out.println(corectaresir(sir,dictionary));
		
	
		
	}

}
