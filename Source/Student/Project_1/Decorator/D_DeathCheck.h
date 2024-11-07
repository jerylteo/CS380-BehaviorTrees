#pragma once
#include "BehaviorNode.h"


class D_DeathCheck : public BaseNode<D_DeathCheck>
{
public:
    D_DeathCheck(float distance = 2.f);

protected:
    float distance;
    Agent* nearestHauntingAgent = nullptr;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    void findNearestHauntingAgent();
};