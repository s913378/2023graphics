#include <GL/glut.h>
void display()
{
    glColor3f(233/255.0,141/255.0,128/255.0);
    glBegin(GL_POLYGON);
    glVertex2f((65-100)/100.0,-(54-100)/100.0);
    glVertex2f((34-100)/100.0,-(138-100)/100.0);
    glVertex2f((55-100)/100.0,-(138-100)/100.0);
    glVertex2f((87-100)/100.0,-(53-100)/100.0);
    glEnd();
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
