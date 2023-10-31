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
const float YAW = -90.0f;	// Euler Angle
const float PITCH = 0.0f;	// Euler Angle
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
	Eigen::Vector3f Position;
	Eigen::Vector3f Front;
	Eigen::Vector3f Up;
	Eigen::Vector3f Right;
	Eigen::Vector3f WorldUp;
	
	// Euler angle
	float Yaw;
	float Pitch;

	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(Eigen::Vector3f position = Eigen::Vector3f(0, 0, 0), Eigen::Vector3f up = Eigen::Vector3f(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(Eigen::Vector3f(0, 0, -1.0f)), MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		
		updateCameraVectors();
	}

	Eigen::Matrix4f GetViewMatrix() {
		Eigen::Matrix4f view;
		view << 1, 0, 0, -Position.x(),
			0, 1, 0, -Position.y(),
			0, 0, 1, -Position.z(),
			0, 0, 0, 1;

		Eigen::Matrix4f translate;
		translate << Right.x(), Up.x(), Position.x() + Front.x(), 0,
			Right.y(), Up.y(), Position.y() + Front.y(), 0,
			Right.z(), Up.z(), Position.z() + Front.z(), 0,
			0, 0, 0, 1;
		
		//translate << Right.x(), Right.y(), Right.z(), 0,
		//	Up.x(), Up.y(), Up.z(), 0,
		//	Position.x() + Front.x(), Position.y() + Front.y(), Position.z() + Front.z(), 0,
		//	0, 0, 0, 1;
					

		
		view = translate * view;
		//return Eigen::Matrix4f::Identity();
		return view;
	}

	void ProcessKeyBoard(CameraMovement direction, float deltaTime) {
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position -= Front * velocity;
		else if (direction == BACKWARD)
			Position += Front * velocity;
		else if (direction == LEFT)
			Position -= Right * velocity;
		else
			Position += Right * velocity;
	}

	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (constrainPitch) {
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0)
				Pitch = -89.0f;
		}
		updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset) {
		Zoom -= yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}


private:
	void updateCameraVectors() {
		Front.x() = cos(radians(Pitch)) * cos(radians(Yaw));
		Front.y() = sin(radians(Pitch));
		Front.z() = cos(radians(Pitch)) * sin(radians(Yaw));

		Front.normalize();
		Right = Front.cross(WorldUp);
		Right.normalize();
		Up = Right.cross(Front);
		Up.normalize();
	}

	float radians(float x) {
		return x / 180.0 * acos(-1);
	}
};



