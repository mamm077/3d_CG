#include <math.h>


double PI = 3.4142135;

class CVector{

public:

    float x, y, z;

    CVector();
    CVector(float x0, float y0, float z0);

    void operator+=(CVector a);
    void operator-=(CVector a);
    void operator*=(float s);
    void operator/=(float s);
    friend CVector operator*(CVector a, float s);
    friend CVector operator*(float s, CVector a);
    friend CVector operator/(CVector a, float s);
    friend CVector operator+(CVector a, CVector b);
    friend CVector operator-(CVector a, CVector b);
    friend float operator*(CVector a, CVector b);
    friend CVector operator^(CVector a, CVector b);
    friend CVector operator>>(CVector a, CVector b);

    float magnitude();  
    void normalize(void);
    void reverse(void);
    CVector normalize2();
    CVector rotate(CVector v, CVector elr);
    void rotX(float angle); 
    void rotY(float angle); 
    void rotZ(float angle); 
    float dist(CVector a, CVector b);
    float getAngle(CVector a, CVector b);
    CVector getEulerX(CVector a, CVector b);
    CVector getEulerZ(CVector a, CVector b);
};
//----------------------------------------------------------------------------

CVector::CVector()
{
    x = y = z = 0.0;
}
//----------------------------------------------------------------------------

CVector::CVector(float x0, float y0, float z0)
{
    x = x0;
    y = y0;
    z = z0;
}
//------------------------------------------------------------------------------

void CVector::operator+=(CVector a)
{
    x += a.x;
    y += a.y;
    z += a.z;
}
//------------------------------------------------------------------------------
void CVector::operator-=(CVector a)
{
    x -= a.x;
    y -= a.y;
    z -= a.z;
}
//------------------------------------------------------------------------------
void CVector::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
}
//------------------------------------------------------------------------------
void CVector::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;
}
//------------------------------------------------------------------------------
CVector operator+(CVector a, CVector b)
{
    return CVector(a.x+b.x, a.y+b.y, a.z+b.z);
}
//------------------------------------------------------------------------------
CVector operator-(CVector a, CVector b)
{
    return CVector(a.x - b.x, a.y - b.y, a.z - b.z);
}
//------------------------------------------------------------------------------

CVector operator*(CVector a, float s)
{
    return CVector(a.x * s, a.y * s, a.z * s);
}
//------------------------------------------------------------------------------

CVector operator*(float s, CVector a)
{
    return CVector(a.x * s, a.y * s, a.z * s);
}
//------------------------------------------------------------------------------

CVector operator/(CVector a, float s)
{
    //if(s == 0.0)
      //  printf("\n");

    return CVector(a.x / s, a.y / s, a.z / s);
}

//------------------------------------------------------------------------------

float operator*(CVector a, CVector b)
{
    return( a.x*b.x + a.y*b.y + a.z*b.z );
}
//------------------------------------------------------------------------------

CVector operator^(CVector a, CVector b)
{
    float x = a.y * b.z - a.z * b.y;
    float y = a.z * b.x - a.x * b.z;
    float z = a.x * b.y - a.y * b.x;
    return( CVector(x, y, z) );
}
//------------------------------------------------------------------------------

CVector operator>>(CVector a, CVector b)
{
    CVector c = b - a;
    c.normalize();
    return c ;
}

//-----------------------------------------------------------------------------
float CVector::magnitude()
{
    return( sqrt(x * x + y * y + z * z) );
}
//-----------------------------------------------------------------------------
void CVector::normalize()
{
    double eps = 0.000001;
    double mag = sqrt(x * x + y * y + z * z) ;
    if(mag <= eps) mag = 1.0;
    x /= mag;
    y /= mag;
    z /= mag;
    if(fabs(x) < eps) x = 0.0;
    if(fabs(y) < eps) y = 0.0;
    if(fabs(z) < eps) z = 0.0;
}
//-----------------------------------------------------------------------------
CVector CVector::normalize2()
{
    double eps = 0.000001;
    double xx, yy, zz;
    double mag = sqrt(x * x + y * y + z * z) ;
    if(mag < eps) mag = 1.0;
    xx = x / mag;
    yy = y / mag;
    zz = z / mag;
    if(fabs(x) < eps) xx = 0.0;
    if(fabs(y) < eps) yy = 0.0;
    if(fabs(z) < eps) zz = 0.0;
    return(CVector(xx, yy, zz));
}

//-----------------------------------------------------------------------------
void CVector::reverse()
{
    x = -x;
    y = -y;
    z = -z;
}

//------------------------------------------------------------------------------------
void CVector::rotX(float angle)
{
	float xx, yy, zz;
	double pp = PI / 180.0;

	xx = x; yy = y; zz = z;
	x = xx;
	y = yy * cos(pp * angle) - zz * sin(pp * angle);
	z = yy * sin(pp * angle) + zz * cos(pp * angle);
}
//------------------------------------------------------------------------------------
void CVector::rotY(float angle)
{
	float xx, yy, zz;
	double pp = PI / 180.0;

	xx = x; yy = y; zz = z;
	x = xx * cos(pp * angle) + zz * sin(pp * angle);
	y = yy;
	z = - xx * sin(pp * angle) + zz * cos(pp * angle);
}
//------------------------------------------------------------------------------------
void CVector::rotZ(float angle)
{
	float xx, yy, zz;
	double pp = PI / 180.0;

	xx = x; yy = y; zz = z;
	x = xx * cos(pp * angle) - yy * sin(pp * angle);
	y = xx * sin(pp * angle) + yy * cos(pp * angle);
	z = zz;
}
//-----------------------------------------------------------------------------
CVector rotate(CVector v, CVector elr)
{
    v.rotX(elr.x);
    v.rotY(elr.y);
    v.rotZ(elr.z);
    return v;
}

CVector rotate(CVector v, double angle[3])
{
    v.rotX(angle[0]);
    v.rotY(angle[1]);
    v.rotZ(angle[2]);
    return v;
}

//------------------------------------------------------------------------------
//ƒxƒNƒgƒ‹ŠÔ‹——£
float dist(CVector a, CVector b)
{
    CVector c = b - a;
    return( c.magnitude() );
}

//-----------------------------------------------------------------------------
float getAngle(CVector a, CVector b)
{
    float ang = (a.x*b.x+a.y*b.y+a.z*b.z)/(a.magnitude()*b.magnitude());
    if(ang >= 1.0) ang = 0.0;
    else if (ang <= -1.0) ang = PI;
    else ang = acos(ang);
    return ang;
}
//-----------------------------------------------------------------------------
CVector getEulerX(CVector a, CVector b)
{
    float cx, cy, cz, len;
    CVector e;
    cx = b.x - a.x;
    cy = b.y - a.y;
    cz = b.z - a.z;
    len = dist(a, b);
    e.x = 0.0;
    if(cz >= len) e.y = -90.0;
    else if(cz <= -len) e.y = 90.0;
    else e.y = - asin(cz / len) * 180.0 / PI;
    if(fabs(cx) <= 0.0001 && fabs(cy) <= 0.0001) e.z = 0.0;
    else e.z = atan2(cy, cx) * 180.0 / PI;
    return e;
}
//------------------------------------------------------------------------------
CVector getEulerZ(CVector a, CVector b)
{
    float cx, cy, cz, len;
    CVector e;
    cx = b.x - a.x;
    cy = b.y - a.y;
    cz = b.z - a.z;
    len = dist(a, b);
    e.x = 0.0;
    if(cz >= len) e.y = 0.0;
    else if(cz <= -len) e.y = 180.0;
    else e.y = acos(cz / len) * 180.0 / PI;
    if(fabs(cx) <= 0.0001 && fabs(cy) <= 0.0001) e.z = 0.0;
    else e.z = atan2(cy, cx) * 180.0 / PI ;
    return e;
}


//------------------------------------------------------------------------------
class CMatrix{

public:

    float e11, e12, e13, e21, e22, e23, e31, e32, e33;

    CMatrix();
    CMatrix(float a11, float a12, float a13,
            float a21, float a22, float a23,
            float a31, float a32, float a33);

    friend CVector operator*(CMatrix m, CVector v);
    friend CVector operator*(CVector v, CMatrix m);

    float det();
    };
//----------------------------------------------------------------------------

CMatrix::CMatrix()
{
    e11 = e12 = e13 = 0.0;
    e21 = e22 = e23 = 0.0;
    e31 = e32 = e33 = 0.0;
}
//-----------------------------------------------------------------------------

CMatrix::CMatrix(float a11, float a12, float a13,
                 float a21, float a22, float a23,
                 float a31, float a32, float a33)
{
    e11 = a11; e12 = a12; e13 = a13;
    e21 = a21; e22 = a22; e23 = a23;
    e31 = a31; e32 = a32; e33 = a33;
}
//----------------------------------------------------------------------------

float CMatrix::det()
{
    return( e11*e22*e33 + e12*e23*e31 + e13*e32*e21
          - e11*e32*e23 - e12*e21*e33 - e31*e22*e13 );
}
//----------------------------------------------------------------------------

CVector operator*(CMatrix m, CVector v)
{
    return CVector(
        m.e11*v.x + m.e12*v.y + m.e13*v.z,    
        m.e21*v.x + m.e22*v.y + m.e23*v.z,    
        m.e31*v.x + m.e32*v.y + m.e33*v.z );  
}
//----------------------------------------------------------------------------

CVector operator*(CVector v, CMatrix m)
{
    return CVector(
        v.x*m.e11 + v.y*m.e21 + v.z*m.e31,
        v.x*m.e12 + v.y*m.e22 + v.z*m.e32,
        v.x*m.e13 + v.y*m.e23 + v.z*m.e33 );
}



