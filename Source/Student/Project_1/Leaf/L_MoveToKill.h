#pragma once
#include "BehaviorNode.h"

class L_MoveToKill : public BaseNode<L_MoveToKill>
{
public:
    L_MoveToKill();
protected:
    Agent* targetAgent = nullptr;
    float killRadius; 

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    void killNearbyAgents();
};