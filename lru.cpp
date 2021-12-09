#include<GL/gl.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include <bits/stdc++.h>
using namespace std;
#define lpr pair<int,pair<int,int>>

int frmcontent[3]={0,0,0},frames[3]={0,0,0}, temp[3],pages[9],curpage=0,pos[9],pgf=0,n;
char status[9];
int frmcontent2[3]={0,0,0},frames2[3]={0,0,0}, temp2[3],curpage2=0,pos2[9],pgf2=0;
char status2[9];
int diffx=0,diffy=0,i=0,window_id,window_id_2;
int diffx2=0,diffy2=0;
unordered_map<int, pair<int,int>> mp;

void init()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,1000,0,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glFlush();

}

void drawText(string s,float x,float y,float z)
{
    //char *c;
    glRasterPos3f(x,y,z);
    glColor3f(1,0,1);
    for (auto c:s)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

void clrsc()
{
    if(strcmp(status,"HIT")==0)
    {
         glClearColor(0,0,0,0);
         glClear(GL_COLOR_BUFFER_BIT);
         glColor3f(0.99,0.94,0.6);
	     drawText("LEAST RECENTLY USED ALGORITHM!!",-500,800,0);
         glColor3f(0.75,0.7,1);
         drawText("THE RESULTS ARE...",-330,650,0);
         glColor3f(1,0,1);
         drawText("PAGE FAULTS:",-300,550,0);
         glRasterPos2f(50,550);
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pgf+'0');
         drawText("PAGE HITS:",-250,450,0);
         glRasterPos2f(30,450);
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (n-pgf)+'0');
         glFlush();
    }
    else
    {
         glClearColor(0,0,0,0);
         glClear(GL_COLOR_BUFFER_BIT);
         glColor3f(0.99,0.94,0.6);
	     drawText("LEAST RECENTLY USED ALGORITHM!!",70,1150,0);
         glColor3f(0.75,0.7,1);
         drawText("THE RESULTS ARE...",270,1000,0);
         glColor3f(1,0,1);
         drawText("PAGE FAULTS:",300,900,0);
         glRasterPos2f(650,900);
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pgf+'0');
         drawText("PAGE HITS:",350,800,0);
         glRasterPos2f(630,800);
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (n-pgf)+'0');
         glFlush();
    }
}

void clrsc2()
{
    if(strcmp(status2,"HIT")==0)
    {
         glClearColor(0,0,0,0);
         glClear(GL_COLOR_BUFFER_BIT);
         glColor3f(0.99,0.94,0.6);
	     drawText("LEAST FREQUENTLY USED ALGORITHM!!",-500,800,0);
         glColor3f(0.75,0.7,1);
         drawText("THE RESULTS ARE...",-330,650,0);
         glColor3f(1,0,1);
         drawText("PAGE FAULTS:",-300,550,0);
         glRasterPos2f(50,550);
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pgf2+'0');
         drawText("PAGE HITS:",-250,450,0);
         glRasterPos2f(30,450);
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (n-pgf2)+'0');
         glFlush();
    }
    else
    {
         glClearColor(0,0,0,0);
         glClear(GL_COLOR_BUFFER_BIT);
         glColor3f(0.99,0.94,0.6);
	     drawText("LEAST FREQUENTLY USED ALGORITHM!!",70,1150,0);
         glColor3f(0.75,0.7,1);
         drawText("THE RESULTS ARE...",270,1000,0);
         glColor3f(1,0,1);
         drawText("PAGE FAULTS:",300,900,0);
         glRasterPos2f(650,900);
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pgf2+'0');
         drawText("PAGE HITS:",350,800,0);
         glRasterPos2f(630,800);
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (n-pgf2)+'0');
         glFlush();
    }
}

int lru(int pages[9],int cpg)               //returns position to fill page in
{
    int m, n, position, k, l;
	int a = 0, b = 0;
    for(m = 0; m < 3; m++)
        if(frames[m] == pages[cpg])   //page hit
        {
            a = 1;
            b = 1;
            return -1;
        }
    // empty frame present
    for(m = 0; m < 3; m++)
    if(frames[m] == 0)
    {
        frames[m] = pages[cpg];
        b = 1;
        pgf++;
        return m;
    }

    // Page fault has occurred
    for(m = 0; m < 3; m++)
        temp[m] = 0;

    // Handling it and emptying a frame to handle the current request
    int flag=0;
    for(k = cpg-1;k>=0;k--)
    {
        for(m = 0; m <3; m++)
        {
            if(frames[m] == pages[k])
            {
                flag++;
                temp[m] = 1;
            }
        }
        if(flag==2)
            break;        
    }
    for(m = 0; m <3; m++)
        if(temp[m] == 0)
        {
            position = m;
            break;
        }
    frames[position] = pages[cpg];
    pgf++;
    return position;
    
}

bool comp(lpr a, lpr b)
{
    if(a.second.first<b.second.first)
        return true;
    else if(a.second.first>b.second.first)
        return false;
    return a.second.second<b.second.second;
}

int lfu(int pages[9],int cpg)               //returns position to fill page in
{
    int m, n, position, k, l;
	int a = 0, b = 0;
    mp[pages[cpg]]=make_pair(mp[pages[cpg]].first++,cpg);
    for(m = 0; m < 3; m++)
    {
        if(frames2[m] == pages[cpg])   //page hit
        {
            a = 1;
            b = 1;
            return -1;
        }
    }
    // empty frame present
    for(m = 0; m < 3; m++)
    {        
        if(frames2[m] == 0)
        {
            frames2[m] = pages[cpg];
            b = 1;
            pgf2++;
            return m;
        }
    }
    // Page fault has occurred
    for(m = 0; m < 3; m++)
        temp2[m] = 0;

    // find the least frequently used frame from the 3 frames 
    vector<pair<int,pair<int,int>>>vec;
    for(auto itr:mp)
    {
        vec.push_back(make_pair(itr.first,itr.second));
    }
    sort(vec.begin(),vec.end(),comp);
    position=vec[0].second.second;
    frames2[position] = pages[cpg];
    pgf2++;
    return position;
}

void boxpush(int x)
{
    glBegin(GL_POLYGON);
    glColor3f(0.8,0.84,1);                                      //initialize box with current page
	glVertex2f(470, 770);
	glVertex2f(530, 770);
	glVertex2f(530, 830);
	glVertex2f(470, 830);
	glEnd();
	glColor3f(0,0,0);
	glRasterPos2f(492, 796);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, x+'0');
	usleep(50000);
	diffy-=10;
    if(pos[curpage]==0&&diffy>-200)                 //if curpage is inserted to frame 1
    {
        strcpy(status,"FAULT");
        glutPostRedisplay();                        //redisplay after each change in position
    }
    else if(pos[curpage]==1&&diffy>-300)             //if curpage is inserted to frame 2
    {
        strcpy(status,"FAULT");
        glutPostRedisplay();
    }
    else if(pos[curpage]==2&&diffy>-380)             //if curpage is inserted to frame 3
    {
        strcpy(status,"FAULT");
        glutPostRedisplay();
    }
     else if(pos[curpage]==-1&&diffx<550)           //if curpage is hit
    {
        usleep(50000);
        diffy=0;
        diffx+=20;
        strcpy(status,"HIT");
        glutPostRedisplay();
    }
    else                                            //move to next page
    {
        if(curpage<n-1)                                     //if 8th page increment and display one final time
        {
              frmcontent[pos[curpage]]=pages[curpage];     //assign curpage value to chosen frame
              curpage++;
              diffy=0;
              diffx=0;                              //reset positions
              glutPostRedisplay();
        }
        else
        {
              clrsc();                              //display result
        }
    }
}

void boxpush2(int x)
{
    glBegin(GL_POLYGON);
    glColor3f(0.8,0.84,1);                                      //initialize box with current page
	glVertex2f(470, 770);
	glVertex2f(530, 770);
	glVertex2f(530, 830);
	glVertex2f(470, 830);
	glEnd();
	glColor3f(0,0,0);
	glRasterPos2f(492, 796);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, x+'0');
	usleep(50000);
	diffy2-=10;
    if(pos2[curpage2]==0&&diffy2>-200)                 //if curpage is inserted to frame 1
    {
        strcpy(status2,"FAULT");
        glutPostRedisplay();                        //redisplay after each change in position
    }
    else if(pos2[curpage2]==1&&diffy2>-300)             //if curpage is inserted to frame 2
    {
        strcpy(status2,"FAULT");
        glutPostRedisplay();
    }
    else if(pos2[curpage2]==2&&diffy2>-380)             //if curpage is inserted to frame 3
    {
        strcpy(status2,"FAULT");
        glutPostRedisplay();
    }
     else if(pos2[curpage2]==-1&&diffx2<550)           //if curpage is hit
    {
        usleep(50000);
        diffy2=0;
        diffx2+=20;
        strcpy(status2,"HIT");
        glutPostRedisplay();
    }
    else                                            //move to next page
    {
        if(curpage2<n-1)                                     //if 8th page increment and display one final time
        {
              frmcontent2[pos2[curpage2]]=pages[curpage2];     //assign curpage value to chosen frame
              curpage2++;
              diffy2=0;
              diffx2=0;                              //reset positions
              glutPostRedisplay();
        }
        else
        {
              clrsc2();                              //display result
        }
    }
}

void drawframes()                                   //draws frames with current content
{
    glBegin(GL_POLYGON);
    glColor3f(0.5,0.9,0.56);
	glVertex2f(470, 570);
	glVertex2f(530, 570);
	glVertex2f(530, 630);
	glVertex2f(470, 630);
	glEnd();
	glColor3f(0,0,0);
	glRasterPos2f(492,592);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, frmcontent[0]+'0');
	glColor3f(0.5,0.9,0.56);
    glBegin(GL_POLYGON);
	glVertex2f(470, 490);
	glVertex2f(530, 490);
	glVertex2f(530, 550);
	glVertex2f(470, 550);
	glEnd();
	glColor3f(0,0,0);
	glRasterPos2f(492,512);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, frmcontent[1]+'0');
	glColor3f(0.5,0.9,0.56);
    glBegin(GL_POLYGON);
	glVertex2f(470, 410);
	glVertex2f(530, 410);
	glVertex2f(530, 470);
	glVertex2f(470, 470);
	glEnd();
	glColor3f(0,0,0);
	glRasterPos2f(492,432);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, frmcontent[2]+'0');
}

void drawframes2()                                   //draws frames with current content
{
    glBegin(GL_POLYGON);
    glColor3f(0.5,0.9,0.56);
	glVertex2f(470, 570);
	glVertex2f(530, 570);
	glVertex2f(530, 630);
	glVertex2f(470, 630);
	glEnd();
	glColor3f(0,0,0);
	glRasterPos2f(492,592);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, frmcontent2[0]+'0');
	glColor3f(0.5,0.9,0.56);
    glBegin(GL_POLYGON);
	glVertex2f(470, 490);
	glVertex2f(530, 490);
	glVertex2f(530, 550);
	glVertex2f(470, 550);
	glEnd();
	glColor3f(0,0,0);
	glRasterPos2f(492,512);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, frmcontent2[1]+'0');
	glColor3f(0.5,0.9,0.56);
    glBegin(GL_POLYGON);
	glVertex2f(470, 410);
	glVertex2f(530, 410);
	glVertex2f(530, 470);
	glVertex2f(470, 470);
	glEnd();
	glColor3f(0,0,0);
	glRasterPos2f(492,432);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, frmcontent2[2]+'0');
}

void drawstatus()                                               //draws status of each page
{
    glColor3f(0.99,0.94,0.6);
	drawText("LEAST RECENTLY USED ALGORITHM!!",60,880,0);
    glColor3f(1,0,1);
	drawText("INPUT",190,780,0);
	glColor3f(1,0,1);
	glRasterPos2f(380, 780);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, curpage+1+'0');
	drawText("SLOT 1",200,580,0);
	drawText("SLOT 2",200,500,0);
	drawText("SLOT 3",200,420,0);
	drawText("STATUS:",190,200,0);
	drawText(status,450,200,0);
}

void drawstatus2()                                               //draws status of each page
{
    glColor3f(0.99,0.94,0.6);
	drawText("LEAST FREQUENTLY USED ALGORITHM!!",60,880,0);
    glColor3f(1,0,1);
	drawText("INPUT",190,780,0);
	glColor3f(1,0,1);
	glRasterPos2f(380, 780);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, curpage2+1+'0');
	drawText("SLOT 1",200,580,0);
	drawText("SLOT 2",200,500,0);
	drawText("SLOT 3",200,420,0);
	drawText("STATUS:",190,200,0);
	drawText(status2,450,200,0);
}

void mykey(unsigned char k, int c, int d)
{
    if(k=='Q' || k=='q')
    {
        glutDestroyWindow(window_id);
        glutDestroyWindow(window_id_2);     
    }
}

void disp()
{
     glClearColor(0,0,0,0);
     glClear(GL_COLOR_BUFFER_BIT);
     drawframes();
     drawstatus();
     glPushMatrix();
     glTranslatef(diffx,diffy,0);                       //push box down/left
     boxpush(pages[curpage]);                           //keep pushing till reach end
     glPopMatrix();
     glutSwapBuffers();
     glFlush();
}

void disp2()
{
     glClearColor(0,0,0,0);
     glClear(GL_COLOR_BUFFER_BIT);
     drawframes2();
     drawstatus2();
     glPushMatrix();
     glTranslatef(diffx2,diffy2,0);                       //push box down/left
     boxpush2(pages[curpage2]);                           //keep pushing till reach end
     glPopMatrix();
     glutSwapBuffers();
     glFlush();
}

int main(int argc,char **argv)
{
    int i;
    printf("Enter the number of pages (maximum 9):\n");
    scanf("%d",&n);
    printf("Enter the sequence of pages:\n");
    for(i=0;i<n;i++)
        scanf("%d",&pages[i]);
    glutInit(&argc,argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(50,650);              // set a window position
    window_id=glutCreateWindow("LEAST RECENTLY USED ALGORITHM");
   
    init();
    glutDisplayFunc(disp);    
    glutInitWindowSize(500,500);   
    glutInitWindowPosition(600,650);            // set a window position     
    window_id_2 = glutCreateWindow("Window Two");
    init();
    glutDisplayFunc(disp2);
    glutKeyboardFunc(mykey);
    // LRU
    printf("\nPAGE NO.\tINSERTED INTO FRAME NO.\t\tFRAME STATE\n");
    for(i=0;i<n;i++)
    {
         pos[i]=lru(pages,i);
         printf("   %d\t\t\t %d\t\t\t   %d %d %d\n",pages[i],pos[i]+1,frames[0],frames[1],frames[2]);
    }
    printf("\nPAGE FAULTS=%d\n",pgf);
    printf("PAGE HITS=%d\n",n-pgf);
    // LFU
    printf("\nPAGE NO.\tINSERTED INTO FRAME NO.\t\tFRAME STATE\n");
    for(i=0;i<n;i++)
    {
         pos2[i]=lfu(pages,i);
         printf("   %d\t\t\t %d\t\t\t   %d %d %d\n",pages[i],pos2[i]+1,frames2[0],frames2[1],frames2[2]);
    }
    printf("\nPAGE FAULTS=%d\n",pgf2);
    printf("PAGE HITS=%d\n",n-pgf2);
    glutMainLoop();
    return 0;
}