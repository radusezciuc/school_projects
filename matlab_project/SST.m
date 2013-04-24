function x=SST(A,b)
%aceasta functie facuta si la laborator(si data efectiv la curs), 
%calculeaza intr-un mod simplu rezultatul unui sistem superior triunghilar,
%prin binecunoscuta metoda gaussiana.
[n,m]=size(A);
b=b(:);
x=zeros(n,1);
x(n)=b(n)/A(n,n);
for i=n-1:-1:1
	x(i)=(b(i)-A(i,i+1:n)*x(i+1:n))/A(i,i);
end
end
