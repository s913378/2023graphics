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
void display()
{
     glColor3f(0,1,0);
     glBegin(GL_POLYGON);
        glVertex2f((168-100)/100.0,  -(78-100)/100.0);
        glVertex2f ((266-100)/100.0,  -(76-100)/100.0);
        glVertex2f ((96-100)/100.0, -(302-100)/100.0);
        glVertex2f ((151-100)/100.0, -( 306-100)/100.0);
        glVertex2f ((172-100)/100.0, -(230-100)/100.0);
        glVertex2f ((239-100)/100.0, -(220-100)/100.0);
        glVertex2f ((272-100)/100.0, -(307-100)/100.0);
        glVertex2f ((315-100)/100.0, -(310-100)/100.0);
        glVertex2f ((267-200)/100.0,  -(82-100)/100.0);

    glEnd();

     glutSwapBuffers();
}
int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week02");
    glutDisplayFunc(display);
    glutMainLoop();
}
