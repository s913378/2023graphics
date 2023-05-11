#include <GL/glut.h>
void display()
{
    glPushMatrix();
        glTranslatef( 0.5, 0.5, 0);
        glutSolidTeapot( 0.3 );
    glPopMatrix();
    glutSwapBuffers();  //交換顯示
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  //設定顯示模式
    glutCreateWindow("week02");  //視窗名稱
    glutDisplayFunc(display);  //顯示的函式
    glutMainLoop();  //主要迴圈最後
}
