#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_MoveToRandomAgent : public BaseNode<L_MoveToRandomAgent>
{
protected:
    Agent* targetAgent = nullptr;
    float offsetDistance = 1.5f;
    float elapsedTime = 0.0f;
    float timeoutDuration = 15.0f;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};