
public class Student {

	String nume;
	int varsta;
	
	/**
	 * Constructor ce initializeaza un student
	 * @param nume
	 * @param varsta
	 */
	
	public Student(String nume, int varsta)
	{
		this.nume=nume;
		this.varsta=varsta;
	}
	
	/** Suprascrierea metodei equals pentru Student
	 * @param o obiectul cu care comparam pe Student
	 * @return true daca numele si varsta lor sunt identice, altfel false
	 */
	@Override
	public boolean equals(Object o)
	{
		if (o instanceof Student)
		{Student s=(Student)o;
		 if ((s.varsta==this.varsta) && (s.nume.equals(this.nume)) ) return true;
		 else return false;
		}
	return false;	
	}
	
	/**
	 * Suprascrierea hashCode conform metodei prezentate
	 */
	@Override
	public int hashCode(){
	 	          int hash = 17;
	 	          hash = 37 * hash + varsta +  nume.hashCode();
	 	   return hash;
	}
	
}
