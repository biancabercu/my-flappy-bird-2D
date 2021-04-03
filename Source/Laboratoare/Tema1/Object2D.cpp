#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };

	triangle->SetDrawMode(GL_TRIANGLES);

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};
	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0,1,2,3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		//draw 3 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}
	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 center, float radius, int verticesNo, glm::vec3 color, bool fill)
{
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(center, color));

	double PI = 3.1415926f;
	for (int i = 1; i <= verticesNo; i++) {
		glm::vec3 aux = center;
		//(i * 2.0f*PI / verticesNo) -current angle
		aux.x = radius * cos(i * 2.0f * PI / verticesNo) + center.x;
		aux.y = radius * sin(i * 2.0f * PI / verticesNo) + center.y;
		vertices.push_back(VertexFormat(aux, color));
	}

	std::vector<unsigned short> indices(verticesNo + 1);
	for (int i = 0; i <= verticesNo; i++) {
		indices[i] = i;
	}

	Mesh* circle = new Mesh(name);
	circle->SetDrawMode(GL_TRIANGLE_FAN);
	circle->InitFromData(vertices, indices);

	return circle;
}