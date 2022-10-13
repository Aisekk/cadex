#pragma once
#include "Curve3D.h"
#include <limits>

namespace CurvesLibrary
{
    Curve3D::Curve3D(Type type)
        : _type(type)
        , _eps(std::numeric_limits<double>::epsilon())
    {}

    Curve3D::~Curve3D() = default;

    Curve3D::Type Curve3D::GetType() const { return _type; }
}


