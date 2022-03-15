/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include files
#ifndef CXX_VECTOR3D_H
#   include "Vector3D.h"
#endif

/*---------------------------------------------------------------------------*/
// Constructor
Vector3D::Vector3D(double _x, double _y, double _z)
: x(_x)
, y(_y)
, z(_z)
{

}

/*---------------------------------------------------------------------------*/
// Constructor
Vector3D::Vector3D(const Vector3D& v)
: x(v.x)
, y(v.y)
, z(v.z)
{

}

/*---------------------------------------------------------------------------*/
// Destructor
Vector3D::~Vector3D()
{
    // Nothing
}

/*---------------------------------------------------------------------------*/
// Dot multiply (Vl . Vr)
double Vector3D::Dot(const Vector3D& lhs, const Vector3D& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

/*---------------------------------------------------------------------------*/
// Cross multiply (Vl x Vr)
Vector3D Vector3D::Cross(const Vector3D& lhs, const Vector3D& rhs)
{
    return Vector3D(lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x);
}

/*---------------------------------------------------------------------------*/
// Operator + (Vo = V + Vv)
Vector3D Vector3D::operator+(const Vector3D& v)
{
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

/*---------------------------------------------------------------------------*/
Vector3D Vector3D::operator*(double s)
{
    return Vector3D(x * s, y * s, z * s);
}

/*---------------------------------------------------------------------------*/
Vector3D operator*(const Vector3D& v, double s)
{
    return Vector3D(v.x * s, v.y * s, v.z * s);
}

/*---------------------------------------------------------------------------*/
/*EOF*/
