#if defined(__APPLE__)
	#include <OpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#else
	#include <GL/gl.h>
	#include <GL/freeglut.h>
#endif

void refresh(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		glColor(1,0,0);
		glVertex3f(-0.5,-0.333,0);
		glVertex3f(0.5,-0.333,0);
		glVertex3f(0,0.666,0);
	glutSwapBuffers();
}

void resize(int a, int b)
{
	int aux = a;
	if (a>b) aux=b;
	glViewport(a*0.1, b*0.1, aux, aux);
}

void ratoli(int a, int b, int x, int y) 
{
	
	glutPostRedisplay();
}

void motion(int x, int y) 
{
	
}

void teclat(unsigned char a, int x, int y)
{
	if (a == 'h') {
		cout << "Ajuda del Bloc 1" << endl;
	}
	if (a == 27) {
		return 0;
	}
}

int main(int argc, const char *argv[]) 
{
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindow("IDI: Practiques OpenGL");
	glutReshapeFunc(resize);
	glutDisplayFunc (refresh);
	glutMouseFunc(ratoli);
	glutMotionFunc(motion);
	glutKeyboardFunc(teclat);
	glutMainLoop();
	return 0;
}
