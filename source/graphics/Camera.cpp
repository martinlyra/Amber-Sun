//
// Created by Martin Lyrå on 2017-12-19.
//

#include "Camera.h"

Matrix4<double> Camera::GetViewProjection() const
{
    return projectionMatrix * orientationMatrix.Inversed();
}

void Camera::SetProjection(float nearPlane, float farPlane, float fov, int width, int height)
{
    projectionMatrix = Matrix4<double>::Perspective(fov, width/height, nearPlane, farPlane);
}
