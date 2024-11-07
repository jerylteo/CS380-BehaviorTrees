#pragma once
#include "BehaviorNode.h"

class L_SpawnBall : public BaseNode<L_SpawnBall>
{
public:
    L_SpawnBall();
protected:
    float spawnHeight;
    int bouncesRemaining;
    float fallSpeed;

    virtual void on_enter() override;
};