#include <GL/glut.h>
void display()
{
    glPushMatrix();
        glTranslatef( 0.5, 0.5, 0);
        glutSolidTeapot( 0.3 );
    glPopMatrix();
    glutSwapBuffers();  //�洫���
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  //�]�w��ܼҦ�
    glutCreateWindow("week02");  //�����W��
    glutDisplayFunc(display);  //��ܪ��禡
    glutMainLoop();  //�D�n�j��̫�
}
