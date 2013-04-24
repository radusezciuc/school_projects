import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.*;

/**
 * Clasa ce reprezinta o solutie partiala pentru problema de rezolvat. Aceste
 * solutii partiale constituie task-uri care sunt introduse in workpool.
 */
class PartialSolution {

	HashMap<String,Integer> hm;			
	ArrayList<HashMap<String,Integer>> v;
	HashMap<String,Float> CuvFrecv;
	String[] sirc;
	int n;
	String doc;
	int inceput;
	int sfarsit;

	//Constructor utilizat pentru efectuarea taskului MAP
	public PartialSolution(String doc, int inceput, int sfarsit){
		hm=new HashMap<String,Integer>();
		this.doc=doc;
		this.inceput=inceput;
		this.sfarsit=sfarsit;
	}

	//Constructor utilizat pentru efectuarea taskului REDUCE1
	public PartialSolution(ArrayList<HashMap<String,Integer>> document,int n,String doc){
		this.v=new ArrayList<HashMap<String,Integer>>();
		v.addAll(document);
		this.doc=doc;
		this.n=n;
	}

	//Constructor utilizat pentru efectuarea taskului REDUCE2
	public PartialSolution(String[] sirc, String doc,HashMap<String,Float> CuvFrecv){
		this.CuvFrecv=new HashMap<String,Float>();
		this.CuvFrecv=CuvFrecv;
		this.doc=doc;
		this.sirc=new String[sirc.length];
		for(int i=0;i<sirc.length;i++)
			this.sirc[i]=sirc[i];
	}

}