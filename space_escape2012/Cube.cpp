// EGC
// Laborator 7
//-------------------------------------------------

#include "Cube.h"

// constructor care primeste ca parametru latura cubului
Cube::Cube() : Object3D()
{
	// valori default
	diffuse = Vector4D(1,1,1,1);
	ambient = Vector4D(0,0,0,0);
	specular = Vector4D(1,1,1,1);
	color = Vector3D(1,1,1);
	scale = Vector3D(0.3,0.3,0.3);
	
	// default , nu este wireframe
	Wireframe = false;

	latura = 1.0;

}

// functie care seteaza latura cubului
void Cube::SetLatura(GLfloat _latura)
{
	latura = _latura;
}

// Seteaza culoare difuza ( atentie , la testul alfa se foloseste componenta A din culoarea difuza !!!_
void Cube::SetDiffuse(Vector4D *color)
{
	diffuse = *color;
}

void Cube::SetScale(Vector3D *meh)
{
	scale=*meh;
}

// DRAW
// Suprascriem prin polimorfism functia de desenare a clasei parinte 
// pentru a avea propria functie de desenare
//-------------------------------------------------
void Cube::Draw ()
{
	
	// daca nu este vizibil, nu-l desenam
	if(!Visible)
	return;

	glPushMatrix();

	// translatie
	glTranslatef( translation.x , translation.y , translation.z );

	// rotatie
	glRotatef( rotation.x , 1.0 , 0.0 , 0.0 );
	glRotatef( rotation.y , 0.0 , 1.0 , 0.0 );
	glRotatef( rotation.z , 0.0 , 0.0 , 1.0 );

	// scalare
	glScalef( scale.x , scale.y , scale.z);

	// setari de material :
	// daca nu este selectat
	if( !selected )
	{
		// culoare normala
		glColor3f(color.x,color.y,color.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(diffuse.x,diffuse.y,diffuse.z,diffuse.a)).Array());
	}
	else
	{
		// culoarea atunci cand obiectul este selectat
		glColor3f(SelectedColor.x, SelectedColor.y, SelectedColor.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(SelectedColor.x,SelectedColor.y,SelectedColor.z,1)).Array());
	}
	// culoare speculara, default
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(Vector4D(0.1,0.1,0.1,1)).Array());

	// daca este wireframe
	if( Wireframe )
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
	// daca nu este wireframe
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}

	glutSolidDodecahedron();

	glEnd();

	glPopMatrix();
}