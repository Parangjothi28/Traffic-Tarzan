#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

float r = 1,g = 1,b = 0;
void idle() {
   glutPostRedisplay();
}
float** makeM(int rows,int col){
    float** m=NULL;
    m=(float**)malloc(rows*sizeof(float*));
    for(int i=0;i<rows;i++){
        m[i]=(float*)malloc(col*sizeof(float));
    }
    return m;
}

int score = 0;
int mult = 1;
float** m[100];
float** p[100];
float** q[100];
int x1=0,y13=500,z1=0,x2=1,y2=1,z2=1,flag = 0,f1=0,l = 100;

float** translateM(float x,float y,float z){
float** m=makeM(4,4);
for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
        if(i==j){
            m[i][i]=1;
        }
        else{
            m[i][j]=0;
        }
    }}
    m[0][3]=x;
    m[1][3]=y;
    m[2][3]=z;
    return m;
}

float** scaleM(float x,float y,float z){
float** m=makeM(4,4);
for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
        if(i==j){
            m[i][j]=1;
        }
        else{
            m[i][j]=0;
        }
    }}
    m[0][0]=x;
    m[1][1]=y;
    m[2][2]=z;
    return m;
}

float** rotateM(double angle,int axis){
    float** m=makeM(4,4);
    double c=cos(angle);
    double s=sin(angle);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j){
                m[i][i]=1;
            }
            else{
                m[i][j]=0;
        }
    }
    }
    if(axis==1){
        m[1][1]=c;
        m[1][2]=-s;
        m[2][1]=s;
        m[2][2]=c;
    }
    if(axis==2){
        m[0][0]=c;
        m[0][2]=s;
        m[2][0]=-s;
        m[2][2]=c;
    }
    if(axis==3){
        m[0][0]=c;
        m[0][1]=-s;
        m[1][0]=s;
        m[1][1]=c;
    }
    return m;
}
float** vectorM(float x,float y,float z){
    float** m=makeM(4,1);
    m[0][0]=x;
    m[1][0]=y;
    m[2][0]=z;
    m[3][0]=1;
    return m;
}
float** mulM(float** a,float** b,int n1,int c1,int n2,int c2){
    float** m=makeM(n1,c2);
    for(int i=0;i<n1;i++){
        for(int j=0;j<c2;j++){
            for(int k=0;k<n2;k++){
                m[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    return m;
}
void drawpoint(int a,int b,float r,float g,float b1){
    glBegin(GL_POINTS);
    glColor3f(r, g, b1);
    glVertex2d(a,b);
    glEnd();}
void bres(double x1,double Y1,double x2,double y2,float r,float g,float b){
    int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = x2-x1;
	dy = y2-Y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < Y1) incy = -1;
	x = x1; y = Y1;
	if (dx > dy) {
		drawpoint(x, y,r,g,b);
		e = 2*dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			drawpoint(x, y, r, g, b);
		}

	} else {
		drawpoint(x, y,r,g,b);
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			drawpoint(x, y, r, g, b);
		}
	}
}
void car(){

    m[0] = vectorM(-40,-234,0);
    m[1] = vectorM(-40,-250,0);
    m[2] = vectorM(-20,-250,0);
    m[3] = vectorM(-20,-234,0);
    m[4] = vectorM(40,-234,0);
    m[5] = vectorM(40,-250,0);
    m[6] = vectorM(20,-250,0);
    m[7] = vectorM(20,-234,0);
    m[8] = vectorM(-40,-234,0);
    m[9] = vectorM(40,-234,0);
    m[10] = vectorM(40,-200,0);
    m[11] = vectorM(-40,-200,0);
    m[12] = vectorM(-34,-204,0);
    m[13] = vectorM(-34,-216,0);
    m[14] = vectorM(-32,-216,0);
    m[15] = vectorM(-32,-204,0);
    m[16] = vectorM(34,-204,0);
    m[17] = vectorM(34,-216,0);
    m[18] = vectorM(32,-216,0);
    m[19] = vectorM(32,-204,0);
    m[20] = vectorM(-10,-228,0);
    m[21] = vectorM(10,-228,0);
    m[22] = vectorM(10,-232,0);
    m[23] = vectorM(-10,-232,0);
    m[24] = vectorM(-32,-200,0);
    m[25] = vectorM(32,-200,0);
    m[26] = vectorM(20,-166,0);
    m[27] = vectorM(-20,-166,0);
    m[28] = vectorM(-30,-200,0);
    m[29] = vectorM(30,-200,0);
    m[30] = vectorM(18,-170,0);
    m[31] = vectorM(-18,-170,0);
    for(int i=0;i<32;i++){
        p[i]=vectorM((float)m[i][0][0],(float)m[i][1][0],(float)m[i][2][0]);
    }
}
void drawcar(float r,float g,float b){
        bres(m[0][0][0],m[0][1][0],m[1][0][0],m[1][1][0],r,g,b);
        bres(m[1][0][0],m[1][1][0],m[2][0][0],m[2][1][0],r,g,b);
        bres(m[2][0][0],m[2][1][0],m[3][0][0],m[3][1][0],r,g,b);
        bres(m[3][0][0],m[3][1][0],m[0][0][0],m[0][1][0],r,g,b);
        bres(m[4][0][0],m[4][1][0],m[5][0][0],m[5][1][0],r,g,b);
        bres(m[5][0][0],m[5][1][0],m[6][0][0],m[6][1][0],r,g,b);
        bres(m[6][0][0],m[6][1][0],m[7][0][0],m[7][1][0],r,g,b);
        bres(m[7][0][0],m[7][1][0],m[4][0][0],m[4][1][0],r,g,b);
        bres(m[8][0][0],m[8][1][0],m[9][0][0],m[9][1][0],r,g,b);
        bres(m[9][0][0],m[9][1][0],m[10][0][0],m[10][1][0],r,g,b);
        bres(m[10][0][0],m[10][1][0],m[11][0][0],m[11][1][0],r,g,b);
        bres(m[11][0][0],m[11][1][0],m[8][0][0],m[8][1][0],r,g,b);
        bres(m[12][0][0],m[12][1][0],m[13][0][0],m[13][1][0],r,g,b);
        bres(m[13][0][0],m[13][1][0],m[14][0][0],m[14][1][0],r,g,b);
        bres(m[14][0][0],m[14][1][0],m[15][0][0],m[15][1][0],r,g,b);
        bres(m[15][0][0],m[15][1][0],m[12][0][0],m[12][1][0],r,g,b);
        bres(m[16][0][0],m[16][1][0],m[17][0][0],m[17][1][0],r,g,b);
        bres(m[17][0][0],m[17][1][0],m[18][0][0],m[18][1][0],r,g,b);
        bres(m[18][0][0],m[18][1][0],m[19][0][0],m[19][1][0],r,g,b);
        bres(m[19][0][0],m[19][1][0],m[16][0][0],m[16][1][0],r,g,b);
        bres(m[20][0][0],m[20][1][0],m[21][0][0],m[21][1][0],r,g,b);
        bres(m[21][0][0],m[21][1][0],m[22][0][0],m[22][1][0],r,g,b);
        bres(m[22][0][0],m[22][1][0],m[23][0][0],m[23][1][0],r,g,b);
        bres(m[23][0][0],m[23][1][0],m[20][0][0],m[20][1][0],r,g,b);
        bres(m[24][0][0],m[24][1][0],m[25][0][0],m[25][1][0],r,g,b);
        bres(m[25][0][0],m[25][1][0],m[26][0][0],m[26][1][0],r,g,b);
        bres(m[26][0][0],m[26][1][0],m[27][0][0],m[27][1][0],r,g,b);
        bres(m[27][0][0],m[27][1][0],m[24][0][0],m[24][1][0],r,g,b);
        bres(m[28][0][0],m[28][1][0],m[29][0][0],m[29][1][0],r,g,b);
        bres(m[29][0][0],m[29][1][0],m[30][0][0],m[30][1][0],r,g,b);
        bres(m[30][0][0],m[30][1][0],m[31][0][0],m[31][1][0],r,g,b);
        bres(m[31][0][0],m[31][1][0],m[28][0][0],m[28][1][0],r,g,b);
}
void carmove(int x,int y,int z){
    float** trans = translateM(x,y,z);
    for(int i=0;i<32;i++){
        m[i]=mulM(trans,m[i],4,4,4,1);
    }
}
void drawobs(){
    float** trans=translateM(x1,y13,z1);
    float** scale=scaleM(x2,y2,z2);
    float** mul=mulM(trans,scale,4,4,4,4);
    for(int i=0;i<32;i++){
        q[i]=mulM(mul,p[i],4,4,4,1);
    }
        bres(q[0][0][0],q[0][1][0],q[1][0][0],q[1][1][0],r,g,b);
        bres(q[1][0][0],q[1][1][0],q[2][0][0],q[2][1][0],r,g,b);
        bres(q[2][0][0],q[2][1][0],q[3][0][0],q[3][1][0],r,g,b);
        bres(q[3][0][0],q[3][1][0],q[0][0][0],q[0][1][0],r,g,b);
        bres(q[4][0][0],q[4][1][0],q[5][0][0],q[5][1][0],r,g,b);
        bres(q[5][0][0],q[5][1][0],q[6][0][0],q[6][1][0],r,g,b);
        bres(q[6][0][0],q[6][1][0],q[7][0][0],q[7][1][0],r,g,b);
        bres(q[7][0][0],q[7][1][0],q[4][0][0],q[4][1][0],r,g,b);
        bres(q[8][0][0],q[8][1][0],q[9][0][0],q[9][1][0],r,g,b);
        bres(q[9][0][0],q[9][1][0],q[10][0][0],q[10][1][0],r,g,b);
        bres(q[10][0][0],q[10][1][0],q[11][0][0],q[11][1][0],r,g,b);
        bres(q[11][0][0],q[11][1][0],q[8][0][0],q[8][1][0],r,g,b);
        bres(q[12][0][0],q[12][1][0],q[13][0][0],q[13][1][0],r,g,b);
        bres(q[13][0][0],q[13][1][0],q[14][0][0],q[14][1][0],r,g,b);
        bres(q[14][0][0],q[14][1][0],q[15][0][0],q[15][1][0],r,g,b);
        bres(q[15][0][0],q[15][1][0],q[12][0][0],q[12][1][0],r,g,b);
        bres(q[16][0][0],q[16][1][0],q[17][0][0],q[17][1][0],r,g,b);
        bres(q[17][0][0],q[17][1][0],q[18][0][0],q[18][1][0],r,g,b);
        bres(q[18][0][0],q[18][1][0],q[19][0][0],q[19][1][0],r,g,b);
        bres(q[19][0][0],q[19][1][0],q[16][0][0],q[16][1][0],r,g,b);
        bres(q[20][0][0],q[20][1][0],q[21][0][0],q[21][1][0],r,g,b);
        bres(q[21][0][0],q[21][1][0],q[22][0][0],q[22][1][0],r,g,b);
        bres(q[22][0][0],q[22][1][0],q[23][0][0],q[23][1][0],r,g,b);
        bres(q[23][0][0],q[23][1][0],q[20][0][0],q[20][1][0],r,g,b);
        bres(q[24][0][0],q[24][1][0],q[25][0][0],q[25][1][0],r,g,b);
        bres(q[25][0][0],q[25][1][0],q[26][0][0],q[26][1][0],r,g,b);
        bres(q[26][0][0],q[26][1][0],q[27][0][0],q[27][1][0],r,g,b);
        bres(q[27][0][0],q[27][1][0],q[24][0][0],q[24][1][0],r,g,b);
        bres(q[28][0][0],q[28][1][0],q[29][0][0],q[29][1][0],r,g,b);
        bres(q[29][0][0],q[29][1][0],q[30][0][0],q[30][1][0],r,g,b);
        bres(q[30][0][0],q[30][1][0],q[31][0][0],q[31][1][0],r,g,b);
        bres(q[31][0][0],q[31][1][0],q[28][0][0],q[28][1][0],r,g,b);
    y13 = y13-10;
    if(y13<0){

        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        y13=500;
        score = score + mult;
        mult++;
        l = l-10;
        if(l<20){
            l=20;
        }
        int a=rand();
        if(a%3==0){
            x1 = 0;
        }
        else if(a%3==1){
            x1 = 109;
        }
        else{
            x1 = -109;
        }
    }
}
void print(int x, int y,char* String)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);
    for (int i=0; i<strlen(String); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
void checkCol(){
    if(q[1][0][0]==m[1][0][0]){
        if(q[5][1][0]<=m[26][1][0]){
            flag = 2;
            y13 = 500;
        }
    }
}

void scenery(){
    float r=0,g=1,b=0;
    bres(-250,-250,-250,250,r,g,b);
    bres(-250,250,-165,250,r,g,b);
    bres(-165,250,-165,-250,r,g,b);
    bres(-165,-250,-250,-250,r,g,b);
    bres(250,-250,250,250,r,g,b);
    bres(250,250,165,250,r,g,b);
    bres(165,250,165,-250,r,g,b);
    bres(165,-250,250,-250,r,g,b);
    }

void road(){
    float r=1,g=1,b=1;
    bres(-165,-250,-165,250,r,g,b);
    bres(-165,250,165,250,r,g,b);
    bres(165,250,165,-250,r,g,b);
    bres(165,-250,-165,-250,r,g,b);
    bres(-56,-250,-56,250,r,g,b);
    bres(-56,250,-54,250,r,g,b);
    bres(-54,250,-54,-250,r,g,b);
    bres(-54,-250,-56,-250,r,g,b);
    bres(56,-250,56,250,r,g,b);
    bres(56,250,54,250,r,g,b);
    bres(54,250,54,-250,r,g,b);
    bres(54,-250,56,-250,r,g,b);
}
void display()
{

    if(flag == 0){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        char string1[64],s2[64],s3[64],s4[64];
        glColor3f(1,1,0);
        sprintf(string1, "Please enter P to start playing");
        print(115,250,string1);
        sprintf(s3, "Use A to move the left");
        sprintf(s4, "Use D to move to the right");

        print(160,200,s3);
        print(140,150,s4);
        sprintf(s2,"Traffic Tarzan!!");
        print(185,400,s2);
        glutSwapBuffers();
    }
    if(flag == 1){
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        road();
        if(f1 == 0)
            car();
        drawcar(0,1,1);
        scenery();
        drawobs();
        checkCol();
        glFlush();
        Sleep(l);
    }
    if(flag == 2){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        char string1[64],s2[64],s3[64],s4[64],s5[64];
        car();
        glColor3f(1,1,0);
        sprintf(s4,"Your Score:");
        print(200,300,s4);
        itoa(score,s5,10);
        print(300,300,s5);
        if(score<=6){
        sprintf(string1, "You could do better!!!! Good luck!");}
        else{
        sprintf(string1, "You were on a roll there!Good Job!");
        }
        print(117,250,string1);
        sprintf(s3, " Enter P to play again ");
        print(150,200,s3);
        sprintf(s2,"Traffic Tarzan!!");
        print(185,400,s2);
        glutSwapBuffers();
    }
}
void myKey(unsigned char key,int x,int y)
{
glClear(GL_COLOR_BUFFER_BIT);
    if(flag == 1){
    if(key=='a'||key=='A')
    {
        f1 = 1;
        if(m[1][0][0]-109>=-165){
        carmove(-109,0,0);}
    }
    else if(key=='d'||key=='D'){
        f1 = 1;
        if(m[1][0][0]+109<=165){
        carmove(109,0,0);}
    }}
    else if(key=='p'||key=='P'){
        flag = 1;
        l = 100;
        mult = 1;
        score = 0;
    }
}
void reshape(int w, int h)
{
glViewport(0.0, 0.0, w, h);
glLoadIdentity();
gluOrtho2D(-w/2,w/2,-h/2,h/2);
}
void intiopenGL()
{
glClearColor(0.0,0.0 ,0.0 , 0.0);
glColor3f(0.0,0.0,1.0);
}
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitWindowSize(500, 500);
glutInitWindowPosition(100, 100);
glutCreateWindow("Traffic Tarzan");
intiopenGL();
gluOrtho2D(-250 , 250, -250 , 250);
glutDisplayFunc(display);
glutKeyboardFunc(myKey);
glutIdleFunc(display);
glutReshapeFunc(reshape);
glutMainLoop();
return 0;
}
