#pragma once
#include <iostream>
#include "CurvesManager.h"

constexpr double PI = 3.14;

int main()
{
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);

    CurvesManager manager;

    auto firstContainer = manager.PopulateContainer(15);
    //CurvesManager::Output(firstContainer);

    manager.PrintPointsAndDerivatives(firstContainer, PI/4);

    std::cout << "\n";
    auto secondContainer = manager.PopulateContainerFromOther(firstContainer);
    //CurvesManager::Output(secondContainer);

    std::cout << "\n";
    manager.SortContainerByCircleRadius(secondContainer);
    //CurvesManager::Output(secondContainer);

    std::cout << "\n";
    double sum = manager.ComputeCurvesRadiiTotalSum(secondContainer);
    std::cout << "sum = " << sum << "\n\n";

    double parallel_sum = manager.ParallelComputeCurvesRadiiTotalSum(secondContainer);
    std::cout << "tbb parallel_sum = " << parallel_sum << std::endl;

    return 0;
}
