#pragma once
#include <glew\GL\glew.h>
#include <vector>
#include <string>

#include "MeshAttribute.h"

class Mesh
{
public:
	Mesh(const std::string& name, const std::vector<GLfloat>& verts, const std::vector<GLuint>& indices, const std::vector<MeshAttribute>& attribs) : name(name), verts(verts), indices(indices), attribs(attribs) {}

	//~Mesh() { cleanUp(); }

	virtual void load();
	virtual void cleanUp();

	inline const std::vector<float>& getVerts() { return verts; }
	inline const std::vector<GLuint>& getIndices() { return indices; }

	inline const GLuint& getVAOID() const { return vertexArrayObjectID; }
	inline const GLuint& getVBOID() const { return vertexBufferObjectID; }
	inline const GLuint& getIBOID() const { return indexBufferObjectID; }

	inline const std::string& getName() const { return name; }

	inline const std::string& getPath() const { return path; }
	inline void setPath(const std::string& path) { this->path = path; }

protected:
	std::string name;
	std::string path;

	GLuint vertexArrayObjectID;
	GLuint vertexBufferObjectID;
	GLuint indexBufferObjectID;

	std::vector<GLfloat> verts;
	std::vector<GLuint> indices;
	std::vector<MeshAttribute> attribs;

	virtual void bind();
	virtual void unbind();
};