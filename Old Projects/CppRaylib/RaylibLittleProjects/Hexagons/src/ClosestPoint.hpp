#pragma once
#include <Eigen/Dense>
#include <raylib.h>


//v1 and v2 are vectors, P is target point 
Vector2 GetClosestPoint(Vector2 vector1, Vector2 vector2, Vector2 point);