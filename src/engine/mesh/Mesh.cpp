#include "Mesh.h"
#include "../debug/Debug.h"

void Mesh::load()
{
	bind();

	std::vector<int> pos;
	int stride = 0;
	for (std::size_t i = 0; i != attribs.size(); ++i)
	{
		if (attribs[i] == MeshAttribute::position)
		{
			pos.push_back(3);
			stride = stride + 3;
		}
		else if (attribs[i] == MeshAttribute::normal)
		{
			pos.push_back(3);
			stride = stride + 3;
		}
		else if (attribs[i] == MeshAttribute::color)
		{
			pos.push_back(3);
			stride = stride + 3;
		}
		else if (attribs[i] == MeshAttribute::texture)
		{
			pos.push_back(3);
			stride = stride + 3;
		}
		else
		{
			Debug::print(name);
			Debug::print("Undefined attribute name");
			return;
		}
	}
	int start = 0;
	for (std::size_t i = 0; i != attribs.size(); ++i)
	{
		if (attribs[i] == MeshAttribute::position)
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*) (start * sizeof(float)));
		}
		else if (attribs[i] == MeshAttribute::normal)
		{
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*) (start * sizeof(float)));
		}
		else if (attribs[i] == MeshAttribute::texture)
		{
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*) (start * sizeof(float)));
		}
		else if (attribs[i] == MeshAttribute::color)
		{
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*) (start * sizeof(float)));
		}
		else
		{

		}
		start = start + pos[i];
	}

}

void Mesh::bind()
{
	glGenVertexArrays(1, &vertexArrayObjectID);
	glBindVertexArray(vertexArrayObjectID);

	glGenBuffers(1, &vertexBufferObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectID);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), &verts[0], GL_STATIC_DRAW);

	glGenBuffers(1, &indexBufferObjectID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

void Mesh::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}