import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.*;
import java.util.concurrent.CyclicBarrier;

public class Main {

	public static void main(String[] args) {

		int threads = Integer.parseInt(args[0]);
		BufferedWriter out=null;
		try {
			//Initializari pentru fisierele din care citim/scriem
			File f=new File(args[1]);
			Scanner s=new Scanner(f);
			FileWriter h=new FileWriter(args[2]);
			out=new BufferedWriter(h);
			
			//Citirea din fisierul de intrare
			int nc=s.nextInt();

			String[] sirc=new String[nc];
			for (int i=0;i<nc;i++) {
				sirc[i]=s.next();
			}

			int d=s.nextInt();
			int n=s.nextInt();
			int x=s.nextInt();
			int nd=s.nextInt();

			String[] sird=new String[nd];
			for (int i=0;i<nd;i++) {
				sird[i]=s.next();
			}

			//Crearea primului WorkPool - necesar pentru functia Map.
			WorkPool wp=new WorkPool(threads,"map");

			//Aplicam Map tuturor documentelor
			for(int doc=0;doc<sird.length;doc++){	
				int marimef,i,w;
				File g=new File(sird[doc]);
				marimef=(int)g.length();

				//Crearea vectorului de solutii partiale necesare pentru Map
				PartialSolution[] ps=new PartialSolution[(int)g.length()/d+1];	
				i=0; w=0;
				while(marimef>0){
					if(marimef>=d) {
						marimef=marimef-d;
						ps[w]=new PartialSolution(sird[doc],i,i+d-1);
						wp.putWork(ps[w]);      //Umplerea workpoolului cu taskuri
						i=i+d;
						w++;
					}
					else {ps[w]=new PartialSolution(sird[doc],i,(int)g.length());
					wp.putWork(ps[w]);			//Umplerea workpoolului cu taskuri
					marimef=0;
					}	
				}

			}	

			//Initializarea thread-urilor si distribuirea lor pentru maparea documentelor
			Worker maperi[]= new Worker[threads];
			for(int w=0;w<threads;w++){
				maperi[w]=new Worker(wp);
			}
			for(int w=0;w<threads;w++){
				maperi[w].start();
			}
			for(int w=0;w<threads;w++){
				try {
					maperi[w].join();
				} catch(Exception e) {
					System.out.println("exceptie1");
				}
			}
			
			//Initializarea unui nou WorkPool pentru realizarea taskurilor de tip reduce1
			WorkPool wp2=new WorkPool(threads,"reduce");

			//Pentru fiecare document, realizarea stivei de solutii partiale pentru reduce1
			for(int doc=0;doc<sird.length;doc++){

				ArrayList<HashMap<String,Integer>> nume=new ArrayList<HashMap<String,Integer>>();
				for(int i=0;i<wp.l.size();i++){
					if (wp.l.get(i).containsKey(sird[doc])) 
						nume.add(wp.l.get(i).get(sird[doc]));
				}
				PartialSolution ps=new PartialSolution(nume,n,sird[doc]);

				wp2.putWork(ps);
			}

			//Initializarea si distribuirea thread-urilor pentru rezolvarea efectiva a reduce1
			Worker reduceri[]=new Worker[threads];
			for(int i=0;i<threads;i++){
				reduceri[i]=new Worker(wp2);
			}
			for(int i=0;i<threads;i++){
				reduceri[i].start();
			}
			for(int i=0;i<threads;i++){
				try {
					reduceri[i].join();
				} catch(Exception e) {
					System.out.println("exceptie2");
				}
			}

			//Initializarea unui nou WorkPool pentru realizarea taskurilor de tip reduce2
			WorkPool wp3=new WorkPool(threads,"reduce2");

			for(int doc=0;doc<sird.length;doc++){
				if (wp2.a.containsKey(sird[doc])){
					PartialSolution ps=new PartialSolution(sirc,sird[doc],wp2.a.get(sird[doc]));
					wp3.putWork(ps);
				}
			}
			//Initializarea si distribuirea thread-urilor pentru rezolvarea efectiva a reduce2
			Worker reduceri2[]=new Worker[threads];
			for(int i=0;i<threads;i++){
				reduceri2[i]=new Worker(wp3);
			}
			for(int i=0;i<threads;i++){
				reduceri2[i].start();
			}
			for(int i=0;i<threads;i++){
				try {
					reduceri2[i].join();
				} catch(Exception e) {
					System.out.println("exceptie2");
				}
			}

			//Scrierea in fisier text a rezultatelor finale
			out.write("Rezultate pentru: (");
			for(int i=0;i<sirc.length-1;i++){
				out.write(sirc[i]+", ");
			}
			out.write(sirc[sirc.length-1]+")");
			out.write("\n\n");
			DecimalFormat df = new DecimalFormat("#.00"); //Afisarea cu formatul cerut
			int k=0;
			for(int doc=0;doc<sird.length;doc++){
				if(wp3.result.containsKey(sird[doc]) && k<x){ //Afiseaza pentru cel mult x documente relevante
					k++;
					out.write(sird[doc]+" (");
					for(int i=0;i<sirc.length-1;i++){
						if (wp3.result.get(sird[doc]).containsKey(sirc[i])){
							float aux=wp3.result.get(sird[doc]).get(sirc[i]);
							aux=aux*100;
							aux=(int)aux;
							aux=aux/100;
							out.write(df.format(aux)+", ");
						}
					}
					float aux=wp3.result.get(sird[doc]).get(sirc[sirc.length-1]);
					aux=aux*100;
					aux=(int)aux;
					aux=aux/100;
					if(doc<sird.length-1)
						out.write(df.format(aux)+")\n");
					else out.write(df.format(aux)+")");
				}
			}
		}
		catch (FileNotFoundException ex){
			System.out.println(ex.getMessage());
		}
		catch (IOException e){
			System.out.println(e.getMessage());
		}
		finally {
			if(out!=null){
				try{
					out.close();  //Inchiderea fisierului text pentru scriere
				}
				catch(IOException e){

				}
			}
		}
	}
}