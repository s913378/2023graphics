#include <GL/glut.h>
#include "glm.h"
GLMmodel*pmode1=NULL;
void display()
{
    if(pmode1==NULL){
        pmode1=glmReadOBJ("week08.obj");
        glmUnitize(pmode1);
    }
    glmDraw(pmode1,GLM_SMOOTH|GLM_MATERIAL);
    ///glutSolidTeapot( 0.3 );
    glutSwapBuffers();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    glutDisplayFunc(display);
    glutMainLoop();
}
