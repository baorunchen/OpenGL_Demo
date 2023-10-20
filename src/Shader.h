#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <Eigen/Dense>
#include <GL/glew.h>

class Shader{
public:
	unsigned int Program;
	Shader(const char* vertexPath, const char* fragmentPath);
	void Use();
	void setMat4(const std::string name, Eigen::Matrix4f& mat);
};

