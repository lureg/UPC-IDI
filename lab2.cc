#if defined(__APPLE__)
	#include <OpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif
#include <string>
#include <iostream>
using namespace std;

string mode;
int xx = 0;
int yy = 0;
int zz = 0;
int mx = 0;
int my = 0;


void refresh(void)
{
	
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glRotated(xx,yy,zz,1);
	glutWireTeapot(0.5);
	
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
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);
		glVertex3f(x,y,0);
		glColor3f(0,1,0);
		glVertex3f(x,y,0);
		glColor3f(0,0,1);
		glVertex3f(x,y,0);
	glEnd();
	glutPostRedisplay();
}

void motion(int x, int y) 
{
	if (mode == "c") {
		glClearColor(x*0.001,y*0.001,x+y*0.001,1);
	}
	if (mode == "rx") {
		yy = 0;
		zz = 0;
		if (mx < x) xx += 5; 
		else xx -=5;
		cout << "mx = " << mx << " x = " << x << endl;
		mx = x;
	}
	if (mode == "ry") {
		xx= 0;
		zz= 0;
		if (my < y) yy += 5;
		else yy -=5;
		cout << "my = " << my << " y = " << y << endl;
		my = y;
	}
	if (mode == "rz") {
		xx = 0;
		yy = 0;
		if (mx > x) zz += 5;
		else zz -=5;
		cout << "mz = " << my << " z = " << y << endl;
		mx = x;
	}
		glTranslated(1-x,1-y,0);
	
	glutPostRedisplay();
}

void teclat(unsigned char a, int x, int y)
{
	if (a == 'h') {
		cout << "Ajuda del bloc 2" << endl;
		cout << "La tecla r serveix per a canviar al mode rotacions" << endl;
		cout << "La tecla t serveix per a canviar al mode translacions" << endl;
		cout << "La tecla c serveix per a canviar el color de fons" << endl;
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
		cout << "Prem x, y o z per a sel·leccionar l'eix de rotació. Prem '+' per a sel·leccionar més d'un eix." << endl;
	}
	else if (a == 'c') {
		mode = a;
		cout << "Mou el ratolí per la pantalla i canvia el color de fons" << endl;
	}
	else if (a == 'x') mode = "rx";
	else if (a == 'y') mode = "ry";
	else if (a == 'z') mode = "rz";
	
}

int main(int argc, const char *argv[]) 
{
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutCreateWindow("IDI: Practiques OpenGL");
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glutReshapeFunc(resize);
	glutDisplayFunc (refresh);
	glutMouseFunc(ratoli);
	glutMotionFunc(motion);
	glutKeyboardFunc(teclat);
	glutMainLoop();
	return 0;
}
