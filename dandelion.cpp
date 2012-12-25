// dandelion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "math.h"
#include <gl/glut.h>

int WINDOW_HEIGHT = 500;
int WINDOW_WIDTH = 500;
float xrot = 0, yrot = 0, xpos = 0, ypos = 2, zpos = 10;

void floor( int, int );

void camera(){
    glRotatef( xrot, 1.0, 0.0, 0.0 );
    glRotatef( yrot, 0.0, 1.0, 0.0 );
    glTranslated( -xpos, -ypos, -zpos );
}

void display( void ){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	glPushMatrix();

	camera();
	//gluLookAt(0, 2, 10, 0, 0, 0, 0, 1, 0 ); 

	glColor3f( 0, 1.0, 0 );
	glLineWidth( 1 );

	floor( 4, 4 );

	glPopMatrix();
	glutSwapBuffers();
	glEnable( GL_DEPTH_TEST );
	glFlush();
}

void floor( int row, int col ){
	glBegin( GL_LINE_STRIP );
	glVertex3d( 0, 0, 0 );
	for( int r = 1; r <= row; r++ ){
		for( int c = 1; c <= col; c++ ){
			glVertex3d( r, 0, -c+1 );
			glVertex3d( r, 0, -c );
			glVertex3d( r-1, 0, -c+1 );
			glVertex3d( r-1, 0, -c );
			glVertex3d( r, 0, -c );
		}
		glVertex3d( r, 0, 0 );
	}
	glEnd();
}

void keyboard( unsigned char key, int x, int y ){
	float yrad = (yrot / 180 * 3.141592654f);
    float xrad = (xrot / 180 * 3.141592654f);
	switch( key ) {
		case 'w':   // Move FORWARD
            xpos += float( sin(yrad));
            zpos -= float( cos(yrad));
            ypos -= float( sin(xrad));
            break;
        case 'a':   // Side step LEFT
            xpos -= float( cos(yrad)) * 0.2;
            zpos -= float( sin(yrad)) * 0.2;
            break;
        case 's':   // Move camera BACKWARD
            xpos -= float( sin(yrad));
            zpos += float( cos(yrad));
            ypos += float(sin(xrad));
            break;
        case 'd':   // Side step RIGHT 
            xpos += float( cos(yrad)) * 0.2;
            zpos += float( sin(yrad)) *0.2;
            break;
        case 'q':   // Exit.
            exit(1);
            break;
	}
}

void timer( int val ){
	glutPostRedisplay();
	glutTimerFunc( 10, timer, 0 );

}

int main(int argc, char* argv[])
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize( WINDOW_HEIGHT, WINDOW_WIDTH );
	glutCreateWindow( argv[0] );

	glEnable( GL_DEPTH_TEST );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45, 1, 1, -1.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glutDisplayFunc(display) ;
	glutKeyboardFunc( keyboard );
	glutTimerFunc( 10, timer, 0 );

	glutMainLoop();

	return 0;
}

