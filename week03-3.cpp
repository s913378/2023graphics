#include <GL/glut.h>
#include <stdio.h>
float X=0,Y=0,Z=0;
void display()
{
    //留下glClear()清背景，glutSwapBuffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSwapBuffers();
}
void mouse(int button,int state,int x,int y)
{
    X=(x-150)/150.0;
    Y=-(y-150)/150.0;
    if(state==GLUT_DOWN) printf("  glVertex2f(%.2f,%.2f);\n",X,Y);
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  //設定顯示模式
    glutCreateWindow("week03");  //視窗名稱
    glutMouseFunc(mouse);
    glutDisplayFunc(display);  //顯示的函式
    glutMainLoop();  //主要迴圈最後
}
