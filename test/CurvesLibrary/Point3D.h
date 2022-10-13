#pragma once

namespace CurvesLibrary
{
    struct Point3D
    {
        double x;
        double y;
        double z;

        Point3D(double x_ = 0.0, double y_ = 0.0, double z_ = 0.0)
            : x(x_), y(y_), z(z_) {}
    };
}

