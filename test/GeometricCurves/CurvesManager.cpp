#include "CurvesManager.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"
#include "Summator.h"
#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <functional>
#include <thread>
#include <numeric>
#include <algorithm>
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"

CurvesManager::CurvesManager() {}

CurvesLibrary::Curves3D CurvesManager::PopulateContainer(int curvesCount) const
{
    CurvesLibrary::Curves3D curves;
    curves.reserve(curvesCount);

    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    int seed = (int)(duration.count() % 100);
    int sign = 1;

    for (int i = 0; i < curvesCount; ++i)
    {
        auto curve = CreateRandomCurve(seed);
        curves.push_back(curve);
        srand(i + seed);
        seed += (i + sign * rand() % 100);
        sign *= -1;
    }
    return curves;
}

void CurvesManager::PrintPointsAndDerivatives(const CurvesLibrary::Curves3D& curves, double t) const
{
    double eps = std::numeric_limits<double>::epsilon();
    auto print = [t](const CurvesLibrary::Curve3DPtr& curve)
    {
        if (curve && curve->GetType() != CurvesLibrary::Curve3D::Invalid)
        {
            auto point = curve->GetPoint(t);
            auto derivs = curve->GetFirstDerivative(t);

            int n = 8;

            std::cout.flags(std::ios::left | std::ios::dec | std::ios::showbase);
            std::cout.setf(std::ios::fixed);
            std::cout.precision(2);

            std::cout << std::setw(n) << "x = " << std::setw(n) << point.x
                << std::setw(n) << ", y = " << std::setw(n) << point.y
                << std::setw(n) << ", z = " << std::setw(n) << point.z
                << std::endl;

            std::cout << std::setw(n) << "x_t = " << std::setw(n) << derivs.dx_dt
                << std::setw(n) << ", y_t = " << std::setw(n) << derivs.dy_dt
                << std::setw(n) << ", z_t = " << std::setw(n) << derivs.dz_dt
                << std::endl;
        }
    };
    std::for_each(curves.cbegin(), curves.cend(), print);
}

CurvesLibrary::Curves3D CurvesManager::PopulateContainerFromOther(const CurvesLibrary::Curves3D& other) const
{
    using namespace CurvesLibrary;
    Curves3D curves;
    std::copy_if(other.cbegin(), other.cend(), std::back_inserter(curves),
        [](const Curves3D::value_type& value)
    {
        return (value->GetType() == Curve3D::Circle);
    }
    );
    return curves;
}

void CurvesManager::SortContainerByCircleRadius(CurvesLibrary::Curves3D& curves) const
{
    using namespace CurvesLibrary;
    double eps = std::numeric_limits<double>::epsilon();
    std::sort(curves.begin(), curves.end(), [eps](const Curves3D::value_type& curve1, const Curves3D::value_type& curve2)
    {
        if (curve1->GetType() == Curve3D::Circle && curve2->GetType() == Curve3D::Circle)
        {
            auto circle1 = std::static_pointer_cast<Circle>(curve1);
            auto circle2 = std::static_pointer_cast<Circle>(curve2);
            return (circle1->GetRadius() - circle2->GetRadius() < eps);
        }
        return false;
    });
}

double CurvesManager::ComputeCurvesRadiiTotalSum(const CurvesLibrary::Curves3D& curves) const
{
    using namespace CurvesLibrary;
    double sum = 0.0;
    std::for_each(curves.cbegin(), curves.cend(), [&sum](const Curves3D::value_type& curve)
    {
        if (curve->GetType() == Curve3D::Circle)
        {
            auto circle = std::static_pointer_cast<Circle>(curve);
            sum += circle->GetRadius();
        }
    }
    );
    return sum;
}

double CurvesManager::ParallelComputeCurvesRadiiTotalSum(const CurvesLibrary::Curves3D& curves) const
{
    size_t hardware_threads = std::thread::hardware_concurrency();
    size_t threads_num = hardware_threads != 0 ? hardware_threads : 2;

    Summator summator(curves);
    auto range = tbb::blocked_range<int>(0, curves.size(), threads_num);
    tbb::parallel_reduce(range, summator);

    return summator.Result();
}

CurvesLibrary::Curve3DPtr CurvesManager::CreateRandomCurve(int seed) const
{
    CurvesLibrary::Curve3DPtr curve;

    std::default_random_engine engine(seed);

    int min = (int)CurvesLibrary::Curve3D::Circle;
    int max = (int)CurvesLibrary::Curve3D::Helix;

    std::uniform_int_distribution uniform(min, max);

    CurvesLibrary::Curve3D::Type type = (CurvesLibrary::Curve3D::Type)uniform(engine);

    switch (type)
    {
    case CurvesLibrary::Curve3D::Invalid:
        break;
    case CurvesLibrary::Curve3D::Circle:
    {
        auto values = GenerateRandomValues(1);
        double radius = values.front();
        curve = _api.createCircle(radius);
        break;
    }
    case CurvesLibrary::Curve3D::Ellipse:
    {
        auto values = GenerateRandomValues(2);
        double semiaxis1 = values.front();
        double semiaxis2 = *(std::next(values.begin(), 1));
        curve = _api.createEllipse(semiaxis1, semiaxis2);
        break;
    }
    case CurvesLibrary::Curve3D::Helix:
    {
        auto values = GenerateRandomValues(2);
        double radius = values.front();
        double step = *(std::next(values.begin(), 1));
        curve = _api.createHelix(radius, step);
        break;
    }
    default: break;
    }

    return curve;
}

std::vector<double> CurvesManager::GenerateRandomValues(int paramCount) const
{
    std::vector<double> values;
    values.reserve(paramCount);

    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();

    std::default_random_engine engine;

    double min = 0.1;
    double max = 999.1;
    std::uniform_real_distribution<double> uniform(min, max);

    for (int i = 0; i < paramCount; ++i)
    {
        double seed = (double)(duration.count() + i * 100);
        engine.seed(seed);
        double rand = uniform(engine);
        values.push_back(rand);
    }

    return values;
}

void CurvesManager::Output(const CurvesLibrary::Curves3D& curves)
{
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);

    for (const auto& curve : curves)
    {
        auto type = curve->GetType();
        switch (type)
        {
        case CurvesLibrary::Curve3D::Invalid:
            break;
        case CurvesLibrary::Curve3D::Circle:
        {
            auto circle = std::static_pointer_cast<CurvesLibrary::Circle>(curve);
            std::cout << "Circle: R = " << circle->GetRadius() << std::endl;
            break;
        }
        case CurvesLibrary::Curve3D::Ellipse:
        {
            auto ellipse = std::static_pointer_cast<CurvesLibrary::Ellipse>(curve);
            std::cout << "Ellipse: a = " << ellipse->GetSemiaxis1() << "; b = " << ellipse->GetSemiaxis2() << std::endl;
            break;
        }
        case CurvesLibrary::Curve3D::Helix:
        {
            auto helix = std::static_pointer_cast<CurvesLibrary::Helix>(curve);
            std::cout << "Helix: R = " << helix->GetRadius() << "; step = " << helix->GetStep() << std::endl;
            break;
        }
        default: break;
        }
    }
}
