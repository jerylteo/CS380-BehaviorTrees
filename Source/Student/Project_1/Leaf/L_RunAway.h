#pragma once
#include "BehaviorNode.h"

class L_RunAway : public BaseNode<L_RunAway>
{
public:
    L_RunAway();
protected:
    Vec3 fleeTarget;
    float fleeDistance = 10.0f; // Preset flee distance 

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

};