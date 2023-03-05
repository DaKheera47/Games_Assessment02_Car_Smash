
#ifndef HELPERS
#define HELPERS

#include "enums.h";
#include <TL-Engine.h>
using namespace tle;

void calculateFacingVector(IModel* model, SVector3& facingVector);
float calculateDotProduct(IModel* boxObj, IModel* sphereObj);
bool BoxToSphere(float sphereRad, IModel* sphereObj, IModel* boxObj, BoundingBox boxBBox);
// calculate distance between two points, x, y, z, using SVector3
float calculateDistance(SVector3 point1, SVector3 point2);

#endif // HELPERS