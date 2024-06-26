#ifndef _CAMERA_H
#define _CAMERA_H
#include <cmath>
#include <iostream>

#include "geometry.h"

// pinhole camera
class Camera
{
private:
    Vec3f position;
    Vec3f forward;
    Vec3f right;
    Vec3f up;

    float FOV;
    float focal_length;

public:
    Camera(const Vec3f &position, const Vec3f &forward, float FOV = 0.5f * PI)
        : position(position), forward(forward)
    {
        // by default, right towards y+ axis
        right = normalize(cross(forward, Vec3f(0, 1, 0)));
        up = normalize(cross(right, forward));

        // compute focal length from FOV
        focal_length = 1.0f / std::tan(0.5f * FOV);

        std::cout << "Camera position: " << '(' << position[0] << ',' << position[1] << ',' << position[2] << ')' << std::endl;
        std::cout << "Camera forward: " << '(' << forward[0] << ',' << forward[1] << ',' << forward[2] << ')' << std::endl;
        std::cout << "Camera right direction: " << '(' << right[0] << ',' << right[1] << ',' << right[2] << ')' << std::endl;
        std::cout << "Camera up direction: " << '(' << up[0] << ',' << up[1] << ',' << up[2] << ')' << std::endl;
        std::cout << "Camera focal length: " << focal_length << std::endl;
    }

    // sample ray emitting from the given sensor coordinate
    // NOTE: uv: [-1, -1] x [1, 1], sensor coordinate
    bool sampleRay(const Vec2f &uv, Ray &ray, float &pdf) const
    {
        const Vec3f pinholePos = position + focal_length * forward;
        const Vec3f sensorPos = position + uv[0] * right + uv[1] * up;
        ray = Ray(sensorPos, normalize(pinholePos - sensorPos));
        pdf = 1.0f;
        return true;
    }
};

#endif