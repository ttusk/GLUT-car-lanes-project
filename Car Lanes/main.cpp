#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <windows.h>
#include <cmath>
#include <math.h>


void display();
void reshape(int w,int h);
void keyboard(unsigned char Key, int x, int y);
void SpecialInput(int key, int x, int y);  //Used for arrow keys (Up - Down - Right - Left)
void OnMouseClick(int button, int state, int x, int y);
void timer(int);



// Initializes background color
void init()
{
    glClearColor(0.498, 0.498, 0.490, 0.7);
}

int main(int argc,char**argv)
{


    glutInit(&argc,argv);       // Initializes GLUT library
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 0);
    glutInitWindowSize(1200, 800);

    glutCreateWindow("211010004");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialInput);
    glutMouseFunc(OnMouseClick);

    glutTimerFunc(0, timer, 0);


    glutMainLoop();
}


void OnMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        glClearColor(0.498, 0.498, 0.490, 0.7);
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
    {
        glClearColor(0.4, 0.4, 0.39, 0.7);
    }
}

// For the movement
int translateXClock = 0, translateYClock = 0;
int translateXCar = 0, translateYCar = 0;

void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            translateYClock++;
        break;

        case GLUT_KEY_DOWN:
            translateYClock--;
        break;

        case GLUT_KEY_LEFT:
            translateXClock--;
        break;

        case GLUT_KEY_RIGHT:
            translateXClock++;
        break;
    }
}

bool fullScreen;

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'd' : translateXCar++;
        break;

        case 'a' : translateXCar--;
        break;

        case 'w' : translateYCar++;
        break;

        case 's' : translateYCar--;
        break;

        case 'f': fullScreen = !fullScreen;
        if (fullScreen)
        {
            glutFullScreen();
        }
        else
        {
            glutReshapeWindow(1200, 800);
            glutPositionWindow(200, 0);
        }
        break;

        case 27 : exit(0);
        break;
    }
}



float Animation = 0.0;
float AnimationSpeed = 0.2;
float MaxAnimation = 25.0;

void roadLines(){
    glLineWidth(20.0);
    glBegin(GL_LINES);

    // Upper line
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-10, 10);
    glVertex2f(-6, 10);

    glColor3f(133.0/255.0, 138.0/255.0, 0.0);
    glVertex2f(-6, 10);
    glVertex2f(-2, 10);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-2, 10);
    glVertex2f(2, 10);

    glColor3f(133.0/255.0, 138.0/255.0, 0.0);
    glVertex2f(2, 10);
    glVertex2f(6, 10);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(6, 10);
    glVertex2f(10, 10);

    // Bottom lines
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-10, -10);
    glVertex2f(-6, -10);

    glColor3f(133.0/255.0, 138.0/255.0, 0.0);
    glVertex2f(-6, -10);
    glVertex2f(-2, -10);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-2, -10);
    glVertex2f(2, -10);

    glColor3f(133.0/255.0, 138.0/255.0, 0.0);
    glVertex2f(2, -10);
    glVertex2f(6, -10);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(6, -10);
    glVertex2f(10, -10);

    // Middle lines
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-10, 0);
    glVertex2f(-6, 0);

    glColor3f(133.0/255.0, 138.0/255.0, 0.0);
    glVertex2f(-6, 0);
    glVertex2f(-2, 0);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-2, 0);
    glVertex2f(2, 0);

    glColor3f(133.0/255.0, 138.0/255.0, 0.0);
    glVertex2f(2, 0);
    glVertex2f(6, 0);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(6, 0);
    glVertex2f(10, 0);

    glEnd();
}

void lanes(){
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);

    // Upper lanes
    /*glVertex2f(-9, 5);
    glVertex2f(-7, 5);

    glVertex2f(-6, 5);
    glVertex2f(-4, 5);

    glVertex2f(-3, 5);
    glVertex2f(-1, 5);

    glVertex2f(0, 5);
    glVertex2f(2, 5);
    */

    for(float x = -10; x < 10; x += 3){
        glVertex2f(x + 3, 5);
        glVertex2f(x - 2 + 3, 5);
    }

    // Bottom lanes
     for(float x = -10; x < 10; x += 3){
        glVertex2f(x + 3, -5);
        glVertex2f(x - 2 + 3, -5);
    }
    glEnd();
}

void drawCar(float posX, float posY, float red, float green, float blue) {
    glPushMatrix(); // Pushes a copy of the matrix
    glTranslatef(posX, posY, 0.0); // Translates (moves) the current matrix
    glScalef(2.0, 2.0, 1.0); // Scales up the car (x, y, z)

    // Body
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.2);
    glVertex2f(0.5, -0.2);
    glVertex2f(0.5, 0.2);
    glVertex2f(-0.5, 0.2);
    glEnd();

    // Roof
    glColor3f(red + 0.2, green + 0.2, blue + 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.2);
    glVertex2f(0.4, 0.2);
    glVertex2f(0.2, 0.5);
    glVertex2f(-0.2, 0.5);
    glEnd();

    // Windows
    glColor3f(red + 0.3, green + 0.3, blue + 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(-0.35, 0.25);
    glVertex2f(0.35, 0.25);
    glVertex2f(0.2, 0.45);
    glVertex2f(-0.2, 0.45);
    glEnd();

    // Wheels
    glColor3f(0, 0, 0);
    const float wheelRadius = 0.15;

    // Front wheel
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i += 10) {
        float angle = i * 3.14159 / 180;
        glVertex2f(-0.3 + wheelRadius * cos(angle), -0.2 + wheelRadius * sin(angle));
    }
    glEnd();

    // Rear wheel
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i += 10) {
        float angle = i * 3.14159 / 180;
        glVertex2f(0.3 - wheelRadius * cos(angle), -0.2 + wheelRadius * sin(angle));
    }
    glEnd();

    glPopMatrix();
}

void drawClock(float posX, float posY)
{
    glTranslatef(posX, posY, 0.0); // Translates (moves) the current matrix
    // Clock Circle
    float clockRaduis = 1.0;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(9.5, 9.5); // Top right corner
    for (int i = 0; i <= 360; i += 10)
    {
        float angle = i * 3.14159 / 180;
        glVertex2f(9.5 + clockRaduis * cos(angle), 9.5 + clockRaduis * sin(angle));
    }
    glEnd();

    // Clock Hand
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(9.5, 9.5); // Top right corner
    float angle = Animation * 3.14159 / 180;  // Angle of rotation
    glVertex2f(9.5 + 0.5 * cos(angle), 9.5 - 0.5 * sin(angle));
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clears color buffer
    glLoadIdentity(); // Loads identity matrix

    roadLines();

    lanes();

    drawCar(-12 + Animation, 7.5, 1.0, 0.0, 0.0);
    drawCar(-9 + Animation, 7.5, 0.925, 0.423, 0.937);
    drawCar(-5 + Animation, 7.5, 0.0, 0.749, 0.482);

    drawCar(-10 + Animation, 2.5, 0.0, 0.0, 1.0);
    drawCar(-6 + Animation, 2.5, 0.752, 0.752, 0.752);

    drawCar(12 - Animation, -7.5, 0.925, 0.423, 0.937);
    drawCar(10 - Animation, -2.5, 0.0, 0.0, 1.0);

    // Car that moves using WASD
    drawCar(5 + translateXCar, -2.5 + translateYCar, 0.0, 0.749, 0.482);

    // Clock moves using arrow keys (special input)
    drawClock(translateXClock, translateYClock);

    glutSwapBuffers();            // Show object on screen (Buffer swap)
    glFlush();
}

void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h); // Sets the viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10,10,-10,10);    // X minimum : -10 || X Maximum : 10
    glMatrixMode(GL_MODELVIEW);   // Y Minimum : -10 || Y Maximum : 10
}

void timer(int)
{
    glutPostRedisplay(); // Redraws
    glutTimerFunc(1000 / 60, timer, 0);

    Animation += AnimationSpeed; // updates the Animation variable

    if (Animation > MaxAnimation)
        Animation = 0.0; // Resets Animation variable when it reaches the maximum value assigned globally at the top
}
