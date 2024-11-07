#pragma once
#include "BehaviorNode.h"

class D_DistanceCheck : public BaseNode<D_DistanceCheck>
{
public:
    D_DistanceCheck(float distance = 20.0f);

protected:
    float distance;
    Agent* nearestHauntingAgent = nullptr;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    void findNearestHauntingAgent();
};