#pragma once
#include "Forwards.h"
#include "tbb/blocked_range.h"

class Summator
{
public:
    explicit Summator(const CurvesLibrary::Curves3D& curves);
    Summator(const Summator& summator, tbb::split spl);
    void operator()(const tbb::blocked_range<int>& range);
    void join(const Summator& summator);
    double Result() const;
private:
    const CurvesLibrary::Curves3D& _curves;
    double _sum;
};


