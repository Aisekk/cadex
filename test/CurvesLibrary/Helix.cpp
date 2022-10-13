#include "Helix.h"
#include <cmath>

namespace CurvesLibrary
{
    Helix::Helix(double radius, double step)
        : Curve3D(Curve3D::Helix)
        , _radius(std::abs(radius))
        , _step(step)
    {}

    Point3D Helix::GetPoint(double t) const
    {
        if (_radius < _eps || _step < _eps)
            return Point3D();

        double x = _radius * std::cos(t);
        double y = _radius * std::sin(t);
        double z = _step * t;

        Point3D point(x, y, z);
        return point;
    }

    Vector3D Helix::GetFirstDerivative(double t) const
    {
        if (_radius < _eps || _step < _eps)
            return Vector3D();

        double dx_dt = -_radius * std::sin(t);
        double dy_dt = _radius * std::cos(t);

        Vector3D deriv(dx_dt, dy_dt, _step);
        return deriv;
    }

    double Helix::GetRadius() const
    {
        return _radius;
    }

    double Helix::GetStep() const
    {
        return _step;
    }
}

