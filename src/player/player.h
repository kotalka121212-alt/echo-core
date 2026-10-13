#pragma once
#include "entity/Entity.h"

class Player : public Entity {
public:
    Player(Vector3 startPos = { 0.0f, 0.5f, 0.0f });

    void update(float deltaTime) override; 
    void render(const ModelManager& modelMgr) const override;       

private:
    float speed;        
    float size;         
};


