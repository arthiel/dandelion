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

Flower::Flower(float x, float y, float z, float r){
	_x = x;
	_y = y;
	_z = z;
   tess_value = (int)rand() % 2 + 2;
    //tess_value = 3;
    height = 1 + (float)(rand() % 10)*.1;
    count = 0;
    //seedlet_limit = 2;
    seedlet_limit = rand() % 3;
    radius = r;
    root = Seedlet();
    seed_ind = 0;
    seed_hair = (rand()%30)+10;
	mathFlower();
}

void Flower::mathFlower(){

	Sphere(tess_value);

}

void Flower::makeFlower(){
    glPushMatrix();
	glTranslatef( _x, _y, _z );
	// THis is the green stalk of the flower.
    glPushMatrix();
	glRotatef( -90, 1, 0, 0 );
    glColor3f( 1, .6, 0 ); 

	GLUquadricObj *c = gluNewQuadric();
	gluCylinder( gluNewQuadric(), .02, .02, height, 10, 10 );

	glPopMatrix();

    glTranslatef( 0, height - .05, 0 );

    for( int i = 0; i < seed_ind; i++ ){
        seeds[i].drawSeedlet();
    }
    glPopMatrix();

}

void Flower::HardSphere(){
    Seedlet up( 0, 1, 0, radius);
    up.drawSeedlet();
    Seedlet dup( 0, 1, 0, radius );
    dup.drawSeedlet();
    for( int i =0; i < 13; i++ ){
    glRotatef( 45, 0, 0, 1);
    glPushMatrix();
        glRotatef(45, 1, 0, 0 );
        Seedlet sup( 0, 1, 0, radius );
        sup.drawSeedlet();
    glPopMatrix();
    }
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
   
    
     Point3 v10(-a, -1, 0);
    Point3 v11(a, -1, 0);

    // Begin the tesselation!
    tesselateHead( v0, v1, v2, n );
    tesselateHead( v3, v2, v1, n );
    tesselateHead( v3, v4, v5, n );
    tesselateHead( v3, v5, v6, n );
    tesselateHead( v0, v7, v8, n );
    tesselateHead( v0, v8, v9, n );

    tesselateHead( v1, v9, v4, n );
    tesselateHead( v2 ,v6, v7, n );

    tesselateHead( v3, v1, v4, n );
    tesselateHead( v3, v6, v2, n );
    tesselateHead( v0, v9, v1, n );
    tesselateHead( v0, v2, v7, n );

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

        Vector3 xside( 1, 0, 0 );
        Vector3 yside( 0, 1, 0 );
        Vector3 zside( 0, 0, 1 );

        if( seedlet_limit == 0 || seedlet_limit == 2){
                        glPushMatrix();

            Vector3 a = v0 - Point3(0,0,0);

            float angx = (xside * a);
            float angy = (yside * a);
            float angz = (zside * a);
            glColor3f( 1, 1, 1); // white tip fuzz
            // Add the sphere to the end of the seedlet, this is where the hairs will spout from.
            Point3 rotateMe( 100*angx, 100*angy, 100*angz );
            checkSeedletExist( rotateMe, root );

            glPopMatrix();
        }
        if( seedlet_limit == 1 || seedlet_limit == 2 ){
            glPushMatrix();
            Vector3 a = v1 - Point3(0,0,0);
            float angx = (xside * a);
            float angy = (yside * a);
            float angz = (zside * a);
      
            Point3 rotateMe2( 100*angx, 100*angy, 100*angz );

            checkSeedletExist( rotateMe2, root );

            glColor3f( 0, 1, 0 );
            glPopMatrix();
        }
       // std::cout << "COunt: " << (count+= 2) << std::endl;
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

void Flower::printInfo(){
    std::cout << "Tesselation Factor: " << tess_value << std::endl;
    std::cout << "Density Level: " << seedlet_limit << std::endl;
    std::cout << "# of Seedlets: " << seed_ind << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Radius: " << radius << std::endl;
    std::cout << "Seedlet Hair Length: " << seed_hair << std::endl;
    std::cout << std::endl;
}

void Flower::checkSeedletExist( Point3 rotateMe, Seedlet go ){
    //std::cout << seed_ind << std::endl;
    if( seed_ind >= 50 ){
        return;
    }
    for( int i = 0; i <= seed_ind; i++ ){
        if( rotateMe == seeds[i].returnRots() ){
            return;
        }
    }
    seeds[seed_ind] = Seedlet( rotateMe, radius, seed_hair);
    seed_ind++;
    return;

}