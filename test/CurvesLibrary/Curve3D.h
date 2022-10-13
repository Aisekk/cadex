#pragma once
#include "Point3D.h"
#include "Vector3D.h"

namespace CurvesLibrary
{
    class Curve3D
    {
    public:
        enum Type
        {
            Invalid,
            Circle,
            Ellipse,
            Helix
        };

        Curve3D(Type type = Invalid);
        virtual ~Curve3D();

        Type GetType() const;

        virtual Point3D GetPoint(double t) const = 0;
        virtual Vector3D GetFirstDerivative(double t) const = 0;

    protected:
        Type _type;
        const double _eps;
    };
}


