import java.io.*;
import java.util.*;



public class Main {

	//Functie de ajutor care returneaza valoarea de adevar in functie de rezultatul compararii a doua fisiere
	
	static boolean fisidentice(String fis1,String fis2,int linii){
		
		boolean ok=true;
		
		try{
		FileReader fisier1= new FileReader(fis1);		//Pregatirea fisierului 1 pentru citire
		BufferedReader bf1=new BufferedReader(fisier1); 
		
		FileReader fisier2= new FileReader(fis2);		//Pregatirea fisierului 2 pentru citire
		BufferedReader bf2=new BufferedReader(fisier2);
		bf1.readLine();                               
		bf1.readLine();
		bf1.readLine();
		
		bf2.readLine();								//Sar peste primele linii ("P2, nr coloane, nrlinii, maxval")
		bf2.readLine();
		bf2.readLine();
		
		for(int i=0;i<linii;i++){
			if (!bf1.readLine().equals(bf2.readLine())) {  //Testez daca liniile sunt egale
				ok=false; 
				break;
				}
			}
		}
		
		catch ( FileNotFoundException f )
		{											//Prinderea exceptiilor
			System.out.println("meh");
		}
		catch (IOException e){
			System.out.println("");
		}
		
		
		return ok;
	}
	

	public static void main(String[] args) {
				
	ArrayList<Integer> imagine=new ArrayList<Integer>();		//Initializarea vectorilor in care pastrez valorile fiecarui pixel in parte(culoare, masca foreground, masca background
	ArrayList<Integer> fore=new ArrayList<Integer>();			
	ArrayList<Integer> back=new ArrayList<Integer>();
	
		
	try{
		FileReader fisier= new FileReader("imagine.pgm");     //Deschiderea fisierului pentru citirea efectiva a culorilor pixelilor
		BufferedReader bf=new BufferedReader(fisier);
		
		String sir=bf.readLine();						
		sir=bf.readLine();
		String[] ceva=sir.split(" ");
		int nrcol=Integer.parseInt(ceva[0]),nrlin=Integer.parseInt(ceva[1]);       //Citirea numarului de linii si de coloane din fisier
		
		sir=bf.readLine();
		
		for(int i=0;i<nrcol*nrlin;i++){
			imagine.add(Integer.parseInt(bf.readLine()));
	
		}
		
		
		FileReader fisier2= new FileReader("mask_fg.pgm");    //Deschiderea fisierului pentru citirea efectiva a mastii foreground a pixelilor
		BufferedReader bf2=new BufferedReader(fisier2);
		
		
		
		sir=bf2.readLine();									//Ignorarea primelor linii ale fisierului
		sir=bf2.readLine();
		sir=bf2.readLine();
		
		for(int i=0;i<nrcol*nrlin;i++)
				fore.add(Integer.parseInt(bf2.readLine()));
		
		
		FileReader fisier3= new FileReader("mask_bg.pgm");   //Deschiderea fisierului pentru citirea efectiva a mastii background a pixelilor
		BufferedReader bf3=new BufferedReader(fisier3);
		
		
		sir=bf3.readLine();
		sir=bf3.readLine();									//Ignorarea primelor linii ale fisierului
		sir=bf3.readLine();
		
		for(int i=0;i<nrcol*nrlin;i++)
				back.add(Integer.parseInt(bf3.readLine()));
		
		
		FileReader fisierp= new FileReader("parametri.txt");    //Citirea parametrilor lambda si treshold fin fisierul text "parametri.txt"
		BufferedReader bfp=new BufferedReader(fisierp);
		
		sir=bfp.readLine();
		ceva=sir.split(" ");
		int lambda=Integer.parseInt(ceva[0]);
		int treshold=Integer.parseInt(ceva[1]);
		
		//Gata cu citirea
        System.gc();
		Formule f=new Formule();
		int source=0,sink=0;
		source=nrcol*nrlin;
		sink=nrcol*nrlin+1;
		
		Graf g=new Graf(nrcol,nrlin);						//Initializarea grafului cu numarul de noduri specific:nrcol*nrlin
		for (int i=0;i<imagine.size();i++){
																				//Crearea muchiilor intre nodurile grafului
			if (i-1>=0 && i%nrcol!=0 && (!g.exmuchie(i,i-1))) 
				g.addedges(i-1,i,lambda*f.fstrange2(i-1,i,imagine,treshold));			
			if (i+1<imagine.size() && (i+1)%nrcol!=0 && (!g.exmuchie(i,i+1))) 
				g.addedges(i+1,i,lambda*f.fstrange2(i,i+1,imagine,treshold));		
			
			if (i-nrcol>=0 && (!g.exmuchie(i,i-nrcol))) 
				g.addedges(i-nrcol,i,lambda*f.fstrange2(i-nrcol,i,imagine,treshold));   	
			
			if (i+nrcol<imagine.size() && (!g.exmuchie(i,i+nrcol))) 
				g.addedges(i,i+nrcol,lambda*f.fstrange2(i,i+nrcol,imagine,treshold));   
			
			
			g.addedges(source,i,f.fstrange1(1,i,imagine,fore,back));		//Adaugarea muchiei intre nodul curent si sursa, cu capacitatea calculata dupa formula specifica
			g.addedges(sink,i,f.fstrange1(0,i,imagine,fore,back));			//Acelasi proces si pentru drena
			
		}		
        System.gc();

		double maxflow=g.maximum_flow(source, sink);								//Apelarea functiei ce calculeaza maximum_flow(echivalenta cu energia minima a configuratiei)
		Vector<Boolean> mneh=new Vector<Boolean>();
		mneh=g.min_cut(source);                            //Calcularea taieturii minime ale grafului, si obtinerea vectorului final cu pixelii apartinand foregroundului/backgroundului
        System.gc();

		FileWriter fstream = new  FileWriter("segment.pgm");		//Scrierea in fisierul text
		BufferedWriter out = new  BufferedWriter(fstream);
		
		out.write("P2\n");
	    out.write(nrcol+ " "+nrlin+"\n");
		out.write(255 + "\n");
		for (int i = 0; i<nrcol*nrlin; i++)
			if  (mneh.get(i))
				out.write(0 +" \n");
		else
			out.write(255 +" \n");
		  		  
		out.close();

		//boolean ok=fisidentice("segment.pgm","example.pgm",nrlin*nrcol);       //testarea suplimentara a corectitudinii rezultatelor
		//System.out.println(ok);
        System.gc();

		System.out.println(maxflow);
		
	}
	catch ( FileNotFoundException f )				//prinderea exceptiilor
	{
		System.out.println("meh");
	}
	catch (IOException e){
		System.out.println("");
	}
	}
}
