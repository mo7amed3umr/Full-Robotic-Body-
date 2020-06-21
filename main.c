#include <GL/glut.h>
#include <math.h>
static int shoulderXR = 0, shoulderYR = 0, shoulderZR = 0,shoulderXL = 0, shoulderYL = 0, shoulderZL = 0,thighXR=0, thighZR = 0, elbowZR= 0, elbowZL= 0, fingerBase = 0, fingerUp = 0,finger1Base = 0, finger1Up = 0,finger2Base = 0, finger2Up = 0,finger3Base = 0, finger3Up = 0,finger4Base = 0, finger4Up = 0;
int moving, startx, starty, kneeZR = 0, thighZL = 0, thighXL = 0, kneeZL = 0,fingerBaseL = 0, fingerUpL = 0,finger1BaseL = 0, finger1UpL = 0,finger2BaseL = 0, finger2UpL = 0,finger3BaseL = 0, finger3UpL = 0, head=0;
static int shoulder = 0, shoulder2 = 0, elbow = 0, rhip = 0, rhip2 = 0, rknee = 0, lknee = 0, lhip = 0, lhip2 = 0 ;
double eye[] = { 0, 0, -20 };
double center[] = { 0, 0, 1 };
double up[] = { 0, 1, 0 };
double direction[] = {0,0,0};
double speed = 0.1;
double theta = 3.14/120;
GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */

void init(void)
{

   glMatrixMode(GL_PROJECTION);
	gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);
}
void myWireSphere(GLfloat radius, int slices, int stacks) {
  glPushMatrix();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glutWireSphere(radius, slices, stacks);
  glPopMatrix();
}

void wireBox(GLdouble width, GLdouble height, GLdouble depth) {
  glPushMatrix();
  glScalef(width, height, depth);
  glutWireCube(1.0);
  glPopMatrix();
}
void finger(GLdouble x, GLdouble y, GLdouble z,GLdouble fingerbase,GLfloat fingerup) {
  
   glPushMatrix();
   //Draw finger flang 1 
   glTranslatef(x, y, z);
   glRotatef(fingerbase, 1.0, 0.0, 0.0);
   glTranslatef(0, -0.075, 0);
   wireBox(0.1,0.15,0.15);
      

   //Draw finger flang 1 
   glTranslatef(0, -0.075, 0);
   glRotatef(fingerup, 1.0, 0.0, 0.0);
   glTranslatef(0, -0.075, 0);

   // glTranslatef(-x, -y - 0.05, -z);
   wireBox(0.1,0.15,0.15);

   glPopMatrix();
  
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta))*(a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta))*(a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta))*(a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta)*p[0];
	temp[1] += cos(theta)*p[1];
	temp[2] += cos(theta)*p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];

}

void Left()
{
   rotatePoint(up,-theta,eye);
	// implement camera rotation arround vertical window screen axis to the left
	// used by mouse and left arrow
}

void Right()
{
   rotatePoint(up,theta,eye);

	// implement camera rotation arround vertical window screen axis to the right
	// used by mouse and right arrow
}

void Up()
{
   double horizontal[3];

   crossProduct(eye,up,horizontal);
   normalize(horizontal);
   rotatePoint(horizontal,theta,eye);
   rotatePoint(horizontal,theta,up);
	// implement camera rotation arround horizontal window screen axis +ve
	// used by up arrow
}

void Down()
{	
   double horizontal[3];

   crossProduct(eye,up,horizontal);
   normalize(horizontal);
   rotatePoint(horizontal,-theta,eye);
   rotatePoint(horizontal,-theta,up);
	// implement camera rotation arround horizontal window screen axis 
	// used by down arrow
}

void moveForward()
{
   direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

   eye[0]    -= direction[0] * speed;
	eye[1]    -= direction[1] * speed;
	eye[2]    -= direction[2] * speed;

	center[0] -= direction[0] * speed;
	center[1] -= direction[1] * speed;
	center[2] -= direction[2] * speed;
}

void moveBack()
{
    direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

   eye[0]    += direction[0] * speed;
	eye[1]    += direction[1] * speed;
	eye[2]    += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[1] += direction[1] * speed;
	center[2] += direction[2] * speed;
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
   glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
  
	glTranslatef(0,1,0);
	//Head
   glPushMatrix();

   glTranslatef(0,2.7,0);
   glRotatef((GLfloat)head, 0.0, 1.0, 0.0);
   glTranslatef(0,-2.7,0);

   glPushMatrix();
   glTranslatef(0,2.7,0);
   glColor3f(0.2, 0.4,0.7);
   myWireSphere(0.7, 10, 10);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-0.2,2.8,0.6);
   myWireSphere(0.1,10,10);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.2,2.8,0.6);
   myWireSphere(0.1,10,10);
   glPopMatrix();
   
   glPopMatrix();
	// Chest
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glColor3f(0.2,0.4,0.7);
	glScalef(2,3,0.4);
	glutSolidCube(1);
	// wireBox(2.0, 3.0, 0.4);
	glPopMatrix();

	// shoulder right
	glPushMatrix();

	// glTranslatef(1.5,1.5,0);
	// glRotatef((GLfloat)shoulderXR,1,0,0);
	// glTranslatef(-1.5,-1.5,0);

	glTranslatef(1.25,1.5,0);
	glRotatef((GLfloat)shoulderZR,0,0,1);
	glTranslatef(-1.25,-1.5,0);

	glTranslatef(1.5,1.5,0);
	glRotatef((GLfloat)shoulderYR,0,1,0);
	glTranslatef(-1.5,-1.5,0);

	glTranslatef(1.25,1.5,0);
	glRotatef((GLfloat)shoulderZR,0,0,-1);
	glTranslatef(-1.25,-1.5,0);

	glTranslatef(1.25,1.5,0);
	glRotatef((GLfloat)shoulderZR,0,0,1);
	glTranslatef(-1.25,-1.5,0);

	glPushMatrix();
	glTranslatef(1.5,0.9,0);
	wireBox(0.5,1.2,0.4);
	glPopMatrix();

	// elbow left 

	glTranslatef(1.5,0.3,0.5);
	glRotatef((GLfloat)elbowZR,0,0,1);
	glTranslatef(-1.5,-0.3,-0.5);

	glPushMatrix();
	glTranslatef(1.5,-0.25,0);
	wireBox(0.5,1.1,0.4);
	glPopMatrix();


	finger(1.30,-0.8,-0.15,fingerBase,fingerUp);
	finger(1.5,-0.8,-0.15,finger1Base,finger1Up);
	finger(1.7,-0.8,-0.15,finger2Base,finger2Up);
	finger(1.5,-0.8,0.15,finger3Base,finger3Up);
	glPopMatrix();


	// shoulder left
	glPushMatrix();


	// glTranslatef(-1.5,1.5,0);
	// glRotatef((GLfloat)shoulderXL,1,0,0);
	// glTranslatef(1.5,-1.5,0);

	glTranslatef(-1.25,1.5,0);
	glRotatef((GLfloat)shoulderZL,0,0,-1);
	glTranslatef(1.25,-1.5,0);


	glTranslatef(-1.5,1.5,0);
	glRotatef((GLfloat)shoulderYL,0,-1,0);
	glTranslatef(1.5,-1.5,0);

	glTranslatef(-1.25,1.5,0);
	glRotatef((GLfloat)shoulderZL,0,0,1);
	glTranslatef(1.25,-1.5,0);


	glTranslatef(-1.25,1.5,0);
	glRotatef((GLfloat)shoulderZL,0,0,-1);
	glTranslatef(1.25,-1.5,0);

	glPushMatrix();
	glTranslatef(-1.5,0.9,0);
	wireBox(0.5,1.2,0.4);
	glPopMatrix();

	// elbow left 

	glTranslatef(-1.5,0.3,0.5);
	glRotatef((GLfloat)elbowZL,0,0,-1);
	glTranslatef(1.5,-0.3,-0.5);

	glPushMatrix();
	glTranslatef(-1.5,-0.25,0);
	wireBox(0.5,1.1,0.4);
	glPopMatrix();

	finger(-1.30,-0.8,-0.15,fingerBaseL,fingerUpL);
	finger(-1.5,-0.8,-0.15,finger1BaseL,finger1UpL);
	finger(-1.7,-0.8,-0.15,finger2BaseL,finger2UpL);
	finger(-1.5,-0.8,0.15,finger3BaseL,finger3UpL);


	glPopMatrix();

	// Leg Right
	glPushMatrix();

	glTranslatef(0.65,-1.5,0.2);
	glRotatef((GLfloat)thighZR,0,0,1);
	glTranslatef(-0.65,1.5,-0.2);

	glTranslatef(0.65,-1.5,0.2);
	glRotatef((GLfloat)thighXR,1,0,0);
	glTranslatef(-0.65,1.5,-0.2);

	glTranslatef(0.65,-1.5,0.2);
	glRotatef((GLfloat)thighZR,0,0,-1);
	glTranslatef(-0.65,1.5,-0.2);


	glTranslatef(0.65,-1.5,0.2);
	glRotatef((GLfloat)thighZR,0,0,1);
	glTranslatef(-0.65,1.5,-0.2);


	glPushMatrix();
	glTranslatef(0.65,-2.25,0);
	wireBox(0.7,1.5,0.4);
	glPopMatrix();

	// knee right 
	glTranslatef(0.65,-3,0.2);
	glRotatef((GLfloat)kneeZR,1,0,0);
	glTranslatef(-0.65,3,-0.2);
	glPushMatrix();
	glTranslatef(0.65,-3.75,0);
	wireBox(0.7,1.5,0.4);
	glPopMatrix();

	// feet right
	glPushMatrix();
	glTranslatef(0.65,-4.65,0);
	glScalef(0.7,0.3,0.7);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();

	//Leg Left
	glPushMatrix();

	glTranslatef(-0.65,-1.5,0.2);
	glRotatef((GLfloat)thighZL,0,0,-1);
	glTranslatef(0.65,1.5,-0.2);

	glTranslatef(-0.65,-1.5,0.2);
	glRotatef((GLfloat)thighXL,1,0,0);
	glTranslatef(0.65,1.5,-0.2);

	glTranslatef(-0.65,-1.5,0.2);
	glRotatef((GLfloat)thighZL,0,0,1);
	glTranslatef(0.65,1.5,-0.2);


	glTranslatef(-0.65,-1.5,0.2);
	glRotatef((GLfloat)thighZL,0,0,-1);
	glTranslatef(0.65,1.5,-0.2);

	glPushMatrix();
	glTranslatef(-0.65,-2.25,0);
	wireBox(0.7,1.5,0.4);
	glPopMatrix();

	// knee left 
	glTranslatef(-0.65,-3,0.2);
	glRotatef((GLfloat)kneeZL,1,0,0);
	glTranslatef(0.65,3,-0.2);
	glPushMatrix();
	glTranslatef(-0.65,-3.75,0);
	wireBox(0.7,1.5,0.4);
	glPopMatrix();

	// feet left
	glPushMatrix();
	glTranslatef(-0.65,-4.65,0);
	glScalef(0.7,0.3,0.7);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: Left(); break;
	case GLUT_KEY_RIGHT: Right(); break;
	case GLUT_KEY_UP:    Up(); break;
	case GLUT_KEY_DOWN:  Down(); break;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	// List all youe keyboard keys from assignment two her for body movement
	switch (key)
	{
	case '8':
		moveForward();
		glutPostRedisplay();
		break;
	case '9':
		moveBack();
		glutPostRedisplay();
		break;
	case 't':
      if (head > -160){
      head = (head - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'T':
      if (head < 0){
      head = (head + 5) % 360;
      glutPostRedisplay();}
      break;
   case '1':
      if (shoulderXR > -160){
      shoulderXR = (shoulderXR - 5) % 360;
      glutPostRedisplay();}
      break;
   case '4':
      if (shoulderXR < 0){
      shoulderXR = (shoulderXR + 5) % 360;
      glutPostRedisplay();}
      break;
   case '2':
      if(shoulderYR > -180){
      shoulderYR = (shoulderYR - 5) % 360;
      glutPostRedisplay();}
      break;
   case '5':
      if(shoulderYR < 0){
      shoulderYR = (shoulderYR + 5) % 360;
      glutPostRedisplay();}
      break;
   case '3':
      if(shoulderZR < 135){
      shoulderZR = (shoulderZR + 5) % 360;
      glutPostRedisplay();}
      break;

   case '6':
      if(shoulderZR > 0){
      shoulderZR = (shoulderZR - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'e':
      if (elbowZR < 140){
      elbowZR = (elbowZR + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'E':
      if (elbowZR > 0){
      elbowZR = (elbowZR - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'f':
      if(thighZR < 90){
      thighZR = (thighZR + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'F':
      if(thighZR >0){
      thighZR = (thighZR - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'q':
      if (shoulderXL > -160){
      shoulderXL = (shoulderXL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'Q':
      if (shoulderXL < 0){
      shoulderXL = (shoulderXL + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'w':
      if(shoulderYL > -180){
      shoulderYL = (shoulderYL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'W':
      if(shoulderYL < 0){
      shoulderYL = (shoulderYL + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'a':
      if(shoulderZL < 135){
      shoulderZL = (shoulderZL + 5) % 360;
      glutPostRedisplay();}
      break;

   case 'A':
      if(shoulderZL > 0){
      shoulderZL = (shoulderZL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 's':
      if (elbowZL < 140){
      elbowZL = (elbowZL + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'S':
      if (elbowZL > 0){
      elbowZL = (elbowZL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'z':
      if(thighZR < 90){
      thighZR = (thighZR + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'Z':
      if(thighZR >0){
      thighZR = (thighZR - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'x':
      if(thighXR > -90){
      thighXR = (thighXR - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'X':
      if(thighXR < 0){
      thighXR = (thighXR + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'c':
      if(kneeZR < 120){
      kneeZR = (kneeZR + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'C':
      if(kneeZR >0){
      kneeZR = (kneeZR - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'd':
      if(thighZL < 90){
      thighZL = (thighZL + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'D':
      if(thighZL >0){
      thighZL = (thighZL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'r':
      if(thighXL > -90){
      thighXL = (thighXL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'R':
      if(thighXL < 0){
      thighXL = (thighXL + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'v':
      if(kneeZL < 120){
      kneeZL = (kneeZL + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'V':
      if(kneeZL >0){
      kneeZL = (kneeZL - 5) % 360;
      glutPostRedisplay();}
      break;

   case 'g':
      if(fingerUp > -90){
      fingerUp = (fingerUp - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'G':
      if(fingerUp <0){     
      fingerUp = (fingerUp + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'h':
      if(fingerBase>-90){
      fingerBase = (fingerBase - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'H':
      if(fingerBase <0){
      fingerBase = (fingerBase + 5) % 360;
      glutPostRedisplay();}
      break;

   case '/':
      if(finger1Base>-90){
      finger1Base = (finger1Base - 5) % 360;
      glutPostRedisplay();}
      break;
   case '?':
      if(finger1Base< 0){
      finger1Base = (finger1Base + 5) % 360;
      glutPostRedisplay();}
      break;
   case '.':
      if(finger1Up>-90){
      finger1Up = (finger1Up - 5) % 360;
      glutPostRedisplay();}
      break;
   case '>':
      if(finger1Up< 0){
      finger1Up = (finger1Up + 5) % 360;
      glutPostRedisplay();}
      break;

   case ',':
      if(finger2Base>-90){
      finger2Base = (finger2Base - 5) % 360;
      glutPostRedisplay();}
      break;
   case '<':
      if(finger2Base< 0){
      finger2Base = (finger2Base + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'm':
      if(finger2Up>-90){
      finger2Up = (finger2Up - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'M':
      if(finger2Up<0){
      finger2Up = (finger2Up + 5) % 360;
      glutPostRedisplay();}
      break;

   case 'n':
      if(finger3Base< 90){
      finger3Base = (finger3Base + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'N':
      if(finger3Base>0){
      finger3Base = (finger3Base - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'b':
      if(finger3Up<90){
      finger3Up = (finger3Up + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'B':
      if(finger3Up>0){
      finger3Up = (finger3Up - 5) % 360;
      glutPostRedisplay();}
      break;
    case 'y':
      if(fingerUpL > -90){
      fingerUpL = (fingerUpL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'Y':
      if(fingerUpL <0){     
      fingerUpL = (fingerUpL + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'u':
      if(fingerBaseL>-90){
      fingerBaseL = (fingerBaseL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'U':
      if(fingerBaseL <0){
      fingerBaseL= (fingerBaseL + 5) % 360;
      glutPostRedisplay();}
      break;

   case 'i':
      if(finger1BaseL>-90){
      finger1BaseL = (finger1BaseL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'I':
      if(finger1BaseL< 0){
      finger1BaseL = (finger1BaseL + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'o':
      if(finger1UpL>-90){
      finger1UpL = (finger1UpL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'O':
      if(finger1UpL< 0){
      finger1UpL = (finger1UpL + 5) % 360;
      glutPostRedisplay();}
      break;

   case 'p':
      if(finger2BaseL>-90){
      finger2BaseL = (finger2BaseL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'P':
      if(finger2BaseL< 0){
      finger2BaseL = (finger2BaseL + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'j':
      if(finger2UpL>-90){
      finger2UpL = (finger2UpL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'J':
      if(finger2UpL<0){
      finger2UpL = (finger2UpL + 5) % 360;
      glutPostRedisplay();}
      break;

   case 'l':
      if(finger3BaseL<90){
      finger3BaseL = (finger3BaseL + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'L':
      if(finger3BaseL>0){
      finger3BaseL = (finger3BaseL - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'k':
      if(finger3UpL< 90){
      finger3UpL = (finger3UpL + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'K':
      if(finger3UpL>0){
      finger3UpL = (finger3UpL - 5) % 360;
      glutPostRedisplay();}
      break;
	default:
		break;
	}
}
static void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      moving = 1;
      startx = x;
      starty = y;
    }
    if (state == GLUT_UP) {
      moving = 0;
    }
  }
}


static void motion(int x, int y)
{
  if (moving) {
      /* angle = angle + (x - startx);
      angle2 = angle2 + (y - starty); */
      if (x > startx){
         Right();
      }
      else Left();
      startx = x;

    glutPostRedisplay();
  }
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("body");
	init();
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
	glutDisplayFunc(display);
   glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
