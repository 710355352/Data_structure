#include "mesh.h"
Point::Point() 
{
	this->x = 0;
	this->y = 0;
};

Point::Point(double x_, double y_, std::string name)
{
	this->x = x_;
	this->y = y_;
	this->name = name;
}

void Point::show()
{
	std::cout << this->name << "(" << this->x << "," << this->y << ")";
}

Element::Element() {};
Element::Element(const Element& ele) 
{
	this->points = ele.points;
}
Element::Element(std::vector<Point*> points_, std::string name)
{
	this->points = points_;
	this->name = name;
}
Element::~Element() {}
Mesh::~Mesh() {}
