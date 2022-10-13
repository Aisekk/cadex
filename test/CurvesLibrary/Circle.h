#pragma once
#include "Curve3D.h"

namespace CurvesLibrary
{
    class Circle : public Curve3D
    {
    public:
        Circle(double radius = 0.0);

        Point3D GetPoint(double t) const override;
        Vector3D GetFirstDerivative(double t) const override;

        double GetRadius() const;

    private:
        double _radius;
    };
}

