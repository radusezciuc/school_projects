import java.util.LinkedList;
import java.util.*;

/**
 * Clasa ce implementeaza un "work pool" conform modelului "replicated workers".
 * Task-urile introduse in work pool sunt obiecte de tipul PartialSolution.
 *
 */
public class WorkPool {
	int nThreads; // nr total de thread-uri worker
	String tip;		//tipul WorkPool-ului: map,reduce sau reduce2
	ArrayList<HashMap<String,Integer>> v;    
	HashMap<String,HashMap<String,Float>> result;		//Structura de date necesara pentru salvarea rezultatelor 
														//finale
	HashMap<String,HashMap<String,Float>> a;			//Structura de date necesara pentru salvarea rezultatelor
														//din REDUCE1
	ArrayList<HashMap<String,HashMap<String,Integer>>> l; //Structura de date necesara pentru salvarea rezultatelor
															// MAP
	int nWaiting = 0; // nr de thread-uri worker care sunt blocate asteptand un task
	public boolean ready = false; // daca s-a terminat complet rezolvarea problemei 

	LinkedList<PartialSolution> tasks = new LinkedList<PartialSolution>();

	/**
	 * Constructor pentru clasa WorkPool.
	 * @param nThreads - numarul de thread-uri worker
	 */
	public WorkPool(int nThreads,String tip) {
		v=new ArrayList<HashMap<String,Integer>>();
		a=new HashMap<String,HashMap<String,Float>>();
		l=new ArrayList<HashMap<String,HashMap<String,Integer>>>();
		result=new HashMap<String,HashMap<String,Float>>();
		this.nThreads = nThreads;
		this.tip=tip;
	}

	/**
	 * Functie care incearca obtinera unui task din workpool.
	 * Daca nu sunt task-uri disponibile, functia se blocheaza pana cand 
	 * poate fi furnizat un task sau pana cand rezolvarea problemei este complet
	 * terminata
	 * @return Un task de rezolvat, sau null daca rezolvarea problemei s-a terminat 
	 */
	public synchronized PartialSolution getWork() {
		if (tasks.size() == 0) { // workpool gol
			nWaiting++;
			/* condtitie de terminare:
			 * nu mai exista nici un task in workpool si nici un worker nu e activ 
			 */
			if (nWaiting == nThreads) {
				ready = true;
				/* problema s-a terminat, anunt toti ceilalti workeri */
				notifyAll();
				return null;
			} else {
				while (!ready && tasks.size() == 0) {
					try {
						this.wait();
					} catch(Exception e) {e.printStackTrace();}
				}

				if (ready)
					/* s-a terminat prelucrarea */
					return null;

				nWaiting--;

			}
		}
		return tasks.remove();

	}


	/**
	 * Functie care introduce un task in workpool.
	 * @param sp - task-ul care trebuie introdus 
	 */
	synchronized void putWork(PartialSolution sp) {
		//System.out.println("WorkPool - adaugare task: " + sp);
		tasks.add(sp);
		/* anuntam unul dintre workerii care asteptau */
		this.notify();

	}


}