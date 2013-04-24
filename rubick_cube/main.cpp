//Sezciuc Radu Cristian
//grupa 331CB
//tema 2 EGC



#include "WorldDrawer3d.h"
#include <ctime>
#include <cstdio>
bool WorldDrawer3d::animation=true;


//Variabile globale
CoordinateSystem3d *cs1;
Object3d *o1, *o2, *o3, *o4,*o5, *o6,*o7;
std::vector<Object3d*> fata;
std::vector<Object3d*> top,bottom,front,back,left,right,medy,medx,medz;
std::vector<Point3d> points,points2,points3,points4,points5,points6;
std::vector<int> topology;
std::vector<std:: pair<float, int>> rotiri;
std::vector<Object3d*> scor;
Point3d centru;
int nr=0,layer,miscari,mutari=0;
int x;

//Functie ce creeaza o fata primind ca parametrii vectorul de puncte, topologie, culoarea, si pozitia pe sistemul de coordonate
Object3d* creeazafata(std::vector<Point3d> p,std::vector<int> t,float c1,float c2,float c3,float x,float y,float z){

	Object3d *o=new Object3d(p,t); 
	cs1->objectAdd(o);
	o->setcolor(c1,c2,c3);
	o->translate(x,y,z);
	return o;
}

//Functie ce roteste un anumit set de cuburi dupa o axa in functie de numarul de radiani
void rotestecuburi(std::vector<Object3d*> v,float u,int p){

	centru=Point3d(0,0,0);

	for (int i=0;i<v.size();i++)
		if (p==0) v[i]->rotateXRelativeToPoint(centru,u);
		else if (p==1) v[i]->rotateYRelativeToPoint(centru,u);
		else if (p==2) v[i]->rotateZRelativeToPoint(centru,u);
}

//Functia care actualizeaza layerele cubului Rubick dupa rotirea unui set de cuburi mai mici.
void actlayere(){
	//Resetarea layerelor vechi

			for(int i=rotiri.size()-1;i>=0;i--)						//Rotirea cubului in pozitia initiala
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
			
			
			top.clear();
			bottom.clear();
			left.clear();
			right.clear();
			front.clear();
			back.clear();
			medx.clear();
			medy.clear();
			medz.clear();
			
			for(int i=0;i<fata.size();i++){
				bool ok=true;
				for(int j=0;j<fata[i]->points.size();j++)			//Actualizarea stratului top
					if (fata[i]->points[j].y<3.9f) ok=false;
				if (ok==true) top.push_back(fata[i]);
			}

			for(int i=0;i<fata.size();i++){
				bool ok=true;
				for(int j=0;j<fata[i]->points.size();j++)			//Actualizarea stratului bottom
					if (fata[i]->points[j].y>-3.9f) ok=false;
				if (ok==true) bottom.push_back(fata[i]);
			}

			for(int i=0;i<fata.size();i++){
				bool ok=true;
				for(int j=0;j<fata[i]->points.size();j++)			//Actualizarea stratului left
					if (fata[i]->points[j].x>-3.9f) ok=false;
				if (ok==true) left.push_back(fata[i]);
			}
		
			for(int i=0;i<fata.size();i++){
				bool ok=true;
				for(int j=0;j<fata[i]->points.size();j++)			//Actualizarea stratului right
					if (fata[i]->points[j].x<3.9f) ok=false;
				if (ok==true) right.push_back(fata[i]);
			}

			for(int i=0;i<fata.size();i++){
				bool ok=true;
				for(int j=0;j<fata[i]->points.size();j++)			//Actualizarea stratului front
					if (fata[i]->points[j].z<3.9f) ok=false;
				if (ok==true) front.push_back(fata[i]);
			}

			for(int i=0;i<fata.size();i++){
				bool ok=true;
				for(int j=0;j<fata[i]->points.size();j++)			//Actualizarea stratului back
					if (fata[i]->points[j].z>-3.9f) ok=false;
				if (ok==true) back.push_back(fata[i]);
			}

			for(int i=0;i<fata.size();i++){
				bool ok=true;
				for(int j=0;j<fata[i]->points.size();j++)							//Actualizarea stratului medy
					if (fata[i]->points[j].y>3.9f || fata[i]->points[j].y<-3.9f) ok=false;
				if (ok==true) medy.push_back(fata[i]);
			}

			for(int i=0;i<fata.size();i++){
				bool ok=true;
				for(int j=0;j<fata[i]->points.size();j++)								//Actualizarea stratului medz
					if (fata[i]->points[j].z>3.9f || fata[i]->points[j].z<-3.9f) ok=false;
				if (ok==true) medz.push_back(fata[i]);
			}

			for(int i=0;i<fata.size();i++){
				bool ok=true;
				for(int j=0;j<fata[i]->points.size();j++)							//Actualizarea stratului medx
					if (fata[i]->points[j].x>3.9f || fata[i]->points[j].x<-3.9f) ok=false;
				if (ok==true) medx.push_back(fata[i]);
			}

			for(int i=0;i<rotiri.size();i++)						//Rotirea cubului in pozitia lui
				rotestecuburi(fata,rotiri[i].first,rotiri[i].second);
}

void WorldDrawer3d::init(){
	//creeaza 2 sistem de coordonate client
	cs1 = new CoordinateSystem3d();
	cs_used.push_back(cs1);
	centru=Point3d(0,0,0);
	layer=0; miscari=0;
	nr=0;
	
	//Crearea primului mic cub format din 6 fete
	
	points.push_back(Point3d(3.5f,3.5f,3.5f));points.push_back(Point3d(3.5f,3.5f,-3.5f));
	points.push_back(Point3d(-3.5f,3.5f,-3.5f));points.push_back(Point3d(-3.5f,3.5f,3.5f));
	topology.push_back(0);topology.push_back(1);topology.push_back(2);								//top
	topology.push_back(2);topology.push_back(3);topology.push_back(0);
	fata.push_back(new Object3d(points,topology));
	fata[0]->setcolor(0,0,0);

	points2.push_back(Point3d(3.5f,-3.5f,3.5f));points2.push_back(Point3d(3.5f,-3.5f,-3.5f));		 //bottom
	points2.push_back(Point3d(-3.5f,-3.5f,-3.5f));points2.push_back(Point3d(-3.5f,-3.5f,3.5f));
	fata.push_back(new Object3d(points2,topology));
	fata[1]->setcolor(0,0,0);

	points3.push_back(Point3d(-3.5f,3.5f,3.5f));points3.push_back(Point3d(-3.5f,3.5f,-3.5f));		//left
	points3.push_back(Point3d(-3.5f,-3.5f,-3.5f));points3.push_back(Point3d(-3.5f,-3.5f,3.5f));	
	fata.push_back(new Object3d(points3,topology));
	fata[2]->setcolor(0,0,0);

	points4.push_back(Point3d(3.5f,3.5f,3.5f));points4.push_back(Point3d(3.5f,3.5f,-3.5f));			//right
	points4.push_back(Point3d(3.5f,-3.5f,-3.5f));points4.push_back(Point3d(3.5f,-3.5f,3.5f));
	fata.push_back(new Object3d(points4,topology));
	fata[3]->setcolor(0,0,0);

	points5.push_back(Point3d(3.5f,-3.5f,3.5f));points5.push_back(Point3d(3.5f,3.5f,3.5f));			//front
	points5.push_back(Point3d(-3.5f,3.5f,3.5f));points5.push_back(Point3d(-3.5f,-3.5f,3.5f));
	fata.push_back(new Object3d(points5,topology));
	fata[4]->setcolor(0,0,0);

	points6.push_back(Point3d(3.5f,-3.5f,-3.5f));points6.push_back(Point3d(3.5f,3.5f,-3.5f));		//back
	points6.push_back(Point3d(-3.5f,3.5f,-3.5f));points6.push_back(Point3d(-3.5f,-3.5f,-3.5f));
	fata.push_back(new Object3d(points6,topology));
	fata[5]->setcolor(0,0,0);

	//Adaugarea cubului la sistemul de coordonate cs1
	for(int i=0;i<6;i++)
		cs1->objectAdd(fata[i]);
	
	//Crearea cubului Rubick

	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++){
			if (i==2){
				o1=creeazafata(points,topology,0.01f,0.01f,1,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);		
				top.push_back(o1);												//Crearea fetelor de pe stratul top
				if (j==2) left.push_back(o1);
				if (j==0) right.push_back(o1);
				if (k==2) front.push_back(o1);
				if (k==0) back.push_back(o1);
			}
			else{
				o1=creeazafata(points,topology,0,0,0,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);
				if (i==0) bottom.push_back(o1);
				if (j==2) left.push_back(o1);
				if (j==0) right.push_back(o1);
				if (k==2) front.push_back(o1);
				if (k==0) back.push_back(o1);
			}

			if (i==0){
				o1=creeazafata(points2,topology,0.6f,0.01f,1,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);	
				bottom.push_back(o1);											//Crearea fetelor de pe stratul bottom
				if (j==2) left.push_back(o1);
				if (j==0) right.push_back(o1);
				if (k==2) front.push_back(o1);
				if (k==0) back.push_back(o1);
			}
			else{
				o1=creeazafata(points2,topology,0,0,0,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);
				if (i==2) top.push_back(o1);
				if (j==2) left.push_back(o1);
				if (j==0) right.push_back(o1);
				if (k==2) front.push_back(o1);
				if (k==0) back.push_back(o1);
			}

			if (j==2){
				o1=creeazafata(points3,topology,0.8f,1,0.01f,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);	
				if (i==0) bottom.push_back(o1);									//Crearea fetelor de pe stratul left
				if (i==2) top.push_back(o1);
				left.push_back(o1);
				if (k==2) front.push_back(o1);
				if (k==0) back.push_back(o1);
			}
			else{
				o1=creeazafata(points3,topology,0,0,0,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);
				if (i==0) bottom.push_back(o1);								
				if (i==2) top.push_back(o1);
				if (j==0) right.push_back(o1);
				if (k==2) front.push_back(o1);
				if (k==0) back.push_back(o1);
			}

			if (j==0){ 
				o1=creeazafata(points4,topology,0.01f,1,0.01f,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);												//Crearea fetelor de pe stratul right
				if (i==0) bottom.push_back(o1);
				if (i==2) top.push_back(o1);
				right.push_back(o1);
				if (k==2) front.push_back(o1);
				if (k==0) back.push_back(o1);
			}
			else{
				o1=creeazafata(points4,topology,0,0,0,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);
				if (i==0) bottom.push_back(o1);
				if (i==2) top.push_back(o1);
				if (j==2) left.push_back(o1);
				if (k==2) front.push_back(o1);
				if (k==0) back.push_back(o1);
			}

			if (k==2){
				o1=creeazafata(points5,topology,1,0.5f,0.01f,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);		
				if (i==0) bottom.push_back(o1);								//Crearea fetelor de pe stratul front
				if (i==2) top.push_back(o1);
				if (j==2) left.push_back(o1);
				if (j==0) right.push_back(o1);
				front.push_back(o1);
			}
			else{
				o1=creeazafata(points5,topology,0,0,0,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);
				if (i==0) bottom.push_back(o1);
				if (i==2) top.push_back(o1);
				if (j==2) left.push_back(o1);
				if (j==0) right.push_back(o1);
				if (k==0) back.push_back(o1);
			}

			if (k==0){
				o1=creeazafata(points6,topology,1,0.01f,0.01f,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);			
				if (i==0) bottom.push_back(o1);								//Crearea fetelor de pe stratul back
				if (i==2) top.push_back(o1);
				if (j==2) left.push_back(o1);
				if (j==0) right.push_back(o1);
				back.push_back(o1);
			}
			else{
				o1=creeazafata(points6,topology,0,0,0,8*(1-j),8*(i-1),8*(k-1));
				fata.push_back(o1);
				if (i==0) bottom.push_back(o1);
				if (i==2) top.push_back(o1);
				if (j==2) left.push_back(o1);
				if (j==0) right.push_back(o1);
				if (k==2) front.push_back(o1);
			}
		}

		actlayere();

}
void WorldDrawer3d::onIdle(){	//per frame
	static int iteration=1;
	if (animation){
	
	if (miscari!=0 && layer==1){
			for(int i=rotiri.size()-1;i>=0;i--)
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
			rotestecuburi(top,0.314159f,1);
			for(int i=0;i<rotiri.size();i++)
				rotestecuburi(fata,rotiri[i].first,rotiri[i].second);			//Rotirea efectiva a stratului top
			miscari--;
			if (rotiri.size()<=10)
				Sleep(50);
			else if (rotiri.size()<=20)
				Sleep(10);
			if (miscari==0) {actlayere(); layer=0;}
	}
	
	if (miscari!=0 && layer==2){
			for(int i=rotiri.size()-1;i>=0;i--)
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
			rotestecuburi(bottom,0.314159f,1);
			for(int i=0;i<rotiri.size();i++)
				rotestecuburi(fata,rotiri[i].first,rotiri[i].second);		//Rotirea efectiva a stratului bottom
			miscari--;
			if (rotiri.size()<=10)
				Sleep(50);
			else if (rotiri.size()<=20)
				Sleep(10);
			if (miscari==0) {actlayere(); layer=0;}
	}

	if (miscari!=0 && layer==3){
			for(int i=rotiri.size()-1;i>=0;i--)
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
			rotestecuburi(left,0.314159f,0);
			for(int i=0;i<rotiri.size();i++)
				rotestecuburi(fata,rotiri[i].first,rotiri[i].second);			//Rotirea efectiva a stratului left
			miscari--;
			if (rotiri.size()<=10)
				Sleep(50);
			else if (rotiri.size()<=20)
				Sleep(10);
			if (miscari==0) {actlayere(); layer=0;}
	}

	if (miscari!=0 && layer==4){
			for(int i=rotiri.size()-1;i>=0;i--)
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
			rotestecuburi(right,0.314159f,0);
			for(int i=0;i<rotiri.size();i++)
				rotestecuburi(fata,rotiri[i].first,rotiri[i].second);			//Rotirea efectiva a stratului right
			miscari--;
			if (rotiri.size()<=10)
				Sleep(50);
			else if (rotiri.size()<=20)
				Sleep(10);
			if (miscari==0) {actlayere(); layer=0;}
	}

	if (miscari!=0 && layer==5){
			for(int i=rotiri.size()-1;i>=0;i--)
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
			rotestecuburi(front,0.314159f,2);
			for(int i=0;i<rotiri.size();i++)
				rotestecuburi(fata,rotiri[i].first,rotiri[i].second);			//Rotirea efectiva a stratului front
			miscari--;
			if (rotiri.size()<=10)
				Sleep(50);
			else if (rotiri.size()<=20)
				Sleep(10);
			if (miscari==0) {actlayere(); layer=0;}
	}

	if (miscari!=0 && layer==6){
			for(int i=rotiri.size()-1;i>=0;i--)
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
			rotestecuburi(back,0.314159f,2);
			for(int i=0;i<rotiri.size();i++)
				rotestecuburi(fata,rotiri[i].first,rotiri[i].second);			//Rotirea efectiva a stratului back
			miscari--;
			if (rotiri.size()<=10)
				Sleep(50);
			else if (rotiri.size()<=20)
				Sleep(10);
			if (miscari==0) {actlayere(); layer=0;}
	}

	if (miscari!=0 && layer==7){
			for(int i=rotiri.size()-1;i>=0;i--)
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
			rotestecuburi(medx,0.314159f,0);
			for(int i=0;i<rotiri.size();i++)
				rotestecuburi(fata,rotiri[i].first,rotiri[i].second);			//Rotirea efectiva a stratului medx
			miscari--;
			if (rotiri.size()<=10)
				Sleep(50);
			else if (rotiri.size()<=20)
				Sleep(10);
			if (miscari==0) {actlayere(); layer=0;}
	}

	if (miscari!=0 && layer==8){
			for(int i=rotiri.size()-1;i>=0;i--)
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
			rotestecuburi(medy,0.314159f,1);
			for(int i=0;i<rotiri.size();i++)
				rotestecuburi(fata,rotiri[i].first,rotiri[i].second);			//Rotirea efectiva a stratului medy
			miscari--;
			if (rotiri.size()<=10)
				Sleep(50);
			else if (rotiri.size()<=20)
				Sleep(10);
			if (miscari==0) {actlayere(); layer=0;}
	}

	if (miscari!=0 && layer==9){
			for(int i=rotiri.size()-1;i>=0;i--)
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
			rotestecuburi(medz,0.314159f,2);
			for(int i=0;i<rotiri.size();i++)
				rotestecuburi(fata,rotiri[i].first,rotiri[i].second);			//Rotirea efectiva a stratului medz
			miscari--;
			if (rotiri.size()<=10)
				Sleep(50);
			else if (rotiri.size()<=20)
				Sleep(10);
			if (miscari==0) {actlayere(); layer=0;}
	}

	bool ok=true;
	
	if (nr==1){					//Testez, pe rand, daca layerele au aceeasi culoare
	
	bool mda=true;
	float cx=0;
	float cy=0;
	float cz=0;

	for(int i=rotiri.size()-1;i>=0;i--)									//Rotirea cubului in stare initiala
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
	

	int p=0;
	for(int i=0;i<fata.size();i++){
		mda=true;
		for(int j=0;j<fata[i]->points.size();j++)
			if (fata[i]->points[j].y<7) mda=false;				
		if (mda==true) {
			if (p==0) {cx=fata[i]->colorx; cy=fata[i]->colory; cz=fata[i]->colorz;p=1;}
			else if (cx!=fata[i]->colorx || cy!=fata[i]->colory || cz!=fata[i]->colorz)
					ok=false;
		}
	}
	p=0;
	mda=true;
	cx=0;cy=0;cz=0;
	for(int i=0;i<fata.size();i++){
		mda=true;
		for(int j=0;j<fata[i]->points.size();j++)
			if (fata[i]->points[j].y>-7) mda=false;
		if (mda==true) {
			if (p==0) {cx=fata[i]->colorx; cy=fata[i]->colory; cz=fata[i]->colorz;p=1;}
			else if (cx!=fata[i]->colorx || cy!=fata[i]->colory || cz!=fata[i]->colorz)
					ok=false;
		}
	}
	p=0;
	cx=0;cy=0;cz=0;
	for(int i=0;i<fata.size();i++){
		mda=true;
		for(int j=0;j<fata[i]->points.size();j++)
			if (fata[i]->points[j].x>-7) mda=false;
		if (mda==true) {
			if (p==0) {cx=fata[i]->colorx; cy=fata[i]->colory; cz=fata[i]->colorz;p=1;}
			else if (cx!=fata[i]->colorx || cy!=fata[i]->colory || cz!=fata[i]->colorz)
					ok=false;
		}
	}

	cx=0;cy=0;cz=0;
	p=0;
	for(int i=0;i<fata.size();i++){
		mda=true;
		for(int j=0;j<fata[i]->points.size();j++)
			if (fata[i]->points[j].x<7) mda=false;
		if (mda==true) {
			if (p==0) {cx=fata[i]->colorx; cy=fata[i]->colory; cz=fata[i]->colorz;p=1;}
			else if (cx!=fata[i]->colorx || cy!=fata[i]->colory || cz!=fata[i]->colorz)
					ok=false;
		}
	}

	cx=0;cy=0;cz=0;
	p=0;
	for(int i=0;i<fata.size();i++){
		mda=true;
		for(int j=0;j<fata[i]->points.size();j++)
			if (fata[i]->points[j].z<7) mda=false;
		if (mda==true) {
			if (p==0) {cx=fata[i]->colorx; cy=fata[i]->colory; cz=fata[i]->colorz;p=1;}
			else if (cx!=fata[i]->colorx || cy!=fata[i]->colory || cz!=fata[i]->colorz)
					ok=false;
		}
	}

	cx=0;cy=0;cz=0;
	p=0;
	for(int i=0;i<fata.size();i++){
		mda=true;
		for(int j=0;j<fata[i]->points.size();j++)
			if (fata[i]->points[j].z>-7) mda=false;
		if (mda==true) {
			if (p==0) {cx=fata[i]->colorx; cy=fata[i]->colory; cz=fata[i]->colorz;p=1;}
			else if (cx!=fata[i]->colorx || cy!=fata[i]->colory || cz!=fata[i]->colorz)
					ok=false;
		}
	}

	for(int i=0;i<rotiri.size();i++)
				rotestecuburi(fata,rotiri[i].first,rotiri[i].second);
	
	if (ok==true){				//Daca au aceeasi culoare, scoate obiectele
		for(int i=0;i<fata.size();i++)
			cs1->objectRemove(fata[i]);
		cs1->objectRemove(o2);
		cs1->objectRemove(o3);
		cs1->objectRemove(o4);
		cs1->objectRemove(o5);
		cs1->objectRemove(o6);
		cs1->objectRemove(o7);

		clock_t begin = clock();;
		while( (std::clock() - begin ) / (double)CLOCKS_PER_SEC < 2 ) {			//Schimbarea culorii ecranului
		glClearColor(0,0,0,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glutSwapBuffers();
		}
		int y=10,z,x;
		for(int i=0;i<mutari;i++){				//Afisarea scorului pe ecran
			if (i%7==0) z=0;
			if (i%7==1) z=-5;
			if (i%7==2) z=-10;
			if (i%7==3) z=-15;
			if (i%7==4) z=-20;
			if (i%7==5) z=-25;
			if (i%7==6) z=-30;
			x=-90+i*15;
			if (i>=7) {y=0; x=-90+(i-7)*15;}
			if (i>=14){y=-10; x=-90+(i-14)*15;}
			if (i>=21){y=-20; x=-90+(i-21)*15;}
			if (i>=28){y=-30; x=-90+(i-28)*15;}
			if (i>=35){y=-40; x=-90+(i-35)*15;}
			if (i>=42){y=-50; x=-90+(i-42)*15;}
			scor.push_back(creeazafata(points,topology,0,0,1,x,y,z));
			scor.push_back(creeazafata(points2,topology,0,0,1,x,y,z));
			scor.push_back(creeazafata(points3,topology,0,0,1,x,y,z));
			scor.push_back(creeazafata(points4,topology,0,0,1,x,y,z));
			scor.push_back(creeazafata(points5,topology,0,0,1,x,y,z));
			scor.push_back(creeazafata(points6,topology,0,0,1,x,y,z));
		}

		animation=!animation;
		
		ok=false;
	}
	}
	}
	iteration++;
}



void WorldDrawer3d::onKey(unsigned char key){
	switch(key){
		case KEY_SPACE:
				animation=!animation;
			break;
		case '1':
			rotestecuburi(fata,0.1f,0);							//Rotirea cubului Rubick in jurul axei OX
			if (rotiri.size()>1 && rotiri[rotiri.size()-1].second==0){
				float aux=rotiri[rotiri.size()-1].first;
				rotiri.pop_back();
				rotiri.push_back(std::make_pair(aux+0.1f,0));		//Salvarea rotirii
			}
			else rotiri.push_back(std::make_pair(0.1f,0));

			break;
		case '2':
			rotestecuburi(fata,0.1f,1);							//Rotirea cubului Rubick in jurul axei OY
			if (rotiri.size()>1 && rotiri[rotiri.size()-1].second==1){
				float aux=rotiri[rotiri.size()-1].first;
				rotiri.pop_back();
				rotiri.push_back(std::make_pair(aux+0.1f,1));		//Salvarea rotirii
			}
			else rotiri.push_back(std::make_pair(0.1f,1));
						
			break;
		case '3':
			rotestecuburi(fata,0.1f,2);							//Rotirea cubului Rubick in jurul axei OZ
			if (rotiri.size()>1 && rotiri[rotiri.size()-1].second==2){
				float aux=rotiri[rotiri.size()-1].first;
				rotiri.pop_back();
				rotiri.push_back(std::make_pair(aux+0.1f,2));		//Salvarea rotirii
			}
			else rotiri.push_back(std::make_pair(0.1f,2));
			break;
		case 'x':	
			mutari++;
			miscari=5;			//Rotirea stratului front la apasarea tastei 'x'
			layer=7;
			break;
		case 'y':	
			mutari++;
			miscari=5;			//Rotirea stratului front la apasarea tastei 'y'
			layer=8;
			break;
		case 'z':	
			mutari++;
			miscari=5;			//Rotirea stratului front la apasarea tastei 'z'
			layer=9;
			break;
		case 't':	
			mutari++;
			miscari=5;			//Rotirea stratului front la apasarea tastei 't'
			layer=1;
			break;
		case 'd':
			mutari++;
			miscari=5;			//Rotirea stratului front la apasarea tastei 'd'
			layer=2;
			break;
		case 'l':
			mutari++;
			miscari=5;			//Rotirea stratului front la apasarea tastei 'l'
			layer=3;
			break;
		case 'r':
			mutari++;
			miscari=5;			//Rotirea stratului front la apasarea tastei 'r'
			layer=4;
			break;
		case 'f':								
			mutari++;
			miscari=5;			//Rotirea stratului front la apasarea tastei 'f'
			layer=5;
			break;
		case 'b':
			mutari++;
			miscari=5;			//Rotirea stratului bottom la apasarea tastei 'b'
			layer=6;
			break;
		case 's':
			o2=creeazafata(points,topology,1,0,0,18,10,-10);
			o3=creeazafata(points2,topology,1,0,0,18,10,-10);
			o4=creeazafata(points3,topology,1,0,0,18,10,-10);		//Inceperea modului de rezolvare
			o5=creeazafata(points4,topology,1,0,0,18,10,-10);
			o6=creeazafata(points5,topology,1,0,0,18,10,-10);
			o7=creeazafata(points6,topology,1,0,0,18,10,-10);
			mutari=0;
			nr=1;
			break;

		case 'q':
			for(int i=0;i<scor.size();i++)
				cs1->objectRemove(scor[i]);
			glClearColor(0.4f,0.5f,1.1f,1);							//Reinitializarea jocului: disparitia scorului si aparitia cubului
			for(int i=0;i<fata.size();i++)
				cs1->objectAdd(fata[i]);
			nr=0;
			for(int i=rotiri.size()-1;i>=0;i--)
				rotestecuburi(fata,-rotiri[i].first,rotiri[i].second);
			rotiri.clear();
			animation=!animation;
	}
}


int main(int argc, char** argv){
	WorldDrawer3d wd3d(argc,argv,600,600,200,100,std::string("Lab 2"));
	wd3d.init();
	wd3d.run();
	return 0;
}