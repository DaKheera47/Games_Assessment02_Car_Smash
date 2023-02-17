#include <iostream>
using namespace std;

#include "dev.h";

void PrintBoundingBox(BoundingBox bbox)
{
	// Print the bounding box
	cout << "Bounding box: " << endl;
	cout << "minX: " << bbox.minX << endl;
	cout << "maxX: " << bbox.maxX << endl;
	cout << "minY: " << bbox.minY << endl;
	cout << "maxY: " << bbox.maxY << endl;
	cout << "minZ: " << bbox.minZ << endl;
	cout << "maxZ: " << bbox.maxZ << endl;
	cout << endl;
}

void PrintVector(SVector3 vector)
{
	// Print the vector
	cout << "Vector: " << endl;
	cout << "x: " << vector.x << endl;
	cout << "y: " << vector.y << endl;
	cout << "z: " << vector.z << endl;
	cout << endl;
}