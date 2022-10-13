#pragma once

#include "Curve3D.h"

namespace CurvesLibrary
{
    class Helix : public Curve3D
    {
    public:
        Helix(double radius = 0.0, double step = 0.0);

        Point3D GetPoint(double t) const override;
        Vector3D GetFirstDerivative(double t) const override;

        double GetRadius() const;
        double GetStep() const;

    private:
        double _radius;
        double _step;
    };
}

