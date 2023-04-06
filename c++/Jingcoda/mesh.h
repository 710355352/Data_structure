#pragma once
// mesh.h
#include <vector>
#include<iostream>
#include<string>
class Point {
public:
	double x, y;
	std::string name;
	Point();
	Point(double x_, double y_, std::string name = "");
	void virtual show();
};

class Element {
public:
	std::vector<Point*> points;
	std::vector<Element*> neighbors;
	std::string name;
	Element();
	Element(const Element& ele);
	Element(std::vector<Point*> points_,std::string name);
	virtual ~Element();
	
};
class Mesh {
public:
	std::vector<Point*> points;
	std::vector<Element*> elements;
	virtual ~Mesh();
};