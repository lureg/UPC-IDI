#if defined(__APPLE__)
	#include <OpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

char mode;
int x1, x2, x3, y1, y2, y3;
int count;
double width = 600;
double height = 600;
void refresh(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	if(mode == 't') {
		glColor3f(1,0,0);
		cout << width << " " << height << endl;
		
		glVertex3f(-1+double(x1)/double(width/2),-1+double(height-y1)/double(height/2),0);
		glColor3f(0,1,0);
		glVertex3f(-1+double(x2)/double(width/2),-1+double(height-y2)/double(height/2),0);
		glColor3f(0,0,1);
		glVertex3f(-1+double(x3)/double(width/2),-1+double(height-y3)/double(height/2),0);
	}
	else {
		glColor3f(1,0,0);
		glVertex3f(-0.5,-0.333,0);
		glColor3f(0,1,0);
		glVertex3f(0.5,-0.333,0);
		glColor3f(0,0,1);
		glVertex3f(0,0.666,0);
	}
		glEnd();
		glutSwapBuffers();
}

void resize(int a, int b)
{
	
	if (a>=b) {
		glViewport(a/2-b/2, 0, b, b);
		width=b; height=b;
	}
	else {
		glViewport(0,b/2-a/2,a,a);
		width=a; height=a;
	}
}

void ratoli(int a, int b, int x, int y) 
{
	if (x<=width and y <=height){
		if (mode == 't' && b==GLUT_UP) {
			cout << count << " x: " << x << " y: " << y << endl;
			if (count==3) { x1 = x; y1 = y;}
			else if (count==2) { x2 = x; y2 = y;}
			else if (count==1) { x3 = x; y3 = y;}
			count--;
			glutPostRedisplay();
		}
	}
	else cout << "Clica dins de la vista!" << endl;
}

void motion(int x, int y) 
{
	if (mode == 'f'){
	glClearColor(x*0.001,y*0.001,x+y*0.001,1);
	glutPostRedisplay();
	}
}

void teclat(unsigned char a, int x, int y)
{
	if (a == 'h') {
		cout << "Prem la tecla 'f' per activar o desactivar la modificació del color de fons" << endl;
		cout << "Prem la tecla 't' per a dibuixar un triangle mitjançant el ratolí" << endl;
		cout << "Prem ESC per a sortir de l'aplicació" << endl;
	}
	else if (a == 27) {
		exit(0);
	}
	else if (a == 't') { mode = 't'; count = 3; x1=x2=x3=y1=y2=y3=0;}
	else if (a == 'f') mode = 'f';
}

int main(int argc, const char *argv[]) 
{
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutCreateWindow("IDI: Practiques OpenGL");
	glutReshapeFunc(resize);
	glutDisplayFunc (refresh);
	glutMouseFunc(ratoli);
	glutMotionFunc(motion);
	glutKeyboardFunc(teclat);
	glutMainLoop();
	return 0;
}
