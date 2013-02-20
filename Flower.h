/** 
 * The actual Dandelion Flower object.
 * Author: Emily Egeland
 **/
#ifndef FLOWER_H
#define FLOWER_H

#include "stdafx.h"
#include <cstdlib>
#include <list>
#include "gl/glut.h"
#include "vecmath.h"
#include "Seedlet.h"


class Flower{
    typedef list<Seedlet> SEEDLETS;
public:
    	float _x, _y, _z, height;
        int tess_value;
        int count, seedlet_limit;
        float radius;
        Seedlet seeds[50];
        Seedlet root;
        int seed_ind;
        int seed_hair;

    Flower();
	Flower( float x, float y, float z, float r);
	void mathFlower();
    void makeFlower();
    void Sphere( int n );
    void HardSphere();
    void tesselateHead( Point3 v0, Point3 v1, Point3 v2, int factor );
    Point3 midpoint( Point3 a1, Point3 b1 );
    void addTriangle( Point3 a, Point3 b, Point3 c );
    Point3 jitter( Point3 x );
    void drawHairs( );
    void printInfo();
    void checkSeedletExist( Point3 rot, Seedlet);
};

#endif