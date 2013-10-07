#if defined(__APPLE__)
	#include <OpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif
#include <string>
#include <iostream>
#include "model.h"
using namespace std;

string mode;
double xx = 0;
double yy = 0;
double zz = 0;

int ax = 0;
int ay = 0;
int az = 0;
double angle = 0;

double ex;
double ey;
double ez;

double mx = 0;
double my = 0;

double width = 600;
double height = 600;
double maxX, maxY, maxZ;
double minX, minY, minZ;
double centX, centY, centZ;
double maxTam;
Model m;
vector<Model> models;

void minimax() {
	maxX = minX = m.vertices()[0];
	maxY = minY = m.vertices()[1];
	maxZ = minZ = m.vertices()[2];

	for(int i = 3; i < m.vertices().size(); i += 3) {
		maxX = max(maxX,m.vertices()[i]);
		minX = min(minX,m.vertices()[i]);

		maxY = max(maxY,m.vertices()[i+1]);
		minY = min(minY,m.vertices()[i+1]);

		maxZ = max(maxZ,m.vertices()[i+2]);
		minZ = min(minZ,m.vertices()[i+2]);
	}

	centX = ((maxX - minX)/2) + minX;
	centY = ((maxY - minY)/2) + minY;
	centZ = ((maxZ - minZ)/2) + minZ;
	
	maxTam = max(max(maxX - minX, maxY - minY), maxZ - minZ);
}

void pintaMODEL() {
	minimax();
	glPushMatrix();
	glBegin(GL_TRIANGLES);
		for(int i = 0; i < m.faces().size(); i++){
			const Face &f = m.faces()[i];
			
			for(int j = 0; j < 3; j++)
				//glColor4dv(reinterpret_cast<double*>(Materials[f.mat].diffuse));
				glVertex3dv(&m.vertices()[f.v[j]]);
		}
	glEnd();
	glPopMatrix();
}

void pintaNINOT(){
	
	glPushMatrix();
	glTranslated(0,0,0);
	glutWireSphere(0.4, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0.6,0);
	glutWireSphere(0.2, 30, 30);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0.1,0.6,0);
	glRotated(90,0,1,0);
	glutWireCone(0.1,0.2,20,20);
	glPopMatrix();
}

void pintaQUADRAT() {
	glPushMatrix();
	glRotated(10,1,0,0);
	glRotated(10,0,1,0);
	glTranslated(0,-0.4,0);
	glBegin(GL_QUADS);
		glVertex3f(-0.5,-0.4,-1);
		glVertex3f(1,-0.4,-1);
		glVertex3f(1,-0.4,0.5);
		glVertex3f(-0.5,-0.4,0.5);
	glEnd();
	glPopMatrix();
}

void refresh(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLoadIdentity();
	glPushMatrix();
	glRotated(angle,ax,ay,az);
	glTranslated(xx,yy,zz);
	
	glPushMatrix();
	glRotated(angle, 0.0, 1.0, 0.0);
	glTranslated(-(centX / maxTam), -(centY / maxTam), -(centZ / maxTam));
	glScaled(0.5,0.5,0.5);
	pintaMODEL();
	glPopMatrix();
	
	pintaQUADRAT();
	pintaNINOT();	
	
	glPopMatrix();

	glutSwapBuffers();
}

void resize(int a, int b)
{
	if (a>=b) {
		glViewport(a/2-b/2, 0, b, b);
	}
	else
		glViewport(0,b/2-a/2,a,a);
}

void ratoli(int a, int b, int x, int y) 
{

}

void motion(int x, int y) 
{
	if (mode == "c") {
		glClearColor(x*0.001,y*0.001,x+y*0.001,1);
	}
	if (mode == "t") {
		xx = -1+double(x)/double(width/2);
		yy = -1+double(height-y)/double(height/2);
		cout << xx << "   " << yy << endl;
	}	
	if (mode == "r") {
		if(ax)cout << "Seleccionat eix de gir X "; 
		if(ay)cout << "Seleccionat eix de gir Y ";
		if(az)cout << "Seleccionat eix de gir Z ";
		cout << angle << endl;
		if (my > y) angle--;
		else angle++;
		if (angle==360 or angle==-360) angle =0;
		my=y;
	}
	glutPostRedisplay();
}

void teclat(unsigned char a, int x, int y)
{
	if (a == 'h') {
		cout << "Ajuda del bloc 2" << endl;
		cout << "La tecla 'r' serveix per a canviar al mode rotacions" << endl;
		cout << "La tecla 't' serveix per a canviar al mode translacions" << endl;
		cout << "La tecla 'c' serveix per a canviar el color de fons" << endl;
		cout << "La tecla 'e' serveix per a canviar al mode reescalar" << endl;
		cout << "ESC tanca el programa" << endl;
	}
	else if (a == 27) {
		exit(0);
	}
	else if (a == 't') {
		mode = a;
		cout << "Mou el ratolí per la pantalla i arrossega el model" << endl;
	}
	else if (a == 'r') {
		mode = a;
		cout << "Mou el ratolí per la pantalla i fes girar el model" << endl;
		cout << "Prem x, y o z per a sel·leccionar l'eix de rotació. Per a desel·leccionar-lo torna a prémer la tecla" << endl;
	}
	else if (a == 'c') {
		mode = a;
		cout << "Mou el ratolí per la pantalla i canvia el color de fons" << endl;
	}
	else if (a == 'e') {
		mode = a;
		cout << "Introdueix noves x, y i z i canvia el tamany de la figura" << endl;
		cout << "x: "; cin >> ex; cout << "y: "; cin >> ey; cout << "z: "; cin >> ez; cout << endl;
	}
	else if (a == 'x') {
		if (ax==1) ax = 0;
		else ax = 1;
	}
	else if (a == 'y') {
		if (ay==1) ay = 0;
		else ay = 1;
	}
	else if (a == 'z') {
		if (az==1) az = 0;
		else az = 1;
	}

	
}

void carregamodel(string s) {
	m.load(s);
	cout << m.vertices().size() << endl;
	cout << m.normals().size() << endl;
	cout << m.faces().size() << endl;
}

int main(int argc, const char *argv[]) 
{
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutCreateWindow("IDI: Practiques OpenGL");
	string nommodel;
	cout << "Escriu al terminal el nom del model a carregar:" << endl;
	cin>>nommodel;
	carregamodel(nommodel);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc (refresh);
	glutReshapeFunc(resize);
	glutMouseFunc(ratoli);
	glutMotionFunc(motion);
	glutKeyboardFunc(teclat);
	glutMainLoop();
	return 0;
}
