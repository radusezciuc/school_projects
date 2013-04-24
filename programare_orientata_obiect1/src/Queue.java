import java.util.ArrayList;
/**
 * 
 * @author Sezciuc Radu
 *
 */
	public class Queue  {
	 
	 ArrayList<Nod> list;
	 
	 /**Constructor al cozii
	  * 
	  * @param n:numarul de elemente alocat pentru vector
	  */
	 
	 public Queue(int n)
	 {
	  list= new ArrayList<Nod>(n);
	 }
	 
	 /**Metoda ce elimina un element din coada
	  * 
	  * @return elementul eliminat din coada
	  */
	
	 public Nod pop() 
	 {
	  Nod aux = list.get(0);
	  list.remove(0);
	  return aux;
	 }

	 /**Metoda ce adauga un element in coada
	  * 
	  * @param nod:nodul de adaugat in coada
	  */
	 public void push(Nod nod) 
	 {
	 int i=0;
	 if (list.size()!=0) while ((i<list.size()) && (nod.frec>list.get(i).frec)) //adauga nodul in coada de prioritati la locul corespunzator acestuia,astfel incat coada sa fie ordonata in permanenta dupa frecventele de aparitie ale caracterelor
		 				 i++;
	 list.add(i,nod);
	 }

	 /**Metoda ce determina marimea cozii
	  * 
	  * @return marimea cozii
	  */
	 
	 public int size() 
	 {
	  return list.size();
	  
	 }

	 /**Metoda ce determina daca coada e goala sau nu
	  * 
	  * @return adevarat daca coada este goala,altfel fals
	  */
	 
	 public boolean isEmpty() 
	 {
	  if (list.size()==0) return true;
	  return false;
	 }

	
	}