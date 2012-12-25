/** 
 * The actual Dandelion Flower object.
 * Author: Emily Egeland
 **/

#include "stdafx.h"
#include "Flower.h"

	float _x, _y, _z;
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
		GLUquadricObj *c = gluNewQuadric();
		gluCylinder( gluNewQuadric(), .05, .05, 1.5, 10, 10 );
		glPopMatrix();
		glTranslatef( 0, 1.45, 0 );
		glutWireSphere( .5, 10, 10 );

		glPopMatrix();
	}
