/**
 * Particle for each individual Seedlet
 * Author: Emily Egeland
 **/
#ifndef SEEDLET_H
#define SEEDLET_H
#include <cstdlib>
#include "gl/glut.h"
#include "vecmath.h"

class Seedlet {
private:
    int hairCount;  // Number of hairs on seedlet
    float jitterAmount; // Amount to jitter by for base
    float width; // width of seedlet base
    float height; // height of seedlet
    //float base_x, base_y, base_z; // Position elements of base
    float top_x, top_y, top_z; // Position elements of top
public:
    // Constructors
    Seedlet();
    Seedlet( float x, float y, float z );
    void drawSeedlet();
    void jitter();
    void drawHairs();
};
#endif