#pragma once
#include "MathPerso.h"

class Camera
{
public:
	~Camera() = default;

	static Camera& Get();
	static void Destroy();

	void Update();
	void CheckMoveInput();
	void Move(const Vector3D& t);
	void Rotation(float angle, Vector3D axis, Vector3D anchor = Vector3D::zero);

	Vector3D GetEye();
	Vector3D GetCenter();
	Vector3D GetDirection();
	Matrix4x4 GetViewMatrix();
	Matrix4x4 GetProjectionMatrix();
	Matrix4x4 GetVPMatrix();

	void SetFov(float newFov);
	void SetNearFar(float newNear, float newFar);
	
	float speed{ 10.f };
	bool recalculateView = true;
	bool recalculateProjection = true;
	bool recalculateVP = true;
private:
	Camera();
	static Camera* instance;
	
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 vpMatrix;
	
	Vector3D eye;
	Vector3D center;

	float _fov{90.f};
	float _near{ 0.1f };
	float _far{ 1000.f };
	
};

