#pragma once

namespace CurvesLibrary
{
    struct Vector3D
    {
        double dx_dt;
        double dy_dt;
        double dz_dt;

        Vector3D(double dx_dt_ = 0.0, double dy_dt_ = 0.0, double dz_dt_ = 0.0)
            : dx_dt(dx_dt_)
            , dy_dt(dy_dt_)
            , dz_dt(dz_dt_)
        {}
    };
}
