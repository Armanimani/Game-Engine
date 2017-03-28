#include "OBJFileReader.h"
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <utility>


std::shared_ptr<Mesh> OBJFileReader::readOBJFile(const std::string& path, std::istream &file)
{
	std::string name;
	std::vector<GLfloat> verts;
	std::vector<GLuint> indices;
	std::vector<MeshAttribute> attribs;
	verts.reserve(1024);
	indices.reserve(1024);

	name = std::string(path.begin() + path.find_last_of("/") + 1, path.end() - 4);

	std::string line;
	std::string key;

	std::vector<GLfloat> verts_temp;
	std::vector<GLfloat> normal_temp;
	std::vector<GLfloat> tex_temp;
	std::vector<GLuint> indv_temp;
	std::vector<GLuint> indvn_temp;
	std::vector<GLuint> indvt_temp;
	verts_temp.reserve(1024);
	normal_temp.reserve(1024);
	tex_temp.reserve(1024);
	indv_temp.reserve(1024);
	indvn_temp.reserve(1024);
	indvt_temp.reserve(1024);

	while (std::getline(file, line))
	{
		if (line == "" || line[0] == '#')
		{
			continue;
		}
		std::istringstream lineStream(line);
		lineStream >> key;

		float temp[3];
		int temp2[9];
		if (key == "v")
		{
			sscanf_s(line.c_str(), "%*s %f %f %f", &temp[0], &temp[1], &temp[2]);
			verts_temp.push_back(temp[0]);
			verts_temp.push_back(temp[1]);
			verts_temp.push_back(temp[2]);
		}
		else if (key == "vn")
		{
			sscanf_s(line.c_str(), "%*s %f %f %f", &temp[0], &temp[1], &temp[2]);
			normal_temp.push_back(temp[0]);
			normal_temp.push_back(temp[1]);
			normal_temp.push_back(temp[2]);
		}
		else if (key == "vt")
		{
			sscanf_s(line.c_str(), "%*s %f %f %f", &temp[0], &temp[1], &temp[2]);
			tex_temp.push_back(temp[0]);
			tex_temp.push_back(temp[1]);
			tex_temp.push_back(temp[2]);
		}
		else if (key == "f")
		{
			sscanf_s(line.c_str(), "%*s %i/%i/%i %i/%i/%i %i/%i/%i", &temp2[0], &temp2[1], &temp2[2], &temp2[3], &temp2[4], &temp2[5], &temp2[6], &temp2[7], &temp2[8]);
			indv_temp.push_back(temp2[0]);
			indvt_temp.push_back(temp2[1]);
			indvn_temp.push_back(temp2[2]);
			indv_temp.push_back(temp2[3]);
			indvt_temp.push_back(temp2[4]);
			indvn_temp.push_back(temp2[5]);
			indv_temp.push_back(temp2[6]);
			indvt_temp.push_back(temp2[7]);
			indvn_temp.push_back(temp2[8]);
		}
	}

	std::vector<std::tuple<GLuint, GLuint, GLuint>> vec;
	vec.reserve(1024);
	std::tuple<GLuint, GLuint, GLuint> temp3;
	std::size_t index;

	for (std::size_t i = 0; i != indv_temp.size(); i = i + 3)
	{
		for (auto j = 0; j != 3; ++j)
		{
			temp3 = std::make_tuple(indv_temp[i + j], indvt_temp[i + j], indvn_temp[i + j]);
			auto it = std::find(vec.begin(), vec.end(), temp3);
			if (it == vec.end())
			{
				vec.push_back(temp3);
				index = vec.size();
				verts.push_back(verts_temp[3 * (std::get<0>(temp3) - 1)]);
				verts.push_back(verts_temp[3 * (std::get<0>(temp3) - 1) + 1]);
				verts.push_back(verts_temp[3 * (std::get<0>(temp3) - 1) + 2]);
				verts.push_back(normal_temp[3 * (std::get<2>(temp3) - 1)]);
				verts.push_back(normal_temp[3 * (std::get<2>(temp3) - 1) + 1]);
				verts.push_back(normal_temp[3 * (std::get<2>(temp3) - 1) + 2]);
				verts.push_back(tex_temp[3 * (std::get<1>(temp3) - 1)]);
				verts.push_back(tex_temp[3 * (std::get<1>(temp3) - 1) + 1]);
				verts.push_back(tex_temp[3 * (std::get<1>(temp3) - 1) + 2]);
			}
			else
			{
				index = it - vec.begin() + 1;
			}
			indices.push_back(index -1);
		}
	}

	if (verts_temp.size() != 0) attribs.push_back(MeshAttribute::position);
	if (normal_temp.size() != 0) attribs.push_back(MeshAttribute::normal);
	if (tex_temp.size() != 0) attribs.push_back(MeshAttribute::texture);

	return std::make_shared<Mesh>(name, verts, indices, attribs);
}
