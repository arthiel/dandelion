/** 
 * The actual Dandelion Flower object.
 * Author: Emily Egeland
 **/
#include "stdafx.h"
#include <cstdlib>
#include "gl/glut.h"

class Flower{
	float _x, _y, _z;
public:
	Flower( float, float, float );
	void makeFlower();
};