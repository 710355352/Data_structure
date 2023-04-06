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
	// ����������ԭ��������element�������ֱ�ӷ���color_points���������ʡ��������������һ��map��
	// ʹ��ԭ��Element���µ�points��Color_mesh�µ�color_pointsһһ��Ӧ
	// ��������ķ����ṹ��Ƚϸ��� �������� ���ﻹ�Ƿѵ��´�����һ��Color_element��������Color_ϵ�е�����
	// ����������Color_ϵ�������ԭ�������Meshָ��ĺ������ر��ǻ��޸����Եĺ������������Բ�һ�µ�����
{
public:
	std::vector<Color_point*> color_points;
	std::vector<Color_element*> color_neighbors;
	Color_element();
	Color_element(std::vector<Point*> points, std::string name);
	Color_element(const Element& element, std::vector<Color_point*> color_points, std::vector<Point*> points);
	void Update();
};

class Color_mesh : public Mesh // �̳к�main.cpp �е� find_neighbors��Mesh& mesh�����Լ�������Color_mesh�µĶ���
{
public:
	std::vector<Color_point*> color_points;
	std::vector<Color_element*> color_elements;
	Color_mesh();
	Color_mesh(const Mesh& mesh);
	void Update(bool is_points_to_colorpoints=0);
};


