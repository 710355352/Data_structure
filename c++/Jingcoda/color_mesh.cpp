#include "color_mesh.h"

// Color_系列的类对自身的拷贝构造在我这里面没用到，就不写了
// 析构也没写,主要没涉及到方法的多态,所以直接在mesh里面写循环一直delete就好了

// 打算实现一个Update函数
// （将Color子类的属性值称之为color_系列属性）
// 用于同步各类父属性和color_子属性的值
Color_point::Color_point() {}// 无参构造
Color_point::Color_point(double a, double b, std::string c = "g") // 有参构造
{
	this->x = a;
	this->y = b;
	this->color = c;
}
Color_point::Color_point(const Point& point) // 针对父类的拷贝构造
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

Color_element::Color_element() // 无参构造,里面不设内容，免得占用空间
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

Color_element::Color_element(const Element& element, std::vector<Color_point*> color_points, std::vector<Point*> points) // 针对父类的构造函数，复制Element的属性值，并改成Color_系列属性
{
	// 一共需要构造两个color_系列的属性,从color_points中拿到指针而非新建
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
	// 2. color_neighbors 拷贝 neighbors，毕竟neighbors里也只是一些父类Elements对象的地址，对子类也不适用，就不写了，而且写会有死循环
	// 把名字复制过来，加上color_
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

Color_mesh::Color_mesh() // 无参构造
{
	
}

Color_mesh::Color_mesh(const Mesh& mesh) // 通过构造函数复制Mesh类的属性值到Colormesh下面，并将points elements改成color系列属性
{
	// 这边考虑到构造点的顺序问题，先构造点，后面构造color_element的时候就按照点的顺序装进去,
	// 这个流程其实不太好，按理讲在Element的时候就应该在构造函数里再加一个std::vector<int> index,这样把点和Mesh points里的点的指针一一对应，
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
	// 将自身的属性 color_points color_elements的指针 同步到从父类继承下来的属性 points elements 的上,
	// 防止对color_系列属性vector的增删没有同步父类属性上，导致无法使用原来定义的函数。
	// 也就是实现一下属性的多态(权宜之计),其实开辟的Color_points的空间是不会增加的，就是多存了一组指针
	// 这边其实在设计父类的Mesh的时候 可以考虑做成纯虚类。
	// 把属性设为私有，不继承到子类，调用属性的从该属性的get等方法调，这样就能更好地使用c++的虚指针（多态机制）
	if (is_points_to_colorpoints)
	{
		// 使用colorpoints指针更新points
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
		// 使用elements 更新 color_elements
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
