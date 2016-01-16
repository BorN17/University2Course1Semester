#include "objects.h"

Cannon::Cannon() {
	center.setX(0);
	center.setY(0);
	center.setZ(0);
}

Cannon::Cannon(float x, float y, float z) {
	center.setX(x);
	center.setY(y);
	center.setZ(z);
}

//returns center point
Point Cannon::getCenter() {
	return center;
}

void Cannon::setX(float x) {
	center.setX(x);
}

void Cannon::setY(float y) {
	center.setY(y);
}

void Cannon::setZ(float z) {
	center.setZ(z);
}

//Draw trajectory
void Cannon::drawPath() {
	glColor3f(255, 0, 0);

	for (int i = 0; i < pathPoints.size(); i++) {
		glPushMatrix();

		glTranslatef(pathPoints[i].getX(), pathPoints[i].getY() + RADIUS, pathPoints[i].getZ());

		glutSolidSphere(0.1, 64, 64);

		glPopMatrix();
	}

}

//Add point to path
void Cannon::savePositionToPath() {
	pathPoints.push_back(center);
}

void Cannon::draw()
{
	//Draw trajectory
	drawPath();

	glPushMatrix();

	//Translate and rotate cannonball
	glTranslatef(center.getX(), center.getY() + RADIUS, center.getZ());
	glRotatef(90, 1.0f, 0.0f, 0.0f);

	glColor3f(0, 0, 0);
	glutSolidSphere(RADIUS, 64, 64);

	glPopMatrix();
}

//Reset cannonball to start
void Cannon::reset() {
	pathPoints.clear();
	center.setX(0);
	center.setY(0);
	center.setZ(0);
}
