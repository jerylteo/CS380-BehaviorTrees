#pragma once
#include "BehaviorNode.h"

class L_FallOutOfBounds : public BaseNode<L_FallOutOfBounds>
{
public:
    L_FallOutOfBounds();
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};