#include "mesh.h"
#include <iostream>
#include<climits>
#include<math.h>
#include "color_mesh.h"
#pragma once

Mesh& example()
{
	// 1. 先定义所有的Point, 一共10，存放到Points里
	std::vector<Point*>* points = new std::vector<Point*>(10);
	std::vector<Point*>& Points = *points;

	Points[0] = new Point(0, 4, "P1");
	Points[1] = new Point(4, 4, "P2");
	Points[2] = new Point(4, 2, "P3");
	Points[3] = new Point(4, 0, "P4");
	Points[4] = new Point(2, 0, "P5");
	Points[5] = new Point(0, 0, "P6");
	Points[6] = new Point(1, 1, "P7");
	Points[7] = new Point(2, 2, "P8");
	Points[8] = new Point(3, 1, "P9");
	Points[9] = new Point(3, 3, "P10");

	// 2. 构造Elements，在每个Elememts中存好自己的points，一共5个
	std::vector<Element*>* elements = new std::vector<Element*>(5);
	std::vector<Element*>& Elements = *elements;

	Elements[0] = new Element(std::vector<Point*>{Points[0],Points[1],Points[9],
		Points[7],Points[6],Points[5]}, "E1");
	Elements[1] = new Element(std::vector<Point*>{ Points[1],Points[2],Points[8],
		Points[9] }, "E2");
	Elements[2] = new Element(std::vector<Point*>{ Points[2],Points[3],Points[4],
		Points[6],Points[7],Points[8] }, "E3");
	Elements[3] = new Element(std::vector<Point*>{ Points[4],Points[5],Points[6]}, "E4");
	Elements[4] = new Element(std::vector<Point*>{ Points[7],Points[9],Points[8]}, "E5");

	// 3. 构造mesh的数据
	Mesh* mesh_example = new Mesh;
	mesh_example->points = Points;
	mesh_example->elements = Elements;
	return *mesh_example;
}

// 判断两元素是否共边
bool issameborder(Element& ele1, Element& ele2)
{
	// 判断ele1和ele2是否共边，要看ele1中向量ab是否存在另个图形ele2中，顺序储存的话需要看点a在ele2中，点b是否也在且相邻
	// 考虑到头尾相连的情况(闭环)，在points的最后一个点做特殊处理。
	// 比如是个三角形的话，有三个点，a b c，不仅要考虑到ab bc，还要考虑ca的情况。
	unsigned int ele1_size = ele1.points.size();
	unsigned int ele2_size = ele2.points.size();
	for (unsigned int ele1_i = ele1_size; ele1_i < 2*ele1_size; ++ele1_i)
	{
		Point* ele1_cur_point = ele1.points[ele1_i % ele1_size];
		Point* ele1_next_point = ele1.points[(ele1_i+1) % ele1_size];

		for (unsigned int ele2_i = ele2_size; ele2_i < 2*ele2_size; ++ele2_i)
		{
			Point* ele2_cur_point = ele2.points[ele2_i % ele2_size];
			Point* ele2_next_point = ele2.points[(ele2_i+1) % ele2_size];
			Point* ele2_pre_point = ele2.points[(ele2_i - 1) % ele2_size];

			if (ele1_cur_point == ele2_cur_point && 
				(
					ele1_next_point == ele2_next_point || ele1_next_point == ele2_pre_point)
				)
			{
				return true;
			}
		}
	}
	return false;

}

// 第一题主程序
void find_neighbors(Mesh& mesh) // 题1
{
	// 从E1开始遍历，遍历E1中的每个点p，看p 和 p的下一个点是否在E2 E3 E4 .. 里，并且是按照顺序排放的
	unsigned int elements_num = mesh.elements.size();
	for (unsigned int cur_elements_index = 0; cur_elements_index < elements_num; ++cur_elements_index)
	{
		Element* cur_element = mesh.elements[cur_elements_index];
		for (unsigned int other_element_index = 0; other_element_index < elements_num; ++other_element_index)
		{
			if (other_element_index == cur_elements_index) continue;
			Element* other_element = mesh.elements[other_element_index];
			if (std::count(other_element->neighbors.begin(), other_element->neighbors.end(), cur_element))
			{
				continue;
			}
			else 
			{
				if (issameborder(*cur_element, *other_element))
				{
					cur_element->neighbors.push_back(other_element);
					other_element->neighbors.push_back(cur_element);
				}
			}
		}
	}
}
// 第一题的展示函数
void show_neighbors(Mesh& mesh_ex)
{
	// 打印第一题的结果
	// 打印mesh里的所有元素的邻居个数以及名称
	for (unsigned int j = 0; j < mesh_ex.elements.size(); ++j)
	{
		std::cout << mesh_ex.elements[j]->name << "的相邻有:" << mesh_ex.elements[j]->neighbors.size() << "个" << std::endl;
		for (unsigned int i = 0; i < mesh_ex.elements[j]->neighbors.size(); ++i)
		{
			std::cout << mesh_ex.elements[j]->neighbors[i]->name << " ";
		}
		std::cout << "\n";
	}
}
// 工具函数，返回point在mesh.points列表下的index
int point_getindex(Point* point, const Mesh& mesh)
{
	// 返回point在mesh.points下的index
	unsigned int mesh_point_size = mesh.points.size();
	for (unsigned int i = 0; i < mesh_point_size; ++i)
	{
		if (point == mesh.points[i])
		{
			return i;
		}
	}
	return -1;// 这个运行不到
}
// 返回point在ele下的相邻元素，可能为空 可能为两个point
std::vector<int> get_near_point(Point* point, const Element& ele , const Mesh& mesh)
{
	// 寻找point在某个element里最近的两个点
	// 返回point在mesh.points里的index
	unsigned int ele_size = ele.points.size();
	std::vector<int> point_near_list;
	for (unsigned int i = 0; i < ele_size; ++i)
	{
		if (point == ele.points[i])
		{
			point_near_list.push_back(point_getindex( ele.points[(i + 1 + ele_size) % ele_size], mesh));
			point_near_list.push_back(point_getindex(ele.points[(i - 1 + ele_size) % ele_size],mesh));
			return point_near_list;
		}
	}
	return point_near_list;
	 
}
// 工具函数 制作邻接表
void make_route(std::vector< std::vector<bool>>& array, const Mesh& mesh)
{
	// 制作连通矩阵（邻接表），并打印矩阵
	unsigned int mesh_points_num = mesh.points.size();
	for (unsigned int i = 0; i < mesh_points_num; ++i)
	{
		Point* cur_point = mesh.points[i]; // 遍历每个点
		for (unsigned int j = 0; j < mesh.elements.size(); ++j) // 看cur_point是否在cur_element里，在的话将相邻的点放在邻接表里
		{
			Element* cur_element = mesh.elements[j];
			std::vector<int> temp = get_near_point(cur_point, *cur_element, mesh);
			if (temp.empty()) // cur_point 不在 cur_element 里会导致temp为空。
			{
				continue;
			}
			else // 否则temp会存放cur_point在cur_element里的两个点，这里其实还是有重复计算，有优化的空间
			{
				array[i][temp[0]] = 1;
				array[i][temp[1]] = 1;
			}
		}
	}
	std::cout << "该mesh_ex的联通矩阵如下：\n";
	for (unsigned int i = 0; i < mesh_points_num; ++i)
	{
		for (unsigned int j = 0; j < mesh_points_num; ++j)
		{
			std::cout << array[i][j] << " ";
		}
		std::cout << "\n";
	};
}
// 工具函数 计算斜率k
double get_k(Point* p1, Point* p2)
{
	// 计算两个点的斜率k, 并返回double
	if (p1->x - p2->x)
	{
		double k = (p1->y - p2->y) / (p1->x - p2->x);
		return  k;
	}
	else
	{
		return DBL_MAX;
	}
	
}
// 工具函数 判断i是否在容器内
bool if_in_vector(int i, std::vector<int>& out)
{
	// 判断i是否在out这个向量里。
	if (std::count(out.begin(), out.end(), i))
	{
		return true;
	}
	return false;
}
// 返回bfs函数里的准入栈元素
std::vector<int> get_in(int i, std::vector<std::vector<bool>>& route,const Mesh& mesh, double k, std::vector<int>& Out)
{
	// 只用于bfs函数里，Out是已经出栈的点（也就是使用过的点）,k是固定斜率，
	std::vector<int> inn;
	for (unsigned int j = 0; j < route[i].size(); ++j)
	{
		// 邻接表里点i 点j 如果直接联通 并且 i j点之间的斜率维持在原来的斜率k上，并且j没有使用过 ，
		// 那么j是合法的可用于下次观察的点
		if (route[i][j] && !if_in_vector(j, Out) && k == get_k(mesh.points[i], mesh.points[j]) )
		{
			inn.push_back(j);
		}
	}
	return inn;
}
// bfs，寻找point i 的所又可以形成直线的 point 的index
std::vector<int> bfs(int i, std::vector<std::vector<bool>>& route, const Mesh& mesh)
{
	// bfs算法，对点i 先寻求其周围的邻接点，对每个邻接点求斜率，
	// 并以此斜率为标准向下扩散，保持斜率不变的点j+进入Out中，
	// 进入后将j+合法的邻接点继续加入In中，直至所有的可能均消失。
	std::vector<int> start;
	for (unsigned int j = 0; j < route[i].size(); ++j)
	{
		if (route[i][j])
		{
			start.push_back(j);
		}
	}
	std::vector<int> out;
	for (unsigned int j = 0; j < start.size(); ++j)
	{
		int cur = start[j];
		double k = get_k(mesh.points[i], mesh.points[cur]);
		std::vector<int> Out{i,cur};
		std::vector<int> In = get_in(cur, route, mesh,k, Out);
		while (!In.empty())
		{
			std::vector<int> temp;
			for (unsigned int index = 0; index < In.size(); ++index)
			{
				Out.push_back(In[index]);
				std::vector<int> temp0 = get_in(In[index], route, mesh, k, Out);
				for (unsigned int i0 = 0; i0 < temp0.size(); ++i0)
				{
					temp.push_back(temp0[i0]);
				}
			}
			In = temp;
		}
		for (unsigned int h = 1; h < Out.size(); ++h)
		{
			out.push_back(Out[h]);
		}
	}
	// 打印结果用于验证
	std::cout << "P" << i+1 << "的联通点为:\n";
	for (unsigned int h = 0; h < out.size(); ++h)
	{
		std::cout << "P" << out[h] + 1 << " ";
	}
	std::cout << "\n";
	return out;
}
// 当i==j 时，填充array的值
void get_matrix_num(int i, std::vector< std::vector<double>>& array ,const Mesh& mesh)
{
	// 用于计算i == j的情况，并将array[i][i]部分填好
	unsigned int mesh_points_num = mesh.points.size();
	unsigned int temp = 0;
	Point* cur_point = mesh.points[i];
	for (unsigned int ele_index = 0; ele_index < mesh.elements.size(); ++ele_index)
	{
		Element* cur_ele = mesh.elements[ele_index];
		for (unsigned int h = 0; h < cur_ele->points.size(); ++h)
		{
			if (cur_point == cur_ele->points[h])
			{
				++temp;
			}
		}
	}
	array[i][i] = temp;
}
// 工具函数 计算两个点欧式距离
double get_distance(Point* p1, Point* p2)
{
	// 计算两点距离
	return sqrt( (p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y)) ;
}
// 第二题主函数，打印在函数内部实现
void print_matrix(const Mesh& mesh)  // 题2
{
	// 1. 先定义一个矩阵array， 这个就是所求
	unsigned int mesh_points_num = mesh.points.size();
	std::vector< std::vector<bool>> route(mesh_points_num, std::vector<bool>(mesh_points_num, 0));
	make_route(route, mesh); // 制作各点的连通图
	std::vector< std::vector<double>> array(mesh_points_num, std::vector<double>(mesh_points_num, 0));
	// 计算矩阵矩阵array
	for (unsigned int i = 0; i < mesh.points.size(); ++i)
	{
		// 题意要求针对 i == j 和 i!= j 的情况分开判断
	// 按照题意应该分情况来计算，如果分开来实现，那么代码效率降低，但易于维护，
	// 若放在一起实现，效率更高，代码维护成本大，放在一起的话可以考虑新建一个数据结构，根据边来hash 含有此边的elements
	// 因为是个demo  我就分开实现了
		get_matrix_num(i, array, mesh);
		std::vector<int> linking_points_list = bfs(i, route, mesh);
		for (unsigned int j = i; j < linking_points_list.size(); ++j) // 从j从i开始计数减少运算量，因为array是个对称矩阵
		{
			int j_ = linking_points_list[j];
			array[i][j_] = get_distance(mesh.points[i], mesh.points[j_]);
			array[j_][i] = get_distance(mesh.points[i], mesh.points[j_]);
		}
	}
	// 打印ARRAY 检验结果
	std::cout << "Array如下：\n";
	for (unsigned int i = 0; i < array.size(); ++i)
	{
		for (unsigned int j = 0; j < array[0].size(); ++j)
		{
			std::cout << array[i][j] << "\t";
		}
		std::cout << "\n";
	}
}
// 第三题前提条件的测试函数
void test03(Mesh& mesh_ex)
{
	// 测试第三题的继承关系和构造关系
	Mesh* temp = new Color_mesh(mesh_ex);
	// 打印
	std::cout << "test03 函数内测试 第三题 前提条件部分\n\n";
	std:: cout<< "Mesh* temp 调用 Color_mesh 对象， color_points 为：\n ";
	for (unsigned int i = 0; i < temp->points.size(); ++i)
	{
		temp->points[i]->show();
		std::cout << "\t";
	}
	std::cout << "\n";
	std::cout << "color_elements为：\n";
	for (unsigned int j = 0; j < temp->elements.size(); ++j)
	{
		std::cout << temp->elements[j]->name << ":\t";
		for (unsigned int i = 0; i < temp->elements[j]->points.size(); ++i)
		{
			temp->elements[j]->points[i]->show();
			std::cout << "\t";
		}
		std::cout <<"\n";
	}
	find_neighbors(*temp);
	std::cout << "\nfind_neighbors对*temp的调用结果为：\n";
	show_neighbors(*temp);
	std::cout << "\n\n";

}
// 对color_mesh对象所有元素的颜色赋值，用来作例子的
void change_points_color(Color_mesh& color_mesh)
{
	// 给color_mesh的color属性赋值
	unsigned int color_points_num = color_mesh.points.size();
	color_mesh.color_points[0]->color = "r";
	color_mesh.color_points[1]->color = "b";
	color_mesh.color_points[2]->color = "b";
	color_mesh.color_points[3]->color = "g";
	color_mesh.color_points[4]->color = "g";
	color_mesh.color_points[5]->color = "b";
	color_mesh.color_points[6]->color = "g";
	color_mesh.color_points[7]->color = "r";
	color_mesh.color_points[8]->color = "g";
	color_mesh.color_points[9]->color = "r";
}
// 第三题的主函数，内置了打印函数
std::vector<Element*> find_element_with_three_or_more_color(const Color_mesh& color_mesh) 
{
	// 第三题
	// 计算包含三种颜色的color_element,并返回vector<Element*>
	std::vector<Element*> ans;
	unsigned int color_elements_num = color_mesh.color_elements.size();
	
	for (unsigned int i = 0; i < color_elements_num; ++i)
	{
		std::vector<std::string> temp{};
		Color_element* cur_element = color_mesh.color_elements[i];
		unsigned int cur_color_points_num = cur_element->color_points.size();
		for (unsigned int j = 0; j < cur_color_points_num; ++j)
		{
			Color_point* cur_point = cur_element->color_points[j];
			if (!std::count(temp.begin(), temp.end(), cur_point->color))
			{
				temp.push_back(cur_point->color);
			}
			
			if (temp.size() >= 3)
			{
				ans.push_back(cur_element);
				break;
			}
		}
	}

	for (unsigned int i = 0; i < ans.size(); ++i)
	{
		std::cout << ans[i]->name << "\t";
	}
	std::cout << "\n";
	return ans;
}
// 第四题的第一问，判断是不是凸的
bool is_convex(const Element& element) 
{
	// 判断方法：
	// 二维向量叉乘：(x1,y1)×(x2,y2) = x1y2-x2y1
	// 值的绝对值是两向量同起点，构成平行四边形的面积
	// 值为正，(x2, y2)在(x1, y1)逆时针方向
	// 值为负，(x2, y2)在(x1, y1)顺时针方向
	// 值为0，(x2, y2)和(x1, y1)共线
	unsigned int points_num = element.points.size();
	if (points_num < 3 )
	{
		return false;
	}
	if (points_num == 3)
	{
		return true;
	}
	std::vector<Point*> temp = {};// 用来盛放连续三个点
	for (unsigned int i = 0; i < points_num; i++)  // 每个循环都计算以i为起点，连续三个点的夹角
	{
		
		temp.push_back(element.points[(i + points_num)% points_num]);
		temp.push_back(element.points[(i + points_num + 1) % points_num]);
		temp.push_back(element.points[(i + points_num + 2) % points_num]);

		// 计算三点夹角
		// 这里发现Point正好可以表示一个向量，就借用point了
		Point v1( temp[1]->x - temp[0]->x, temp[1]->y - temp[0]->y, "temp_v1");
		Point v2( temp[2]->x - temp[1]->x, temp[2]->y - temp[1]->y, "temp_v2");
		// 计算叉乘(第三维度是0),结点我是顺时针存的，结论是 结果大于0就是凹的，全大于0才是凸
		if ((v1.x * v2.y - v1.y * v2.x) >= 0) return false;
		temp.clear();
	}
	return true;
}
// 第四题的第二问，把凸函数切成三角形
void cut_triangle(Mesh& mesh)
{
	unsigned int elements_num = mesh.elements.size();
	for (unsigned int i = 0; i < elements_num; ++i)
	{
		Element* cur_element = mesh.elements[i];
		if (cur_element->points.size() > 3 && is_convex(*cur_element)) // 如果不是三角形且是凸多边形
		{
			// 切分方法是对第一个点，从index = 1，2，3....到size-2 的位置连线，组成新的Element
			Point* p1 = cur_element->points[0];
			Point* p2 = cur_element->points[1];
			Point* p3 = cur_element->points[2];
			std::vector<Element*> new_elements;
			for (unsigned int j = 2; j < cur_element->points.size(); ++j)
			{
				p3 = cur_element->points[j];
				std::string new_name = cur_element->name + "::new" + std::to_string(j - 1);
				new_elements.push_back(new Color_element(std::vector<Point*>{p1, p2, p3}, new_name));
				p2 = p3;
			}
			mesh.elements[i] = new_elements[0];
			// 这儿为了后面看到color_elements的状态就不delete，如果不要看得话可以delete 对 Update 没有影响
			cur_element->name = "已删除";
			cur_element->neighbors.clear();
			cur_element->points.clear();
			// delete cur_element;// 释放该指针指向的堆区(一些vector内的指针)
			for (unsigned int j = 1; j < new_elements.size(); ++j) // 将新的elements添加到mesh.elements
			{
				mesh.elements.push_back(new_elements[j]);
			}
		}
	}
	find_neighbors(mesh);//最后把neighbors制作好
}
// 工具函数 打印***来作为分割线
void print_stars(int num = 80)
{
	std::cout << "\n";
	for (int i = 0 ;i < num; ++i)
	{
		std::cout << "* ";
	}
	std::cout << "\n";
}
// 主函数
int main()
{

	// 制作一个 Mesh对象，mesh_ex 是个例子。
	Mesh mesh_ex = example();
	// 第一题
	find_neighbors(mesh_ex);// 第一题程序
	std::cout << "第一题\n\n find_neighbors 对mesh_ex的执行结果为：\n";
	show_neighbors(mesh_ex);// 第一题的结果的打印程序
	print_stars();
	std::cout << "\n\n\n";
	
	// 第二题
	std::cout << "第二题\n\nprint_matrix的邻接表以及结果为：\n";
	print_matrix(mesh_ex);// 第二题的程序，打印的函数内置在里面了
	print_stars();
	std::cout << "\n\n\n";

	// 第三题
	// 首先要实现Color_mesh的类可以把mesh_ex的属性全部拷贝下来，
	// 下面是打印的结果，说明Color_mesh的类成功复制了mesh_ex的属性并且添加了自身的颜色属性
	std::cout << "第三题\n \n";
	test03(mesh_ex);
	std::cout << "find_element_with_three_or_more_color 对 color_mesh的结果：(我这里设置了E4 E5不行)\n";
	Color_mesh color_mesh(mesh_ex);
	change_points_color(color_mesh);
	find_element_with_three_or_more_color(color_mesh);
	std::cout << "\n";
	print_stars();
	std::cout << "\n\n\n";

	// 第四题
	std::cout << "第四题\n \n";
	// 1. 判断是否是凸多边形
	std::cout << "判断E1-E5是否是凸多边形:\n";
	for (unsigned int i = 0; i < color_mesh.elements.size(); ++i)
	{
		std::string ans = (bool)is_convex(*color_mesh.elements[i]) ? "凸多边形" : "凹多边形";
		std::cout << color_mesh.elements[i]->name << ":\t" << ans << "\n";
	}
	// 2. 对凸多边形进行拆分
	std::cout << "\n\n" << "进行拆分，并将邻居打印出来（例子中只有E2可以拆分，我拆成E2::new1 (p2 p3 p9), E2::new2 (p2,p9,p10)）:\n";
	cut_triangle(color_mesh);
	show_neighbors(color_mesh);
	std::cout << "\n\n重新查看凹凸情况(color_mesh.elements):\n";
	for (unsigned int i = 0; i < color_mesh.elements.size(); ++i)
	{
		std::string ans = (bool)is_convex(*color_mesh.elements[i]) ? "凸多边形" : "凹多边形";
		std::cout << color_mesh.elements[i]->name << ":\t" << ans << "\n";
	}
	std::cout << "\n\n重新查看凹凸情况(color_mesh.color_elements)[未更新]:\n";
	for (unsigned int i = 0; i < color_mesh.color_elements.size(); ++i)
	{
		if (color_mesh.color_elements[i]->name == "已删除")
		{
			std::cout << "已删除\n";
			continue;
		};
		std::string ans = (bool)is_convex(*color_mesh.color_elements[i]) ? "凸多边形" : "凹多边形";
		std::cout << color_mesh.color_elements[i]->name << ":\t" << ans << "\n";
	}
	// 3. 更新Mesh的数据
	color_mesh.Update();
	std::cout << "\n\n已对color_elements属性同步完成:\n";
	std::cout << "\n\n重新查看凹凸情况(color_mesh.color_elements):\n";
	// 上面的程序主要说明color_mesh里的elements属性改变了，现在看是否同步到color_elements里了,也就是看Update是否生效
	for (unsigned int i = 0; i < color_mesh.color_elements.size(); ++i)
	{
		std::string ans = (bool)is_convex(*color_mesh.color_elements[i]) ? "凸多边形" : "凹多边形";
		std::cout << color_mesh.color_elements[i]->name << ":\t" << ans << "\n";
	}
	std::cout << "\n\n查看各个color_elements的具体属性:\n";
	for (unsigned int i = 0; i < color_mesh.color_elements.size(); ++i)
	{
		std::string ele_name = color_mesh.color_elements[i]->name;
		std::cout << ele_name << ":\n";
		std::cout << "点集为：\n";
		for (unsigned int j = 0; j < color_mesh.color_elements[i]->color_points.size(); ++j)
		{
			color_mesh.color_elements[i]->color_points[j]->show();
			std::cout << ", ";
		}
		std::cout << "\n";
		std::cout << "邻居有：\n";
		for (unsigned int j = 0; j < color_mesh.color_elements[i]->color_neighbors.size(); ++j)
		{
			std::cout << color_mesh.color_elements[i]->color_neighbors[j]->name <<"\t";
		}
		std::cout << "\n";

	}
	
	
	
	system("pause");

}



  