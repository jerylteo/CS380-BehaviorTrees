#pragma once
#include "BehaviorNode.h"

class L_Rotate : public BaseNode<L_Rotate>
{
public:
    L_Rotate();
protected:
    float totalDuration;
    float elapsedTime = 0.0f;
    float rotationSpeed;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};