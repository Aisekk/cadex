#include "Summator.h"
#include "Circle.h"

using namespace CurvesLibrary;

Summator::Summator(const Curves3D& curves)
    : _curves(curves) {}

Summator::Summator(const Summator& summator, tbb::split spl) :
    _curves(summator._curves),
    _sum(0.0)
{}

void Summator::operator()(const tbb::blocked_range<int>& range)
{
    int begin = range.begin(), end = range.end();
    for (int i = begin; i != end; ++i)
    {
        if (_curves[i]->GetType() == Curve3D::Circle)
        {
            auto circle = std::static_pointer_cast<Circle>(_curves[i]);
            _sum += circle->GetRadius();
        }
    }
}

void Summator::join(const Summator& summator)
{
    _sum += summator._sum;
}

double Summator::Result() const
{
    return _sum;
}