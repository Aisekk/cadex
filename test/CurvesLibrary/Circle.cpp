#include "Circle.h"
#include <cmath>

namespace CurvesLibrary
{
    Circle::Circle(double radius)
        : Curve3D(Curve3D::Circle)
        , _radius(std::abs(radius))
    {}

    Point3D Circle::GetPoint(double t) const
    {
        if (_radius < _eps)
            return Point3D();

        double x = _radius * std::cos(t);
        double y = _radius * std::sin(t);

        Point3D point(x, y);
        return point;
    }

    Vector3D Circle::GetFirstDerivative(double t) const
    {
        if (_radius < _eps)
            return Vector3D();

        double dx_dt = -_radius * std::sin(t);
        double dy_dt = _radius * std::cos(t);

        Vector3D deriv(dx_dt, dy_dt);
        return deriv;
    }

    double Circle::GetRadius() const
    {
        return _radius;
    }
}

