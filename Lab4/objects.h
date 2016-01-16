#pragma once
#include <windows.h>
#include <GL/glut.h> 
#include "geometry.h"
#include <vector>  

class Cannon {

	Point center;	//Center of Cannon

	std::vector<Point> pathPoints;	//Trajectory points

public:

	const float RADIUS = 2;
	const float START_SPEED = 1.0f;
	const float START_ANGLE = 45.0f;

	Cannon();

	Cannon(float x, float y, float z);

	//returns center point
	Point getCenter();

	//sets x coordinate
	void setX(float x);

	//sets y coordinate
	void setY(float y);

	//sets z coordinate
	void setZ(float z);

	//Draws trajectory
	void drawPath();

	//Add point to trajectory
	void savePositionToPath();

	//Draw Cannon
	void draw();

	//Reset ball coordinates
	void reset();
};
