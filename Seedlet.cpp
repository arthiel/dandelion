/** 
 * Particle for each individual seedlet
 * Author: Emily Egeland
 **/
#include "stdafx.h"
#include "Seedlet.h"

Seedlet::Seedlet(){

}

Seedlet::Seedlet( float x, float y, float z ){
    top_x = x;
    top_y = y;
    top_z = z;
}

void Seedlet::drawSeedlet(){

    glPushMatrix();
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( top_x, top_y, top_z );
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(top_x, top_y, top_z );
    glutSolidSphere( .02, 15, 15 );
    drawHairs();
    glPopMatrix();

}

void Seedlet::jitter(){

}

void Seedlet::drawHairs( ){
    glPushMatrix();
    for( int i = 0; i < 13; i++ ){
    glRotatef( 20, 0, 1, 0 );
    // Point P
    Point3 p( 0, 0, 0 );
    // Point Q
    Point3 q( .5, 0, 0 );
    // Point S
    Point3 s( .5, .5, 0 );

    glBegin(GL_POINTS);
    for( float u = 0; u < .5; u+=.01 ){
        float Pux = (.5 - u ) * p.x + (u * q.x);
        float Puy = (.5 - u ) * p.y + (u * q.y );
        float Qux = (.5 - u ) * q.x + (u * s.x );
        float Quy = (.5 - u ) * q.y + (u * s.y );

        float pntx = (.5 - u ) * Pux + u * Qux;
        float pnty = (.5 - u ) * Puy + u * Quy;

        glVertex3f( pntx, pnty, 0 );
    }
    glEnd();
    }

    glPopMatrix();
}