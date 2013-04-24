function numeout=tema2(numefis,d,eps)

PR1=iterative(numefis,d,eps);
PR2=algebraic(numefis,d);
numeout=strcat(numefis,'.out');
f=fopen(numeout,'wt');
[N,M]=size(PR1);
fprintf(f,'%i\n',N);
for i=1:N
         fprintf(f,'%f\n',PR1(i));
end
fprintf(f,'\n');
for i=1:N
         fprintf(f,'%f\n',PR2(i));
end

g=fopen(numefis,'rt');
x=fgets(g);
for i=1:N
         x=fgets(g);
end
val1=fscanf(g,'%f',1);
val2=fscanf(g,'%f',1);
fclose(g);

a=1/(val2-val1);
b=(-val1)/(val2-val1);


PR2S=PR2;
for i=1:N-1
         for j=i+1:N
                    if PR2S(i)<PR2S(j)
                                    aux=PR2S(j);
                                    PR2S(j)=PR2S(i);
                                    PR2S(i)=aux;
                    end
         end
end
fprintf(f,'\n');

for i=1:N
         for j=1:N
                  if PR2S(i)==PR2(j)
                                    ind(i)=j;
                  end
         end
end
             

for i=1:N
         fprintf(f,'%i %i ',i,ind(i));
         if PR2S(i)<val1 
                        fprintf(f,'%i\n',0);
         end
         if PR2S(i)<=val2 && PR2S(i)>val1 
                                    fprintf(f,'%f\n',a*PR2S(i)+b);
         end
         if PR2S(i)>=val2 
                        fprintf(f,'%i\n',1);
         end
end
                     
             
           




end

         