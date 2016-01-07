#pragma once
#include <windows.h>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <objidl.h>
#include <gdiplus.h>
#include <iostream>
#include <cmath>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

class PointT
{
private:
	int xValue, yValue; // cordinates
public:
	PointT();
	PointT(int x, int y);
	int x();
	int y();
};

struct LineT
{
public:
	double a, b, c; // aX + bY + c = 0
	LineT(PointT a, PointT b);
};

double signedDistance(PointT p, LineT l);

double distance(PointT a, PointT b);

bool cmp(std::pair<PointT, PointT> a, std::pair<PointT, PointT> b); // returns true if length of a < length of b

bool intersects(std::pair<PointT, PointT> a, std::pair<PointT, PointT> b); // returns true if a intersects b

class SetOfPoint
{
private:
	int pointsNum;
	std::vector<PointT> points;
public:
	SetOfPoint();
	int size();
	void add(PointT newPoint);
	void clear();				
	void fill();				// reading from file
	void draw(HDC hdc);			// drawing points
	void triangulate(HDC hdc);	// choosing lines for triangulation and drawing them
};
