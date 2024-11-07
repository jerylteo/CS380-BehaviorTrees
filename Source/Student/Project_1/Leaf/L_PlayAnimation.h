#pragma once
#include "BehaviorNode.h"

class L_PlayAnimation : public BaseNode<L_PlayAnimation>
{
public:
    L_PlayAnimation();
protected:
    float totalDuration = 0.0f;  // Total duration of the animation sequence
    float elapsedTime = 0.0f;   // Elapsed time within the sequence

    // Parameters for scaling and rotation adjustments
    float scaleFactor = 1.0f; // Current scaling factor
    float scaleSpeed = 0.5f;  // Speed of scaling change
    float rotationSpeed = 90.0f; // Rotation speed in degrees per second

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};