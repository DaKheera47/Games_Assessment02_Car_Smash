
#ifndef HELPERS
#define HELPERS

#include "enums.h";
#include <TL-Engine.h>
using namespace tle;

void calculateFacingVector(IModel* model, SVector3& facingVector);
float calculateDotProduct(IModel* boxObj, IModel* sphereObj);
bool BoxToSphere(float sphereRad, IModel* sphereObj, IModel* boxObj, BoundingBox boxBBox);

#endif // HELPERS