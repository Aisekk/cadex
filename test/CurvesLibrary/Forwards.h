#pragma once
#include <memory>
#include <vector>

namespace CurvesLibrary
{
    class Curve3D;
    using Curve3DPtr = std::shared_ptr<Curve3D>;
    using Curves3D = std::vector<Curve3DPtr>;

    class Circle;
    using CirclePtr = std::shared_ptr<Circle>;

    class Ellipse;
    using EllipsePtr = std::shared_ptr<Ellipse>;

    class Helix;
    using HelixPtr = std::shared_ptr<Helix>;
}



