#pragma once
#include "Curve3D.h"

namespace CurvesLibrary
{
    class Ellipse : public Curve3D
    {
    public:
        Ellipse(double semiaxis1 = 0.0, double semiaxis2 = 0.0);

        Point3D GetPoint(double t) const override;
        Vector3D GetFirstDerivative(double t) const override;

        double GetSemiaxis1() const;
        double GetSemiaxis2() const;

    private:
        double _semiaxis1;
        double _semiaxis2;
    };
}

