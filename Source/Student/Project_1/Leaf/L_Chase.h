#pragma once
#include "BehaviorNode.h"

class L_Chase : public BaseNode<L_Chase>
{
public:
    L_Chase(float chaseDistance = 0.0f);
protected:

    Agent* targetAgent = nullptr;
    float chaseDistance;;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};