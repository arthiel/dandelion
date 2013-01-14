/** 
 * The actual Dandelion Flower object.
 * Author: Emily Egeland
 **/
#ifndef FLOWER_H
#define FLOWER_H

#include "stdafx.h"
#include <cstdlib>
#include "gl/glut.h"
#include "vecmath.h"


class Flower{
public:
    	float _x, _y, _z;

    Flower();
	Flower( float, float, float );
	void makeFlower();
    void Sphere( int n );
    void tesselateHead( Point3 v0, Point3 v1, Point3 v2, int factor );
    Point3 midpoint( Point3 a1, Point3 b1 );
    void addTriangle( Point3 a, Point3 b, Point3 c );
};

#endif