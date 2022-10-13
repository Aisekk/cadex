#include "CurvesLibraryApi.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"

namespace CurvesLibrary
{
    CurvesLibraryApi::CurvesLibraryApi() {}

    Curve3DPtr CurvesLibraryApi::createCircle(double radius)
    {
        auto circle = std::make_shared<Circle>(radius);
        return circle;
    }

    Curve3DPtr CurvesLibraryApi::createEllipse(double semiaxis1, double semiaxis2)
    {
        auto ellipse = std::make_shared<Ellipse>(semiaxis1, semiaxis2);
        return ellipse;
    }

    Curve3DPtr CurvesLibraryApi::createHelix(double radius, double step)
    {
        auto helix = std::make_shared<Helix>(radius, step);
        return helix;
    }
}
