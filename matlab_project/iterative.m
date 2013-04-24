function PR=iterative(numefis,d,eps)

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
%construirea lui M, efectiv dupa formula gasita in documentatia temei
M=inv(K)*A;
M=M';
for i=1:N
         R(i)=1/N;
end
I=ones(N,1);
R=R';
RS=d*M*R+(1-d)/N*I;
c=0;
%instructiunea repetitiva ce calculeaza termenul final al recurentei, pana
%la indeplinirea conditiei


while max(abs(RS-R))>=eps
                    c=c+1;
                    R=RS;
                    RS=d*M*R+(1-d)/N*I;
end
%returnarea lui PR ca rezultat final
PR=RS;
fclose(f);
end
    
