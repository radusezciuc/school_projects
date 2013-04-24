import java.util.*;
import java.lang.Math;

public class Formule {              //Clasa folosita pentru implementarea formulelor
	
	public int cardinal(ArrayList<Integer> multime){            //Metoda ce calculeaza cardinalul unui tablou de intregi
		
		int result=0;
		
		for(int i=0;i<multime.size();i++)
			if (multime.get(i)>0) result++;
		
		return result;
			
	}
	
	public double uf(ArrayList<Integer> fore, ArrayList<Integer> imagine){    //Functie ce calculeaza miuf, dupa ce primeste vectorul cu masca de foreground si culorile pixelilor
		
		double result=0;
		
		for(int i=0;i<fore.size();i++)
			if (fore.get(i)>0) result+=imagine.get(i);
		
		result=result/cardinal(fore);
		
		return result;
		
	}
	
	public double ub(ArrayList<Integer> back, ArrayList<Integer> imagine){     //Functie ce calculeaza miub, dupa ce primeste vectorul cu masca de background si culorile pixelilor
			
		double result=0;
			
		for(int i=0;i<back.size();i++)
			if (back.get(i)>0) result+=imagine.get(i);
			
		result=result/cardinal(back);
			
		return result;
			
		}
	
	public double sigmaf(ArrayList<Integer> fore, ArrayList<Integer> imagine, double u){    //Functie ce calculeaza sigma de foreground sau de background, in functie de parametrii primiti, si de miu cel specific
		
		double result=0;
		
		for (int i=0;i<fore.size();i++)
			if (fore.get(i)>0) result+=(u-imagine.get(i))*(u-imagine.get(i));
		
		result=Math.sqrt(result/cardinal(fore));
		
		return result;
		
	}
	//sa nu uit sa modific
	
	public double fstrange1(int x,int i,ArrayList<Integer> imagine,ArrayList<Integer> fore, ArrayList<Integer> back){  //Functie ce calculeaza fu rond, folosita pentru crearea muchiilor intre sursa si noduri
		
		double miuf=uf(fore,imagine),sf=sigmaf(fore,imagine,miuf),miub=ub(back,imagine),sb=sigmaf(back,imagine,miub);
		
		double result=x*(((imagine.get(i)-miuf)/sf)*((imagine.get(i)-miuf)/sf)/2 + Math.log(Math.sqrt(2*Math.PI*sf*sf)))+
				(1-x)*(((imagine.get(i)-miub)/sb)*((imagine.get(i)-miub)/sb)/2 + Math.log(Math.sqrt(2*Math.PI*sb*sb)));
		
		if (result<10) return result;
		else return 10;
		
	}
	
	public int fstrange2(int i,int j,ArrayList<Integer> imagine,int treshold){   //Functie ce calculeaza fp,folosita pentru crearea muchiilor intre nodurile insele
		
		if (Math.abs(imagine.get(i)-imagine.get(j))<=treshold) return 1;
		else return 0;
	}
}
