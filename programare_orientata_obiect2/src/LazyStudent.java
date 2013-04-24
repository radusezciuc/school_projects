
public class LazyStudent extends Student {
	
	/**
	 * Constructor ce initializeaza LazyStudent
	 * @param nume
	 * @param varsta
	 */
	 public LazyStudent(String nume, int varsta) {
	      super(nume, varsta);
  }
	 /**
	  * Suprascrierea hashCode, astfel incat acesta sa fie constant
	  */
	 @Override
	   public int hashCode(){
		      return 0;      
	   }

}
