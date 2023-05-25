#include <GL/glut.h>
#include <math.h>
void cir(float r,float x,float y)
{
    glBegin(GL_POLYGON);
    for(float a=0;a<=2*3.141592;a+=0.01){
        glVertex2f(r*cos(a)+x,r*sin(a)+y);
    }
    glEnd();
}
void display()
{
    glColor3f(233/255.0,141/255.0,128/255.0);
    cir(0.5,0,0);
    glColor3f(1,1,0);
    cir(0.3,0.5,0.5);
    glColor3f(1,0,0);
    cir(0.3,-0.5,0.5);
    glColor3f(0,1,0);
    cir(0.3,-0.5,-0.5);
    glColor3f(0,0,1);
    cir(0.3,0.5,-0.5);
    glutSwapBuffers();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("week02");
    glutDisplayFunc(display);
    glutMainLoop();
}
