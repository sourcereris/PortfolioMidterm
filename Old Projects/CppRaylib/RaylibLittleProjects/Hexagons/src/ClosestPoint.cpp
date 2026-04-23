#include "ClosestPoint.hpp"
#include <iostream>

Vector2 GetClosestPoint(Vector2 vector1, Vector2 vector2, Vector2 point)
{
    // Define the two vectors
    Eigen::Vector2d v1(vector1.x, vector1.y);
    Eigen::Vector2d v2(vector2.x, vector2.y);

    // Define the target point
    Eigen::Vector2d p(point.x, point.y);

    // Construct the matrix V
    Eigen::Matrix2d V;
    V << v1, v2;

    // Solve for c using least squares
    Eigen::Vector2d c = (V.transpose() * V).inverse() * V.transpose() * p;
    std::cout << "Coefficients: a = " << c(0) << ", b = " << c(1) << std::endl;
    c(0) = round(c(0));
    c(1) = round(c(1));
    
    // Closest point
    Eigen::Vector2d closestPoint = c(0) * v1 + c(1) * v2;

    std::cout << "Coefficients: a = " << c(0) << ", b = " << c(1) << std::endl;
    std::cout << "Closest Point: (" << closestPoint(0) << ", " << closestPoint(1) << ")" << std::endl;

    // Results
    return {(float)closestPoint(0), (float)closestPoint(1)};




}