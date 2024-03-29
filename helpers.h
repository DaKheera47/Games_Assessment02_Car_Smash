
#ifndef HELPERS
#define HELPERS

#include "enums.h"
#include "VARS.h"

#include <TL-Engine.h>
using namespace tle;

void calculateFacingVector(IModel* model, SVector3& facingVector);
float calculateDotProduct(IModel* boxObj, IModel* sphereObj);
COLLISION_AXIS BoxToSphere(float sphereRad, IModel* sphereObj, IModel* boxObj, BoundingBox boxBBox);
// calculate distance between two points, x, y, z, using SVector3
float calculateDistance(SVector3 point1, SVector3 point2);
string truncateDecimal(double preciseNum, int precision);
float generateRandomFloat(float rangeMin, float rangeMax);

#endif // HELPERS