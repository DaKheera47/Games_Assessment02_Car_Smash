#include <math.h>
#include <utility>
#include <iostream>
using namespace std;

#include <TL-Engine.h>
using namespace tle;
#include "helpers.h";
#include "dev.h";

void calculateFacingVector(IModel* model, SVector3& facingVector)
{
	SVector3 initialPos = { model->GetX(), model->GetY(), model->GetZ() };
	model->MoveLocalZ(1.0f);
	SVector3 finalPos = { model->GetX(), model->GetY(), model->GetZ() };
	facingVector = { finalPos.x - initialPos.x, finalPos.y - initialPos.y, finalPos.z - initialPos.z };
	model->MoveLocalZ(-1.0f);
}

float calculateDotProduct(IModel* boxObj, IModel* sphereObj)
{
	const float sphereObjX = sphereObj->GetX();
	const float sphereObjY = sphereObj->GetY();
	const float sphereObjZ = sphereObj->GetZ();

	const float boxObjX = boxObj->GetX();
	const float boxObjY = boxObj->GetY();
	const float boxObjZ = boxObj->GetZ();

	SVector3 vObjToSphere;
	vObjToSphere.x = sphereObjX - boxObjX;
	vObjToSphere.y = sphereObjY - boxObjY;
	vObjToSphere.z = sphereObjZ - boxObjZ;

	SVector3 vObjFacing;
	calculateFacingVector(boxObj, vObjFacing);

	SVector3 vSphereFacing;
	calculateFacingVector(sphereObj, vSphereFacing);

	float dotProduct = vSphereFacing.x * vObjFacing.x + vSphereFacing.y * vObjFacing.y + vSphereFacing.z * vObjFacing.z;
	return dotProduct;
}

bool BoxToPoint(BoundingBox box, SVector3 point)
{
	if (point.x > box.minX && point.x < box.maxX)
	{
		if (point.z > box.minZ && point.z < box.maxZ)
		{
			return true;
		}
	}
	return false;
}

// sphere to box
bool BoxToSphere(float sphereRad, IModel* sphereObj, IModel* boxObj, BoundingBox boxBBox)
{
	SVector3 spherePos = { sphereObj->GetX(), sphereObj->GetY(), sphereObj->GetZ() };
	SVector3 boxPos = { boxObj->GetX(), boxObj->GetY(), boxObj->GetZ() };

	// bounding box edge lengths
	SVector3 boxLengths{};
	boxLengths.x = boxBBox.maxX - boxBBox.minX;
	boxLengths.y = boxBBox.maxY - boxBBox.minY;
	boxLengths.z = boxBBox.maxZ - boxBBox.minZ;

	BoundingBox objSimulatedBBox{
		boxPos.x - boxLengths.x / 2 - sphereRad,
		boxPos.x + boxLengths.x / 2 + sphereRad,
		boxPos.y - boxLengths.y / 2 - sphereRad,
		boxPos.y + boxLengths.y / 2 + sphereRad,
		boxPos.z - boxLengths.z / 2 - sphereRad,
		boxPos.z + boxLengths.z / 2 + sphereRad
	};

	return BoxToPoint(objSimulatedBBox, spherePos);
}

float calculateDistance(SVector3 point1, SVector3 point2)
{
	// calculate distance between two points, x, y, z, using SVector3
	const float xDiff = point1.x - point2.x;
	const float yDiff = point1.y - point2.y;
	const float zDiff = point1.z - point2.z;

	return sqrt(xDiff * xDiff + yDiff * yDiff + zDiff * zDiff);
}