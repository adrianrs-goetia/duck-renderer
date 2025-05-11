#pragma once

#include <math.h>
#include <raylib.h>
#include <stdlib.h>

#include "raymath.h"
#include "typedefs.h"

#define LOG_CAMERA(camera)                                                                                             \
    TraceLog(LOG_INFO, "Camera: [%f, %f, %f]", camera->position.x, camera->position.y, camera->position.z)

static inline Camera3D
init_camera() {
    DisableCursor();
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.f, 10.f, 10.f };
    camera.target = (Vector3){ 0.f, 0.f, 0.f };
    camera.up = g_up;
    camera.fovy = 45.f;
    camera.projection = CAMERA_PERSPECTIVE;
    return camera;
}

static inline void
rotate_camera(Camera3D* camera, float delta) {
    const float springarm_length = Vector3Length(camera->position); // Assume we always look at Vector.ZERO
    LOG_CAMERA(camera);

    const float yaw_angle = (GetMouseDelta().x * delta) / 2.f;
    const float yaw_sin = sin(yaw_angle / 2.0);
    const Quaternion yaw_rotation = QuaternionNormalize((Quaternion){ 0.f, yaw_sin, 0.f, cos(yaw_angle) });

    const float pitch_angle = (GetMouseDelta().y * delta) / 2.f;
    const float pitch_sin = sin(pitch_angle / 2.0);
    const Vector3 right_cross = Vector3CrossProduct(Vector3Normalize(camera->position), g_up);
    const Quaternion pitch_rotation = QuaternionNormalize(
        (Quaternion){ pitch_sin * right_cross.x, 0.f, pitch_sin * right_cross.z, cos(pitch_angle) });

    const Quaternion quat_rot = QuaternionMultiply(yaw_rotation, pitch_rotation);

    const Vector3 camera_yaw_dir = Vector3Normalize(Vector3RotateByQuaternion(camera->position, quat_rot));
    camera->position = Vector3Scale(camera_yaw_dir, springarm_length);
}
