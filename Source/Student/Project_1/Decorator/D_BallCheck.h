#pragma once
#include "BehaviorNode.h"

class D_BallCheck : public BaseNode<D_BallCheck>
{
public:
    D_BallCheck();

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};