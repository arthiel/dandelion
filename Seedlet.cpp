/** 
 * Particle for each individual seedlet
 * Author: Emily Egeland
 **/
#include "stdafx.h"
#include "Seedlet.h"

Seedlet::Seedlet(){

}

Seedlet::Seedlet( Point3 rot, float h ) {
    rot_x = rot.x;
    rot_y = rot.y;
    rot_z = rot.z;
    hairlen = (float)((rand() % 3)/4) + .5;
    ctrlpnt_x = .3;
    ctrlpnt_y = .1;
    height = h;
}

Seedlet::Seedlet( float x, float y, float z, float h ){
    rot_x = x;
    rot_y = y;
    rot_z = z;
    hairlen = (float)((rand() % 3)/4) + .5;
    ctrlpnt_x = .3;
    ctrlpnt_y = .1;
    height = h;
    //ctrlpnt_x = (rand() % 4 ) * .1;
    //ctrlpnt_y = (rand() % 2 ) * .1;
}

void Seedlet::drawSeedlet(){
    glPushMatrix();
    glRotatef( rot_x, 1, 0, 0 );
    glRotatef( rot_y, 0, 1, 0 );
    glRotatef( rot_z, 0, 0, 1 );
    // This is the Seedlet Stalk emerging from the base.
    glPushMatrix();
        // Stalk is green
        glColor3f( .4, .6, 0 );
        glBegin( GL_LINES );
        glVertex3f( 0, 0, 0 );
        glVertex3f( 0, height, 0 );
        glEnd();
    glPopMatrix();

    // Hairs are white
    glColor3f( 1, 1, 1); 

    // Create a spherical connection for hairs.
    glPushMatrix();
        glTranslatef( 0, height, 0 );
        glutSolidSphere( .02, 15, 15 );
        glPushMatrix();
            // Draw the hairs on the sphere.
            drawHairs();
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void Seedlet::jitter(){

}

void Seedlet::drawHairs( ){
    glPushMatrix();
    int angle = 0;
    for( int i = 0; i < 18; i++ ){
        // Rotate to a different position
        glRotatef( 20, 0, 1, 0 );

        Vector3 rot_matrix[3] = { Vector3(0, 0, 0), Vector3(0, (1-cos(angle))+cos(angle), 0), Vector3(0,0,0) };
        // Point P
        Point3 p( 0, 0, 0 );
        // Point Q
        Point3 q( hairlen/**cos(angle)*/, 0, 0 );
        // Point S
        Point3 s( (hairlen+ctrlpnt_x)/**cos(angle)*/, /*-(hairlen+ctrlpnt_x)*sin(angle)+*/(hairlen+ctrlpnt_y)/**cos(angle)*/, 0 );

        glBegin(GL_POINTS);
        // Create each point on the bezier curve
        for( float u = 0; u < hairlen; u+=.01 ){
            float Pux = (hairlen - u ) * p.x + (u * q.x);
            float Puy = (hairlen - u ) * p.y + (u * q.y );
            float Qux = (hairlen - u ) * q.x + (u * s.x );
            float Quy = (hairlen - u ) * q.y + (u * s.y );

            float pntx = (hairlen - u ) * Pux + u * Qux;
            float pnty = (hairlen - u ) * Puy + u * Quy;

            //pntx = pntx * cos( angle ) + pnty * sin(angle);//pntx;//*rot_matrix[0].x + pnty*rot_matrix[0].y;
            //pnty = -pntx * sin( angle ) + pnty * cos(angle );//pnty*rot_matrix[1].y;
            glVertex3f( pntx, pnty, 0 );
        }
        glEnd();
        angle += 20;
    }

    glPopMatrix();
}