#include "camera.h"
#include "entity/Entity.h"

FlyCamera::FlyCamera(Vector3 startPos)
    : mode(CustomCameraMode::FLY), targetEntity(nullptr),
      yaw(270.0f), pitch(15.0f),
      moveSpeed(10.0f), mouseSensitivity(0.1f),
      followDistance(7.0f), followHeight(2.5f), smoothness(10.0f)
{
    camera.position = startPos;
    camera.target   = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up       = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy     = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void FlyCamera::setTargetEntity(const Entity* entity) {
    targetEntity = entity;
}

void FlyCamera::setMode(CustomCameraMode newMode) {
    mode = newMode;
}

void FlyCamera::update(float deltaTime) {
    if (mode == CustomCameraMode::FOLLOW && targetEntity != nullptr) {
        updateFollowMode(deltaTime);
    } else {
        updateFlyMode(deltaTime);
    }
}

void FlyCamera::updateFlyMode(float deltaTime) {
    Vector2 mouseDelta = GetMouseDelta();

    yaw   += mouseDelta.x * mouseSensitivity  * 0.01;
    pitch -= mouseDelta.y * mouseSensitivity  * 0.01;

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

void FlyCamera::updateFollowMode(float deltaTime) {
    Vector3 targetPos = targetEntity->getPosition();

    // ТЕСТ: Убираем проверку на зажатую ПКМ, чтобы камера крутилась ВСЕГДА при движении мыши
    Vector2 mouseDelta = GetMouseDelta();
    yaw   -= mouseDelta.x * mouseSensitivity * 0.01; 
    pitch += mouseDelta.y * mouseSensitivity * 0.01;

    // Зум колесиком
    followDistance -= GetMouseWheelMove() * 0.5f;
    if (followDistance < 3.0f)  followDistance = 3.0f;
    if (followDistance > 15.0f) followDistance = 15.0f;

    // Ограничиваем вертикальный обзор
    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f; 

    // Расчет тригонометрии
    float pitchRad = pitch * DEG2RAD;
    float yawRad = yaw * DEG2RAD;

    Vector3 offset;
    offset.x = followDistance * cosf(pitchRad) * sinf(yawRad);
    offset.y = followDistance * sinf(pitchRad);
    offset.z = followDistance * cosf(pitchRad) * cosf(yawRad);

    Vector3 idealPosition = Vector3Add(targetPos, offset);

    // Сглаживание движения
    camera.position.x = Lerp(camera.position.x, idealPosition.x, smoothness * deltaTime);
    camera.position.y = Lerp(camera.position.y, idealPosition.y, smoothness * deltaTime);
    camera.position.z = Lerp(camera.position.z, idealPosition.z, smoothness * deltaTime);

    
    camera.target = targetPos;
}



Camera3D FlyCamera::get() const { return camera; }
Vector3 FlyCamera::getPosition() const { return camera.position; }
void FlyCamera::setPosition(Vector3 pos) { camera.position = pos; }





