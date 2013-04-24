import java.util.ArrayList;
/**
 * 
 * @author Sezciuc Radu
 *
 */
public class Stack {
	 ArrayList<Nod> list;
	 
	 /**Constructor ce initializeaza stiva
	  * 
	  * @param n:numarul de elemente de alocat in stiva
	  */
	 
	 public Stack(int n)
	 {
	  list= new ArrayList<Nod>(n);
	 }
	 
	 /**Metoda ce scoate un element din stiva
	  * 
	  * @return elementul eliminat din stiva
	  */
	 
	 public Nod pop() 
	 {
	  Nod aux = list.get(list.size()-1);
	  list.remove(list.size()-1);
		 return aux;
	 }

	 /**Metoda ce adauga un nou element in stiva
	  * 
	  * @param nod:elementul de adaugat in stiva
	  */
	 
	 public void push(Nod nod) 
	 {
	   list.add(list.size(),nod);
	 }
	 
	 /**Metoda ce determina marimea stivei
	  * 
	  * @return marimea stivei
	  */
	
	 public int size() 
	 {
	  return list.size();
	 }

	 /**Metoda ce determina daca stiva este goala sau nu
	  * 
	  * @return adevarat daca stiva e goala, altfel fals
	  */
	 
	 public boolean isEmpty() 
	 {
	  return list.isEmpty();
	 }

	
	 

	}