#include "mesh.h"
#include <iostream>
#include<climits>
#include<math.h>
#include "color_mesh.h"
#pragma once

Mesh& example()
{
	// 1. �ȶ������е�Point, һ��10����ŵ�Points��
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

	// 2. ����Elements����ÿ��Elememts�д���Լ���points��һ��5��
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

	// 3. ����mesh������
	Mesh* mesh_example = new Mesh;
	mesh_example->points = Points;
	mesh_example->elements = Elements;
	return *mesh_example;
}

// �ж���Ԫ���Ƿ񹲱�
bool issameborder(Element& ele1, Element& ele2)
{
	// �ж�ele1��ele2�Ƿ񹲱ߣ�Ҫ��ele1������ab�Ƿ�������ͼ��ele2�У�˳�򴢴�Ļ���Ҫ����a��ele2�У���b�Ƿ�Ҳ��������
	// ���ǵ�ͷβ���������(�ջ�)����points�����һ���������⴦��
	// �����Ǹ������εĻ����������㣬a b c������Ҫ���ǵ�ab bc����Ҫ����ca�������
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

// ��һ��������
void find_neighbors(Mesh& mesh) // ��1
{
	// ��E1��ʼ����������E1�е�ÿ����p����p �� p����һ�����Ƿ���E2 E3 E4 .. ������ǰ���˳���ŷŵ�
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
// ��һ���չʾ����
void show_neighbors(Mesh& mesh_ex)
{
	// ��ӡ��һ��Ľ��
	// ��ӡmesh�������Ԫ�ص��ھӸ����Լ�����
	for (unsigned int j = 0; j < mesh_ex.elements.size(); ++j)
	{
		std::cout << mesh_ex.elements[j]->name << "��������:" << mesh_ex.elements[j]->neighbors.size() << "��" << std::endl;
		for (unsigned int i = 0; i < mesh_ex.elements[j]->neighbors.size(); ++i)
		{
			std::cout << mesh_ex.elements[j]->neighbors[i]->name << " ";
		}
		std::cout << "\n";
	}
}
// ���ߺ���������point��mesh.points�б��µ�index
int point_getindex(Point* point, const Mesh& mesh)
{
	// ����point��mesh.points�µ�index
	unsigned int mesh_point_size = mesh.points.size();
	for (unsigned int i = 0; i < mesh_point_size; ++i)
	{
		if (point == mesh.points[i])
		{
			return i;
		}
	}
	return -1;// ������в���
}
// ����point��ele�µ�����Ԫ�أ�����Ϊ�� ����Ϊ����point
std::vector<int> get_near_point(Point* point, const Element& ele , const Mesh& mesh)
{
	// Ѱ��point��ĳ��element�������������
	// ����point��mesh.points���index
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
// ���ߺ��� �����ڽӱ�
void make_route(std::vector< std::vector<bool>>& array, const Mesh& mesh)
{
	// ������ͨ�����ڽӱ�������ӡ����
	unsigned int mesh_points_num = mesh.points.size();
	for (unsigned int i = 0; i < mesh_points_num; ++i)
	{
		Point* cur_point = mesh.points[i]; // ����ÿ����
		for (unsigned int j = 0; j < mesh.elements.size(); ++j) // ��cur_point�Ƿ���cur_element��ڵĻ������ڵĵ�����ڽӱ���
		{
			Element* cur_element = mesh.elements[j];
			std::vector<int> temp = get_near_point(cur_point, *cur_element, mesh);
			if (temp.empty()) // cur_point ���� cur_element ��ᵼ��tempΪ�ա�
			{
				continue;
			}
			else // ����temp����cur_point��cur_element��������㣬������ʵ�������ظ����㣬���Ż��Ŀռ�
			{
				array[i][temp[0]] = 1;
				array[i][temp[1]] = 1;
			}
		}
	}
	std::cout << "��mesh_ex����ͨ�������£�\n";
	for (unsigned int i = 0; i < mesh_points_num; ++i)
	{
		for (unsigned int j = 0; j < mesh_points_num; ++j)
		{
			std::cout << array[i][j] << " ";
		}
		std::cout << "\n";
	};
}
// ���ߺ��� ����б��k
double get_k(Point* p1, Point* p2)
{
	// �����������б��k, ������double
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
// ���ߺ��� �ж�i�Ƿ���������
bool if_in_vector(int i, std::vector<int>& out)
{
	// �ж�i�Ƿ���out��������
	if (std::count(out.begin(), out.end(), i))
	{
		return true;
	}
	return false;
}
// ����bfs�������׼��ջԪ��
std::vector<int> get_in(int i, std::vector<std::vector<bool>>& route,const Mesh& mesh, double k, std::vector<int>& Out)
{
	// ֻ����bfs�����Out���Ѿ���ջ�ĵ㣨Ҳ����ʹ�ù��ĵ㣩,k�ǹ̶�б�ʣ�
	std::vector<int> inn;
	for (unsigned int j = 0; j < route[i].size(); ++j)
	{
		// �ڽӱ����i ��j ���ֱ����ͨ ���� i j��֮���б��ά����ԭ����б��k�ϣ�����jû��ʹ�ù� ��
		// ��ôj�ǺϷ��Ŀ������´ι۲�ĵ�
		if (route[i][j] && !if_in_vector(j, Out) && k == get_k(mesh.points[i], mesh.points[j]) )
		{
			inn.push_back(j);
		}
	}
	return inn;
}
// bfs��Ѱ��point i �����ֿ����γ�ֱ�ߵ� point ��index
std::vector<int> bfs(int i, std::vector<std::vector<bool>>& route, const Mesh& mesh)
{
	// bfs�㷨���Ե�i ��Ѱ������Χ���ڽӵ㣬��ÿ���ڽӵ���б�ʣ�
	// ���Դ�б��Ϊ��׼������ɢ������б�ʲ���ĵ�j+����Out�У�
	// �����j+�Ϸ����ڽӵ��������In�У�ֱ�����еĿ��ܾ���ʧ��
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
	// ��ӡ���������֤
	std::cout << "P" << i+1 << "����ͨ��Ϊ:\n";
	for (unsigned int h = 0; h < out.size(); ++h)
	{
		std::cout << "P" << out[h] + 1 << " ";
	}
	std::cout << "\n";
	return out;
}
// ��i==j ʱ�����array��ֵ
void get_matrix_num(int i, std::vector< std::vector<double>>& array ,const Mesh& mesh)
{
	// ���ڼ���i == j�����������array[i][i]�������
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
// ���ߺ��� ����������ŷʽ����
double get_distance(Point* p1, Point* p2)
{
	// �����������
	return sqrt( (p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y)) ;
}
// �ڶ�������������ӡ�ں����ڲ�ʵ��
void print_matrix(const Mesh& mesh)  // ��2
{
	// 1. �ȶ���һ������array�� �����������
	unsigned int mesh_points_num = mesh.points.size();
	std::vector< std::vector<bool>> route(mesh_points_num, std::vector<bool>(mesh_points_num, 0));
	make_route(route, mesh); // �����������ͨͼ
	std::vector< std::vector<double>> array(mesh_points_num, std::vector<double>(mesh_points_num, 0));
	// ����������array
	for (unsigned int i = 0; i < mesh.points.size(); ++i)
	{
		// ����Ҫ����� i == j �� i!= j ������ֿ��ж�
	// ��������Ӧ�÷���������㣬����ֿ���ʵ�֣���ô����Ч�ʽ��ͣ�������ά����
	// ������һ��ʵ�֣�Ч�ʸ��ߣ�����ά���ɱ��󣬷���һ��Ļ����Կ����½�һ�����ݽṹ�����ݱ���hash ���д˱ߵ�elements
	// ��Ϊ�Ǹ�demo  �Ҿͷֿ�ʵ����
		get_matrix_num(i, array, mesh);
		std::vector<int> linking_points_list = bfs(i, route, mesh);
		for (unsigned int j = i; j < linking_points_list.size(); ++j) // ��j��i��ʼ������������������Ϊarray�Ǹ��Գƾ���
		{
			int j_ = linking_points_list[j];
			array[i][j_] = get_distance(mesh.points[i], mesh.points[j_]);
			array[j_][i] = get_distance(mesh.points[i], mesh.points[j_]);
		}
	}
	// ��ӡARRAY ������
	std::cout << "Array���£�\n";
	for (unsigned int i = 0; i < array.size(); ++i)
	{
		for (unsigned int j = 0; j < array[0].size(); ++j)
		{
			std::cout << array[i][j] << "\t";
		}
		std::cout << "\n";
	}
}
// ������ǰ�������Ĳ��Ժ���
void test03(Mesh& mesh_ex)
{
	// ���Ե�����ļ̳й�ϵ�͹����ϵ
	Mesh* temp = new Color_mesh(mesh_ex);
	// ��ӡ
	std::cout << "test03 �����ڲ��� ������ ǰ����������\n\n";
	std:: cout<< "Mesh* temp ���� Color_mesh ���� color_points Ϊ��\n ";
	for (unsigned int i = 0; i < temp->points.size(); ++i)
	{
		temp->points[i]->show();
		std::cout << "\t";
	}
	std::cout << "\n";
	std::cout << "color_elementsΪ��\n";
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
	std::cout << "\nfind_neighbors��*temp�ĵ��ý��Ϊ��\n";
	show_neighbors(*temp);
	std::cout << "\n\n";

}
// ��color_mesh��������Ԫ�ص���ɫ��ֵ�����������ӵ�
void change_points_color(Color_mesh& color_mesh)
{
	// ��color_mesh��color���Ը�ֵ
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
// ��������������������˴�ӡ����
std::vector<Element*> find_element_with_three_or_more_color(const Color_mesh& color_mesh) 
{
	// ������
	// �������������ɫ��color_element,������vector<Element*>
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
// ������ĵ�һ�ʣ��ж��ǲ���͹��
bool is_convex(const Element& element) 
{
	// �жϷ�����
	// ��ά������ˣ�(x1,y1)��(x2,y2) = x1y2-x2y1
	// ֵ�ľ���ֵ��������ͬ��㣬����ƽ���ı��ε����
	// ֵΪ����(x2, y2)��(x1, y1)��ʱ�뷽��
	// ֵΪ����(x2, y2)��(x1, y1)˳ʱ�뷽��
	// ֵΪ0��(x2, y2)��(x1, y1)����
	unsigned int points_num = element.points.size();
	if (points_num < 3 )
	{
		return false;
	}
	if (points_num == 3)
	{
		return true;
	}
	std::vector<Point*> temp = {};// ����ʢ������������
	for (unsigned int i = 0; i < points_num; i++)  // ÿ��ѭ����������iΪ��㣬����������ļн�
	{
		
		temp.push_back(element.points[(i + points_num)% points_num]);
		temp.push_back(element.points[(i + points_num + 1) % points_num]);
		temp.push_back(element.points[(i + points_num + 2) % points_num]);

		// ��������н�
		// ���﷢��Point���ÿ��Ա�ʾһ���������ͽ���point��
		Point v1( temp[1]->x - temp[0]->x, temp[1]->y - temp[0]->y, "temp_v1");
		Point v2( temp[2]->x - temp[1]->x, temp[2]->y - temp[1]->y, "temp_v2");
		// ������(����ά����0),�������˳ʱ���ģ������� �������0���ǰ��ģ�ȫ����0����͹
		if ((v1.x * v2.y - v1.y * v2.x) >= 0) return false;
		temp.clear();
	}
	return true;
}
// ������ĵڶ��ʣ���͹�����г�������
void cut_triangle(Mesh& mesh)
{
	unsigned int elements_num = mesh.elements.size();
	for (unsigned int i = 0; i < elements_num; ++i)
	{
		Element* cur_element = mesh.elements[i];
		if (cur_element->points.size() > 3 && is_convex(*cur_element)) // �����������������͹�����
		{
			// �зַ����ǶԵ�һ���㣬��index = 1��2��3....��size-2 ��λ�����ߣ�����µ�Element
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
			// ���Ϊ�˺��濴��color_elements��״̬�Ͳ�delete�������Ҫ���û�����delete �� Update û��Ӱ��
			cur_element->name = "��ɾ��";
			cur_element->neighbors.clear();
			cur_element->points.clear();
			// delete cur_element;// �ͷŸ�ָ��ָ��Ķ���(һЩvector�ڵ�ָ��)
			for (unsigned int j = 1; j < new_elements.size(); ++j) // ���µ�elements��ӵ�mesh.elements
			{
				mesh.elements.push_back(new_elements[j]);
			}
		}
	}
	find_neighbors(mesh);//����neighbors������
}
// ���ߺ��� ��ӡ***����Ϊ�ָ���
void print_stars(int num = 80)
{
	std::cout << "\n";
	for (int i = 0 ;i < num; ++i)
	{
		std::cout << "* ";
	}
	std::cout << "\n";
}
// ������
int main()
{

	// ����һ�� Mesh����mesh_ex �Ǹ����ӡ�
	Mesh mesh_ex = example();
	// ��һ��
	find_neighbors(mesh_ex);// ��һ�����
	std::cout << "��һ��\n\n find_neighbors ��mesh_ex��ִ�н��Ϊ��\n";
	show_neighbors(mesh_ex);// ��һ��Ľ���Ĵ�ӡ����
	print_stars();
	std::cout << "\n\n\n";
	
	// �ڶ���
	std::cout << "�ڶ���\n\nprint_matrix���ڽӱ��Լ����Ϊ��\n";
	print_matrix(mesh_ex);// �ڶ���ĳ��򣬴�ӡ�ĺ���������������
	print_stars();
	std::cout << "\n\n\n";

	// ������
	// ����Ҫʵ��Color_mesh������԰�mesh_ex������ȫ������������
	// �����Ǵ�ӡ�Ľ����˵��Color_mesh����ɹ�������mesh_ex�����Բ���������������ɫ����
	std::cout << "������\n \n";
	test03(mesh_ex);
	std::cout << "find_element_with_three_or_more_color �� color_mesh�Ľ����(������������E4 E5����)\n";
	Color_mesh color_mesh(mesh_ex);
	change_points_color(color_mesh);
	find_element_with_three_or_more_color(color_mesh);
	std::cout << "\n";
	print_stars();
	std::cout << "\n\n\n";

	// ������
	std::cout << "������\n \n";
	// 1. �ж��Ƿ���͹�����
	std::cout << "�ж�E1-E5�Ƿ���͹�����:\n";
	for (unsigned int i = 0; i < color_mesh.elements.size(); ++i)
	{
		std::string ans = (bool)is_convex(*color_mesh.elements[i]) ? "͹�����" : "�������";
		std::cout << color_mesh.elements[i]->name << ":\t" << ans << "\n";
	}
	// 2. ��͹����ν��в��
	std::cout << "\n\n" << "���в�֣������ھӴ�ӡ������������ֻ��E2���Բ�֣��Ҳ��E2::new1 (p2 p3 p9), E2::new2 (p2,p9,p10)��:\n";
	cut_triangle(color_mesh);
	show_neighbors(color_mesh);
	std::cout << "\n\n���²鿴��͹���(color_mesh.elements):\n";
	for (unsigned int i = 0; i < color_mesh.elements.size(); ++i)
	{
		std::string ans = (bool)is_convex(*color_mesh.elements[i]) ? "͹�����" : "�������";
		std::cout << color_mesh.elements[i]->name << ":\t" << ans << "\n";
	}
	std::cout << "\n\n���²鿴��͹���(color_mesh.color_elements)[δ����]:\n";
	for (unsigned int i = 0; i < color_mesh.color_elements.size(); ++i)
	{
		if (color_mesh.color_elements[i]->name == "��ɾ��")
		{
			std::cout << "��ɾ��\n";
			continue;
		};
		std::string ans = (bool)is_convex(*color_mesh.color_elements[i]) ? "͹�����" : "�������";
		std::cout << color_mesh.color_elements[i]->name << ":\t" << ans << "\n";
	}
	// 3. ����Mesh������
	color_mesh.Update();
	std::cout << "\n\n�Ѷ�color_elements����ͬ�����:\n";
	std::cout << "\n\n���²鿴��͹���(color_mesh.color_elements):\n";
	// ����ĳ�����Ҫ˵��color_mesh���elements���Ըı��ˣ����ڿ��Ƿ�ͬ����color_elements����,Ҳ���ǿ�Update�Ƿ���Ч
	for (unsigned int i = 0; i < color_mesh.color_elements.size(); ++i)
	{
		std::string ans = (bool)is_convex(*color_mesh.color_elements[i]) ? "͹�����" : "�������";
		std::cout << color_mesh.color_elements[i]->name << ":\t" << ans << "\n";
	}
	std::cout << "\n\n�鿴����color_elements�ľ�������:\n";
	for (unsigned int i = 0; i < color_mesh.color_elements.size(); ++i)
	{
		std::string ele_name = color_mesh.color_elements[i]->name;
		std::cout << ele_name << ":\n";
		std::cout << "�㼯Ϊ��\n";
		for (unsigned int j = 0; j < color_mesh.color_elements[i]->color_points.size(); ++j)
		{
			color_mesh.color_elements[i]->color_points[j]->show();
			std::cout << ", ";
		}
		std::cout << "\n";
		std::cout << "�ھ��У�\n";
		for (unsigned int j = 0; j < color_mesh.color_elements[i]->color_neighbors.size(); ++j)
		{
			std::cout << color_mesh.color_elements[i]->color_neighbors[j]->name <<"\t";
		}
		std::cout << "\n";

	}
	
	
	
	system("pause");

}



  