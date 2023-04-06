#pragma once
#include "mesh.h"

class Color_point: public Point
{
public:
	std::string color;
	Color_point();
	Color_point(double a, double b, std::string c);
	Color_point(const Point & point);
	virtual void show();
	
};

class Color_element :public Element 
	// 制作这个类的原因是想在element层面可以直接访问color_points，这里如果省掉这个类可以制作一个map，
	// 使得原来Element类下的points和Color_mesh下的color_points一一对应
	// 不过上面的方法结构会比较复杂 不够清晰 这里还是费点事从新做一个Color_element类来访问Color_系列的属性
	// 但是这样对Color_系列类调用原来的针对Mesh指针的函数（特别是会修改属性的函数）会有属性不一致的问题
{
public:
	std::vector<Color_point*> color_points;
	std::vector<Color_element*> color_neighbors;
	Color_element();
	Color_element(std::vector<Point*> points, std::string name);
	Color_element(const Element& element, std::vector<Color_point*> color_points, std::vector<Point*> points);
	void Update();
};

class Color_mesh : public Mesh // 继承后，main.cpp 中的 find_neighbors（Mesh& mesh）可以继续调用Color_mesh下的对象
{
public:
	std::vector<Color_point*> color_points;
	std::vector<Color_element*> color_elements;
	Color_mesh();
	Color_mesh(const Mesh& mesh);
	void Update(bool is_points_to_colorpoints=0);
};


