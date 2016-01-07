#pragma once
#include <windows.h>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <objidl.h>
#include <gdiplus.h>
#include <iostream>
#include <cmath>
#include "poligons.h"
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

PointT::PointT()
{
	xValue = yValue = 0;
}
PointT::PointT(int x, int y){
	xValue = x;
	yValue = y;
}
int PointT::x(){
	return xValue;
}
int PointT::y(){
	return yValue;
}

LineT::LineT(PointT frst, PointT scnd)
{
	a = (frst.y() - scnd.y());
	b = (scnd.x() - frst.x());
	c = -frst.x()*(frst.y() - scnd.y()) + frst.y() * (frst.x() - scnd.x());
}

double distance(PointT a, PointT b)
{
	double dx = a.x() - b.x();
	double dy = a.y() - b.y();
	return sqrtf(dx * dx + dy * dy);
}

bool cmp(std::pair<PointT, PointT> a, std::pair<PointT, PointT> b) // returns true is length of a < length of b
{
	return distance(a.first, a.second) < distance(b.first, b.second);
}

double signedDistance(PointT p, LineT l)
{
	return l.a * p.x() + l.b * p.y() + l.c;
}

bool intersects(std::pair<PointT, PointT> a, std::pair<PointT, PointT> b) // returns true if a intersects b
{
	const double EPS = 0.00000000001;
	LineT line1(a.first, a.second);
	LineT line2(b.first, b.second);
	double V1 = signedDistance(a.first, line2) * signedDistance(a.second, line2);
	double V2 = signedDistance(b.first, line1) * signedDistance(b.second, line1);
	if (V1 < -EPS && V2 < -EPS)
		return true; else
		return false;
}

SetOfPoint::SetOfPoint(){
	pointsNum = 0;
	points.clear();
}
int SetOfPoint::size(){
	return pointsNum;
}
void SetOfPoint::add(PointT newPoint){
	pointsNum++;
	points.push_back(newPoint);
}
void SetOfPoint::clear()
{
	pointsNum = 0;
	points.clear();
}
void SetOfPoint::fill()
{
	FILE *stream;
	freopen_s(&stream, "input.txt", "r", stdin);
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		std::cin >> x >> y;
		add(PointT(x, y));
	}
}
void SetOfPoint::draw(HDC hdc){
	Graphics graphics(hdc);
	Pen      pen(Color(255, 0, 0, 255));
	const int DIAM = 5;
	for (int i = 0; i < points.size(); i++)
	{
		graphics.DrawEllipse(&pen, Rect(points[i].x() - DIAM / 2, points[i].y() - DIAM / 2, DIAM, DIAM));
		//graphics.DrawEllipse(&pen, )
	}
}
void SetOfPoint::triangulate(HDC hdc){
	Graphics graphics(hdc);
	Pen      pen(Color(255, 0, 0, 255));
	// completing list of segments
	std::vector<std::pair<PointT, PointT> > lines;
	for (int i = 0; i < pointsNum; i++)
		for (int j = i + 1; j < pointsNum; j++)
		{
			std::pair<PointT, PointT> newPair = std::make_pair(points[i], points[j]);
			lines.push_back(newPair);
		}
		
	std::sort(lines.begin(), lines.end(), cmp);

	std::vector<std::pair<PointT, PointT>> choosed; // lines if triangulation
	for (int i = 0; i < lines.size(); i++)
	{
		bool inter = false;
		for (int j = 0; j < choosed.size(); j++)
			if (intersects(lines[i], choosed[j]))
				inter = true;
		if (!inter)
			choosed.push_back(lines[i]), 
			graphics.DrawLine(&pen, lines[i].first.x(), lines[i].first.y(), lines[i].second.x(), lines[i].second.y());
	}
}
