#pragma once
#include <vector>
#include <GL/glew.h>
#include <Eigen/Dense>

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// default camera values
const float YAM = -90.0f;
