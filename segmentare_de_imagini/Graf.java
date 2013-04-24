import java.util.*;

public class Graf {
	
	public HashMap<Integer,ArrayList<Muchii>> edges;     //Structura HashMap ce retine muchiile grafului
	int size;												//Camp al grafului ce retine marimea acestuia
	
	public Graf(int nrcol,int nrlin){                 //Constructor ce initializeaza campurile grafului
		
		this.size=nrcol*nrlin+2;	
		this.edges=new HashMap<Integer,ArrayList<Muchii>>();   		
		
		for(int i=0;i<size;i++){
			edges.put(i,new ArrayList<Muchii>());
		}
		
	}
	
	public void addedges(int x,int y, double c){		//Metoda ce are rolul de a adauga o noua muchie in graf, dupa ce primeste nodurile capete ale ei si capacitatea ei
		
		edges.get(x).add(new Muchii(y,c));
		edges.get(y).add(new Muchii(x,c));		
		
	}
	
	public ArrayList<Muchii> neighbors(int x){    //Metoda ce returneaza toti vecinii nodului dat ca parametru
		
		return edges.get(x);
	}
	
	public Muchii muchie(int x,int y){        //Metoda ce-mi returneaza muchia grafului in functie de nodurile sale capete
		
		ArrayList<Muchii> muchii=edges.get(x);
		Muchii m=null;
		
		for(int i=0;i<muchii.size();i++)
			if (muchii.get(i).y==y) m=muchii.get(i);
		
		return m;
		
	}
	
	public boolean exmuchie(int x,int y){      //Metoda ce imi arata daca exista muchie de la nodul x la nodul y
		
		if (muchie(x,y)!=null) return true;
		else return false;
	}
	
	Vector<Integer> bfs(int source,int sink){        //Metoda ce reprezinta Breadth First Search. Ea returneaza calea dintre nodurile date ca parametru
		
		Vector<Integer> parent=new Vector<Integer>();       //Initializarea vectorului de parinti si a cozii necesare pentru calcularea BFS
		Queue<Integer> q=new LinkedList<Integer>();
		
		for(int i=0;i<size;i++){
			parent.add(-1);
		}
		
		int u;
		q.add(source);				//Adaugarea nodului sursa in coada
		
		while (!q.isEmpty() && parent.get(sink)==-1){      //Cat timp sunt elemente in coada si calea nu a ajuns inca la drena
			u=q.peek();
			for(int i=0;i<neighbors(u).size();i++){
			ArrayList<Muchii> list=edges.get(u);        
			int v=list.get(i).y;
			if (list.get(i).c>0 && (parent.get(v)==-1)){
					parent.set(v,u);                                   //Construirea vectorului de parinti pentru marcarea caii de la sursa la drena
					q.add(v);											//Adaugarea nodului vecin in coada
					}
			}
			q.poll();
			if (parent.get(sink)!=-1) 
				break;
		}
		
		if (parent.get(sink)==-1)      
			return new Vector<Integer>();
	    
		Vector<Integer> path=new Vector<Integer>();      //Vectorul unde pastrez calea aflata de la sursa la drena
		int node=sink;
		
		while (node!=source){
			path.add(node);
			node=parent.get(node);
		}
		path.add(source);
		return path;	
	}
	
	
	double saturate_path(Vector<Integer> path){    //Metoda ce satureaza calea de la sursa la drena
		
		int i;
		double maxf=Integer.MAX_VALUE;
		double c=0;
	
		
		for(i=path.size()-1;i>0;i--){
			c=muchie(path.get(i),path.get(i-1)).c;    //Calcularea valorii minime a capacitatii din cale
			if (c<maxf) maxf=c;
		}
		
		for(i=path.size()-1;i>0;i--)
			muchie(path.get(i),path.get(i-1)).c-=maxf;         //Saturarea propriu zisa a caii
		
		for(i=path.size()-1;i>0;i--)
			muchie(path.get(i-1),path.get(i)).c-=maxf;        //Se repeta saturarea in sens opus deoarece graful este neorientat
		
		return maxf;
	}
	
	
	double maximum_flow(int source, int sink){       //Metoda ce calculeaza maximum flow (echivalenta energiei minime a configuratiei)
		
		Vector<Integer> path=new Vector<Integer>();
		double valoare=0;
		
		while(true){
			path=bfs(source,sink);                     //Aflarea unei cai intre sursa si drena
			if (path.size()==0) break;
			else valoare+=saturate_path(path);         //Calcularea energiei totale
		}
		
		return valoare;
	}
	

	Vector<Boolean> min_cut(int source){        //Metoda ce afla taietura minima
		
		Vector<Boolean> in_queue=new Vector<Boolean>();         //Vectorul boolean in care se va salva starea pixelilor(foreground==false, background==true)
		Queue<Integer> q=new LinkedList<Integer>();
		for (int i=0;i<size;i++){
			in_queue.add(false);                         //Initializarea vectorului
		}
		
		int u;
		q.add(source);
		in_queue.set(source, true);
		
		while (!q.isEmpty()){                       //aplicarea unui nou BFS modificat pentru a afla starea pixelilor
			u=q.poll();
			for(int i=0;i<size;i++){
				if (exmuchie(u,i) && muchie(u,i).c>0 && in_queue.get(i)==false){      
					in_queue.set(i,true);
					q.add(i);
				}
			}
		}
		return in_queue;
		}
}
