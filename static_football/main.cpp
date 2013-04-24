//-----------------------------------------------------------------------------------------------
//					LAB 1
//
//	Fisiere de interes: Transform2d.cpp main.cpp
//
//	Functii WorldDrawer2d:
//	-init e apelat o singura data, la inceput.
//	-idle e apelat per cadru de desenare
//	-onKey la apasarea unei taste.
//
//	Obiecte:
//	- un obiect este reprezentat prin punct si topologia punctelor (cum sunt legate pctele)
//	- obiectele sunt compuse din triunghiuri! de exemplu cu 4 puncte si 6 indici de topologie
//	pot crea 2 triunghiuri adiacente ce impreuna formeaza un dreptunghi.
//
//	Sisteme de coordonate:
//	- sunt 2 tipuri de sisteme de coordonate (fix - bleu&magenta) si dinamic(rosu&albastru)
//	- ca un obiect sa fie desenat trebuie sa fie atasat unui sistem de coordonate
//	- cand un obiect e atasat la un sistem de coordonate urmeaza transformarile sistemului.
//
//	Control obiecte:
//	- daca translatez/rotesc un obiect/punct direct (ex: o->translate(1,1)) o fac in coordonate globale
//	- daca translatez/rotesc un obiect printr-un sistem de coordonate o fac in coordonate locale
//	- pentru simplitate toate coordonatele mentinute in obiecte(de c++) sunt globale.
//
//	Happy coding.
//----------------------------------------------------------------------------------------------

#include "WorldDrawer2d.h"
#include <time.h>
bool WorldDrawer2d::animation=true;


//used global vars
CoordinateSystem2d *cs1, *cs2,*cs3,*cs4,*cs5,*cs6,*cs7,*cs8,*cs9,*cs10;
Object2d *o1, *o2, *o3,*o4,*o5,*o6,*o7,*o8,*o9,*o10,*o11,*o12,*o13,*o14,*o15,*o16,*o17,*o18,*o19,*o20,*o21,*o22,*o23,*o24,*o25,*o26,*o27;
std::vector<Object2d*> Steaua;
std::vector<Object2d*> Dinamo;
std::vector<bool> posesies;
std::vector<bool> posesied;
float tractx=0,tracty=0;
int reset=0;
int scorsteaua=0,scordinamo=0,golsteaua=0,goldinamo=0;

std::vector<Point2d> pointsc;
std::vector<int> topologyc;

std::vector<Point2d> pointsx;
std::vector<int> topologyx;


//add


//Functie ce deseneaza un dreptunghi, avand ca parametri coordanetele lui

Object2d* desenaredreptunghi(Object2d *o,float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float c1,float c2,float c3)
{
	std::vector<Point2d> points;
	std::vector<int> topology;
	points.push_back(Point2d(x1,y1));
	points.push_back(Point2d(x2,y2));
	points.push_back(Point2d(x3,y3));
	points.push_back(Point2d(x4,y4));
	topology.push_back(0);
	topology.push_back(1);
	topology.push_back(2);
	topology.push_back(2);
	topology.push_back(3);
	topology.push_back(0);
	o = new Object2d(points,topology);
	o->setcolor(c1,c2,c3);

	cs1->objectAdd(o);
	return o;
}


void WorldDrawer2d::init(){
	
	cs1 = new CoordinateSystem2d();
	cs_used.push_back(cs1);
	
	//linia de mijloc

	desenaredreptunghi(o2,-13,0.1f,-13,-0.1f,13,-0.1f,13,0.1f,1,1,1);

	//tuse

	desenaredreptunghi(o3,-13.5f,17,-13.5f,-17,-13,-17,-13,17,1,1,1);
	

	desenaredreptunghi(o4,13.5f,17,13.5f,-17,13,-17,13,17,1,1,1);
	

	desenaredreptunghi(o5,-13.5f,17.5f,-13.5f,17,-3,17,-3,17.5f,1,1,1);
	

	desenaredreptunghi(o6,3,17.5f,3,17,13.5f,17,13.5f,17.5f,1,1,1);
	

	desenaredreptunghi(o7,-13.5f,-17.5f,-13.5f,-17,-3,-17,-3,-17.5f,1,1,1);


	desenaredreptunghi(o8,3,-17.5f,3,-17,13.5f,-17,13.5f,-17.5f,1,1,1);
	

	//poarta superioara

	desenaredreptunghi(o9,-3,17,-2.7f,17,-2.7f,19,-3,19,1,1,1);
	

	desenaredreptunghi(o10,-2.7f,19,-2.7f,18.7f,2.7f,18.7f,2.7f,19,1,1,1);
	

	desenaredreptunghi(o11,2.7f,19,3,19,3,17,2.7f,17,1,1,1);
	

	//poarta inferioara

	desenaredreptunghi(o12,-3,-17,-2.7f,-17,-2.7f,-19,-3,-19,1,1,1);
	

	desenaredreptunghi(o13,-2.7f,-19,-2.7f,-18.7f,2.7f,-18.7f,2.7f,-19,1,1,1);
	

	desenaredreptunghi(o14,2.7f,-19,3,-19,3,-17,2.7f,-17,1,1,1);
	

	//Mingea

	
	
	for(int i=0;i<11;i++)
	{
		pointsc.push_back(Point2d(0,0));
		pointsc.push_back(Point2d((float)(0.5*cos(i*3.14/6)),(float)(0.5*sin(i*3.14/6))));
		pointsc.push_back(Point2d((float)(0.5*cos((i+1)*3.14/6)),(float)(0.5*sin((i+1)*3.14/6))));
	}

	pointsc.push_back(Point2d(0,0));
	pointsc.push_back(Point2d((float)(0.5*cos(11*3.14/6)),(float)(0.5*sin(11*3.14/6))));
	pointsc.push_back(Point2d(0.5,0));

	for (int i=0;i<36;i++)
		topologyc.push_back(i);
		
	o15=new Object2d(pointsc,topologyc);
	o15->setcolor(0,1,0);
			
	cs1->objectAdd(o15);

	//Jucatori

	for (int j=0;j<6;j++)
	{
		Steaua.push_back(new Object2d(pointsc,topologyc));
		Steaua[j]->setcolor(0,0,1);
		cs1->objectAdd(Steaua[j]);
		Steaua[j]->scale(1.8f,1.8f);
	}
	Steaua[0]->translate(0,-16);
	Steaua[1]->translate(-8,-11);
	Steaua[2]->translate(-2,-1);
	Steaua[3]->translate(3,-3);
	Steaua[4]->translate(7,7);
	Steaua[5]->translate(-6,14);


	for (int j=0;j<6;j++)
	{
		Dinamo.push_back(new Object2d(pointsc,topologyc));
		Dinamo[j]->setcolor(1,0,0);
		cs1->objectAdd(Dinamo[j]);
		Dinamo[j]->scale(1.8f,1.8f);
	}

	Dinamo[0]->translate(0,16);
	Dinamo[1]->translate(8,11);
	Dinamo[2]->translate(2,1);
	Dinamo[3]->translate(-3,3);
	Dinamo[4]->translate(-7,-7);
	Dinamo[5]->translate(6,-14);

	

	//teren

	o1=desenaredreptunghi(o1,-13,17,-13,-17,13,-17,13,17,0,1,0);

	//initializarea vectorului de posesie

	for(int i=0;i<6;i++)
	{
		posesies.push_back(false);
		posesied.push_back(false);
	}

	//afisarea scorului

	//1.X-ul este format din doua paralelograme

	desenaredreptunghi(o16,16,-2,16.5f,-2,18,2,17.5f,2,0,0,0);
	
	//2.X-ul este format din doua paralelograme

	desenaredreptunghi(o17,18,-2,16.5f,2,16,2,17.5f,-2,0,0,0);

	//Scorul echipei STEAUA BUCURESTI
	
	pointsx.push_back(Point2d(16,-8));
	pointsx.push_back(Point2d(16.5f,-8));
	pointsx.push_back(Point2d(16.5f,-4));
	pointsx.push_back(Point2d(16,-4));
	topologyx.push_back(0);
	topologyx.push_back(1);
	topologyx.push_back(2);
	topologyx.push_back(2);
	topologyx.push_back(3);
	topologyx.push_back(0);

	o18 = new Object2d(pointsx,topologyx);
	o18->setcolor(0,0,1);
	cs1->objectAdd(o18);

	o20 = new Object2d(pointsx,topologyx);
	o20->setcolor(0,0,1);
	cs1->objectAdd(o20);
	o20->translate(1.5f,0);
		
	std::vector<Point2d> pointsx1;
	std::vector<int> topologyx1;
	pointsx1.push_back(Point2d(16.5f,-8));
	pointsx1.push_back(Point2d(18,-8));
	pointsx1.push_back(Point2d(18,-7.5f));
	pointsx1.push_back(Point2d(16.5f,-7.5f));
	topologyx1.push_back(0);
	topologyx1.push_back(1);
	topologyx1.push_back(2);
	topologyx1.push_back(2);
	topologyx1.push_back(3);
	topologyx1.push_back(0);

	o19 = new Object2d(pointsx1,topologyx1);
	o19->setcolor(0,0,1);
	cs1->objectAdd(o19);

	o21 = new Object2d(pointsx1,topologyx1);
	o21->setcolor(0,0,1);
	cs1->objectAdd(o21);
	o21->translate(0,3.5f);


	//Scorul echipei adverse

	o22 = new Object2d(pointsx,topologyx);
	o22->setcolor(1,0,0);
	cs1->objectAdd(o22);
	o22->translate(0,12);

	o23 = new Object2d(pointsx,topologyx);
	o23->setcolor(1,0,0);
	cs1->objectAdd(o23);
	o23->translate(1.5f,0);
	o23->translate(0,12);
	
	o24 = new Object2d(pointsx1,topologyx1);
	o24->setcolor(1,0,0);
	cs1->objectAdd(o24);
	o24->translate(0,12);

	o25 = new Object2d(pointsx1,topologyx1);
	o25->setcolor(1,0,0);
	cs1->objectAdd(o25);
	o25->translate(0,3.5f);
	o25->translate(0,12);



	scorsteaua=0;
	scordinamo=0;

}
void WorldDrawer2d::onIdle(){	//per frame
	static int iteration=1;
	
	float distanta;
	float d1,d2;
	float sumaraze;
	float distx,disty;
	int i;

	//Resetez scorul, dupa ce una dintre echipe a batut

	if (reset==2){
		scorsteaua=0;
		scordinamo=0;
		cs1->objectRemove(o18);
		cs1->objectRemove(o20);
		cs1->objectRemove(o26);
		cs1->objectRemove(o22);
		cs1->objectRemove(o23);
		cs1->objectRemove(o24);
		cs1->objectRemove(o25);
		cs1->objectRemove(o27);

		//Schimb culoarea terenului si a jucatorilor

		o1->setcolor(1,1,1);


		for(int i=0;i<6;i++)
		{
			Steaua[i]->setcolor(1,1,1);
			Dinamo[i]->setcolor(1,1,1);
		}			
					
		Sleep(3000);
		cs1->objectAdd(o18);
		cs1->objectAdd(o19);
		cs1->objectAdd(o20);
		cs1->objectAdd(o21);
	
		cs1->objectAdd(o22);
		cs1->objectAdd(o23);
		cs1->objectAdd(o24);
		cs1->objectAdd(o25);
		o1->setcolor(0,1,0);

		for(int i=0;i<6;i++)
		{
			Steaua[i]->setcolor(0,0,1);
			Dinamo[i]->setcolor(1,0,0);
		}		
		reset=0;
	}

	//Distribuirea mingii unui jucator aleator la inceputul jocului

	if (reset==0){

		srand( time( NULL ) );
		if (golsteaua==0 && goldinamo==0) i=rand()%12;
		else if (golsteaua == 1) i=rand()%6+6;
		else if (goldinamo == 1) i=rand()%6;

		o15->translate(-o15->points[0].x,-o15->points[0].y);
		if (i<=5){
			distx=-o15->points[0].x+Steaua[i]->points[0].x;
			disty=-o15->points[0].y+Steaua[i]->points[0].y;
			tractx=distx/400;
			tracty=disty/400;
			}
		else {
			distx=-o15->points[0].x+Dinamo[i-6]->points[0].x;
			disty=-o15->points[0].y+Dinamo[i-6]->points[0].y;
			tractx=distx/400;
			tracty=disty/400;
		}
	reset=1;
	}

	//Desfasurarea propriu zisa a jocului
			
	if (reset==1) {
	golsteaua=0;
	goldinamo=0;
	o15->translate(tractx,tracty);

	//Coliziunea cu mantele
	
	if (o15->points[0].x<=12.51 && o15->points[0].x>=12.49)
			tractx=-tractx;
	if (o15->points[0].x>=-12.51 && o15->points[0].x<=-12.49) 			
			tractx=-tractx;
	if (o15->points[0].y<=16.51 && o15->points[0].y>=16.49)
	{   
		//Daca prima echipa a marcat, modificarea scorului
		
		if (o15->points[0].x<=3 && o15->points[0].x>=-3) 
				{
					tractx=0; 
					tracty=0;
					reset=0;
					o15->setcolor(0,1,0);
					golsteaua=1;
					scorsteaua++;
					
					if (scorsteaua==1) {
						cs1->objectRemove(o18);
						cs1->objectRemove(o19);
						cs1->objectRemove(o20);
						cs1->objectRemove(o21);
	
						o26 = new Object2d(pointsx,topologyx);
						o26->setcolor(0,0,1);
						cs1->objectAdd(o26);
						o26->translate(0.73f,0);
					}
					else if (scorsteaua==2) {
						cs1->objectRemove(o26);
						cs1->objectAdd(o18);
						cs1->objectAdd(o20);
					}
					else if (scorsteaua==3){
						cs1->objectAdd(o26);
						reset=2;				

					}
				}
			else tracty=-tracty;
	}
	if (o15->points[0].y>=-16.52 && o15->points[0].y<=-16.48)
	{
		//Daca a doua echipa a marcat, modificarea scorului
			
			if (o15->points[0].x<=3 && o15->points[0].x>=-3) {
				tractx=0; 
				tracty=0;
				reset=0;
				o15->setcolor(0,1,0);
				goldinamo=1;
				scordinamo++;
				if (scordinamo==1) {
					cs1->objectRemove(o22);
					cs1->objectRemove(o23);
					cs1->objectRemove(o24);
					cs1->objectRemove(o25);

					o27 = new Object2d(pointsx,topologyx);
					o27->setcolor(1,0,0);
					cs1->objectAdd(o27);
					o27->translate(0.73f,0);
					o27->translate(0,12);
				}
				else if (scordinamo==2) {
					cs1->objectRemove(o27);
					cs1->objectAdd(o22);
					cs1->objectAdd(o23);
				}
				else if (scordinamo==3){
					cs1->objectAdd(o27);
					reset=2;
				}			
			}
			else tracty=-tracty;
	}

	//Coliziunea jucator-minge
	
	for (int i=0;i<6;i++)
	{	
		d1=o15->points[0].x-Steaua[i]->points[0].x;
		d2=o15->points[0].y-Steaua[i]->points[0].y;
		distanta=(float)sqrt(d1*d1+d2*d2);
		sumaraze=(float)(0.5+0.5*1.8);
		if (distanta>=sumaraze-0.01f && distanta<=sumaraze+0.02f) 
		{
			tractx=0; 
			tracty=0;
			posesies[i]=true;
			o15->setcolor(1,1,1);
		}

		d1=o15->points[0].x-Dinamo[i]->points[0].x;
		d2=o15->points[0].y-Dinamo[i]->points[0].y;
		distanta=sqrt(d1*d1+d2*d2);
		sumaraze=(float)(0.5+0.5*1.8);
		if (distanta>=sumaraze-0.01f && distanta<=sumaraze+0.02f) 
		{
			tractx=0; 
			tracty=0;
			posesied[i]=true;
			o15->setcolor(1,1,1);
		}
		
	}
	}
	
	
	if(animation){
		iteration++;
	}
}

void WorldDrawer2d::onKey(unsigned char key){
	float distx;
	float disty;
	float sumaraze=(float)(0.5+0.5*1.8);
	switch(key){
		case 'w':
			for (int i=0;i<6;i++)
			{
				if (posesies[i]==true)
				{
					distx=o15->points[0].x-Steaua[i]->points[0].x;
					disty=o15->points[0].y-Steaua[i]->points[0].y;    //Lansarea mingii pe directia determinata de centrul mingii si a 
					tractx=distx/100;								//jucatorului
					tracty=disty/100;
					posesies[i]=false;
				}
			
			}
			break;
		case 'a':
			for (int i=0;i<6;i++)
				if (posesies[i]==true)
					o15->rotateRelativeToPoint(Steaua[i]->points[0],0.1f);			//Rotirea mingii
			    
			break;
		case 'd':
			for (int i=0;i<6;i++)
				if (posesies[i]==true)
					o15->rotateRelativeToPoint(Steaua[i]->points[0],-0.1f);			//Rotirea mingii
			break;
		case 'i':
			for (int i=0;i<6;i++)
				if (posesied[i]==true)
				{
					distx=o15->points[0].x-Dinamo[i]->points[0].x;
					disty=o15->points[0].y-Dinamo[i]->points[0].y;
					tractx=distx/100;
					tracty=disty/100;
					posesied[i]=false;
				} 
			break;
		case 'j':
			for (int i=0;i<6;i++)
			 if (posesied[i]==true) o15->rotateRelativeToPoint(Dinamo[i]->points[0],-0.1f);
			break;
		case 'l':
			for (int i=0;i<6;i++)
				if (posesied[i]==true) o15->rotateRelativeToPoint(Dinamo[i]->points[0],0.1f);
			
			break;
		case 'h':
				//animation=!animation;
			break;
		default:
			break;
	}
}


int main(int argc, char** argv){
	WorldDrawer2d wd2d(argc,argv,600,600,200,100,std::string("Lab 1"));
	wd2d.init();
	wd2d.run();
	return 0;
}