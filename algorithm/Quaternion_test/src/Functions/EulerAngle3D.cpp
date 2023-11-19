/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include files
#ifndef CXX_EULERANGLE3D_H
#   include "EulerAngle3D.h"
#endif

/*---------------------------------------------------------------------------*/
// Constructor
EulerAngle3D::EulerAngle3D(double _x, double _y, double _z)
: x(_x)
, y(_y)
, z(_z)
{

}

/*---------------------------------------------------------------------------*/
// Constructor
EulerAngle3D::EulerAngle3D(const EulerAngle3D& v)
: x(v.x)
, y(v.y)
, z(v.z)
{

}

/*---------------------------------------------------------------------------*/
// Destructor
EulerAngle3D::~EulerAngle3D()
{
    // Nothing
}

/*---------------------------------------------------------------------------*/
// Dot multiply (Vl . Vr)
double EulerAngle3D::Dot(const EulerAngle3D& lhs, const EulerAngle3D& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

/*---------------------------------------------------------------------------*/
// Cross multiply (Vl x Vr)
EulerAngle3D EulerAngle3D::Cross(const EulerAngle3D& lhs, const EulerAngle3D& rhs)
{
    return EulerAngle3D(lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x);
}

/*---------------------------------------------------------------------------*/
// Operator + (Vo = V + Vv)
EulerAngle3D EulerAngle3D::operator+(const EulerAngle3D& v)
{
    return EulerAngle3D(x + v.x, y + v.y, z + v.z);
}

/*---------------------------------------------------------------------------*/
EulerAngle3D EulerAngle3D::operator*(double s)
{
    return EulerAngle3D(x * s, y * s, z * s);
}

/*---------------------------------------------------------------------------*/
EulerAngle3D operator*(const EulerAngle3D& v, double s)
{
    return EulerAngle3D(v.x * s, v.y * s, v.z * s);
}

/*---------------------------------------------------------------------------*/
/*EOF*/
