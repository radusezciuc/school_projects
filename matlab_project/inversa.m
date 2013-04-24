function T=inversa(M)
%calcularea inversei unei matrici M, folosind algoritmul lui Gram-Schmidt
%si SST-rezolvarea unui sistem triunghiular superior.


[N,N]=size(M);
[Q,R]=GS(M);
for i=1:N
         e=zeros(N,1);
         e(i)=1;
         t=SST(R,Q'*e);
         [T(:,i)] = t;
end
