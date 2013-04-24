import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.*;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

/**
 * Clasa ce reprezinta un thread worker.
 */
class Worker extends Thread {

	WorkPool wp;
	CyclicBarrier b;
	public Worker(WorkPool wp){
		this.wp=wp;
		b=new CyclicBarrier(wp.nThreads);
	}

	//Functie necesara pentru transformarea unui bit intr-un caracter
	public static char bittochar(byte[] b){
		String s=new String(b);
		char[] c=s.toCharArray();
		return c[0];
	}

	//Functie necesara pentru returnarea unei chei in functie de valoarea ei
	public static String getKeyFromValue(HashMap<String,Float> hm, int value) {
		for (String o:hm.keySet()) 
			if (hm.get(o)==value) 
				return o;
		return null;
	}
	/**
	 * Procesarea unei solutii partiale. Aceasta poate implica generarea unor
	 * noi solutii partiale care se adauga in workpool folosind putWork().
	 * Daca s-a ajuns la o solutie finala, aceasta va fi afisata.
	 */

	//Rezolvarea unui task de tip Map
	void processPartialSolution1(PartialSolution ps) {

		//Initializarea unei structuri de date auxiliare pentru retinerea datelor temporare
		HashMap<String,HashMap<String,Integer>> aux=new HashMap<String,HashMap<String,Integer>>();
		try{

			//Pregatirea pentru citirea din fisier text
			FileInputStream f = new FileInputStream(ps.doc);
			DataInputStream d = new DataInputStream(f);

			boolean primulcuv=false;
			String cuvant="";
			byte[] b=new byte[1];
			char car;

			//Daca nu este prima secventa de octeti dintr-un document
			if (ps.inceput>=2){

				//Sar la bucata de octeti care ma intereseaza
				d.skipBytes(ps.inceput-2);

				//Citesc primul caracter.
				b[0]=d.readByte();
				car=bittochar(b);

				//Daca bucata mea de octeti incepe in mijlocul unui cuvant
				while(Character.isLetter(car) && car!=' '){ 
					b[0]=d.readByte();
					car=bittochar(b);
					ps.inceput++;
				}
			}
			else{
				b[0]=d.readByte();
				car=bittochar(b);
			}

			boolean finalcuv=false;
			boolean puterea=false;//Variabila care imi spune daca trebuie sa termin si ultimul cuvant din secventa
			int ok=0;

			//Cat timp mai sunt octeti de citit din secventa mea de octeti 
			while (ps.inceput<=ps.sfarsit || puterea){	
				if (Character.isLetter(car) && car!=' '){ //Daca e litera, atunci citesc si adaug la cuvant
					finalcuv=false;
					cuvant=cuvant+car;
					b[0]=d.readByte();
					car=bittochar(b);
					ps.inceput++;
					finalcuv=true;
					puterea=true;
				}
				else {		//Daca nu, termin cuvantul si-l adaug la structura de date
					if (finalcuv) {
						cuvant=cuvant.toLowerCase();
						if (ps.hm.containsKey(cuvant))
							ps.hm.put(cuvant, ps.hm.get(cuvant).intValue()+1);
						else ps.hm.put(cuvant, 1);
						finalcuv=false; 
						ok++;
					}
					b[0]=d.readByte();
					car=bittochar(b);
					ps.inceput++;
					cuvant="";
					puterea=false;
				}
			}		
		}
		catch (Exception ex) {
			System.out.println("Nu s-a gasit fisierul");
		}

		aux.put(ps.doc, ps.hm);
		wp.l.add(aux);		//Adaugarea in WorkPool a rezultatului
	}

	
	//Rezolvarea task-ului Reduce1
	void processPartialSolution2(PartialSolution ps) {
		int i=0,j=0,numar=0,aux;

		HashMap<String,Float> hm=new HashMap<String,Float>();

		ArrayList<Integer> a=new ArrayList<Integer>();

		//Adunarea numarului de aparitii a cuvintelor din toate secventele documentului si adaugarea lor
		//intr-o noua structura
		for(i=0;i<ps.v.size();i++)
			for(String key:ps.v.get(i).keySet())
			{	if (hm.containsKey(key)) hm.put(key,(float) hm.get(key).intValue()+ps.v.get(i).get(key).intValue());
			else hm.put(key,(float) ps.v.get(i).get(key).intValue());
			}

		//Adaugarea valorilor aparitiilor cuvintelor intr-un vector
		for(String key:hm.keySet()){
			j=hm.get(key).intValue();
			a.add(j);
			numar+=j;
		}
		//Sortarea acestui vector pentru a afla care este al n-lea cuvant care trebuie adaugat in lista finala
		for (i=0;i<a.size()-1;i++)
			for(j=i+1;j<a.size();j++)
				if(a.get(i)<a.get(j)) {
					aux=a.get(i);
					a.set(i,a.get(j));
					a.set(j, aux);
				}
		if (ps.n<=a.size()) aux=a.get(ps.n-1);
		else aux=a.size();

		i=1;
		//Scoaterea cuvintelor care nu sunt relevante
		while(i<aux){
			String key = getKeyFromValue(hm,i);
			if (key!=null) hm.remove(key);
			else i++;
		}

		//Calcularea frecventelor de aparitie
		for(String key:hm.keySet()){
			hm.put(key,(float) hm.get(key).intValue()/numar*100);
		}
		
		//Adaugarea rezultatelor intr-o noua structura de date
		wp.a.put(ps.doc, hm);
	}

	//Efectuarea ultimului task: Reduce2
	void processPartialSolution3(PartialSolution ps) {
		boolean ok=true;

		HashMap<String,Float> hm=new HashMap<String,Float>();
		ok=true;
		
		//Selectarea documentelor care contin toate cuvintele cautate
		for(int i=0;i<ps.sirc.length;i++)
			if (!ps.CuvFrecv.containsKey(ps.sirc[i]))
				ok=false;
		if (ok==true){
			for(int i=0;i<ps.sirc.length;i++)
				hm.put(ps.sirc[i],ps.CuvFrecv.get(ps.sirc[i]));
			
			//Punerea lor in WorkPool, in structura de date finala
			wp.result.put(ps.doc, hm);
		}

	}


	public void run() {

		//System.out.println("Thread-ul worker " + this.getName() + " a pornit...");
		while (true) {
			PartialSolution ps = wp.getWork();
			if (ps == null)
				break;
			if(wp.tip.equals("map"))
				processPartialSolution1(ps);
			if(wp.tip.equals("reduce")){
				processPartialSolution2(ps);
			}
			if(wp.tip.equals("reduce2")){
				processPartialSolution3(ps);
			}

		}
		//System.out.println("Thread-ul worker " + this.getName() + " s-a terminat...");
	}


}