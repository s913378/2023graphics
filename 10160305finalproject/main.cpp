
#include <windows.h>
#include <opencv/highgui.h> ///�ϥ� OpenCV 2.1 ���²��, �u�n�� High GUI �Y�i
#include <opencv/cv.h>
#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"
#include "CMP3_MCI.h" //�����޸��A��ܦb�P�@�ؿ�
CMP3_MCI myMP3;
GLMmodel * head = NULL;
GLMmodel * eyeandbrown = NULL;
GLMmodel * body = NULL; ///GLMmodel * gundam = NULL;
GLMmodel * arm1 = NULL, * arm2 = NULL;
GLMmodel * hand1 = NULL, * hand2 = NULL;
GLMmodel * bot = NULL;
GLMmodel * leg1 = NULL, * leg2 = NULL;
GLMmodel * foot1 = NULL, * foot2 = NULL;
float teapotX = 0, teapotY = 0, oldX = 0, oldY = 0;
float angle[20] = {}, angle2[20] = {};///float angle = 0, angle2 = 0;
float NewAngle[20] = {}, NewAngle2[20] = {};
float OldAngle[20] = {}, OldAngle2[20] = {};
GLuint tex1 , tex2, tex3, tex4 , tex5, tex6 , tex7 ,tex8 ,tex9, tex10  ,tex11 , tex12 ,tex13 ,tex14;
int ID = 0;
FILE * fout = NULL;
FILE * fin = NULL;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };///Z���ȧ令�t�� �����q������

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void timer(int t) {
    printf("�{�btimer(%d)\n", t);
    glutTimerFunc(20, timer, t+1); ///���W�]�w�U�@�Ӿx��

    float alpha = (t%50) / 50.0; ///0.0 ~ 1.0

    if(t%50==0){
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            OldAngle[i] = NewAngle[i];
            OldAngle2[i] = NewAngle2[i];
            fscanf(fin, "%f", &NewAngle[i] );
            fscanf(fin, "%f", &NewAngle2[i] );
        }
    }
    for(int i=0; i<20; i++){
        angle[i] = NewAngle[i] * alpha + OldAngle[i] * (1-alpha);
        angle2[i] = NewAngle2[i] * alpha + OldAngle2[i] * (1-alpha);
    }

    glutPostRedisplay();
}


void myLight()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}
void keyboard(unsigned char key, int x, int y) {
    if(key=='0') ID = 0;
    if(key=='1') ID = 1;
    if(key=='2') ID = 2;
    if(key=='3') ID = 3;
    if(key=='4') ID = 4;
    if(key=='5') ID = 5;
    if(key=='6') ID = 6;
    if(key=='7') ID = 7;
    if(key=='8') ID = 8;
    if(key=='9') ID = 9;
    if(key=='a') ID =10;
    if(key=='w') ID =11;
    if(key=='s'){ ///save�s�� �]�|�ʨ��ɮ�
        if(fout == NULL) fout = fopen("motion.txt", "w");
        for(int i=0; i<20; i++){
            fprintf(fout, "%.2f ", angle[i] );
            fprintf(fout, "%.2f ", angle2[i] );
        }
        fprintf(fout, "\n");
        printf("�g�F�@��\n");
    }
    if(key=='r'){ ///readŪ�� �]�|�ʨ��ɮ�
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            fscanf(fin, "%f", &angle[i] );
            fscanf(fin, "%f", &angle2[i] );
        }
        glutPostRedisplay();
    }
    if(key=='p'){ ///play���� �]�|�ʨ��ɮ�
        glutTimerFunc(0, timer, 0);
        myMP3.Play();
    }
}

int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCVŪ��
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV���m (�ݭncv.h)
    glEnable(GL_TEXTURE_2D); ///1. �}�ҶK�ϥ\��
    GLuint id; ///�ǳƤ@�� unsigned int ���, �s �K��ID
    glGenTextures(1, &id); /// ����Generate �K��ID
    glBindTexture(GL_TEXTURE_2D, id); ///�j�wbind �K��ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// �K�ϰѼ�, �W�L�]�˪��d��T, �N���жK��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// �K�ϰѼ�, �W�L�]�˪��d��S, �N���жK��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// �K�ϰѼ�, ��j�ɪ�����, �γ̪��I
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// �K�ϰѼ�, �Y�p�ɪ�����, �γ̪��I
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}
void motion(int x, int y) {
    teapotX += (x - oldX) / 150.0 * 10; ///teapotX = (x-150)/150.0;
    teapotY += (oldY - y) / 150.0 * 10; ///teapotY = (150-y)/150.0;
    angle[ID] += x - oldX;
    angle2[ID] += oldY - y;
    oldX = x;
    oldY = y;
    glutPostRedisplay();
    printf("  glTranslatef( %.2f, %.2f, 0 ); \n", teapotX, teapotY );
}
void display() {

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
      glPushMatrix();
    {
    glBindTexture(GL_TEXTURE_2D, tex5);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, 1.0); // ���U��
    glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, -1.0); // �k�U��
    glTexCoord2f(1.0, 1.0); glVertex2f(1.0, -1.0); // �k�W��
    glTexCoord2f(1.0, 0.0); glVertex2f(1.0, 1.0); // ���W��
    glEnd();
    }
   glPopMatrix();




    glBindTexture(GL_TEXTURE_2D , tex1);

    glBindTexture(GL_TEXTURE_2D , tex3);
    glPushMatrix();

        glScalef(1.6, 1.6, 1.6);
        glTranslatef(0, -1.0, -0.3);///���U�@�b
         glRotatef(180,0,1,0);
        glPushMatrix();
            glColor3f(1,1,1);
            glScalef(0.04, 0.04, 0.04);
            glRotatef(angle[0], 0, 1, 0); ///���骺���

            glmDraw(body, GLM_MATERIAL|GLM_TEXTURE);///glmDraw(gundam, GLM_MATERIAL|GLM_TEXTURE);

            glPushMatrix();///����
                glTranslatef(-4.07, +21.33, 0 );
                glRotatef(angle[1], 0, 1, 0);
                glRotatef(angle2[1], 1, 0, 1);
                glTranslatef( 4.07, -21.33, 0 );///glTranslatef(teapotX, teapotY, 0);
                glmDraw(arm1, GLM_MATERIAL|GLM_TEXTURE);

                glPushMatrix();
                    glTranslatef(-4.40, +18.53, 0 );
                    glRotatef(angle[2], 0, 1, 0);
                    glRotatef(angle2[2], 0, 2, 1);
                    glTranslatef( 4.40, -18.53, 0 );///glTranslatef(teapotX, teapotY, 0);
                    glmDraw(hand1, GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();
            glPopMatrix();


            glPushMatrix();///�k��
                glTranslatef(+4.07, +21.33, 0 );
                glRotatef(angle[3], 0, 1, 0);
                glRotatef(angle2[3], 1, 0, 1);
                glTranslatef(-4.07, -21.33, 0 );///glTranslatef(teapotX, teapotY, 0);
                glmDraw(arm2, GLM_MATERIAL|GLM_TEXTURE);

                glPushMatrix();
                    glTranslatef(+4.40, +18.53, 0 );
                    glRotatef(angle[4], 0, 1, 0);
                    glRotatef(angle2[4], 1, 0, 0);
                    glTranslatef(-4.40, -18.53, 0 );///glTranslatef(teapotX, teapotY, 0);
                    glmDraw(hand2, GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();
            glPopMatrix();


            glPushMatrix();
                glBindTexture(GL_TEXTURE_2D , tex4);
                glTranslatef(-0.00, +22.43, 0 );
                glRotatef(angle[5], 0, 1, 0);
                glRotatef(angle2[5], 1, 0, 0);
                glTranslatef( 0.00, -22.53, 0 );///glTranslatef(teapotX, teapotY, 0);
                glmDraw(head, GLM_MATERIAL|GLM_TEXTURE);


                glBindTexture(GL_TEXTURE_2D , tex1);

                glmDraw(eyeandbrown, GLM_MATERIAL|GLM_TEXTURE);
            glPopMatrix();



            glPushMatrix();///���}
                glBindTexture(GL_TEXTURE_2D , tex2);
                glmDraw(bot, GLM_MATERIAL|GLM_TEXTURE);

                glPushMatrix();

                    glTranslatef(-2.00, +14.27, 0 );
                    glRotatef(angle[6], 0, 1, 0);
                    glRotatef(angle2[6], 1, 0, 0);
                    glTranslatef( 2.00, -14.27, 0 );///glTranslatef(teapotX, teapotY, 0);
                    glmDraw(leg1, GLM_MATERIAL|GLM_TEXTURE);


                        glPushMatrix();
                            glBindTexture(GL_TEXTURE_2D , tex3);
                            glTranslatef(-2.13, +2.40, 0 );
                            glRotatef(angle[7], 0, 1, 0);
                            glRotatef(angle2[7], 1, 0, 0);
                            glTranslatef( 2.13, -2.40, 0 );///glTranslatef(teapotX, teapotY, 0);
                            glmDraw(foot1, GLM_MATERIAL|GLM_TEXTURE);
                        glPopMatrix();
                    glPopMatrix();

            glPopMatrix();



                glPushMatrix();
         glBindTexture(GL_TEXTURE_2D , tex2);
                    glTranslatef(+2.00, +14.27, 0 );
                    glRotatef(angle[8], 0, 1, 0);
                    glRotatef(angle2[8], 1, 0, 0);
                    glTranslatef(-2.00, -14.27, 0 );///glTranslatef(teapotX, teapotY, 0);
                    glmDraw(leg2, GLM_MATERIAL|GLM_TEXTURE);


                        glPushMatrix();
                            glBindTexture(GL_TEXTURE_2D , tex3);
                            glTranslatef(+2.13, +2.40, 0 );
                            glRotatef(angle[9], 0, 1, 0);
                            glRotatef(angle2[9], 1, 0, 0);
                            glTranslatef(-2.13, -2.40, 0);///glTranslatef(teapotX, teapotY, 0);
                            glmDraw(foot2, GLM_MATERIAL|GLM_TEXTURE);
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();


        glPopMatrix();







    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{

    myMP3.Load("backgroundmusic.mp3");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(1080,1080);
    glutCreateWindow("week16");

    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
     myLight();

    eyeandbrown = glmReadOBJ("model/eyeandbrown.obj");
    head = glmReadOBJ("model/head.obj");
    body = glmReadOBJ("model/body.obj"); ///gundam = glmReadOBJ("model/Gundam.obj");
    arm1 = glmReadOBJ("model/arm1.obj");
    arm2 = glmReadOBJ("model/arm2.obj");
    hand1 = glmReadOBJ("model/hand1.obj");
    hand2 = glmReadOBJ("model/hand2.obj");
    bot = glmReadOBJ("model/bot.obj");
    leg1 = glmReadOBJ("model/leg1.obj");
    leg2 = glmReadOBJ("model/leg2.obj");
    foot1 = glmReadOBJ("model/foot1.obj");
    foot2 = glmReadOBJ("model/foot2.obj");
    tex1 = myTexture("Color.png");
    tex2 = myTexture("Flowers.png");
    tex3 = myTexture("Skin_Patrick2.png");
    tex4 = myTexture("Skin_Patrick.png");
    tex5 = myTexture("background.jpg");


    myTexture("model/Flowers.png");
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}

