function PR=algebraic(numefis,d)

%citirea din fisier text, linie cu linie, dupa care construirea imediata
%a matricei de adiacenta A-fara duplicate, si cu diagonala 0.

f=fopen(numefis,'rt');
N=fscanf(f,'%i',1);
A=zeros(N,N);
for i=1:N
    k=fscanf(f,'%d',1);
    kn=fscanf(f,'%d',1);
    s=fgets(f);
    s=str2num(s);
    for j=1:kn
                if k~=s(j) A(k,s(j))=1;
                end
    end
end
%construirea matricii K,esentiale in calcularea lui M

K=zeros(N,N);
for i=1:N
            for j=1:N
                        K(i,i)=K(i,i)+A(i,j);
            end
end
%construirea lui M,folosindu-ma de functia inversa construita de mine
%pentru a calcula inversa unei matrici, folosind algoritmul Gram-Schmidt
%si rezolvarea unui sistem triunghiular superior
M=inversa(K)*A;
M=M';
I=zeros(N,N);
for i=1:N
         I(i,i)=1;
end
MS=I-d*M;
%calcularea inversei matricii MS, folosindu-ma de acelasi procedeu ca mai
%sus, dar nemaiapeland functia inversa

[Q,R]=GS(MS);
T=zeros(N,N);
for i=1:N
         e=zeros(N,1);
         e(i)=1;
         t=SST(R,Q'*e);
         [T(:,i)] = SST(R,Q'*e);
end
%aplicarea formulei finale,trimiterea lui PR ca rezultat

Y=ones(N,1);
PR=T*(1-d)/N*Y;
fclose(f);
end
                  
