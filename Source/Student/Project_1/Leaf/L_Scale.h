#pragma once
#include "BehaviorNode.h"

class L_Scale : public BaseNode<L_Scale>
{
public:
    L_Scale();
protected:
    float totalDuration;
    float elapsedTime = 0.0f;
    float scaleFactor = 1.0f;
    float scaleSpeed;
    Vec3 originalScaleFactor;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};