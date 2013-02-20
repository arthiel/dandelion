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
const int numRows = 15;
const int numCols = 15;
// End
int numFlowers = 0;
Flower field[numRows][numCols];

Flower view[3];
int num_view;

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
    // Increase the number of flowers.
    numFlowers++;
    // Find a new random place on the grid.
    int x = rand() % numCell;
    int y = rand()% numCell;
    while( field[y][x]._x != 0 ){
        x = rand() % numCell;
        y = rand()  % numCell;
    }
    // Create new flower at this location.
    field[y][x] = Flower( x +.5, 0, -y + .5, (rand()%4)*.25 +.05);
    field[y][x].printInfo();

    // If there are no or less flowers in the view array, add one.
    if( num_view < 3 ){
        for( int i =0; i < 3; i++ ){
            if( view[x]._x == 0 && view[x]._y == 0 && view[x]._z == 0 ){
                view[x] = field[y][x];
                return;
            }
        }
    }
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
        //std::cout << x << " " << y << std::endl;

        x = rand() % numCell;
        y = rand()  % numCell;
    }
    field[y][x] = Flower();
    if( num_view > 0 ){
        int a = 0;
        while( view[a]._x != field[y][x]._x && view[a]._y != field[y][x]._y && view[a]._z != field[y][x]._y && a < 3){
            a++;
        }
        if( a < 3 ){
            view[a] = Flower();
            num_view--;
        }
    }
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
    //gluLookAt( xpos, ypos, zpos, field[0][0]._x, field[0][0]._y, field[0][0]._z, 0, 1, 0 );

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

// Create the gridded floor
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

// View a specific flower.
void view_specific( int x){

    while( view[x]._x == 0 && view[x]._y == 0 && view[x]._z == 0 &&x < num_view ){
        x++;
    }
    if( view[x]._x == 0 && view[x]._y == 0 && view[x]._z == 0 ){
        std::cout << "No Flowers available" << std::endl;
    }
    xpos = view[x]._x;
    ypos = view[x]._y + 1.5;
    zpos = view[x]._z + 1.5;
    view[x].printInfo();
    gluLookAt( xpos, ypos, zpos, view[x]._x, view[x]._y, view[x]._z, 0, 1, 0 );
}

// Keyboard controls
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
        yrot+= 5;
        break;
    case 's':   // Move camera BACKWARD
        xpos -= float( sin(yrad)) *.5;
        zpos += float( cos(yrad)) *.5;
        ypos += float(sin(xrad)) *.5;
        break;
    case 'd':   // Side step RIGHT 
        yrot-=5;
        break;
    case 'j':   // Decrease by 1 Row/Col
        if( numCell > 0 ){
            numCell--;
        }
        else {
            std::cout << "No grid to shrink." << std::endl;
        }
        break;
    case 'k':   // Increase by 1 Row/Col
        if( numCell > numCols ){
            numCell++;
        }
        else {
            std::cout << "Maximum Grid Size (15x15) reached." << std::endl;
        }
        break;
    case 'n':   // Add Flower
        addFlower();
        break;
    case 'm':   // Remove Flower
        removeFlower();
        break;
    case '1':   // Switch to origin flower
        view_specific( 0);
        break;
    case '2':   // Switch to another flower
        view_specific( 1);
        break;
    case '3':   // Switch to another flower
        view_specific( 2 );
        break;
    case 'f': // Print number of flowers
        std::cout << "Number of Flowers: " << numFlowers << std::endl;
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

void mouse( int button, int state, int x, int y ){
    //std::cout << x << std::endl;
}

void mousemove(int x, int y ){
    float yrad = (yrot / 180 * 3.141592654f);
    float xrad = (xrot / 180 * 3.141592654f);
    //std::cout << x << std::endl;
    if( y > WINDOW_HEIGHT/2 ){   // Forward
        xpos += float( sin(yrad)) *.5;
        zpos -= float( cos(yrad)) *.5;
        ypos -= float( sin(xrad)) *.5;
    }
    else if( y < WINDOW_HEIGHT/2 ){   // Backward
        xpos -= float( sin(yrad)) *.5;
        zpos += float( cos(yrad)) *.5;
        ypos += float(sin(xrad)) *.5;
    }
    if( x > WINDOW_WIDTH/2 ){   // Left
        xpos -= float( cos(yrad)) * 0.2;
        zpos -= float( sin(yrad)) * 0.2;
    }
    else if( x < WINDOW_WIDTH /2 ){   // Right
        xpos += float( cos(yrad)) * 0.2;
        zpos += float( sin(yrad)) *0.2;
    }
}

void init() {
    GLfloat mat_spec[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shiny[] = { 50.0 };
    GLfloat light_pos[] = { 0.0, 3.0, 3.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel( GL_SMOOTH );
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
   glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

    glColorMaterial( GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable( GL_COLOR_MATERIAL );
}

int main(int argc, char* argv[])
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize( WINDOW_HEIGHT, WINDOW_WIDTH );
    glutCreateWindow( argv[0] );

    // Uncomment to add lighting
    //init();

    glEnable( GL_DEPTH_TEST );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, 1, 1, -1.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    addFlower();

    glutDisplayFunc(display) ;
    glutKeyboardFunc( keyboard );
    //glutMouseFunc( mouse );
   // glutPassiveMotionFunc( mousemove );
   // glutTimerFunc( 10, timer, 0 );

    glutMainLoop();

    return 0;
}

