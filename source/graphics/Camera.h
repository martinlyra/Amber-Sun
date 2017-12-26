//
// Created by Martin Lyrå on 2017-12-19.
//

#ifndef AMBER_SUN_CAMERA_H
#define AMBER_SUN_CAMERA_H

#include "maths/Matrix4.h"

class Camera {
    void SetProjection(float nearPlane, float farPlane, float fov, int width, int height);

    Matrix4<double> GetViewProjection() const;
private:
    Matrix4<double> projectionMatrix;
    Matrix4<double> orientationMatrix;
};


#endif //AMBER_SUN_CAMERA_H
