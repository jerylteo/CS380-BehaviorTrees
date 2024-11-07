#pragma once
#include "BehaviorNode.h"

class D_DelayRandom : public BaseNode<D_DelayRandom>
{
public:
    D_DelayRandom();

protected:
    static constexpr float MIN_DELAY = 1.0f; 
    static constexpr float MAX_DELAY = 3.0f;
    float delayDuration; 
    float elapsedTime = 0.0f;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};