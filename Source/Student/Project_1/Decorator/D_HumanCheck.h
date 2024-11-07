#pragma once
#include "BehaviorNode.h"

class D_HumanCheck : public BaseNode<D_HumanCheck>
{
public:
    D_HumanCheck(float distance = 10.0f); 

protected:
    float distance;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    bool isHumanNearby(); // Helper function to check for nearby humans
};