#include "Camera.h"
#include "App.h"
#include "Log.h"

#include <Utils/InputHandler.h>
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
    eye = { 0.f, 5.f, 30.f };
    center = { 0.f, 5.f, 35.f  };
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
    Vector3D localAxisX3D;

    if (InputHandler::IsKeyHeld(GLFW_KEY_LEFT))
    {
        //left
        localAxisX3D = Normalize(CrossProduct(Vector3D::axeY, GetDirection()));
        Move(Product(localAxisX3D, movementSpeed));
    }
    if (InputHandler::IsKeyHeld(GLFW_KEY_RIGHT))
    {
        //rigth
        localAxisX3D = Normalize(CrossProduct(Vector3D::axeY, GetDirection()));
        Move(Product(localAxisX3D, -movementSpeed));
    }
    if (InputHandler::IsKeyHeld(GLFW_KEY_UP))
    {
        //front
        Move(Product(GetDirection(), movementSpeed));
    }
    if (InputHandler::IsKeyHeld(GLFW_KEY_DOWN))
    {
        //back
        Move(Product(GetDirection(), -movementSpeed));
    }
    if (InputHandler::IsKeyHeld(GLFW_KEY_E) || InputHandler::IsKeyHeld(GLFW_KEY_SPACE))
    {
        //up
        Move(Product(Vector3D::axeY, movementSpeed));
    }
    if (InputHandler::IsKeyHeld(GLFW_KEY_A) || InputHandler::IsKeyHeld(GLFW_KEY_LEFT_CONTROL))
    {
        //down
        Move(Product(Vector3D::axeY, -movementSpeed));
    }
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

    //between 0 - PI
    float currentAngle = GetAngle(GetDirection(), Vector3D::axeY);
    if (currentAngle > PI - PI / 10 || currentAngle < PI / 10)
    {
        float newAngle = 0;
        if (currentAngle > PI - PI / 10.f)
            newAngle = PI - PI / 10;
        if (currentAngle < PI / 10.f)
            newAngle = PI / 10;
        center.Rotate(-(currentAngle - newAngle), axis, anchor);
    }


    recalculateView = true;
}

Vector3D Camera::GetEye()
{
    return eye;
}

Vector3D Camera::GetCenter()
{
    return center;
}

Vector3D Camera::GetDirection()
{
    Vector3D direction(center,eye);
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
