#include "Ellipse.h"
#include <cmath>

namespace CurvesLibrary
{
    Ellipse::Ellipse(double semiaxis1, double semiaxis2)
        : Curve3D(Curve3D::Ellipse)
        , _semiaxis1(std::abs(semiaxis1))
        , _semiaxis2(std::abs(semiaxis2))
    {}

    Point3D Ellipse::GetPoint(double t) const
    {
        if (_semiaxis1 < _eps || _semiaxis2 < _eps)
            return Point3D();

        double x = _semiaxis1 * std::cos(t);
        double y = _semiaxis2 * std::sin(t);

        Point3D point(x, y);
        return point;
    }

    Vector3D Ellipse::GetFirstDerivative(double t) const
    {
        if (_semiaxis1 < _eps || _semiaxis2 < _eps)
            return Vector3D();

        double dx_dt = -_semiaxis1 * std::sin(t);
        double dy_dt = _semiaxis2 * std::cos(t);

        Vector3D deriv(dx_dt, dy_dt);
        return deriv;
    }

    double Ellipse::GetSemiaxis1() const
    {
        return _semiaxis1;
    }

    double Ellipse::GetSemiaxis2() const
    {
        return _semiaxis2;
    }
}

