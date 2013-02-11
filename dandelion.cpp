// dandelion.cpp : Defines the entry point for the console application.
// Author: Emily Egeland

#include "stdafx.h"
#include <cstdlib>
#include "math.h"
#include <gl/glut.h>
#include "Flower.h"

int WINDOW_HEIGHT = 500;
int WINDOW_WIDTH = 500;
float xrot = 0, yrot = 0, xpos = 0, ypos = 2, zpos = 10;
int numCell = 3;
// Need to be able to increase these.
const int numRows = 5;
const int numCols = 5;
// End
int numFlowers = 0;
Flower field[numRows][numCols];

void floor( int, int );

/** 
* Generate all flowers that are on the map
**/
void makeField( ) {
    for( int y = 0; y < numCell; y++ ){
        for( int x = 0; x < numCell; x++ ){
            if( field[y][x]._x != 0){
                field[y][x].makeFlower();
            }
        }
    }
}

/**
* Adds a flower to the scene
**/
void addFlower() {
    if( numFlowers >= numCell * numCell ) {
        std::cout << "Max Flowers Added." << std::endl;
        return;
    }
    numFlowers++;
    int x = rand() % numCell;
    int y = rand()% numCell;
    while( field[y][x]._x != 0 ){
        std::cout << x << " " << y << std::endl;

        x = rand() % numCell;
        y = rand()  % numCell;
    }
    field[y][x] = Flower( x +.5, 0, -y + .5 );
    return;
}

/** 
* Removes a random flower from the field.
**/
void removeFlower() {
    if( numFlowers == 0 ){
        std::cout << "No Flowers on Field." << std::endl;
        return;
    }
    numFlowers--;
    int x = rand() % numCell;
    int y = rand()% numCell;
    while( field[y][x]._x == 0 ){
        std::cout << x << " " << y << std::endl;

        x = rand() % numCell;
        y = rand()  % numCell;
    }
    field[y][x] = Flower();
    return;
}

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

    glColor3f( 0, 1.0, 0 );
    glLineWidth( 1 );

    floor( numCell, numCell );
    makeField();

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
        xpos += float( sin(yrad)) *.5;
        zpos -= float( cos(yrad)) *.5;
        ypos -= float( sin(xrad)) *.5;
        break;
    case 'a':   // Side step LEFT
        xpos -= float( cos(yrad)) * 0.2;
        zpos -= float( sin(yrad)) * 0.2;
        break;
    case 's':   // Move camera BACKWARD
        xpos -= float( sin(yrad)) *.5;
        zpos += float( cos(yrad)) *.5;
        ypos += float(sin(xrad)) *.5;
        break;
    case 'd':   // Side step RIGHT 
        xpos += float( cos(yrad)) * 0.2;
        zpos += float( sin(yrad)) *0.2;
        break;
    case 'f':	// Add a flower

        break;
    case 'j':   // Decrease by 1 Row/Col
        numCell--;
        break;
    case 'k':   // Increase by 1 Row/Col
        numCell++;
        break;
    case 'n':   // Add Flower
        addFlower();
        break;
    case 'm':   // Remove Flower
        removeFlower();
        break;
    case '1':   // Switch to origin flower
        xpos = field[0][0]._x;
        ypos = field[0][0]._y + 1.5;
        zpos = field[0][0]._z + 1.5;
        break;
    case 'q':   // Exit.
        exit(1);
        break;
    }
    display();
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

    field[0][0] = Flower( 0.5, 0, -0.5 );
    numFlowers++;
    addFlower();

    glutDisplayFunc(display) ;
    glutKeyboardFunc( keyboard );
    //glutTimerFunc( 10, timer, 0 );

    glutMainLoop();

    return 0;
}

