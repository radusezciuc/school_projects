#include <stdlib.h>
#include <freeglut.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "Camera.h"
#include "Object3D.h"
#include "Plane.h"
#include "Light.h"
#include "Cube.h"
#include "Vector3D.h"
#include "Vector4D.h"

// tasta escape
#define ESC	27

typedef struct Vertex {
  float x, y, z;
} Vertex;

typedef struct Face {
  Face(void) : nverts(0), verts(0) {};
  int nverts;
  Vertex **verts;
  float normal[3];
} Face;

typedef struct Mesh {
  Mesh(void) : nverts(0), verts(0), nfaces(0), faces(0) {};
  int nverts;
  Vertex *verts;
  int nfaces;
  Face *faces;
} Mesh;

static Mesh *mesh = NULL;

using namespace std;
std::vector<Cube*> objects;
std::vector<Vector3D*> pos;
std::vector<int> asteroizi;
int globala=631;
int timp=0;
int vieti=2;
int laser=50;
double t;

float *Vector3D::arr;
float *Vector4D::arr;

// Display variables

static int scaling = 0;
static int translating = 0;
static int rotating = 0;
static float scale = 1.0;
static float center[3] = { 0.0, 0.0, 0.0 };
static float rotation[3] = { 0.0, 0.0, 0.0 };
static float translation[3] = { 0.0, 0.0, 0.0 };


// VARIABILE
//-------------------------------------------------
// numarul de obiecte
int objectCount;
// obiectul selectat
int selectedIndex = -1;

// camera
Camera *camera_dinamica,*camera_nava,*camera_asteroid;
int camera=1;
// vector de obiecte 3D
// planul de baza

// lumina omni
Light *light_o1;
Light *light_o2;
int o1=1,o2=1;
// lumina spot
Light *light_s1;
Light *light_s2;

// variabila pentru animatie
GLfloat spin=0.0;
double misc=0;

// variabile necesare pentru listele de afisare

int drawLists = 1;

Vector3D *coordnava;
Vector3D *coords1,*coords2;
Vector3D *coordc,*coordcn,*coordca;

// variabila folosita pentru a determina daca listele de afisare trebuiesc recalculate
int recomputeLists = 0;

// identificatori ferestre
int fereastraStanga=-1,fereastraDreapta=-1,mainWindow;
int obiect = 0;


Mesh *
ReadOffFile(const char *filename)
{
  int i;

  // Open file
  FILE *fp;
  if (!(fp = fopen(filename, "r"))) {
    fprintf(stderr, "Unable to open file %s\n", filename);
    return 0;
  }

  // Allocate mesh structure
  Mesh *mesh = new Mesh();
  if (!mesh) {
    fprintf(stderr, "Unable to allocate memory for file %s\n", filename);
    fclose(fp);
    return 0;
  }

  // Read file
  int nverts = 0;
  int nfaces = 0;
  int nedges = 0;
  int line_count = 0;
  char buffer[1024];
  while (fgets(buffer, 1023, fp)) {
    // Increment line counter
    line_count++;

    // Skip white space
    char *bufferp = buffer;
    while (isspace(*bufferp)) bufferp++;

    // Skip blank lines and comments
    if (*bufferp == '#') continue;
    if (*bufferp == '\0') continue;

    // Check section
    if (nverts == 0) {
      // Read header 
      if (!strstr(bufferp, "OFF")) {
        // Read mesh counts
        if ((sscanf(bufferp, "%d%d%d", &nverts, &nfaces, &nedges) != 3) || (nverts == 0)) {
          fprintf(stderr, "Syntax error reading header on line %d in file %s\n", line_count, filename);
          fclose(fp);
          return NULL;
        }

        // Allocate memory for mesh
        mesh->verts = new Vertex [nverts];
        assert(mesh->verts);
        mesh->faces = new Face [nfaces];
        assert(mesh->faces);
      }
    }
    else if (mesh->nverts < nverts) {
      // Read vertex coordinates
      Vertex& vert = mesh->verts[mesh->nverts++];
      if (sscanf(bufferp, "%f%f%f", &(vert.x), &(vert.y), &(vert.z)) != 3) {
        fprintf(stderr, "Syntax error with vertex coordinates on line %d in file %s\n", line_count, filename);
        fclose(fp);
        return NULL;
      }
    }
    else if (mesh->nfaces < nfaces) {
      // Get next face
      Face& face = mesh->faces[mesh->nfaces++];

      // Read number of vertices in face 
      bufferp = strtok(bufferp, " \t");
      if (bufferp) face.nverts = atoi(bufferp);
      else {
        fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
        fclose(fp);
        return NULL;
      }

      // Allocate memory for face vertices
      face.verts = new Vertex *[face.nverts];
      assert(face.verts);

      // Read vertex indices for face
      for (i = 0; i < face.nverts; i++) {
        bufferp = strtok(NULL, " \t");
        if (bufferp) face.verts[i] = &(mesh->verts[atoi(bufferp)]);
        else {
          fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
          fclose(fp);
          return NULL;
        }
      }

      // Compute normal for face
      face.normal[0] = face.normal[1] = face.normal[2] = 0;
      Vertex *v1 = face.verts[face.nverts-1];
      for (i = 0; i < face.nverts; i++) {
        Vertex *v2 = face.verts[i];
        face.normal[0] += (v1->y - v2->y) * (v1->z + v2->z);
        face.normal[1] += (v1->z - v2->z) * (v1->x + v2->x);
        face.normal[2] += (v1->x - v2->x) * (v1->y + v2->y);
        v1 = v2;
      }

      // Normalize normal for face
      float squared_normal_length = 0.0;
      squared_normal_length += face.normal[0]*face.normal[0];
      squared_normal_length += face.normal[1]*face.normal[1];
      squared_normal_length += face.normal[2]*face.normal[2];
      float normal_length = sqrt(squared_normal_length);
      if (normal_length > 1.0E-6) {
        face.normal[0] /= normal_length;
        face.normal[1] /= normal_length;
        face.normal[2] /= normal_length;
      }
    }
    else {
      // Should never get here
      fprintf(stderr, "Found extra text starting at line %d in file %s\n", line_count, filename);
      break;
    }
  }

  // Check whether read all faces
  if (nfaces != mesh->nfaces) {
    fprintf(stderr, "Expected %d faces, but read only %d faces in file %s\n", nfaces, mesh->nfaces, filename);
  }

  // Close file
  fclose(fp);

  // Return mesh 
  return mesh;
}
void init(void)
{
	// pregatim o scena noua in opengl
	glClearColor(0.0, 0.0, 0.0, 0.0);	// stergem tot
	glEnable(GL_DEPTH_TEST);	// activam verificarea distantei fata de camera (a adancimii)
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_LEQUAL,1);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);			// mod de desenare SMOOTH
	glEnable(GL_LIGHTING);				// activam iluminarea
	glEnable(GL_NORMALIZE);				// activam normalizarea normalelor
}

void initScene(void)
{
	// initialize vector arrays
	Vector3D::arr = new float[3];
	Vector4D::arr = new float[4];
	srand(time(NULL));
	mesh=ReadOffFile("m1354.off");
	coordnava=new Vector3D(-5,0,6);
	coords1=new Vector3D(4.4, 0.1, -5.8);
	coords2=new Vector3D(4.4, 0.1, -6.2);
	coordcn=new Vector3D(4,0.12,-6.25);
	// initializam camera pentru vedere top
	camera_dinamica = new Camera();
	t=0.3;
	// initializam camera pentru vedere front ( cea default )
	camera_nava= new Camera();
	camera_nava->SetPosition(coordcn);
	camera_nava->SetForwardVector(new Vector3D(-1,0,0));
	camera_nava->SetRightVector(new Vector3D(0,0,-1));
	camera_nava->SetUpVector(new Vector3D(0,1,0));

	// initializam o noua lumina omnidirectionala
	light_o1 = new Light();
	light_o2 = new Light();
	// setam pozitia
	light_o1->SetPosition(new Vector3D(-10, -5, -5));
	light_o2->SetPosition(new Vector3D(5, 20, 5));
	light_o1->SetDiffuse(new Vector4D(1,0,0,1.0));
	light_o2->SetDiffuse(new Vector4D(0,0,1,1.0));


	// initializam o noua lumina spot
	light_s1 = new Light();
	light_s2 = new Light();
	light_s1->SetLightType(IlluminationType::Spot);
	light_s2->SetLightType(IlluminationType::Spot);
	// setam pozitia
	light_s1->SetPosition(new Vector3D(-4.4, 0.1, 5.8));
	light_s2->SetPosition(new Vector3D(-4.4, 0.1, 6.2));
	
}

void drawScene(void)
{
	if(glutGetWindow() == fereastraStanga && camera==1)
	{
		camera_dinamica->Render();
	}
	if(glutGetWindow() == fereastraStanga && camera==2)
	{
		camera_nava->SetPosition(coordcn);
		camera_nava->Render();
	}
	if(glutGetWindow() == fereastraStanga && camera==3)
	{
		camera_asteroid->Render();
	}

	// activare lumina omnidirectionala
	if (o1==1)
		light_o1->Render();
	else light_o1->Disable();
	if (o2==1)
		light_o2->Render();
	else light_o2->Disable();
	light_s1->SetPosition(coords1);
	light_s2->SetPosition(coords2);
	light_s1->Render();
	light_s2->Render();
	
	GLuint *buffer = new GLuint();
	// desenare obiecte
	glInitNames();

	timp=time(NULL);
	
	double y= rand()%10-5;
	double z= rand()%15-15;
	
	if (globala%95==0){ 
		objects.push_back(new Cube());
		pos.push_back(new Vector3D(-6,y,z));
		(*objects[objects.size()-1]).SetPosition(pos[pos.size()-1]);
		(*objects[objects.size()-1]).deseneaza=true;
		(*objects[objects.size()-1]).SetDiffuse(new Vector4D(0.4,0.3,0.3,1.0));
		int meh=globala%6;
		if (meh%2==0)
			(*objects[objects.size()-1]).SetDiffuse(new Vector4D(0.9,0.3,0.3,1.0));
		else if (meh%3==0)
			(*objects[objects.size()-1]).SetDiffuse(new Vector4D(0.4,0.3,0.9,1.0));
	}
	if (obiect!=0){
		 glLineWidth(2.5); 
		 glColor3f(0.9,0.0,0.0);
		 glBegin(GL_LINES);
		 glVertex3f(-coordnava->x-0.5,coordnava->y+0.1,-coordnava->z);
		 glVertex3f((*pos[obiect]).x,(*pos[obiect]).y,(*pos[obiect]).z);
		 (*objects[obiect]).deseneaza=false;
		 glEnd();
		 laser--;
		 if (laser==0){
			obiect=0;
			laser=50;
		 }
	}
	glInitNames();
	double dist;
	for ( int i = 0 ; i < objects.size() ; i++ )
	{
		(*pos[i]).x=(*pos[i]).x+0.01;
		(*objects[i]).SetPosition(pos[i]);
		glPushName(i);
		if ((*objects[i]).deseneaza==true)
			(*objects[i]).Draw();
		glPopName();
		if ((*pos[i]).x>=5)
			(*objects[i]).deseneaza=false;
		double x=(*pos[i]).x;
		double y=(*pos[i]).y;
		double z=(*pos[i]).z;
		bool ok=false;
		dist=sqrt((-coordnava->x-0.5-x)*(-coordnava->x-0.5-x)+(coordnava->y+0.1-y)*(coordnava->y+0.1-y)+(-0.25-coordnava->z-z)*(-0.25-coordnava->z-z));
		if (dist<1 && vieti!=-1){
			for (int j=0;j<asteroizi.size();j++){
				if (asteroizi[j]==i)
					ok=true;
			}
			if (ok==false){
				vieti--;
				if (vieti==1)
					o1=0;
				if (vieti==0)
					o2=0;
				(*objects[i]).deseneaza=false;
				asteroizi.push_back(i);
				ok=false;
			}	
		}
	}

	light_o1->Draw();
	light_o2->Draw();

	if (vieti!=-1){
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glPushMatrix();
	glColor4f(0,0,1,t);
	glTranslatef(-coordnava->x-0.5,coordnava->y+0.1,-0.25-coordnava->z);
	glutSolidSphere(0.6,35,35);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();

	glPushMatrix();
	// Draw faces
	
	glRotatef(180,0,1,0);
	glTranslatef(coordnava->x,coordnava->y,coordnava->z);
	for (int i = 0; i < mesh->nfaces; i++) {
		Face& face = mesh->faces[i];
		glBegin(GL_POLYGON);
		glNormal3fv(face.normal);
		for (int j = 0; j < face.nverts; j++) {
		Vertex *vert = face.verts[j];
		glVertex3f(vert->x, vert->y, vert->z);
    }
    glEnd();
	}
	glPopMatrix();}
}

void display(void)
{
	// stergere ecran
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	globala++;
	if(glutGetWindow() == mainWindow)
		return;	
	// Render Pass - deseneaza scena
	drawScene();
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);

	// double buffering
	glutSwapBuffers();
	
	// redeseneaza scena
	glutPostRedisplay();
	glDepthMask(GL_TRUE);
	if (globala>=32000)
		globala=0;
}


void processhits (GLint hits, GLuint buffer[]) {
   int i;
   GLuint names, *ptr, minZ,*ptrNames, numberOfNames;

   // pointer la inceputul bufferului ce contine hit recordurile
   ptr = (GLuint *) buffer;
   // se doreste selectarea obiectului cel mai aproape de observator
   minZ = 0xffffffff;
   for (i = 0; i < hits; i++) 
   {
      // numarul de nume numele asociate din stiva de nume
      names = *ptr;
	  ptr++;
	  ptrNames = ptr+2;
	  // salt la urmatorul hitrecord
	  ptr += names+2;
  }

  // identificatorul asociat obiectului
  ptr = ptrNames;
  obiect = *ptr;
}


void pick(int x, int y)
{
	// buffer de selectie
	GLuint buffer[1024];

	// numar hituri
	GLint nhits;

	// coordonate viewport curent
	GLint	viewport[4];

	// se obtin coordonatele viewportului curent
	glGetIntegerv(GL_VIEWPORT, viewport);
	// se initializeaza si se seteaza bufferul de selectie
	memset(buffer,0x0,1024);
	glSelectBuffer(1024, buffer);
	
	// intrarea in modul de selectie
	glRenderMode(GL_SELECT);

	// salvare matrice de proiectie curenta
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// se va randa doar intr-o zona din jurul cursorului mouseului de [1,1]
	glGetIntegerv(GL_VIEWPORT,viewport);
	gluPickMatrix(x,viewport[3]-y,1.0f,1.0f,viewport);

	gluPerspective(45,(viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]),0.1,1000);
	glMatrixMode(GL_MODELVIEW);

	// se "deseneaza" scena : de fapt nu se va desena nimic in framebuffer ci se va folosi bufferul de selectie
	drawScene();

	// restaurare matrice de proiectie initiala
	glMatrixMode(GL_PROJECTION);						
	glPopMatrix();				

	glMatrixMode(GL_MODELVIEW);
	// restaurarea modului de randare uzual si obtinerea numarului de hituri
	nhits=glRenderMode(GL_RENDER);	
	
	// procesare hituri
	if(nhits != 0)
		processhits(nhits,buffer);
	else
		obiect=0;		
}

void reshapeStanga(int w, int h)
{
	glViewport(0,0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)w/h, 1.0, 60.0); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Initializeaza contextul OpenGL asociat ferestrei
	init();
}


// functie de proiectie

void miscare(){
	misc=misc+0.001;
	spin=spin+1;
	if(spin>360.0)
		spin= spin -360.0;
}
void keyboard(unsigned char key , int x, int y)
{
	switch (key)
	{
		// la escape se iese din program
	
	case 'w' :
		coordnava->y+=0.1;
		coords1->y+=0.1;
		coords2->y+=0.1;
		coordcn->y+=0.1;
		break;
	case 's' :
		coordnava->y+=-0.1;
		coords1->y+=-0.1;
		coords2->y+=-0.1;
		coordcn->y+=-0.1;
		break;
	case 'a' :
		coordnava->x-=-0.1;
		coords1->x+=-0.1;
		coords2->x+=-0.1;
		coordcn->x+=-0.1;
		break;
	case 'd' :  
		coordnava->x-=0.1;
		coords1->x+=0.1;
		coords2->x+=0.1;
		coordcn->x+=0.1;
		break;
	case 'z' :  
		coordnava->z+=0.1;
		coords1->z+=0.1;
		coords2->z+=0.1;
		coordcn->z-=0.1;
		break;
	case 'x' :  
		coordnava->z-=0.1;
		coords1->z-=0.1;
		coords2->z-=0.1;
		coordcn->z+=0.1;
		break;
	case 'i' :
		if (camera==1 ||camera==2)
			camera_nava->MoveUpward(0.2);
		break;
	case 'k' :
		if (camera==1 || camera==2)
			camera_nava->MoveDownward(0.2);
		break;
	case 'j' :
		if (camera==1 || camera==2)
			camera_nava->MoveRight(0.2);
		break;
	case 'l' :
		if (camera==1 || camera==2)
			camera_nava->MoveLeft(0.2);
		break;
	case 'o' :
		if (camera==1 ||camera==2)
			camera_nava->MoveForward(0.2);
		break;
	case 'p' :
		if (camera==1|| camera==2)
			camera_nava->MoveBackward(0.2);
		break;
	case '1' :
		camera=1;
		break;
	case '2':
		camera=2;
		break;
	case '3':
		camera=3;
		break;
	default: break;
	}
}

// handler taste speciale
void keyboard(int key , int x, int y)
{
	/*// incercam sa obtinem un pointer la obiectul selectat
	Object3D *selected;
	// daca nu exista un astfel de obiect
	if( selectedIndex >= 0 && selectedIndex < objectCount )
		selected = &objects[selectedIndex];
	else
		// se iese din functie
		return;

	// cu stanga/dreapta/sus/jos se misca obiectul curent
	switch (key)
	{
	case GLUT_KEY_RIGHT : 
		selected->SetPosition(&(selected->GetPosition() + Vector3D(0.2,0,0))); break;
	case GLUT_KEY_LEFT : 
		selected->SetPosition(&(selected->GetPosition() + Vector3D(-0.2,0,0))); break;
	case GLUT_KEY_DOWN : 
		selected->SetPosition(&(selected->GetPosition() + Vector3D(0,-0.2,0))); break;
	case GLUT_KEY_UP : 
		selected->SetPosition(&(selected->GetPosition() + Vector3D(0,0.2,0))); break;
	}*/
}
void mouse(int buton, int stare, int x, int y)
{
	switch(buton)
	{
	// Am apasat click stanga : porneste animatia si realizeaza picking
	case GLUT_LEFT_BUTTON:
		if(stare == GLUT_DOWN)
		{
			// in aceasta variabila se va intoarce obiectul la care s-a executat pick
			obiect = 0;

			pick(x,y);

			glutIdleFunc(miscare);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if(stare== GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	}
}

void reshape(int w, int h)
{
	// Main Window
	glViewport(0,0, (GLsizei) w, (GLsizei) h);
	// calculare aspect ratio ( Width/ Height )
	GLfloat aspect = (GLfloat) w / (GLfloat) h;

	// intram in modul proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// incarcam matrice de perspectiva 
	gluPerspective(45, aspect, 1.0, 60);

	// Initializeaza contextul OpenGL asociat ferestrei
	init();

	// Fereastra aplicatiei a fost redimensionata : trebuie sa recream subferestrele

	if(fereastraStanga != -1)
		glutDestroyWindow(fereastraStanga);

	// Creeaza fereastra stanga
	fereastraStanga = glutCreateSubWindow(mainWindow,0,0,w,h);

 	glutDisplayFunc(display);
	glutReshapeFunc(reshapeStanga);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard);
}




int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	int w = 800, h= 600;
	glutInitWindowSize(w,h);
	glutInitWindowPosition(100,100);
	
	// Main window
	mainWindow = glutCreateWindow("Lab7");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(miscare);

	// Initializeaza scena 3D
	initScene();

	glutMainLoop();
	return 0;
}