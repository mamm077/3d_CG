#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <stdio.h>

#include "myMath.h"

#define MAX_PARTICLE 3000


float g = 9.8;
float drag = 0.001;
float e = 0.5;
float radius = 0.1;

float getRandom(float fMin, float fMax)
{
    return fMin + (fMax - fMin) * (float)rand() / (float)RAND_MAX;
}

class CParticle {
 public:
  CVector vPosition;
  CVector vVelocity; 
  CVector vAccel;    
  CParticle();
  ~CParticle() {};
  void create();
  void update(float dt);
  void show(bool flagShadow);
};

CParticle::CParticle()
{
    vPosition = CVector(0.0, radius, 0.0);
    vVelocity = CVector(0.0, 0.0, 0.0);
    vAccel = CVector(2.0, - g, 0.0);
}

void CParticle::create()
{
    vPosition = CVector(0.0, radius, 0.0);
    vVelocity = CVector(0.0, 8.0, 0.0);
    vVelocity.x = getRandom(-1.0, 1.0);
    vVelocity.z = getRandom(-1.0, 1.0);
}

void CParticle::update(float dt)
{
    CVector accel = vAccel;
    accel -= drag * vVelocity;
    vVelocity += accel * dt;
    vPosition += vVelocity * dt;
    if(vPosition.y < radius)
    {
        vPosition.y = radius;
        vVelocity.y = - e * vVelocity.y;
    }
}

void CParticle::show(bool flagShadow)
{
    
    float diffuse[] = { 0.6f, 0.7f, 0.9f, 1.0f};
    float ambient[] = { 0.3f, 0.35f, 0.45f, 1.0f};
    
    static float shadowDiffuse[] = {0.2f,0.2f,0.2f,0.1f};
    
    if(flagShadow)
    {
        glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,shadowDiffuse);
    }
    else
    {
        glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
        glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
    }
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glVertex3f(vPosition.x, vPosition.y, vPosition.z);
    glEnd();
}


