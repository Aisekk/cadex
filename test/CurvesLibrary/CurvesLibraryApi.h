#pragma once
#include "Forwards.h"

namespace CurvesLibrary
{
    class CurvesLibraryApi
    {
    public:
        CurvesLibraryApi();

        static Curve3DPtr createCircle(double radius = 0.0);
        static Curve3DPtr createEllipse(double semiaxis1 = 0.0, double semiaxis2 = 0.0);
        static Curve3DPtr createHelix(double radius = 0.0, double step = 0.0);
    };
}
