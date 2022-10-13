#pragma once
#include "CurvesLibraryApi.h"

class CurvesManager
{
public:
    CurvesManager();

    CurvesLibrary::Curves3D PopulateContainer(int curvesCount) const;

    void PrintPointsAndDerivatives(const CurvesLibrary::Curves3D& curves, double t) const;

    CurvesLibrary::Curves3D PopulateContainerFromOther(const CurvesLibrary::Curves3D& other) const;

    void SortContainerByCircleRadius(CurvesLibrary::Curves3D& curves) const;

    double ComputeCurvesRadiiTotalSum(const CurvesLibrary::Curves3D& curves) const;

    double ParallelComputeCurvesRadiiTotalSum(const CurvesLibrary::Curves3D& curves) const;

    static void Output(const CurvesLibrary::Curves3D& curves);

private:

    CurvesLibrary::Curve3DPtr CreateRandomCurve(int seed) const;

    std::vector<double> GenerateRandomValues(int paramCount) const;

    CurvesLibrary::CurvesLibraryApi _api;
};
