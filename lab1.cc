#if defined(__APPLE__)
	#include <OpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif
#include <stdio.h>

void refresh(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);
		glVertex3f(-0.5,-0.333,0);
		glColor3f(0,1,0);
		glVertex3f(0.5,-0.333,0);
		glColor3f(0,0,1);
		glVertex3f(0,0.666,0);
	glEnd();
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
	glClearColor(x*0.001,y*0.001,x+y*0.001,1);
	glutPostRedisplay();
}

void teclat(unsigned char a, int x, int y)
{
	if (a == 'h') {
		printf("Ajuda del Bloc 1\n");
	}
	if (a == 27) {
		exit(0);
	}
	if (a == 't')
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
