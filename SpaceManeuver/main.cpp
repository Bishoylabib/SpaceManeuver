#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<math.h>
#include <time.h>
#include <string>
#include<stdio.h>

class Asteroid{
    public:
    int r;
    int g;
    int b;
    int x;
    int y=155;
    int radius;
    int delta=0;

    Asteroid(){
        int rangex = 275;
        x = rand() % rangex + 1;
        int range_radius =5;
        radius=rand()%range_radius+1;
        int ranger = 2;
        r = rand() % ranger;
        if(r==1){
            g=0;
            b=0;
        }
        else{
            int rangeg = 2;
            g = rand() % rangeg;
            if(g==1){
                r=0;
                b=0;
            }
            else{
                b=1;
                r=0;
                g=0;
            }
        }
    }

    int Circle(float cx,float cy, float r, int segments,int deltay){
        glBegin(GL_POLYGON);
        for(int i=0; i< segments;i++){
            float theta = 2.0f * 3.1415926f*float(i)/float(segments);
            float x = r*cosf(theta);
            float y = r*sinf(theta);
            glVertex2f(x+cx,y+cy+deltay);
        }
        glEnd();
        return deltay-1;
    }

    void draw(){
        glColor3f(r,g,b);
        delta=Circle(x,y,radius,100,delta);
    }
};


int phywidth =1920, phyheight=1080;
int logWidth= phywidth/7;//275
int logHeight=phyheight/7;//155
int centerX = logWidth/2, centerY = logHeight/2;
int Score=0;
int time1=20;
int window=0;
int mouseX, mouseY;
float r=1.0f,g=0.0f,b=0.0f;
int Asteroid_index=0;
Asteroid a[25];

void Timer(int value) {

    glutTimerFunc(15, Timer, value);
    glutPostRedisplay();
}

void semiCircle(float cx,float cy, float r, int segments){
    glBegin(GL_POLYGON);
    for(int i=0; i< segments/2;i++){
        float theta = 2.0f * 3.1415926f*float(i)/float(segments);
        float x = r*cosf(theta);
        float y = r*sinf(theta);
        glVertex2f(x+cx,y+cy);
    }
    glEnd();
}

void printSome(char *str,int x,int y) {
    glColor3f (1, 1, 1);
    glRasterPos2d(x,y);
    for (int i=0;i<strlen(str);i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    }
    glFlush();
}

void init2D (float r,float g,float b){
    glClearColor(r,g,b,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,logWidth,0.0,logHeight);
}

void Keyboard(unsigned char key, int x, int y) {
    if(key==' '){
        if (r == 1.0f && g == 0.0f && b == 0.0f) {
            r = 0.0f;
            g = 1.0f;
            b = 0.0f;
        } else if (r == 0.0f && g == 1.0f && b == 0.0f) {
            r = 0.0f;
            g = 0.0f;
            b = 1.0f;
        } else if (r == 0.0f && g == 0.0f && b == 1.0f) {
            r = 1.0f;
            g = 0.0f;
            b = 0.0f;
        }
    }
    if (key == '\x1B') {
        exit(1);
        }
}



void MotionMouse(int x,int y){
    mouseX = x;
    mouseX=0.5+1.0*mouseX*logWidth/phywidth;
    mouseY = phyheight - y;
    mouseY=0.5+1.0*mouseY*logHeight/phyheight;
}

void plane(int x, int y){
    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);//Body
    glVertex2f(x+2,y+3);
    glColor3f(0.4,0.4,0.4);
    glVertex2f(x-2,y+3);
    glColor3f(0.8,0.8,0.8);
    glVertex2f(x-2,y-4);
    glColor3f(0.4,0.4,0.4);
    glVertex2f(x+2,y-4);
    glColor3f(1,1,1);//Windshield
    glVertex2f(x+1,y+3);
    glColor3f(0.53,0.81,0.92);
    glVertex2f(x+1,y+2);
    glColor3f(1,1,1);
    glVertex2f(x-1,y+2);
    glColor3f(0.53,0.81,0.92);
    glVertex2f(x-1,y+3);
    glColor3f(1,1,0);//Flames
    glVertex2f(x-1,y-4);
    glVertex2f(x+1,y-4);
    glColor3f(1,0,0);
    glVertex2f(x+1.5,y-6);
    glVertex2f(x-1.5,y-6);
    glEnd();
    glBegin(GL_TRIANGLES);//Wings
    glColor3f(0.5,0.5,0.5);
    glVertex2f(x-2,y+1);
    glVertex2f(x-4,y-3);
    glColor3f(0.8,0.8,0.8);
    glVertex2f(x-2,y-3);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.45,0.45,0.45);
    glVertex2f(x+2,y-3);
    glColor3f(0.8,0.8,0.8);
    glVertex2f(x+4,y-3);
    glColor3f(0.7,0.7,0.7);
    glVertex2f(x+2,y+1);
    glEnd();
    glBegin(GL_TRIANGLES);//Tip of the plane
    glColor3f(0.4,0.4,0.4);
    glVertex2f(x-2,y+3);
    glColor3f(0.8,0.8,0.8);
    glVertex2f(x,y+5);
    glVertex2f(x+2,y+3);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x-1,y);
    glVertex2f(x+1,y);
    glVertex2f(x-1,y+1);
    glVertex2f(x+1,y+1);
    glVertex2f(x-1,y-1);
    glVertex2f(x+1,y-1);
    glVertex2f(x-1,y-2);
    glVertex2f(x+1,y-2);
    glEnd();
}

void blaster(int x, int y){
    glBegin(GL_QUADS);
    glColor3f(1,0.8,0);
    glVertex2f(x-2,y);
    glVertex2f(x+2,y);
    glColor3f(r,g,b);
    glVertex2f(x+2,152.08);
    glVertex2f(x-2,152.08);
    glEnd();
    semiCircle(x,152,2,100);
}

void display (){
    glClear(GL_COLOR_BUFFER_BIT);

    if(window==0){
        for(int j=0; j<100;j++){
            int starx = rand() % 275;
            int stary = rand() % 155;
            glBegin(GL_POINTS);
            glVertex2f(starx,stary);
            glEnd();
        }
    if(Asteroid_index<=25){
        for(int i=0;i<Asteroid_index;i++){
            if((a[i].y+a[i].delta-a[i].radius>mouseY+5)&&(a[i].x-a[i].radius<=mouseX+2)&&(a[i].x+a[i].radius>=mouseX-2)&&a[i].r==r&&a[i].b==b&&a[i].g==g){
                a[i].y=-10;
                Score++;
                //sound
               }
            else{
                a[i].draw();
            }
        }
    }
    blaster(mouseX,mouseY);
    plane(mouseX,mouseY);
    char score[10];
    sprintf(score,"Score: %d",Score);
    printSome(score,260,150);
    char time[10];
    sprintf(time,"Time: %d",time1);
    printSome(time,5,150);
    }
    else if(window==1){
        printSome("Press f1 to restart",125,centerY);
        printSome("Press ESC to exit",125,centerY-10);
        char score[10];
        sprintf(score,"Your Score is %d",Score);
        printSome(score,125,centerY+10);

    }
    glutSwapBuffers();
    glFlush();
}

void Asteroid_Timer(int value){
    glutTimerFunc(725,Asteroid_Timer,1);
    if(Asteroid_index<25){
        Asteroid_index++;
    }

}

void Game_Timer(int value){
    glutTimerFunc(1000,Game_Timer,2);
    if(time1>0){
        time1--;
    }
    else if (time1==0)
    {
        window=1;
    }
}

void specialKeyboard(int key, int x, int y){
    if(key==GLUT_KEY_F1){
        Score=0;
        time1=20;
        window=0;
        for(int i=0;i<25;i++){
            a[i]=*new Asteroid();
            a[i].delta=0;
        }
        Asteroid_index=0;
    }
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(phywidth,phyheight);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Space Maneuver");
    for(int i=0;i<25;i++){
            a[i]=*new Asteroid();
        }
    init2D(0,0.03,0.085);
    glutFullScreen();
    glutDisplayFunc(display);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutPassiveMotionFunc(MotionMouse);
    glutMotionFunc(MotionMouse);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(specialKeyboard);
    Timer(0);
    Asteroid_Timer(1);
    Game_Timer(2);
    glutMainLoop();
}
