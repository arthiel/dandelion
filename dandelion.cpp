// dandelion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <gl/glut.h>

int WINDOW_HEIGHT = 500;
int WINDOW_WIDTH = 500;

void display( void ){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	glPushMatrix();
	gluLookAt(0, 2, 10, 0, 0, 0, 0, 1, 0 ); 

	glColor3f( 0, 1.0, 0 );
	glLineWidth( 3 );
	glBegin( GL_LINE_STRIP );
		glVertex3d(0,0,0);
		glVertex3d(2,0, 0);
		glVertex3d(2, 0, -2);
		glVertex3d(0, 0, 0);

		glVertex3d(0, 0, -2);
		glVertex3d( 2, 0, -2);
		
		glVertex3d( 2, 0, -4 );
		glVertex3d( 0, 0, -2 );
		glVertex3d( 0, 0, -4 );
		glVertex3d( 2, 0, -4 );
	glEnd();

	glPopMatrix();
	glEnable( GL_DEPTH_TEST );
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowSize( WINDOW_HEIGHT, WINDOW_WIDTH );
	glutCreateWindow( argv[0] );

	glEnable( GL_DEPTH_TEST );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45, 1, 1, -1.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glutDisplayFunc(display) ;
	glutMainLoop();

	return 0;
}

