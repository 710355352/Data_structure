#include "color_mesh.h"

// Color_ϵ�е��������Ŀ�����������������û�õ����Ͳ�д��
// ����Ҳûд,��Ҫû�漰�������Ķ�̬,����ֱ����mesh����дѭ��һֱdelete�ͺ���

// ����ʵ��һ��Update����
// ����Color���������ֵ��֮Ϊcolor_ϵ�����ԣ�
// ����ͬ�����ุ���Ժ�color_�����Ե�ֵ
Color_point::Color_point() {}// �޲ι���
Color_point::Color_point(double a, double b, std::string c = "g") // �вι���
{
	this->x = a;
	this->y = b;
	this->color = c;
}
Color_point::Color_point(const Point& point) // ��Ը���Ŀ�������
{
	this->x = point.x;
	this->y = point.y;
	this->color = "";
	this->name = point.name;
}

void Color_point::show()
{
	std::cout << this->name << "(" << this->x << "," << this->y << "," << this->color << ")";
}

Color_element::Color_element() // �޲ι���,���治�����ݣ����ռ�ÿռ�
{

}
Color_element::Color_element(std::vector<Point*> points, std::string name)
{
	this->points = points;
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		this->color_points.push_back((Color_point*)points[i]);
	}
	this->name = name;
}

Color_element::Color_element(const Element& element, std::vector<Color_point*> color_points, std::vector<Point*> points) // ��Ը���Ĺ��캯��������Element������ֵ�����ĳ�Color_ϵ������
{
	// һ����Ҫ��������color_ϵ�е�����,��color_points���õ�ָ������½�
	// 1. color_points
	unsigned int color_points_size = color_points.size();
	unsigned int points_size = element.points.size();
	this->points = std::vector<Point*>(points_size);
	for (unsigned int i = 0; i < points_size; ++i)
	{
		for (unsigned int j = 0; j < color_points_size; ++j)
		{
			if (element.points[i] == points[j])
			{
				this->color_points.push_back(color_points[j]);
			}
		}
		this->points[i] = this->color_points[i];
	}
	// 2. color_neighbors ���� neighbors���Ͼ�neighbors��Ҳֻ��һЩ����Elements����ĵ�ַ��������Ҳ�����ã��Ͳ�д�ˣ�����д������ѭ��
	// �����ָ��ƹ���������color_
	this->name = "color_" + element.name;
}
void Color_element::Update()
{
	unsigned int points_size = this->points.size();
	this->points = std::vector<Point*>(points_size);
	for (unsigned int i = 0; i < points_size; ++i)
	{
		this->points[i] = this->color_points[i];
	}
	unsigned int neighbors_size = this->neighbors.size();
	this->neighbors = std::vector<Element*>(neighbors_size);
	for (unsigned int i = 0; i < neighbors_size; ++i)
	{
		this->neighbors[i] = this->color_neighbors[i];
	}
}

Color_mesh::Color_mesh() // �޲ι���
{
	
}

Color_mesh::Color_mesh(const Mesh& mesh) // ͨ�����캯������Mesh�������ֵ��Colormesh���棬����points elements�ĳ�colorϵ������
{
	// ��߿��ǵ�������˳�����⣬�ȹ���㣬���湹��color_element��ʱ��Ͱ��յ��˳��װ��ȥ,
	// ���������ʵ��̫�ã�������Element��ʱ���Ӧ���ڹ��캯�����ټ�һ��std::vector<int> index,�����ѵ��Mesh points��ĵ��ָ��һһ��Ӧ��
	unsigned int points_size = mesh.points.size();
	this->points = std::vector<Point*>(points_size);
	for (unsigned int i = 0; i < points_size; ++i)
	{
		this->color_points.push_back(new Color_point(*mesh.points[i]));
		this->points[i] = this->color_points[i];
	}

	unsigned int element_size = mesh.elements.size();
	this->elements = std::vector<Element*>(element_size);
	for (unsigned int i = 0; i < element_size; ++i)
	{
		this->color_elements.push_back(new Color_element(*mesh.elements[i],  this->color_points, mesh.points));
		this->elements[i] = this->color_elements[i];
	}
}
void Color_mesh::Update(bool is_points_to_colorpoints )
{
	// ����������� color_points color_elements��ָ�� ͬ�����Ӹ���̳����������� points elements ����,
	// ��ֹ��color_ϵ������vector����ɾû��ͬ�����������ϣ������޷�ʹ��ԭ������ĺ�����
	// Ҳ����ʵ��һ�����ԵĶ�̬(Ȩ��֮��),��ʵ���ٵ�Color_points�Ŀռ��ǲ������ӵģ����Ƕ����һ��ָ��
	// �����ʵ����Ƹ����Mesh��ʱ�� ���Կ������ɴ����ࡣ
	// ��������Ϊ˽�У����̳е����࣬�������ԵĴӸ����Ե�get�ȷ��������������ܸ��õ�ʹ��c++����ָ�루��̬���ƣ�
	if (is_points_to_colorpoints)
	{
		// ʹ��colorpointsָ�����points
		unsigned int point_size = this->color_points.size();
		this->points = std::vector<Point*>(point_size);
		for (unsigned int i = 0; i < point_size; ++i)
		{
			this->points[i] = this->color_points[i];
		}
		unsigned int element_size = this->color_elements.size();
		this->elements = std::vector<Element*>(element_size);
		for (unsigned int i = 0; i < element_size; ++i)
		{
			this->elements[i] = this->color_elements[i];
		}
	}
	else
	{
		// ʹ��elements ���� color_elements
		unsigned int point_size = this->points.size();
		this->color_points = std::vector<Color_point*>(point_size);
		for (unsigned int i = 0; i < point_size; ++i)
		{
			this->color_points[i] = (Color_point*) this->points[i];
		}
		unsigned int element_size = this->elements.size();
		this->color_elements = std::vector<Color_element*>(element_size);
		for (unsigned int i = 0; i < element_size; ++i)
		{
			this->color_elements[i] =(Color_element*) this->elements[i];
		}
	}
	
}
