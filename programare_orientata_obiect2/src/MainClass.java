import java.util.*;
/**
 * 
 * @author Sezciuc Radu
 *
 */

public class MainClass {

	
	public static void main(String[] args) {
		   Random randomGenerator = new Random();

		 
		   MyHashMap< Student, Integer > hashStudent = new MyHashMapImpl< Student, Integer >(1003);
		   ArrayList<Student> students = new ArrayList<Student>();
		   {
		   for( int i = 0; i < 1000; i++){
			    students.add(new Student(Integer.toString(randomGenerator.nextInt()), randomGenerator.nextInt()));
		   }	
		   
		   for( int i = 0; i < 1000; i++ ){ 
			    hashStudent.put(students.get(i), randomGenerator.nextInt());
		   }
		   
		   double start = System.currentTimeMillis();
		   for(int i=0;i<1000;i++) {
			   hashStudent.get(students.get(i));
		   }
		   System.out.println( System.currentTimeMillis() - start );
		   }
		   
		   
		   MyHashMap< LazyStudent, Integer > hashLazyStudent = new MyHashMapImpl< LazyStudent, Integer >(1003);
		   ArrayList<LazyStudent> lazystudents = new ArrayList<LazyStudent>();
		   {
		   for( int i = 0; i < 1000; i++){
			    lazystudents.add(new LazyStudent(Integer.toString(randomGenerator.nextInt()), randomGenerator.nextInt()));
		   }	
		   
		   for( int i = 0; i < 1000; i++ ){ 
			    hashStudent.put(lazystudents.get(i), randomGenerator.nextInt());
		   }
		   
		   double start = System.currentTimeMillis();
		   for(int i=0;i<1000;i++) {
			   hashLazyStudent.get(lazystudents.get(i));
		   }
		   System.out.println( System.currentTimeMillis() - start );
		   }
	}
}