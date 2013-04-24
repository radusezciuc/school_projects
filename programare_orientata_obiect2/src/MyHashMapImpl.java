import java.util.*;
/**
 * 
 * @author Sezciuc Radu
 *
 * @param <K>  Tipul cheii pentru HashMap
 * @param <V>  Tipul valorii pentru HashMap
 */
public class MyHashMapImpl<K,V> implements MyHashMap<K,V> {
	
		ArrayList<Bucket<K,V>> listabucket ;     //lista de bucketuri
		int n;									 //numarul de bucketuri
		
		/**
		 * Constructor ce creeaza vectorul de bucketuri, implementat cu ajutorul ArrayList,si initializeaza numarul de bucketuri
		 * @param nrbucketuri numarul de bucketuri pentru care este alocat vectorul
		 */
		
		public MyHashMapImpl(int nrbucketuri)						
		{
		       listabucket=new ArrayList<Bucket<K,V>>(nrbucketuri);
		       for( int i = 0; i < nrbucketuri; i++ ){
		    	   listabucket.add( new BucketsImpl() );			//adauga bucket
		       }
		       n = 0;												
		}
		
		/**
		 * Metoda ce translateaza hashCodeul obtinut pentru cheia trimisa ca parametru, in indicele pentru vectorul de bucketuri
		 * @param key cheia primita ca parametru ce urmeaza a fi translatata
		 * @return indicele pentru vectorul de bucketuri
		 */
		
		public int bucketcode(K key)
		{
		
			return Math.abs(key.hashCode())%listabucket.size();			//translateaza hashCode
		
		}
		
		/**Metoda ce returneaza valoarea unui Entry cautat in HashMap, in functie de cheia acestuia
		 * @param key cheia entryului
		 * @return valoarea Entryului cautat, sau null daca acesta nu exista
		 */
		
		@Override
		public V get(K key) 
		{
			
			int i=0;
			while ( i<listabucket.get(bucketcode(key)).getEntries().size() )		
			{
				if (listabucket.get(bucketcode(key)).getEntries().get(i).getKey().equals(key))			//daca exista acest entry returneaza valoarea lui
								return listabucket.get(bucketcode(key)).getEntries().get(i).getValue();
				i++;
			}
			return null;			//altfel,returneaza null
		}
		
		/**Metoda ce adauga un nou entry
		 * @param key cheia entryului ce trebuie adaugat
		 * @param value valoarea entryului ce trebuie adaugat
		 * @return valoarea entryului ce a fost actualizat, sau null daca a fost adaugat un nou entry
		 */
		
		@Override
		public V put(K key, V value) 
		{	int i=0;
			V val=null;
			while (i<listabucket.get(bucketcode(key)).getEntries().size())
		{
				if (listabucket.get(bucketcode(key)).getEntries().get(i).getKey().equals(key))    //daca exista acest entry, actualizeaza-l
				{val = listabucket.get(bucketcode(key)).getEntries().get(i).getValue();
				  ((ArrayList<Entry<K, V>>)listabucket.get(bucketcode(key)).getEntries()).set(i,new EntryImpl(key,value));					
				  return val;
				}
			i++;
		}
			((ArrayList<Entry<K, V>>)listabucket.get(bucketcode(key)).getEntries()).add(new EntryImpl(key,value));  	//altfel, creaza-l cu parametrii dati
			n++;
		    return val;
		}

		/**Metoda ce permite stergerea unui entry din HashMap
		 * @param key cheia entryului
		 * @return valoarea entryului ce a fost scos, sau null daca acesta nu exista in HashMap
		 */
		
		@Override
		public V remove(K key) 
		{
			int i=0;
			V val=null;
			while (i<listabucket.get(bucketcode(key)).getEntries().size())
			{
				if (listabucket.get(bucketcode(key)).getEntries().get(i).getKey().equals(key))
					{val=listabucket.get(bucketcode(key)).getEntries().get(i).getValue();
					 ((ArrayList<Entry<K, V>>)listabucket.get(bucketcode(key)).getEntries()).remove(i);	 //scoate, daca exista
					 n=n-1;
					 break;
					}
				i++;
			}
			return val;		//returneaza null, daca entryul nu exista, sau valoarea entryului daca acesta a fost scos cu succes
		}

		/**Metoda ce calculeaza marimea vectorului de bucketuri
		 * @return numarul de bucketuri actuale
		 */
		
		@Override
		public int size() {
			return n;
		}
		
		/**Metoda ce intoarce vectorul de bucketuri
		 * @return listabucket vectorul de bucketuri
		 */
		
		@Override
		public List<? extends MyHashMap.Bucket<K, V>> getBuckets() {
			return listabucket; 
		}
		
		/**
		 * @author Sezciuc Radu
		 *
		 */
		class EntryImpl implements Entry< K, V >{

		     K cheie;
		     V val;
	   /**
	    * Constructor pentru tipul EntryImpl
	    * @param key K   informatie pentru membrul cheie
	    * @param it V   informatie pentru membrul item
	    */	   
	   public EntryImpl( K key, V value ){
		      cheie = key;
		      val = value;
	   }
	
	   /**
	    * Metoda getKey
	    * @return cheia K intrarii*/
	   @Override
	   public K getKey() 
	   {
			  return this.cheie;
	   }

	   /**
	    * Metoda getValue
	    * @param valoarea V intrarii
	    */
	   
	   @Override
	   public V getValue() 
	   {
		  	  return this.val;
	   }
		   
	   }
		/**
		 * Bucket al tabelei de dispersie.
		 * 
		 * @author Mihnea
		 *
		 * @param <K> tipul cheii
		 * @param <V> tipul valorii
		 */
	   class BucketsImpl implements Bucket< K, V >{

		     ArrayList<Entry<K, V>> lista;
		
		     public BucketsImpl()
		     {
			        lista = new ArrayList<Entry<K, V>>();
		     }
		     
		     /**
				 * Intoarce lista de intrari continute de acest bucket.
				 * 
				 * @return lista de intrari
				 */
			  @Override
	          public List<? extends Entry<K, V>> getEntries() 
	          {
			         return lista;
		    
	          }
		   
	   }

	}


