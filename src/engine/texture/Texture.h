#pragma once
#include <string>
#include <glew\GL\glew.h>

class Texture
{
public:
	Texture(const std::string& name, const std::string& path, const GLuint& width, const GLuint& height) : name(name), path(path), width(width), height(height) {}

	~Texture() { cleanUp(); }

	virtual void load() {};
	virtual void cleanUp() {};

	inline void setName(const std::string& value) { name = value; }
	inline void setPath(const std::string& value) { path = value; }
	inline void setWidth(const GLuint& value) { width = value; }
	inline void setHeight(const GLuint& value) { height = value; }
	inline void setLocation(const GLuint& value) { location = value; }
	
	inline const GLuint& getID() { return ID; }
	inline const std::string& getName() { return name; }
	inline const std::string& getPath() { return path; }
	inline const GLuint& getWidth() { return width; }
	inline const GLuint& getHeight() { return height; }
	inline const GLuint& getLocation() { return location; }

protected:
	GLuint ID;
	GLuint location;
	std::string name;
	std::string path;
	GLuint width;
	GLuint height;

	void activate();
};