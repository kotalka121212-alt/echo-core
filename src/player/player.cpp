#include "player.h"
#include "voxel/voxel.h"



    Player::Player(Vector3 startPos)
        : position(startPos), speed(5.0f), size(1.0f) {}

    void Player::update(float deltaTime) {
        Vector3 move = { 0.0f, 0.0f, 0.0f };

        if (IsKeyDown(KEY_W)) move.z -= 1.0f;
        if (IsKeyDown(KEY_S)) move.z += 1.0f;
        if (IsKeyDown(KEY_A)) move.x -= 1.0f;
        if (IsKeyDown(KEY_D)) move.x += 1.0f;

        if (Vector3Length(move) > 0.0f) {
            move = Vector3Normalize(move);
            move = Vector3Scale(move, speed * deltaTime);
            position = Vector3Add(position, move);
        }
    }

    void Player::render() const {
        voxel::draw_cube(position, size, BLUE, DARKBLUE);
    }

    Vector3 Player::getPosition() const { return position; }
    void Player::setPosition(Vector3 pos) { position = pos; }

