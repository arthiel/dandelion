/** 
 * The actual Dandelion Flower object.
 * Author: Emily Egeland
 **/

#include "stdafx.h"
#include "Flower.h"

Flower::Flower( ) {
    _x = 0;
    _y = 0;
    _z = 0;
    // Does not make a flower.
}

Flower::Flower(float x, float y, float z){
	_x = x;
	_y = y;
	_z = z;
	makeFlower();
}

void Flower::makeFlower(){
	glPushMatrix();
	glTranslatef( _x, _y, _z );
	glPushMatrix();
	glRotatef( -90, 1, 0, 0 );
    glColor3f( 1, .6, 0 ); 
	GLUquadricObj *c = gluNewQuadric();
	gluCylinder( gluNewQuadric(), .02, .02, 1.5, 10, 10 );
	glPopMatrix();
	glTranslatef( 0, 1.45, 0 );
	Sphere( 2);
    //glutWireSphere( .5, 10, 10 );

	glPopMatrix();
}

/**** 
 * Create a Sphere
 * Parameters: 
 * int n : tesselation factor
 ****/
void Flower::Sphere(int n){

    // Golden Ration calculation to create icosahedron.
    float a = 2 / (1+ sqrt( 5 ));

    // Starting Points of Icosahedron
    Point3 v0(0, a, -1);
    Point3 v1(-a, 1, 0 );
    Point3 v2(a, 1, 0 );
    Point3 v3( 0, a, 1 );
    Point3 v4(-1, 0, a );
    Point3 v5(0, -a, 1);
    Point3 v6(1, 0, a);
    Point3 v7(1, 0, -a);
    Point3 v8(0, -a, -1);
    Point3 v9(-1, 0, -a);
   // Point3 v10(-a, -1, 0);
   // Point3 v11(a, -1, 0);

    // Begin the tesselation!
    tesselateHead( v0, v1, v2, n );
    tesselateHead( v3, v2, v1, n );
    tesselateHead( v3, v4, v5, n );
    tesselateHead( v3, v5, v6, n );
    tesselateHead( v0, v7, v8, n );
    tesselateHead( v0, v8, v9, n );
   // tesselateHead( v5, v10, v11, n );
   // tesselateHead( v8, v11, v10, n );
    tesselateHead( v1, v9, v4, n );
//    tesselateHead( v10, v4, v9, n );
    tesselateHead( v2 ,v6, v7, n );
 //   tesselateHead( v11, v7, v6, n );
    tesselateHead( v3, v1, v4, n );
    tesselateHead( v3, v6, v2, n );
    tesselateHead( v0, v9, v1, n );
    tesselateHead( v0, v2, v7, n );
 //   tesselateHead( v8, v10, v9, n );
//    tesselateHead( v8, v7, v11, n );
 //   tesselateHead( v5, v4, v10, n );
  //  tesselateHead( v5, v11, v6, n );

    return;
}

void Flower::tesselateHead( Point3 v0, Point3 v1, Point3 v2, int factor ){
     if( factor == 1 ){
        // Normalize
        Vector3 l( v0.x, v0.y, v0.z );
        Vector3 m( v1.x, v1.y, v1.z );
        Vector3 n( v2.x, v2.y, v2.z );
        l.normalize();
        m.normalize();
        n.normalize();
        v0 = jitter( Point3( l.x, l.y, l.z ));
        v1 = jitter( Point3( m.x, m.y, m.z ));
      //  v2 = jitter( Point3( n.x, n.y, n.z ));



        // Make smaller to fit nicely on the screen :D
       // addTriangle( v0*.5, v1*.5, v2*.5 );
        glPushMatrix();
        glColor3f( .4, .6, 0 );
       // glColor3f( 1, .6, 0 );  // A brownish color for seedlet stalks
        // Create the seedlets spouting out from the center of the dandelion

            glVertex3f( 0, 0, 0 );
            glVertex3f( v1.x/2, v1.y/2, v1.z/2 );
           // glVertex3f( 0, 0, 0 );
           // glVertex3f( v2.x/2, v2.y/2, v2.z/2 );
        glEnd();
        
        glColor3f( 1, 1, 1); // white tip fuzz
        // Add the sphere to the end of the seedlet, this is where the hairs will spout from.
        Seedlet something( v0.x/2, v0.y/2, v0.z/2 );
        Seedlet something2( v1.x/2, v1.y/2, v1.z/2 );
        something.drawSeedlet();
        something2.drawSeedlet();

        glColor3f( 0, 1, 0 );
        glPopMatrix();
        return;
    }
    else {
        // Calculate Midpoints
        Point3 midv0 = midpoint( v0, v1 );
        Point3 midv1 = midpoint( v1, v2 );
        Point3 midv2 = midpoint( v2, v0 );
        
        // Multiply each vertex by the golden ratio 
        float q = (1+ sqrt( 5 ))/2;
        v0 *= q;
        v1 *= q;
        v2 *= q;

        // Recurse Tesselation

        // Left ( v0 center )
        tesselateHead( v0, midv0, midv2, factor-1 );
        
        // Upper (v1 center)
        tesselateHead( midv0, v1, midv1, factor-1 );
        
        // Center triangle
        tesselateHead( midv0, midv1, midv2, factor-1 );

        //Right (v2 center )
        tesselateHead( midv2, midv1, v2,  factor-1 );
        
    }
    
    return;
}

/**** 
 * Calculates midpoint nicely
 * Point3 a1, b1 : The two points on the line to calculate between.
 ****/
Point3 Flower::midpoint( Point3 a1, Point3 b1){
    // Normalize the values.
    Vector3 a( a1.x, a1.y, a1.z );
    Vector3 b( b1.x, b1.y, b1.z );
    a.normalize();
    b.normalize();
    // Find the midpoint.
    float x = a.x + ((b.x - a.x )/2 );
    float y = a.y + ((b.y - a.y)/2 );
    float z = a.z + ((b.z - a.z)/2 );
    // Return the new point.
    return Point3( x, y, z );
}

void Flower::addTriangle( Point3 a, Point3 b, Point3 c ){
    glPushMatrix();
    glBegin( GL_LINE_LOOP );
       glVertex3f( a.x, a.y, a.z );

        glVertex3f( b.x, b.y, b.z );
        glVertex3f( c.x, c.y, c.z );

    glEnd();
    glPopMatrix();
}

/// TODO: Multiplies every time the point is hit... SOLVE> 
Point3 Flower::jitter( Point3 x ){
   // x.x = x.x + ( (rand() % 15) * .01 );
   // x.y = x.y + ( (rand() % 15) * .01 );
   // x.z = x.z + ( (rand() % 15) * .01 );
    return x;
}

void Flower::drawHairs( ){
    glPushMatrix();
    //glTranslatef( orig.x, orig.y, orig.z );
    glBegin( GL_LINES );
        glVertex3f( 0, 0, 0 );
        glVertex3f( .1, .1, .1 );
        glVertex3f( 0, 0, 0 );
        glVertex3f( -.1, .1, .1 );
        glVertex3f( 0, 0, 0 );
        glVertex3f( -.1, -.1, .1 );
        glVertex3f( 0, 0, 0 );
        glVertex3f( -.1, .1, -.1 );
        glVertex3f( 0, 0, 0 );
        glVertex3f( -.1, -.1, -.1 );
        glVertex3f( 0, 0, 0 );
        glVertex3f( .1, -.1, .1 );
    glEnd();
    glPopMatrix();
}