#pragma once
#include "BehaviorNode.h"

class D_BounceCheck : public BaseNode<D_BounceCheck>
{
public:
    D_BounceCheck();
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

};