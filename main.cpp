
#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <mmsystem.h>
#include <string>


using namespace std;
/* Global variables */

GLfloat x = 0, y = 0, zz = 0, temp2 = 0,wx = 0, wy = 0, wz = 0 ;
GLint rx = 0,ry = 0,angelx = 0,ln = 0, un = 0, dn = 0, pre = 3, steps = 0, angx = 20, angy = 20 , prekey = 0;
GLint r = 0, rn=0, angely = 0,temp = 90;
bool check = false;
vector<pair<float, pair<float, float> > >v, face[7], take , foodt[7];
void points()
{
    v.push_back({0.5, {1,0.5}});
    v.push_back({0.419608, {0.556863,0.137255}});
    v.push_back({0.560784, {0.737255,0.560784}});
    v.push_back({0.137255, { 0.556863,0.419608}});
    v.push_back({0, {1.0,0.498039}});
    v.push_back({0, {1,0}});
}

void initGL()
{

    glClearColor(0.196078,0.6,0.8, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void sq2(float xx, float yy,float zz , float cx , float cy , float cz)
{
    glBegin(GL_QUADS);
    glColor3f( cx, cy, cz);       // Green
    glVertex3f(-xx, yy, -zz);
    glVertex3f(-xx, yy, -zz);
    glVertex3f(-xx, yy,  zz);
    glVertex3f( xx, yy,  zz);

    // Bottom face (y = -0.05f)
    glColor3f( cx, cy, cz);        // Green
    glVertex3f( xx, -yy,  zz);
    glVertex3f(-xx, -yy,  zz);
    glVertex3f(-xx, -yy, -zz);
    glVertex3f( xx, -yy, -zz);

    // Front face  (z = 0.05f)
    glColor3f( cx, cy, cz);       // Green
    glVertex3f( xx,  yy, zz);
    glVertex3f(-xx,  yy, zz);
    glVertex3f(-xx, -yy, zz);
    glVertex3f( xx, -yy, zz);
    // Back face (z = -0.05f)
    glColor3f( cx, cy, cz);        // Green
    glVertex3f( xx, -yy, -zz);
    glVertex3f(-xx, -yy, -zz);
    glVertex3f(-xx,  yy, -zz);
    glVertex3f( xx,  yy, -zz);

    // Left face (x = -0.05f)
    glColor3f( cx, cy, cz);        // Green
    glVertex3f(-xx,  yy,  zz);
    glVertex3f(-xx,  yy, -zz);
    glVertex3f(-xx, -yy, -zz);
    glVertex3f(-xx, -yy,  zz);

    // Right face (x = 0.05f)
    glColor3f( cx, cy, cz);        // Green
    glVertex3f(xx,  yy, -zz);
    glVertex3f(xx,  yy,  zz);
    glVertex3f(xx, -yy,  zz);
    glVertex3f(xx, -yy, -zz);
    glEnd();  // End of drawing color-cube
}
void cube()
{

    glBegin(GL_QUADS);
    // Top face (y = 1.0f)
    glColor3f(v[4].first, v[4].second.first, v[4].second.second);     // Green
    glVertex3f( 1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0,  1.0);
    glVertex3f( 1.0, 1.0,  1.0);
    // Bottom face (y = -1.0f)
    glColor3f(v[5].first, v[5].second.first, v[5].second.second);     // Orange
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Front face  (z = 1.0f)
    glColor3f(v[0].first, v[0].second.first, v[0].second.second);    // Red
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    // Back face (z = -1.0f)
    glColor3f(v[2].first, v[2].second.first, v[2].second.second);     // Yellow
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    // Left face (x = -1.0f)
    glColor3f(v[3].first, v[3].second.first, v[3].second.second);     // Blue
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    // Right face (x = 1.0f)
    glColor3f(v[1].first, v[1].second.first, v[1].second.second);  // Magenta
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
}

void sq()
{
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    glColor3f( 1, 0.5, 0.5);       // Green
    glVertex3f( -0.05, 0.02, -0.05f);
    glVertex3f(-0.05, 0.02, -0.05f);
    glVertex3f(-0.05f, 0.02f,  0.05f);
    glVertex3f( 0.05f, 0.02f,  0.05f);

    // Bottom face (y = -0.05f)
    glColor3f( 1, 0.3, 0.3);       // Green
    glVertex3f( 0.05, -0.05,  0.05f);
    glVertex3f(-0.05, -0.05,  0.05f);
    glVertex3f(-0.05, -0.05, -0.05f);
    glVertex3f( 0.05, -0.05, -0.05f);

    // Front face  (z = 0.05f)
    glColor3f( 1, 0, 0);       // Green
    glVertex3f( 0.05f,  0.05f, 0.05f);
    glVertex3f(-0.05f,  0.05f, 0.05f);
    glVertex3f(-0.05f, -0.05f, 0.05f);
    glVertex3f( 0.05f, -0.05f, 0.05f);
    // Back face (z = -0.05f)
    glColor3f( 1, 0.3, 0.3);       // Green
    glVertex3f( 0.05f, -0.05f, -0.05f);
    glVertex3f(-0.05f, -0.05f, -0.05f);
    glVertex3f(-0.05f,  0.05f, -0.05f);
    glVertex3f( 0.05f,  0.05f, -0.05f);

    // Left face (x = -0.05f)
    glColor3f( 1, 0.3, 0.3);       // Green
    glVertex3f(-0.05f,  0.05f,  0.05f);
    glVertex3f(-0.05f,  0.05f, -0.05f);
    glVertex3f(-0.05f, -0.05f, -0.05f);
    glVertex3f(-0.05f, -0.05f,  0.05f);

    // Right face (x = 0.05f)
    glColor3f( 1, 0.3, 0.3);       // Green
    glVertex3f(0.05f,  0.05f, -0.05f);
    glVertex3f(0.05f,  0.05f,  0.05f);
    glVertex3f(0.05f, -0.05f,  0.05f);
    glVertex3f(0.05f, -0.05f, -0.05f);
    glEnd();  // End of drawing color-cube
}
void call(float tx, float ty, float tz )
{
    glPushMatrix();
    glTranslatef(tx, ty,tz);
    glRotated(10, 1, 0, 0);
    glRotated(10, 0, 1, 0);
    sq2(0.05, 0.05, 0.05 , 0 , 0 , 1);
    glPopMatrix();
    glutPostRedisplay();
}
void call2(float tx, float ty, float tz )
{
    glPushMatrix();
    glTranslatef(tx, ty,tz);
    glRotated(10, 1, 0, 0);
    glRotated(10, 0, 1, 0);
    sq2(0.05, 0.05, 0.05 , 1 , 1 , 0);
    glPopMatrix();
    glutPostRedisplay();
}
void walls()
{

    for(int j = 1 ; j <= 6 ; j++)
    {
        face[j].push_back({0.5 ,{0.5 , 0}});
        face[j].push_back({0.2 ,{0.2 , 0}});
        face[j].push_back({-0.2 ,{0 , .2}});
    }
}
void food()
{

    for(int j = 1 ; j <= 6 ; j++)
    {
        for (int i = 0; i < 5; i++)
        {
        foodt[j].push_back({0.4 ,{-0.2 , 0}});
        foodt[j].push_back({-0.4 ,{-0.4 , 0}});
        foodt[j].push_back({0.2 ,{0 , 1}});
        }
    }
}
void update( int value )
{
    if(rn == 1)
    {
        if(temp > -90)
        {
            temp -= 2;
            angely -=2;
            if(angy == 20)x-=0.032;
            else x-=0.015;
            if(angy < 20) angy++;
            glutTimerFunc(25, update, 0);
            glutPostRedisplay();
        }
        if( temp == -90)
        {
            angely = 0;

            for(int i = 0 ; i < 3 ; i++)
            {
                swap(v[i], v[i + 1]);
            }
            swap(face[1] , face[4]);
            swap(face[3] , face[4]);
            swap(face[3] , face[2]);
            pre = pre+1;
            temp =0 ;
            rn = 0;
            glutPostRedisplay();
        }
    }
    else if(ln == 1 && temp < 90)
    {
        if(temp < 90)
        {
               temp += 2;
             angely += 2;
            if(angy > 0)x+=0.03;
            else x+=0.3;
            if(y < -0.75 && angy == 20) y +=0.015;
                if(angy < 20) angy++;
            //cout << x<<" " << y<<"\n";
              glutTimerFunc(25, update, 0);
            glutPostRedisplay();
        }
        if( temp == 90)
        {
            angely = 0;
            for(int i = 0 ; i < 3 ; i++)
            {
                swap(face[i+1], face[i + 2]);
            }
            swap(v[3], v[0]);
            swap(v[2],v[3]);
            swap(v[2], v[1]);
            pre = pre + 1;
            temp =0 ;
            ln = 0;
            glutPostRedisplay();
        }
    }
    else if(un == 1 && temp < 90)
    {
        if(temp < 90)
        {
            temp += 2;
            angelx += 2;
            y-=0.032;
            if(angy == 0 && x > 0.75) x-=0.02;
            if(angy > 0) angy--;
            glutTimerFunc(25, update, 0);
            glutPostRedisplay();
        }
        if( temp == 90)
        {
            angelx = 0;
            swap(v[0], v[4]);
            swap(v[4], v[2]);
            swap(v[2], v[5]);
            //*****
            swap(face[1], face[6]);
            swap(face[5], face[6]);
            swap(face[6], face[3]);
            glutPostRedisplay();
            angelx = 0;
            temp =0 ;
            un = 0;
            glutPostRedisplay();
        }
    }
    else if(dn == 1 && temp > -90)
    {
        if(temp > -90)
        {
            temp -= 2;
            angelx -= 2;
            y+=0.032;
            if(angy == 0 && x > 0.75) x+=0.02;
            if(angy > 0) angy--;
            glutTimerFunc(25, update, 0);
            glutPostRedisplay();
        }
        if( temp == -90)
        {
            angelx = 0;
            swap(v[0], v[5]);
            swap(v[4], v[5]);
            swap(v[5], v[2]);
            //****
            swap(face[1], face[5]);
            swap(face[5], face[3]);
            swap(face[3], face[6]);
            for(int i = 0 ; i < 5 ; i++){
                face[1][i].second.second+=1000;
            }
            glutPostRedisplay();
            angelx = 0;
            temp =0 ;
            dn = 0;
            glutPostRedisplay();
        }
    }
    else temp = 0, rn = 0, ln = 0, un = 0, temp = 0, dn = 0, angely=0,angelx=0;
}
void key(int key,int z, int n)
{
    if(key == GLUT_KEY_RIGHT)
    {
        prekey = 1;
    }
    else if(key == GLUT_KEY_LEFT)
{

        prekey = 2;

    }
    else if(key == GLUT_KEY_UP)
    {

        prekey = 3;

    }
    else if(key == GLUT_KEY_DOWN)
    {
        prekey = 4;

    }
    glutPostRedisplay();

}
int convert(float tt){
 float l = 0;
    stringstream stream;
    stream << tt;
    string str;
    stream >> str;
         float ye ;
     l=str.find('.');
     int k= str[l+1] - '0' ;
     if(str.size() >= 4){
     int ll= str[l+2] - '0' ;
     ye = (k * 10) + ll;
     }
     else{
        ye = k * 10;
        if(ye == 0 )  ye = 00;
     }
     return ye;
}
bool checkx( float tt ){

     float t1 = convert(tt);
     for(int i = 0 ; i <3 ; i++){

        if(convert(face[1][i].first) == t1){
            return true;
        }
     }
     return false;
}

bool checky( float tt ){
        float t1 = convert(tt);
       for(int i = 0 ; i < 3 ; i++){
        if(convert(face[1][i].second.first) == t1){
            return true;
        }
     }
     return false;
}
bool checkk(float tt1 , float tt2){
  if(convert(tt1) == convert(tt2)) return true;
  else return false;

}
void Move(){
if(prekey == 1){
 if((x + 0.05 >= 1 && angy == 20)|| (x + 0.05 >= 0.75 && angy == 0))
        {
            rn = 1;
            update(5);
            glutPostRedisplay();
        }
        else if(rn == 0){
        x+=0.0005;
        glutPostRedisplay();
        }
}
else if(prekey == 2){
           if((x <= -0.45 && angy == 20) || (x <= -0.75 && angely == 0))
        {
            ln = 1;
            update(5);
            glutPostRedisplay();
        }
        else if(ln == 0){
        x-=0.0005;
        glutPostRedisplay();
        }

}
else if(prekey == 3){
            if((y >= 0.50 && angy == 20) || (y >= 0.55 && angy == 0))
        {
            un = 1;
            update(5);
            glutPostRedisplay();
        }
        else if(un == 0){
           y+=0.0005;
            glutPostRedisplay();
        }
}
else if(prekey == 4){
         if((y <= -1 && angy == 20) || (y <= -0.95 && angy == 0))
        {
            dn = 1;
            update(5);
            glutPostRedisplay();
        }
            else if(dn ==0){
            y-=0.0005;
            glutPostRedisplay();
            }

}
    }
void display()
{

    Move();
    food();
    walls();
    points();
    gluLookAt(0,0,5,0,0,0,0,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


 //********************************************
    glPushMatrix();
    glTranslatef(0.0, 0.0, -1.5);
    glRotated(angelx + angx, 1, 0, 0);
    glRotated(angely + angy,0, 1, 0);
    cube();
    glPopMatrix();
//*************************************************
    glPushMatrix();
    glTranslatef(x, y,0.5);
    glRotated(10, 1, 0, 0);
    glRotated(10, 0, 1, 0);
    sq();
    glPopMatrix();
    //********walls
    for(int j = 1 ; j <= 6 ; j++){
    for(int i = 0 ; i < 5 ; i++)
    {
        if(j == 1)call(face[j][i].first, face[j][i].second.first, face[j][i].second.second);
        if(j == 5)call(face[j][i].first, face[j][i].second.first+ abs((0.75 + (face[j][i].second.first / (float)3)) - face[j][i].second.first), face[j][i].second.second);
        if(j == 2 && angy == 20)call(face[j][i].first - abs((-0.75 + (face[j][i].first / (float)4)) - face[j][i].first), face[j][i].second.first, face[j][i].second.second);
        if(j == 2 && angy == 0)call(face[j][i].first, face[j][i].second.first, face[j][i].second.second - 45);
        if(j == 4)call(face[j][i].first, face[j][i].second.first, face[j][i].second.second-45);
        if(j == 3)call(face[j][i].first, face[j][i].second.first, face[j][i].second.second-45);
        if(j == 6)call(face[j][i].first, face[j][i].second.first, face[j][i].second.second-45);
    }
    }
    for(int j = 1 ; j <= 6 ; j++){
    for(int i = 0 ; i < 5 ; i++)
    {
        if(j == 1)call2(foodt[j][i].first, foodt[j][i].second.first, foodt[j][i].second.second);
        if(j == 5)call2(foodt[j][i].first, foodt[j][i].second.first+ abs((0.75 + (foodt[j][i].second.first / (float)3)) - foodt[j][i].second.first), foodt[j][i].second.second);
        if(j == 2 && angy == 20)call2(foodt[j][i].first - abs((-0.75 + (foodt[j][i].first / (float)4)) - foodt[j][i].first), foodt[j][i].second.first, foodt[j][i].second.second);
        if(j == 2 && angy == 0)call2(foodt[j][i].first, foodt[j][i].second.first, foodt[j][i].second.second - 45);
        if(j == 4)call2(foodt[j][i].first, foodt[j][i].second.first, foodt[j][i].second.second-45);
        if(j == 3)call2(foodt[j][i].first, foodt[j][i].second.first, foodt[j][i].second.second-45);
        if(j == 6)call2(foodt[j][i].first, foodt[j][i].second.first, foodt[j][i].second.second-45);
    }
    }
    if(checkx(x) && checky(y)){
        cout <<"GAME OVER"<<"\n";
    }
    for(int i = 0 ; i < 5 ; i++){
          //  if(foodt[1][i].second.second < 1) continue;
            float rrt1 = round(foodt[1][i].first * 10) / 10;
            float rrt2 = round(x * 10) / 10;
            float rrt3 = round(foodt[1][i].second.first * 10) / 10;
            float rrt4 = round(y * 10) / 10;
        if((rrt1 == rrt2)  && (rrt3 == rrt4)){
            foodt[1][i].second.second -= 1000;
        }
    }
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)    // GLsizei for non-negative integer
{
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
   glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
int main(int argc, char** argv)
{
    PlaySound(TEXT("C:\\Users\\fhake\\Desktop\\2213\\Background"), NULL, SND_FILENAME | SND_ASYNC);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1400, 880);
    glutInitWindowPosition(0, 00);
    glutCreateWindow("GAME");

    glMatrixMode(GL_PROJECTION);
    gluPerspective(100, 1.5, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(key);

    initGL();
    glutTimerFunc(25, update, 0);
    glPushMatrix();

    glutMainLoop();
    return 0;
}
