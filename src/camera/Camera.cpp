#include "camera.h"



    FlyCamera::FlyCamera(Vector3 startPos)
        : yaw(180.0f), pitch(0.0f),
          moveSpeed(10.0f), mouseSensitivity(0.1f)
    {
        camera.position = startPos;
        camera.target   = Vector3{ 0.0f, 2.0f, 0.0f };
        camera.up       = Vector3{ 0.0f, 1.0f, 0.0f };
        camera.fovy     = 60.0f;
        camera.projection = CAMERA_PERSPECTIVE;

        DisableCursor();
    }

    void FlyCamera::update(float deltaTime) {
        Vector2 mouseDelta = GetMouseDelta();

        yaw   += mouseDelta.x * mouseSensitivity;
        pitch -= mouseDelta.y * mouseSensitivity;

        if (pitch > 89.0f)  pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        Vector3 forward;
        forward.x = cosf(DEG2RAD * yaw) * cosf(DEG2RAD * pitch);
        forward.y = sinf(DEG2RAD * pitch);
        forward.z = sinf(DEG2RAD * yaw) * cosf(DEG2RAD * pitch);
        forward = Vector3Normalize(forward);

        camera.target = Vector3Add(camera.position, forward);

        Vector3 flatForward = Vector3Normalize(Vector3{ forward.x, 0.0f, forward.z });
        Vector3 flatRight = Vector3Normalize(Vector3CrossProduct(flatForward, Vector3{ 0.0f, 1.0f, 0.0f }));

        Vector3 move = { 0 };
        if (IsKeyDown(KEY_W)) move = Vector3Add(move, flatForward);
        if (IsKeyDown(KEY_S)) move = Vector3Subtract(move, flatForward);
        if (IsKeyDown(KEY_A)) move = Vector3Subtract(move, flatRight);
        if (IsKeyDown(KEY_D)) move = Vector3Add(move, flatRight);
        if (IsKeyDown(KEY_SPACE)) move.y += 1.0f;
        if (IsKeyDown(KEY_LEFT_SHIFT)) move.y -= 1.0f;

        if (Vector3Length(move) > 0.0f) {
            move = Vector3Normalize(move);
            move = Vector3Scale(move, moveSpeed * deltaTime);
            camera.position = Vector3Add(camera.position, move);
            camera.target = Vector3Add(camera.target, move);
        }
    }

    Camera3D FlyCamera::get() const {
        return camera;
    }

    Vector3 FlyCamera::getPosition() const {
        return camera.position;
    }

    void FlyCamera::setPosition(Vector3 pos) {
        Vector3 delta = Vector3Subtract(pos, camera.position);
        camera.position = pos;
        camera.target = Vector3Add(camera.target, delta);
    }

