#include "VEC3.h"
#include "Math.h"

VEC3::VEC3(double x, double y, double z)
{
    VEC3::x = x;
    VEC3::y = y;
    VEC3::z = z;
}

VEC3::VEC3()
{
    VEC3::x = 0.0;
    VEC3::y = 0.0;
    VEC3::z = 0.0;
}

VEC3::VEC3(const VEC3& v)
{
    VEC3::x = v.x;
    VEC3::y = v.y;
    VEC3::z = v.z;
}

void VEC3::copia(VEC3 v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

VEC3::~VEC3()
{
    //dtor
}

double VEC3::norma()
{
    double mag;
    mag = sqrt(x*x + y*y + z*z);
    return mag;
}

VEC3 VEC3::unitario()
{
    double mag = this->norma();
    return VEC3(x/mag,y/mag,z/mag);
}

void VEC3::acumula(VEC3 delta)
{
    x += delta.x;
    y += delta.y;
    z += delta.z;
}

ostream& operator <<( ostream& s, VEC3& v )
  {
    s << "[" << v.x << "," << v.y << "," << v.z << "]";
	return s;
  }

VEC3 operator +(VEC3 a, VEC3 b)
{
    return VEC3( a.x + b.x, a.y + b.y, a.z + b.z );
}

VEC3 operator -(VEC3 a, VEC3 b)
{
    return VEC3( a.x - b.x, a.y - b.y, a.z - b.z );
}

VEC3 operator *(VEC3 v, double a)
{
    return VEC3( v.x *a, v.y*a, v.z*a);
}

