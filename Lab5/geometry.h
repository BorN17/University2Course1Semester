#pragma once
#include <cmath>
#include <iostream>

class Point{
private:
    double x, y;
public:
    Point(double X, double Y){
        x = X; 
        y = Y;
    }
    Point(){
        x = y = 0.0;
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
};

double distance(Point A, Point B){
    double dX = A.getX() - B.getX();
    double dY = A.getY() - B.getY();
    return sqrt(dX * dX + dY * dY);
};

class Line{
private:
    Point begin, end;
public:
    Line(Point a, Point b){
        begin = a;
        end = b;
    }
    double length(){
        return distance(begin, end);
    }
    Point getBegin(){
        return begin;
    }
    Point getEnd(){
        return end;
    }
};

class Parallelogram{
private:
    Point vertex[4];
public:
    Parallelogram(Point p1, Point p2, Point p3){
        vertex[0] = p1;
        vertex[1] = p2;
        vertex[2] = p3;
        Point vectorP3P2(p3.getX() - p2.getX(), p3.getY() - p2.getY());
        Point p4(p1.getX() + vectorP3P2.getX(), p1.getY() + vectorP3P2.getY());
        vertex[3] = p4;
    }
    std::pair<Line, Line> getSides(){
        return std::make_pair(Line(vertex[0], vertex[1]), Line(vertex[1], vertex[2]));
    }
    double getPerimeter(){
        Line side1(vertex[0], vertex[1]);
        Line side2(vertex[1], vertex[2]);
        return 2 * (side1.length() + side2.length());
    }
    double getArea(){
        Point vector1(vertex[1].getX() - vertex[0].getX(), vertex[1].getY() - vertex[0].getY());
        Point vector2(vertex[2].getX() - vertex[1].getX(), vertex[2].getY() - vertex[1].getY());
        return fabs(vector1.getX() * vector2.getY() - vector1.getY() * vector2.getX());
    }
};
