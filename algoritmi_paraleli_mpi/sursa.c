#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char** argv){
MPI_Init(&argc, &argv);
MPI_Status stat;

//Declaratii variabile
int tip,maxsteps,rang,N,color,step,i,j,t,tag=15,div;
double xmin,xmax,ymin,ymax,rez,cx,cy,zx,zy,aux,width,height;
double v[9],u[9];
double *matrix,*receive,*buf;
double indi,indf;

MPI_Comm_rank(MPI_COMM_WORLD, &rang);
MPI_Comm_size(MPI_COMM_WORLD, &N);

//Daca procesul meu este cel master
if (rang==0){

	//Deschidere fisierelor de intrare/iesire
	FILE* f=fopen(argv[1],"rt");
	FILE* g=fopen(argv[2],"wt");

	cx=0;
	cy=0;

	//Citirea datelor de intrare
	fscanf(f,"%i",&tip);
	fscanf(f,"%lf",&xmin);
	fscanf(f,"%lf",&xmax);
	fscanf(f,"%lf",&ymin);
	fscanf(f,"%lf",&ymax);
	fscanf(f,"%lf",&rez);
	fscanf(f,"%i",&maxsteps);
	if (tip==1){
		fscanf(f,"%lf %lf",&cx,&cy);
	}
	
	v[0]=tip;
	v[1]=xmin;
	v[2]=xmax;
	v[3]=ymin;
	v[4]=ymax;
	v[5]=rez;
	v[6]=maxsteps;
	v[7]=cx;
	v[8]=cy;

	
	width=(xmax-xmin)/rez;
	height=(ymax-ymin)/rez;
	div=(int)height/N;

	//Trimiterea datelor de intrare celorlalte procese pentru a face partea lor de lucru	
	for (i=1;i<N;i++){
		MPI_Send(v,9,MPI_DOUBLE,i,tag,MPI_COMM_WORLD);
	}	
	
	//Alocarea memoriei pentru matricea unde retinem toate datele si pentru matricea pe care o primim de la celelalte procese
	matrix=(double*)calloc((int)height*(int)width,sizeof(double));
	receive=(double*)calloc((int)height*(int)width, sizeof(double));
	
	//Daca este de tip Mandelbrot, atunci calculeaza algoritmul specific lui
	if (tip==0){
		for(i=0;i<(int)div;i++){
			for(j=0;j<(int)width;j++){
				zx=0;
				zy=0;
				step=0;
				cx=xmin+j*rez;
				cy=ymin+i*rez;
				while ((zx*zx+zy*zy<4) && (step<maxsteps)){
					aux=zx;
					zx=zx*zx-zy*zy + cx;
					zy=aux*zy+aux*zy + cy;
					step++;
				}
			color=step%256;
			matrix[i*(int)width+j]=color;
			}
		}
	}

	//Daca este de tip Julia, atunci calculeaza algoritmul specific lui
	if (tip==1){
		for(i=0;i<(int)div;i++){
			for(j=0;j<(int)width;j++){
				step=0;
				zx=xmin+j*rez;
				zy=ymin+i*rez;
				while ((zx*zx+zy*zy<4) && (step<maxsteps)){
					aux=zx;
					zx=zx*zx-zy*zy + cx;
					zy=aux*zy+aux*zy + cy;
					step++;
				}
			color=step%256;
			matrix[i*(int)width+j]=color;
			}
		}
	}

	//Primirea matricelor partiale de la celelalte procese si formarea matricei totale care cuprinde datele tuturor proceselor
	for (i=1;i<N;i++){
		MPI_Recv(receive,(int)height*(int)width,MPI_DOUBLE,i,tag,MPI_COMM_WORLD,&stat);

		indi=i*div;
		if (i==N-1)
			indf=height;
			else indf=(i+1)*div;

		for(t=(int)indi;t<(int)indf;t++){
			for(j=0;j<(int)width;j++){
				matrix[t*(int)width+j]=receive[t*(int)width+j];
			}
		}
	}

	//Scrierea rezultatelor in fisier text
	fprintf(g,"P2\n");
	fprintf(g,"%i %i\n",(int)width,(int)height);
	fprintf(g,"255\n");

	for(i=(int)height-1;i>=0;i--){
		for(j=0;j<(int)width;j++){
			fprintf(g,"%i ",(int)matrix[i*(int)width+j]);
		}
		fprintf(g,"\n");
	}

	free(matrix);
	matrix=NULL;	

	fclose(f);
	fclose(g);
}


if (rang!=0){
	
	//Primirea datelor de intrare de la procesul master
	MPI_Recv(u,9,MPI_DOUBLE,0,tag,MPI_COMM_WORLD,&stat);
	
	tip=(int)u[0];
	xmin=u[1];
	xmax=u[2];
	ymin=u[3];
	ymax=u[4];
	rez=u[5];
	maxsteps=(int)u[6];
	cx=u[7];
	cy=u[8];

	width=(xmax-xmin)/rez;
	height=(ymax-ymin)/rez;

	div=(int)height/N;
	indi=rang*div;
	if (rang==N-1)
		indf=height;
		else indf=(rang+1)*div;

	//Alocarea de memorie pentru matricea partiala ce va fi calculata de acest proces
	buf = (double*) calloc ((int)height*(int)width, sizeof(double));

	//Agoritmul pentru Mandelbrot aplicat doar pentru bucata de matrice corespunzatoare acestui proces
	if (tip==0){
		for(i=(int)indi;i<(int)indf;i++){
			for(j=0;j<(int)width;j++){
				zx=0;
				zy=0;
				step=0;
				cx=xmin+j*rez;
				cy=ymin+i*rez;
				while ((zx*zx+zy*zy<4) && (step<maxsteps)){
					aux=zx;
					zx=zx*zx-zy*zy + cx;
					zy=aux*zy+aux*zy + cy;
					step++;
				}
			color=step%256;
			buf[i*(int)width+j]=color;
			}
		}
	}

	//Agoritmul pentru Julia aplicat doar pentru bucata de matrice corespunzatoare acestui proces 
	if (tip==1){
		for(i=(int)indi;i<(int)indf;i++){
			for(j=0;j<(int)width;j++){
				step=0;
				zx=xmin+j*rez;
				zy=ymin+i*rez;
				while ((zx*zx+zy*zy<4) && (step<maxsteps)){
					aux=zx;
					zx=zx*zx-zy*zy + cx;
					zy=aux*zy+aux*zy + cy;
					step++;
				}
			color=step%256;
			buf[i*(int)width+j]=color;		
			}
		}
	}

//Trimiterea matricii cu rezultatele partiale procesului master
MPI_Send(buf,(int)height*(int)width,MPI_DOUBLE,0,tag,MPI_COMM_WORLD);

}

MPI_Finalize();

return 0;
}


