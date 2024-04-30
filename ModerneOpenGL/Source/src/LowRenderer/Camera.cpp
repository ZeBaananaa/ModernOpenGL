#include "Camera.h"
#include "App.h"
#include "Log.h"

#include <Core/InputHandler.h>
#include <Utils/Time.h>
Camera* Camera::instance = nullptr;

Camera& Camera::Get()
{
    if (instance == nullptr)
        instance = new Camera();
    return *instance;
}

Camera::Camera()
{
    eye = { 0.f,5.f,30.f };
    center = { 0.f,5.f,35.f };
    projectionMatrix = GetProjectionMatrix();
}

void Camera::Destroy()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void Camera::Update()
{
    CheckMoveInput();

    if (recalculateView)
        GetViewMatrix();

    if (recalculateProjection)
        GetProjectionMatrix();

    if (recalculateVP)
        GetVPMatrix();
}

void Camera::CheckMoveInput()
{
    float movementSpeed = speed * Time::DeltaTime();

    if (InputHandler::IsKeyDown(GLFW_KEY_LEFT))
    {
        //left
        Vector3D localAxisX3D = Normalize(CrossProduct(Vector3D::axeY, GetDirection()));
        Move(Product(localAxisX3D, -movementSpeed));
    }
    if (InputHandler::IsKeyDown(GLFW_KEY_RIGHT))
    {
        //rigth
        Vector3D localAxisX3D = Normalize(CrossProduct(Vector3D::axeY, GetDirection()));
        Move(Product(localAxisX3D, movementSpeed));
    }
    if (InputHandler::IsKeyDown(GLFW_KEY_UP))
    {
        //front
        Move(Product(GetDirection(), movementSpeed));
    }
    if (InputHandler::IsKeyDown(GLFW_KEY_DOWN))
    {
        //back
        Move(Product(GetDirection(), -movementSpeed));
    }
    if (InputHandler::IsKeyDown(GLFW_KEY_A))
    {
        //up
        Move(Product(Vector3D::axeY, movementSpeed));
    }
    if (InputHandler::IsKeyDown(GLFW_KEY_E))
    {
        //down
        Move(Product(Vector3D::axeY, -movementSpeed));
    }

    //std::cout << "Position : " << center.ToString() << std::endl;
    //std::cout << "Direction : " << eye.ToString() << std::endl;
}

void Camera::Move(const Vector3D& t)
{
    eye.Translate(t);
    center.Translate(t);
    recalculateView = true;
}

void Camera::Rotation(float angle, Vector3D axis, Vector3D anchor)
{
    center.Rotate(angle, axis, anchor);
    recalculateView = true;
}

Vector3D Camera::GetEye()
{
    return eye;
}

Vector3D Camera::GetDirection()
{
    Vector3D direction(eye, center);
    return Normalize(direction);
}

Matrix4x4 Camera::GetViewMatrix()
{
    if (recalculateView)
    {
        viewMatrix = ViewMatrix(eye, GetDirection(), Vector3D::axeY);
        recalculateView = false;
        recalculateVP = true;
    }
    return viewMatrix;
}

Matrix4x4 Camera::GetProjectionMatrix()
{
    if (recalculateProjection)
    {
        projectionMatrix = PerspectiveMatrix(_fov, (float)Application::Get().m_width / (float)Application::Get().m_height
            , _near, _far);
        recalculateProjection = false;
        recalculateVP = true;
    }
    return projectionMatrix;
}

Matrix4x4 Camera::GetVPMatrix()
{
    if (recalculateVP)
    {
        vpMatrix = projectionMatrix * viewMatrix;
        recalculateVP = false;
    }
    return vpMatrix;
}

void Camera::SetFov(float newFov)
{
    _fov = newFov;
    recalculateProjection = true;
}

void Camera::SetNearFar(float newNear, float newFar)
{
    _near = newNear;
    _far = newFar;
    recalculateProjection = true;
}
