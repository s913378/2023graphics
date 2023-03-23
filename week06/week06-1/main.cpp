/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/glut.h>
float angle=0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSolidSphere(0.01, 30 ,30);

    glPushMatrix();
        glRotatef(angle, 0, 0,1);
        glTranslatef(0.45, 0, 0);
        glColor3f(0,1,0);
        myCube();
    glPopMatrix();

	glutSwapBuffers();
	angle++;
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("week03");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
}
