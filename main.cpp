#include <iostream>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

typedef float vec3_t[3];

enum {
    UP = 1,
    DOWN,
};

int oldX = -13;
int oldY = -13;
int mState = UP;

vec3_t gRot = {0,0,0};

void drawSphere (void)
{
    glColor3f(0.0f, 0.4f, 0.8f);

    glutWireTeapot(10.0);
}

void drawAxis (void)
{
    glColor3f (0.5, 0.5, 0.5);
    glBegin (GL_LINES);
        glColor3f (0.5, 0.0, 0.0);
        glVertex3f (-20.0, 0.0, 0.0);
        glVertex3f (20.0, 0.0, 0.0);

        glColor3f (0.0, 0.5, 0.0);
        glVertex3f (0.0, 20.0, 0.0);
        glVertex3f (0.0, -20.0, 0.0);

        glColor3f (0.0, 0.0, 0.5);
        glVertex3f (0.0, 0.0, -20.0);
        glVertex3f (0.0, 0.0, 20.0);
    glEnd ();
}

void glutDisplay (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    /* move our eye position 50 units away */
    glTranslatef (0, 0, -50);
    /* apply the rotation from the mouse */
    glRotatef (gRot[0], 1.0, 0.0, 0.0);
    glRotatef (gRot[1], 0.0, 1.0, 0.0);

    drawAxis ();
    drawSphere ();

    glutSwapBuffers();
}

void glutResize (int w, int h)
{
   if (h == 0)
      h = 1;

    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set the view port to be the entire window
    glViewport(0, 0, w, h);

    // set the correct perspective
    gluPerspective(60.0f, ratio, 0.1f, 100.0);

    // go back to model view
    glMatrixMode(GL_MODELVIEW);
}

void usage(){
    //keyboard keys to perform
    std::cout<< "\n\n\
          q,Q: Quit\n\n" ;
          std::cout.flush();
}

void glutMotion(int x, int y)
{
    if (mState == DOWN)
    {
        gRot[0] -= ((oldY - y) * 180.0f) / 100.0f;
        gRot[1] -= ((oldX - x) * 180.0f) / 100.0f;
        glutPostRedisplay ();
    }
    oldX = x;
    oldY = y;
}

void glutMouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        switch(button)
        {
            case GLUT_LEFT_BUTTON:
            case GLUT_RIGHT_BUTTON:
                mState = DOWN;
                oldX = x;
                oldY = y;
            break;
        }
    } else if (state == GLUT_UP)
        mState = UP;
}

void KeyboardFunc (unsigned char key, int eyeX, int eyeY){
    switch (key){
       case 'q':
       case 'Q':
           exit(0);
           break;
    }
    glutPostRedisplay();
}

void init() {
  // Set the current clear color to black and the current drawing color to white
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);
  usage();
}

int main (int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize (400,400);
    glutCreateWindow ("Final");
    init();
    glutDisplayFunc (glutDisplay);
    glutReshapeFunc (glutResize);
    glutMotionFunc (glutMotion);
    glutMouseFunc (glutMouse);
    glutKeyboardFunc(&KeyboardFunc);
    glutMainLoop();
}
